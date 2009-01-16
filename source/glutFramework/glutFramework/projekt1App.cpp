#include "projekt1App.h"

projekt1App::projekt1App(std::string title, int sizeX, int sizeY, int argc, char **argv)
	: oglApp(title, sizeX, sizeY, argc, argv)
{
	initOpenGL();
}

void projekt1App::initOpenGL()
{
    glClearColor(0,0,0,0);//Define our background color

	glMatrixMode(GL_PROJECTION); // Changes the current matrix to the projection matrix

	// Sets up the projection matrix for a perspective transform
	gluPerspective( 45,		// viewing angle
					1.0,	// aspect ratio
					10.0,	// near clip
					200.0);	// far clip

	glMatrixMode(GL_MODELVIEW);

}

void projekt1App::updateScene(void)
{

}

void projekt1App::drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
		glTranslatef(0,0,-100);
		glBegin(GL_QUADS);
			glColor3f(1,0,0);
			glVertex3f(-30,-30,0);

			glColor3f(0,1,0);
			glVertex3f(30,-30,0);

			glColor3f(0,0,1);
			glVertex3f(30,30,0);

			glColor3f(0,0,1);
			glVertex3f(-30,30,0);
		glEnd();
	glPopMatrix();
	glutSwapBuffers();
}