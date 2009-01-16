/////////////////////////////////////////////////////////////
/// oglApp.cpp
///		Here's the definition for the OGL Framework.
/// Many of these functions can be overriden but should work
/// well with their default implementations.
///
/////////////////////////////////////////////////////////////

#include "oglApp.h"

//===================================================
// oglApp
//	Class constructor. Sets certain local variables 
// required for the creation of a window and 
// initialization of GLUT
// 
//===================================================
oglApp::oglApp(std::string title, int sizeX, int sizeY, int argc, char **argv)
{
	glutInitWindowSize(sizeX, sizeY);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow(title.c_str());
	// Unfortunately the glut callback registration stuff is tricky
	// and has to be done from program.cpp
}

int oglApp::run()
{
	glutMainLoop();
	return 0;
}

void oglApp::drawScene(void)
{
	// Clear the screen to black here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}