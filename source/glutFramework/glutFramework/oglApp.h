/////////////////////////////////////////////////////////////
/// oglApp.h
///		This class is designed to be the "framework" for any
/// OpenGL Application. Any time a new OGL Application,
/// such as a game or otherwise, is created you can inherit
/// from this class and override the virtual functions for
/// updating and drawing.
///
/////////////////////////////////////////////////////////////
#ifndef OGLAPP_H
#define OGLAPP_H

#include "oglUtility.h"

class oglApp
{
public:
	oglApp(std::string title, int sizeX, int sizeY, int argc, char **argv);
	~oglApp() {};

	virtual void updateScene(void) {};
	virtual void drawScene(void);
	void glEnable2D();
	void glDisable2D();
	virtual int run();

protected:
	std::string mWindowTitle;

};
#endif