/*
	
	ProtoShip.h
	
*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use, and is provided without any warranty or support.
	If you use this source extensively in your project, I humbly request that you credit me in your program.
*/

#ifndef ProtoShip_H
#define ProtoShip_H

class BSimpleGameSound;

enum EMoveType
{
	MT_STRAIGHT,
	MT_CLOCKWISE,
	MT_COUNTERCLOCK
};

class ProtoShip
{
public:
			ProtoShip(void);
			~ProtoShip(void);
	void	Draw();
	void	Destroy();
	void	Refuel();
	float	Angle();
	void	Move(EMoveType inMove);
	void	Animate();
private:
	float		mRot;
	float		mFuel;
	float		mFlame;
	int			mExCounter;
	EMoveType	mMovement;
	
	BSimpleGameSound	*mFuelSound;
	BSimpleGameSound	*mExplosionSound;
};

#endif