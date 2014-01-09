/*
	
	FuelCrystal.cpp
	
*/

#include "FuelCrystal.h"

#include <GLView.h>

#include "ProtoShip.h"
#include <stdlib.h>
#include <math.h>

FuelCrystal::FuelCrystal(void)
{
	Init();
	mSpin = 0;
	mDelay = 20;
	mRot = 30;
}

void
FuelCrystal::Init()
{
	mRot = abs(rand() % 60);
	mScale = 0;
	mDistance = 0;
	mDelay = abs(rand() % 150);
}


void
FuelCrystal::Animate()
{
	mDelay--;
	
	if (mDelay < 0)
	{
		mSpin = (mSpin + 1) % 360;
		mScale += 0.0004;
		mDistance += 0.01;

		if (mDistance > 2.5)
			Init();
	}
}

void
FuelCrystal::Draw()
{
	glRotatef(mRot - 30, 0, 0, 1.0);
	glTranslatef(0, -mDistance, 0);
	glRotatef(mSpin, 0.0, 0.1, 0.0);
	glScalef(mScale, mScale, mScale);
	glEnable(GL_LIGHT3);
	glBegin(GL_TRIANGLES);
		glNormal3f(1,1,1);
		glVertex3f(0, 0, 1);
		glVertex3f(0, 2, 0);
		glVertex3f(1, 0, 0);

		glNormal3f(1,-1,1);
		glVertex3f(0, 0, 1);
		glVertex3f(1, 0, 0);
		glVertex3f(0, -2, 0);

		glNormal3f(-1,-1,1);
		glVertex3f(0, 0, 1);
		glVertex3f(0, -2, 0);
		glVertex3f(-1, 0, 0);

		glNormal3f(-1,1,1);
		glVertex3f(0, 0, 1);
		glVertex3f(-1, 0, 0);
		glVertex3f(0, 2, 0);

		//bottom faces
		glNormal3f(1,1,-1);
		glVertex3f(0, 0, -1);
		glVertex3f(0, 2, 0);
		glVertex3f(1, 0, 0);

		glNormal3f(1,-1,-1);
		glVertex3f(0, 0, -1);
		glVertex3f(1, 0, 0);
		glVertex3f(0, -2, 0);

		glNormal3f(-1,-1,-1);
		glVertex3f(0, 0, -1);
		glVertex3f(0, -2, 0);
		glVertex3f(-1, 0, 0);

		glNormal3f(-1,1,-1);
		glVertex3f(0, 0, -1);
		glVertex3f(-1, 0, 0);
		glVertex3f(0, 2, 0);
	glEnd();	
	glDisable(GL_LIGHT3);
}

void
FuelCrystal::Collide(ProtoShip *inShip)
{
	if ( (mDistance > 1.7) & (mDistance < 1.9))
		if (fabs(inShip->Angle() - mRot) < 4)
		{
			Init();
			inShip->Refuel();
		}
}