/*
	
	Asteroid.h
	
*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use, and is provided without any warranty or support.
	If you use this source extensively in your project, I humbly request that you credit me in your program.
*/

#ifndef Asteroid_H
#define Asteroid_H

class ProtoShip;

class Asteroid
{
public:
			Asteroid(void);
	void	Init();
	void	Animate();
	void	Draw();
	void	Collide(ProtoShip *inShip);
private:
	int		mRot;
	float	mScale;
	float	mDistance;
	int		mDelay;
	int		mSpin;
};

#endif