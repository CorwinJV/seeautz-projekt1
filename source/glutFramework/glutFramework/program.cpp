//#include "oglApp.h"
#include "projekt1App.h"

// App object
oglApp* newApp = NULL;

// Function prototypes
void doRendering( void );

int main(int argc, char **argv)
{
	newApp = new projekt1App("Awesome", 800, 600, argc, argv);
	glutDisplayFunc(doRendering);
	newApp->run();
}

void doRendering( void )
{
	newApp->updateScene();
	newApp->drawScene();
}