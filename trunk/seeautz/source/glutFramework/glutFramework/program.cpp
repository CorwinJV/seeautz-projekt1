//#include "oglApp.h"
#include "projekt1App.h"

// App object
oglApp* newApp = NULL;

// Function prototypes
void doRendering( void );
void processMouse( int, int ) ;
void processMouseClick(int button, int state, int x, int y);

// mouse stuff

int main(int argc, char **argv)
{

	newApp = new projekt1App("Awesome", 1024, 768, argc, argv);
	glutDisplayFunc(doRendering);
	glutIdleFunc(doRendering);
	glutPassiveMotionFunc(processMouse);
	glutMotionFunc(processMouse);
	glutMouseFunc(processMouseClick);
	newApp->run();
}

void doRendering( void )
{
	newApp->updateScene();
	newApp->drawScene();
}

void processMouse(int x, int y)
{
	newApp->processMouse(x, y);
}

void processMouseClick(int button, int state, int x, int y)
{
	newApp->processMouseClick(button, state, x, y);
}
