#include "projekt1App.h"
#include "States\DevLogoState.h"
#include "playGame.h"
#include "oglGameVars.h"
#include "SG400KGA1.h"
#include <iostream>
using namespace std;

projekt1App::projekt1App(std::string title, int sizeX, int sizeY, int argc, char **argv)
	: oglApp(title, sizeX, sizeY, argc, argv)
{
	initOpenGL();

	//Load our starting state into the GameStateManager
	GameVars->Instance();
	
	//myStateManager.addGameState<playGame>();
	//myStateManager.addGameState<LogicViewState>();
	myStateManager.addGameState<DevLogoState>();		// 0	
	//myStateManager.addGameState<SG400KGA1>();
}

void projekt1App::initOpenGL()
{
    glClearColor(0,0,0,0);//Define our background color

	//glMatrixMode(GL_PROJECTION); // Changes the current matrix to the projection matrix

	//// Sets up the projection matrix for a perspective transform
	//gluPerspective( 45,		// viewing angle
	//				1.0,	// aspect ratio
	//				10.0,	// near clip
	//				200.0);	// far clip

	//glMatrixMode(GL_MODELVIEW);

}

void projekt1App::updateScene(void)
{
	//std::cout << "project1App - Starting Update" << std::endl;
	myStateManager.Update();
}

void projekt1App::drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	myStateManager.Draw();

	// Not sure why, bottom left of the screen is 0,0
	// Top right of the screen is 800,600
	//glEnable2D();
	//	glBegin(GL_QUADS);
	//		glColor3f(1,0,0);
	//		glVertex3f(100,100,0);

	//		glColor3f(0,100,0);
	//		glVertex3f(700,100,0);

	//		glColor3f(0,0,1);
	//		glVertex3f(700,500,0);

	//		glColor3f(0,0,1);
	//		glVertex3f(100,500,0);
	//	glEnd();
	//glDisable2D();

	glFlush();
	glutSwapBuffers();
}

void projekt1App::processMouse(int x, int y)
{
	myStateManager.processMouse(x, y);
}

void projekt1App::processMouseClick(int button, int state, int x, int y)
{
	myStateManager.processMouseClick(button, state, x, y);
}

void projekt1App::keyboardInput(unsigned char c, int x, int y)
{
	myStateManager.keyboardInput(c, x, y);
}
