/*
	
	ProtoShip.cpp
	
*/

#include "ProtoShip.h"

#include <stdio.h>
#include <Application.h>
#include <Alert.h>
#include <GLView.h>
#include <Resources.h>
#include <SimpleGameSound.h>
#include <game/GameSoundDefs.h>

ProtoShip::ProtoShip(void)
{
	mFuelSound = NULL;
	mExplosionSound = NULL;
	mExCounter = 0;
	mRot = 30;
	mFlame = 0;
	Refuel();
	mMovement = MT_STRAIGHT;



	//create a resource object from the executable file - easy way
	BResources *res = be_app->AppResources();
	
	//set the format of the raw data in the resource file
	gs_audio_format format;
	format.frame_rate = 22050;
	format.channel_count = 1;
	format.format = gs_audio_format::B_GS_U8; //8bit
	format.byte_order = 0;
	format.buffer_size = 0;
	
    //load audio data from resource
    size_t theSize = 0;
    const void *theData = NULL;
	
	theData = res->LoadResource(B_RAW_TYPE, 1, &theSize);
	if (theData != NULL)
		mFuelSound = new BSimpleGameSound(theData, theSize, &format);

	theData = res->LoadResource(B_RAW_TYPE, 2, &theSize);
	if (theData != NULL)
		mExplosionSound = new BSimpleGameSound(theData, theSize, &format);

}

ProtoShip::~ProtoShip(void)
{
	mFuelSound->StopPlaying();
	delete mFuelSound;
	mExplosionSound->StopPlaying();
	delete mExplosionSound;
}

void
ProtoShip::Draw()
{
	glPushMatrix();
	
	//rotate & move our origin so we can draw the ship in it's location
	glRotatef(mRot - 30, 0, 0, 1.0);
	glTranslatef(0, -1.8, 0);
	glScalef(0.08, 0.08, 1.0);

	//if we were hit by an asteroid, turn the red light on
	if (mExCounter > 0)
		glEnable(GL_LIGHT2);

	//draw the ship's geometry
	glBegin(GL_TRIANGLES);
		glNormal3f(1,1,1);
		glVertex3f(0, 0, 1);
		glVertex3f(0, 1, 0);
		glVertex3f(1, -0.5, 0);

		glNormal3f(-1,1,1);
		glVertex3f(0, 0, 1);
		glVertex3f(-1, -0.5, 0);
		glVertex3f(0, 1, 0);
	glEnd();	

	glDisable(GL_LIGHT2);

	//draw animated "flames" from the back
	mFlame += 0.1;
	if (mFlame > 1.0) mFlame = 0.0;
	glDisable(GL_LIGHTING);
	glBegin(GL_TRIANGLES);
		glColor3f(mFlame, 0, 0);
		glVertex3f(0, -0.7, 0);
		glVertex3f(-0.3, -0.3, 0);
		glVertex3f(0.3, -0.3, 0);
	glEnd();
	glEnable(GL_LIGHTING);
	
	//reset OpenGL location so we can draw other stuff
	glPopMatrix();
	
	//draw fuel indicator at bottom of screen
	glDisable(GL_LIGHTING);
	glTranslatef(-0.9, -1.9, 0);
	glBegin(GL_QUADS);
		glColor4f(0, 1, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, -0.01, 0);
		glVertex3f(mFuel * 1.8, -0.01, 0);
		glVertex3f(mFuel * 1.8, 0, 0);
	glEnd();
	glEnable(GL_LIGHTING);
		
}

void
ProtoShip::Destroy()
{
	//if we've already been hit, then we are protected for a few seconds
	if (mExCounter == 0)
	{
		mFuel -= 0.4;
		mExCounter = 90;
		if (mExplosionSound != NULL)
			mExplosionSound->StartPlaying();
	}
}

void
ProtoShip::Refuel()
{
	if (mExCounter == 0)
	{
		mFuel = 1.0;
		if (mFuelSound != NULL)
			mFuelSound->StartPlaying();
	}
}

float
ProtoShip::Angle()
{
	return mRot;
}

void
ProtoShip::Move(EMoveType inMove)
{
	mMovement = inMove;
}


void
ProtoShip::Animate()
{
	mFuel -= 0.001;
	
	if (mFuel < 0)
		be_app->WindowAt(0)->PostMessage('egam');

	if (mExCounter > 0)
		mExCounter--;

	if (mMovement == MT_CLOCKWISE)
		mRot -= 1;
	else if (mMovement == MT_COUNTERCLOCK)
		mRot += 1;
	
	if (mRot < 0)
		mRot = 0;
		
	if (mRot > 60)
		mRot = 60;
}