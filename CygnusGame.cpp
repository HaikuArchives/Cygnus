/*
	
	CygnusGame
	
*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use.
	If you use this source extensively in your project, I humbly
	    request that you credit me in your program.
*/

#include <GL/gl.h>

#include "CygnusGame.h"

CygnusGame::CygnusGame()
{
	//initialize game objects
	mShip = new ProtoShip();
	mFuelCrystal = new FuelCrystal();
	for (int i =0; i < NUM_ASTEROIDS; i++)
		mAsteroids[i] = new Asteroid();
	for (int i =0; i < NUM_STARS; i++)
		mStars[i] = new Star();
}


CygnusGame::~CygnusGame(void)
{
	//delete game objects
	delete mShip;
	delete mFuelCrystal;
	for (int i =0; i < NUM_ASTEROIDS; i++)
		delete mAsteroids[i];
	for (int i =0; i < NUM_STARS; i++)
		delete mStars[i];
}


void CygnusGame::Animate()
{
	mFuelCrystal->Animate();

	for (int i= 0; i < NUM_STARS; i++)
		mStars[i]->Animate();
	
	for (int i= 0; i < NUM_ASTEROIDS; i++)
	{
		mAsteroids[i]->Animate();
		mAsteroids[i]->Collide(mShip);
	}
	
	mFuelCrystal->Collide(mShip);

	mShip->Animate();	
}


void CygnusGame::Render()
{
	glLoadIdentity();
	glTranslatef(0, 1, 0);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glPushMatrix();
	mShip->Draw();
	glPopMatrix();
	
	for (int i= 0; i < NUM_STARS; i++)
	{
		glPushMatrix();
		mStars[i]->Draw();
		glPopMatrix();
	}
	
	for (int i= 0; i < NUM_ASTEROIDS; i++)
	{
		glPushMatrix();
		mAsteroids[i]->Draw();
		glPopMatrix();
	}
	
	glPushMatrix();
	mFuelCrystal->Draw();
	glPopMatrix();
}

void CygnusGame::Move( EMoveType inMove )
{
	mShip->Move(inMove);
}