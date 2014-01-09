/*
	
	CygnusView.cpp
	
*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use.
	If you use this source extensively in your project, I humbly
	    request that you credit me in your program.
*/

#include <stdio.h>
#include <stdlib.h>

#include <Message.h>
#include <Region.h>
#include <Alert.h>
#include <Resources.h>
#include <Roster.h>
#include <Application.h>
#include <InterfaceDefs.h>
#include <Bitmap.h>
#include <TranslationUtils.h>

#include "CygnusView.h"
#include "ProtoShip.h"

#define TARGET_FRAME_RATE 30

float white[3] = {1.0,1.0,1.0};
float dimWhite[3] = {0.25,0.25,0.25};
float black[3] = {0.0,0.0,0.0};
float blue[3] = {0.0,0.0,1.0};
float yellow[3] = {1.0,1.0,0.0};
float green[3] = {0.0,1.0,0.0};
float red[3] = {1.0,0.0,0.0};

GLuint ConvertResourceToGLTexture (uint32, int32);

//Constructor for the BView
CygnusView::CygnusView(BRect rect, char *name)
	   	   : BGLView(rect, name, B_FOLLOW_ALL_SIDES, 0, BGL_RGB | BGL_DOUBLE | BGL_DEPTH )
{
	//load the intro screen texture from the app resources
	mTexture = ConvertResourceToGLTexture('PNG ', 1);
	
	mGame = NULL;

	InitGL();

	DrawIntroScreen();
}

CygnusView::~CygnusView(void)
{
	Stop();
	snooze( 500000 );  //wait for drawing thread to finish... this is cheesy, I know
}


void CygnusView::InitGL()
{
	//Start using OpenGL
	LockGL();

	// Clear to black
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	
	// Set up the depth buffer
	glClearDepth( 1.0 );
	glDepthFunc( GL_LESS );
	glEnable( GL_DEPTH_TEST );
	
	// Set up perspective view
	glShadeModel( GL_SMOOTH );
	glMatrixMode( GL_MODELVIEW );
	
	//set up all the light sources
	float position[] = {1.0, 1.0, 1.0, 0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT1, GL_AMBIENT, dimWhite);
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT2, GL_AMBIENT, red);
	glLightfv(GL_LIGHT3, GL_AMBIENT, green);
	glEnable(GL_LIGHTING);
	
	//done using OpenGL
	UnlockGL();

}

void CygnusView::DrawIntroScreen()
{
	//clear the view
	LockGL();
	glLoadIdentity();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//draw the intro screen texture onto the view
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
		glTexCoord2f( 0.0, 1.0 );
		glVertex2f(-1, 1);
		glTexCoord2f( 0.0, 0.0 );
		glVertex2f(-1, -1);
		glTexCoord2f( 1.0, 0.0 );
		glVertex2f(1, -1);
		glTexCoord2f( 1.0, 1.0 );
		glVertex2f(1, 1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	
	//finish using OpenGL
	glFlush();
	UnlockGL();
	SwapBuffers();
}

void CygnusView::Start()
{
	//spawn animation & drawing threads
	mGameRunning = true;
	thread_id theThread = spawn_thread( render_thread, "Object render thread", B_DISPLAY_PRIORITY-1, this );
	resume_thread( theThread );	
}

void CygnusView::Stop()
{
	mGameRunning = false;
}

int32
CygnusView::render_thread( void *data )
{
	((CygnusView *)data)->Run();

	return 0;
}

void CygnusView::Run(void)
{
	mGame = new CygnusGame();

	//rendering loop
	int64 theSleepTime = 1000000 / TARGET_FRAME_RATE;
	int64 theTimeForNextFrame;
	while ( mGameRunning )
	{
		theTimeForNextFrame = system_time() + theSleepTime;
		mGame->Animate();
		LockGL();
		mGame->Render();
		UnlockGL();
		SwapBuffers();
		snooze( theTimeForNextFrame - system_time());
	}

	//clean up
	delete mGame;
	mGame = NULL;
	
	DrawIntroScreen();
}


void CygnusView::KeyDown(const char *bytes, int32 numBytes)
{
	if (mGameRunning && mGame != NULL)
	{	
		if (bytes[0] == B_RIGHT_ARROW)
			mGame->Move(MT_COUNTERCLOCK);
		else if (bytes[0] == B_LEFT_ARROW)
			mGame->Move(MT_CLOCKWISE);
		else
			mGame->Move(MT_STRAIGHT);
	}
	else
		Window()->PostMessage(CMD_START_GAME);
}


void CygnusView::KeyUp(const char *bytes, int32 numBytes)
{
	if (mGame != NULL)
		mGame->Move(MT_STRAIGHT);
}


GLuint ConvertResourceToGLTexture( uint32 theType, int32 theIndex )
{
	GLuint	theTexture = 0;

	BBitmap *theBitmap = BTranslationUtils::GetBitmap( theType, theIndex );

	if (theBitmap != NULL) {

		theBitmap->Lock();
	
		int32 bpr = theBitmap->BytesPerRow();
	
		char *top = static_cast<char *>( theBitmap->Bits() );
		char *bottom = top + theBitmap->Bounds().IntegerHeight() * bpr;
	
		char *tmp_bytes = new char[bpr];
		while( top < bottom )
		{
			// Save a line into the temp buffer.
			memcpy( tmp_bytes, bottom, bpr );
	
			// BBitmap and OpenGL don't
			// even agree on the order of bytes within an RGBA colour.  :-(
			rgb_color *b = (rgb_color *)( bottom );
			rgb_color *t = (rgb_color *)( top );
			for( int i = 0; i < ( bpr / 4 ); i++ ) {
				b->red = t->blue;
				b->green = t->green;
				b->blue = t->red;
				b->alpha = t->alpha;
				b++, t++;
			}
			t = (rgb_color *)( top );
			b = (rgb_color *)( tmp_bytes );
			for( int i = 0; i < ( bpr / 4 ); i++ ) {
				t->red = b->blue;
				t->green = b->green;
				t->blue = b->red;
				t->alpha = b->alpha;
				b++, t++;
			}
	
			bottom -= bpr;
			top += bpr;
		}
	
		theBitmap->Unlock();
		
		glGenTextures( 1, &theTexture );
		
		glBindTexture( GL_TEXTURE_2D, theTexture ); //select the texture to work on
	
		if( theBitmap->ColorSpace() == B_RGBA32 )
		{
			glTexImage2D( GL_TEXTURE_2D, 0, 
						  4, 
						  theBitmap->Bounds().IntegerWidth() + 1,
						  theBitmap->Bounds().IntegerHeight() + 1,
						  0, GL_RGBA, GL_UNSIGNED_BYTE,
						  theBitmap->Bits() );
		}
		else 
		{
			glTexImage2D( GL_TEXTURE_2D, 0, 
						  3, 
						  theBitmap->Bounds().IntegerWidth() + 1,
						  theBitmap->Bounds().IntegerHeight() + 1,
						  0, GL_RGBA, GL_UNSIGNED_BYTE,
						  theBitmap->Bits() );
		}
		
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

		delete theBitmap;
	}

	return theTexture;
}