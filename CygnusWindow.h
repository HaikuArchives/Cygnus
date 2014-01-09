/*
	
	CygnusWindow.h
	
*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use.
	If you use this source extensively in your project, I humbly
	    request that you credit me in your program.
*/

#ifndef CYGNUS_WINDOW_H
#define CYGNUS_WINDOW_H

#include <DirectWindow.h>

class BSimpleGameSound;

class CygnusView;

// CygnusWindow class
class CygnusWindow : public BDirectWindow  
{
public:
					CygnusWindow(BRect frame);
					~CygnusWindow();
	
	void			SetView(BView *inView);			
		
	virtual void	MessageReceived (BMessage *message);
	virtual	bool	QuitRequested();
	
private:
	CygnusView 			*mView; 
	BSimpleGameSound	*mGameMusic;
};

#endif
