/*
	
	FuelCrystal.h
	
*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use, and is provided without any warranty or support.
	If you use this source extensively in your project, I humbly request that you credit me in your program.
*/

#ifndef FuelCrystal_H
#define FuelCrystal_H

class ProtoShip;

class FuelCrystal
{
public:
			FuelCrystal(void);
	void	Init();
	void	Animate();
	void	Draw();
	void	Collide(ProtoShip *inShip);
private:
	int		mSpin;
	float	mRot;
	float	mScale;
	float	mDistance;
	int		mDelay;
};

#endif