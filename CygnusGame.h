/*
	
	CygnusGame.h
	
*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use.
	If you use this source extensively in your project, I humbly
	    request that you credit me in your program.
*/

#ifndef CYGNUS_GAME_H
#define CYGNUS_GAME_H

#include "ProtoShip.h"
#include "Star.h"
#include "Asteroid.h"
#include "FuelCrystal.h"

#define NUM_STARS 50  
#define NUM_ASTEROIDS 10  

class CygnusGame 
{
public:
				CygnusGame(); 
				~CygnusGame();
			
	void			Animate();
	void			Render();
	void			Move( EMoveType inMove );
	
private:
	//Game objects
	ProtoShip		*mShip;
	FuelCrystal		*mFuelCrystal;
	Asteroid		*mAsteroids[NUM_ASTEROIDS];
	Star			*mStars[NUM_STARS];	
};

#endif
