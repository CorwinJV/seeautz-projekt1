#include "projekt1App.h"
#include <iostream>
using namespace std;

projekt1App::projekt1App(std::string title, int sizeX, int sizeY, int argc, char **argv)
	: oglApp(title, sizeX, sizeY, argc, argv), img(NULL)
{
	initOpenGL();

	img = new pixmap("awesome.bmp");
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
    int vPort[4];
    glGetIntegerv(GL_VIEWPORT, vPort);

	img->mX += 1;
	if(img->mX > vPort[2])
		img->mX = 0;

	img->mY += 2;
	if(img->mY > vPort[3])
		img->mY = 0;

	cout << img->mX << endl;
}

void projekt1App::drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(img != NULL)
		img->drawPixMap();

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