/*
	
	Star.cpp
	
*/

#include "Star.h"

#include <GLView.h>
#include <stdlib.h>

Star::Star(void)
{
	Init();
	mDistance = abs(rand() % 120);
	mDistance /= 40.0;
	mDelay = 0;
}

void
Star::Init()
{
	mRot = abs(rand() % 160);
	mScale = 0;
	mDistance = 0;
	mDelay = abs(rand() % 600);
}


void
Star::Animate()
{
	mDelay--;
	
	if (mDelay < 0)
	{
		mScale += 0.00025;
		mDistance += 0.005;

		if (mDistance > 3.0)
			Init();
	}
}

void
Star::Draw()
{
	glRotatef(mRot - 80, 0, 0, 1.0);
	//glScalef(mScale, mScale, 1.0);
	glTranslatef(0, -mDistance, 0);
	
	glDisable(GL_LIGHTING);
	glBegin(GL_POINTS);
		glColor4f(1, 1, 1, 1);
		glVertex3f(0, 0, 0);
	glEnd();
	glEnable(GL_LIGHTING);	
}