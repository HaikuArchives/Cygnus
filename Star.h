/*
	
	Star.h
	
*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use, and is provided without any warranty or support.
	If you use this source extensively in your project, I humbly request that you credit me in your program.
*/

#ifndef Star_H
#define Star_H

class Star
{
public:
			Star(void);
	void	Init();
	void	Animate();
	void	Draw();
private:
	float	mRot;
	float	mScale;
	float	mDistance;
	int		mDelay;
};

#endif