#ifndef PROJEKT1APP_H
#define PROJEKT1APP_H

#include "oglApp.h"

class projekt1App : public oglApp
{
public:
	projekt1App(std::string title, int sizeX, int sizeY, int argc, char **argv);
	~projekt1App();
	void updateScene(float elapsed);
	void drawScene();

private:

};

#endif
