/*
	
	Asteroid.cpp
	
*/

#include "Asteroid.h"

#include <GLView.h>
#include <stdlib.h>

#include "ProtoShip.h"

Asteroid::Asteroid(void)
{
	Init();
	mSpin = abs(rand() % 360);
	mDelay = abs(rand() % 400) + 100;
}

void
Asteroid::Init()
{
	mRot = abs(rand() % 60);
	mScale = 0;
	mDistance = 0;
	mDelay = abs(rand() % 500);
}


void
Asteroid::Animate()
{
	mDelay--;
	
	if (mDelay < 0)
	{
		mSpin = (mSpin + 4) % 360;
		mScale += 0.0005;
		mDistance += 0.01;

		if (mDistance > 2.5)
			Init();
	}
}

void
Asteroid::Draw()
{
	glRotatef(mRot - 30, 0, 0, 1.0);
	glTranslatef(0, -mDistance, 0);
	glRotatef(mSpin, 0.01, 0.005, 0.01);
	glScalef(mScale, mScale, mScale);
	glBegin(GL_TRIANGLES);
		glNormal3f(0,1,1);
		glVertex3f(0, 0, 1);
		glVertex3f(-1, 1, 0);
		glVertex3f(1, 1, 0);

		glNormal3f(1,0,1);
		glVertex3f(0, 0, 1);
		glVertex3f(1, 1, 0);
		glVertex3f(1, -1, 0);

		glNormal3f(0,-1,1);
		glVertex3f(0, 0, 1);
		glVertex3f(1, -1, 0);
		glVertex3f(-1, -1, 0);

		glNormal3f(-1,0,1);
		glVertex3f(0, 0, 1);
		glVertex3f(-1, -1, 0);
		glVertex3f(-1, 1, 0);

		//bottom half of asteroid...
		glNormal3f(0,1,-1);
		glVertex3f(0, 0, -1);
		glVertex3f(-1, 1, 0);
		glVertex3f(1, 1, 0);

		glNormal3f(1,0,-1);
		glVertex3f(0, 0, -1);
		glVertex3f(1, 1, 0);
		glVertex3f(1, -1, 0);

		glNormal3f(0,-1,-1);
		glVertex3f(0, 0, -1);
		glVertex3f(1, -1, 0);
		glVertex3f(-1, -1, 0);

		glNormal3f(-1,0,-1);
		glVertex3f(0, 0, -1);
		glVertex3f(-1, -1, 0);
		glVertex3f(-1, 1, 0);
	glEnd();	
}

void
Asteroid::Collide(ProtoShip *inShip)
{
	if ( (mDistance > 1.7) & (mDistance < 1.9))
		if (fabs(inShip->Angle() - mRot) < 4)
			inShip->Destroy();
}