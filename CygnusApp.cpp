/*
	
	Cygnus.cpp
	
*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use.
	If you use this source extensively in your project, I humbly
	    request that you credit me in your program.
*/


#include "CygnusWindow.h"
#include "CygnusApp.h"
#include <Alert.h>

int main(int, char**)
{	
	// Create an application instance
	CygnusApplication theApplication;
	
	// Run the application looper
	theApplication.Run();
	
	return(0);
}

CygnusApplication::CygnusApplication()
		  		  : BApplication("application/x-vnd.Be-BTL.Cygnus")
{
	mWindow = new CygnusWindow(BRect(200, 200, 455, 455));
	mWindow->Show();
}

void CygnusApplication::AboutRequested(void)
{
	(new BAlert("", "Cygnus v1.0 by Ben Loftis", "Cool"))->Go();
}
