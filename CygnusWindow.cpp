/*

	CygnusWindow.cpp
	
*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use.
	If you use this source extensively in your project, I humbly
	    request that you credit me in your program.
*/

#include <Application.h>
#include <Resources.h>
#include <SimpleGameSound.h>
#include <game/GameSoundDefs.h>

#include "CygnusWindow.h"
#include "CygnusView.h"

CygnusWindow::CygnusWindow(BRect frame)
				: BDirectWindow(frame, "Cygnus X-1", B_TITLED_WINDOW, B_NOT_RESIZABLE)
{
	//add the OpenGL game view to the window
	mView = new CygnusView( Bounds(), NULL );
	AddChild(mView);
	mView->MakeFocus();

	//create a resource object from our app, where we have stored some audio files
	BResources *res = be_app->AppResources();
	
	//set the format of the raw data in the resource file
	gs_audio_format format;
	format.frame_rate = 22050;
	format.channel_count = 1;
	format.format = gs_audio_format::B_GS_U8;
	format.byte_order = 0;
	format.buffer_size = 0;
	
    //load audio data from the app resources
    size_t theSize = 0;
	const void *theData = NULL;
	theData = res->LoadResource(B_RAW_TYPE, 3, &theSize);
	mGameMusic = new BSimpleGameSound(theData, theSize, &format);
	mGameMusic->SetIsLooping(true);
	mGameMusic->SetGain(0.5, 0);
	mGameMusic->StartPlaying();
}

CygnusWindow::~CygnusWindow(void)
{
	mView->Stop();
	mGameMusic->StopPlaying();
	delete mGameMusic;
}

void CygnusWindow::MessageReceived(BMessage *message)
{
	switch ( message->what )
	{
		case CMD_START_GAME:
			mView->Start();
		break;
		
		case CMD_END_GAME:
			mView->Stop();
		break;
		
		default:
			BWindow::MessageReceived(message);
		break;
	}
}

bool CygnusWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return(true);
}