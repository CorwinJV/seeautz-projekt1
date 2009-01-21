#include "projekt1App.h"
#include "TestState.h"
#include "TestSTate2.h"

#include <iostream>
using namespace std;

projekt1App::projekt1App(std::string title, int sizeX, int sizeY, int argc, char **argv)
	: oglApp(title, sizeX, sizeY, argc, argv)
{
	initOpenGL();

	// Load our starting state into the GameStateManager
	myStateManager.addGameState<TestState>();		// 0
	myStateManager.addGameState<TestState2>();		// 1	gets deleted
	myStateManager.addGameState<TestState2>();		// 2	stays active
	myStateManager.addGameState<TestState2>();		// 3	gets set passive
	myStateManager.addGameState<TestState2>();		// 4	gets set hidden
	//myStateManager.addGameState<TestState2>();		// 5
	//myStateManager.addGameState<TestState2>();		// 6
	//myStateManager.addGameState<TestState2>();		// 7

	myStateManager.removeGameStateID(1);

	myStateManager.setState(3, Passive);
	myStateManager.setState(4, Hidden);
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