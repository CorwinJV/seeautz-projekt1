#include "LogicInterface.h"
#define sideBarW 150
#define sideBarH 618
#define sideBarX 874
#define sideBarY 0

#define bottomBarW 1024 + 13
#define bottomBarH 150
#define bottomBarX -10
#define bottomBarY 618

#define instructionSpacing 30

LogicInterface::LogicInterface()
{
	menuBar = new oglTexture2D();
	bottomBarXOffset = 0;
	menuBar->loadImage("blankmenu.png", 1024, 768);
	logicBank = GameVars->Instance()->getAllLogicBlocks();
}

void LogicInterface::Draw()
{
	//=============================================
	// Menu Bars
	menuBar->mX = sideBarX;
	menuBar->mY = sideBarY;
	menuBar->drawImage(sideBarW, sideBarH);

	menuBar->mX = bottomBarX;
	menuBar->mY = bottomBarY;
	menuBar->drawImage(bottomBarW, bottomBarH);
	
	//=============================================
	// Instructions
	std::vector<logicBlock*>::iterator itr = logicBank->begin();
	for(; itr != logicBank->end(); itr++)
	{
		int i = std::distance(logicBank->begin(), itr);
		(*itr)->blockTexture->mY = bottomBarY + 5;
		(*itr)->blockTexture->mX = bottomBarXOffset + ((bottomBarX + 30) + (i * 140) + (i * instructionSpacing));
		(*itr)->blockTexture->drawImage(140, 140);
	}
}

void LogicInterface::processMouse(int x, int y)
{
	bottomBarXOffset = x;
}

void LogicInterface::processMouseClick(int button, int state, int x, int y)
{
	// When the user clicks, wee. 
}

