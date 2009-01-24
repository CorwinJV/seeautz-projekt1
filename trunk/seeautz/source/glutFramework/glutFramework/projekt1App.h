#ifndef PROJEKT1APP_H
#define PROJEKT1APP_H

#include "oglApp.h"
#include "GameStateManager.h"
#include "pixmap.h"

class projekt1App : public oglApp
{
public:
	projekt1App(std::string title, int sizeX, int sizeY, int argc, char **argv);
	~projekt1App();
	void updateScene(void);
	void drawScene(void);

private:
	void initOpenGL();
	
private:
	GameStateManager myStateManager;
};

#endif
