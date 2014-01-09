/*
	
	Cygnus.h

*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use.
	If you use this source extensively in your project, I humbly
	    request that you credit me in your program.
*/

#ifndef CYGNUS_H
#define CYGNUS_H

#include <Application.h>

class CygnusApplication : public BApplication 
{
public:
				CygnusApplication();
private:
	BWindow		*mWindow;
    void        AboutRequested(void);
};

#endif
