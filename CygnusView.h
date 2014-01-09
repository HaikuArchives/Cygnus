/*
	
	Cygnus.h
	
*/
/*
	Originally written by Ben Loftis.
	This source code is available freely for any use.
	If you use this source extensively in your project, I humbly
	    request that you credit me in your program.
*/

#ifndef CYGNUS_VIEW_H
#define CYGNUS_VIEW_H

#include <GLView.h>
#include <Locker.h>

#include "CygnusGame.h"

#define CMD_END_GAME 'egam'
#define CMD_START_GAME 'sgam'

class CygnusView : public BGLView 
{
public:
				CygnusView(BRect frame, char *name); 
				~CygnusView(void);
			
	void			Start();
	void			Stop();

	virtual void	KeyDown(const char *bytes, int32 numBytes);
	virtual void	KeyUp(const char *bytes, int32 numBytes);

private:
	CygnusGame		*mGame;
	BLocker			mRenderLock;
	bool			mGameRunning;
	
	void			Run();
	void			InitGL();
	void			DrawIntroScreen();
	
	GLuint			mTexture;
	
	static int32	render_thread( void *data );
};

#endif
