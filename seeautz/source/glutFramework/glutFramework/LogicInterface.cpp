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
	menuBar->loadImage("blankmenu.png", 1024, 768);

	logicBank = GameVars->getAllLogicBlocks();
	executionList.push_back(GameVars->getPlaceInstructionBlock());
	draggedBlock = NULL;

	bottomBarXOffset = 0;
	sideBarYOffset = 0;

	isMouseDragging = false;
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
	std::vector<logicBlock*>::iterator itr = executionList.begin();

	//=============================================
	// Robot Instructios (sidebar)
	itr = executionList.begin();
	for(; itr != executionList.end(); itr++)
	{
		int i = std::distance(executionList.begin(), itr);
		(*itr)->blockTexture->mX = sideBarX + 5;
		(*itr)->blockTexture->mY = sideBarYOffset + ((sideBarY + 30) + (i * 140) + (i * instructionSpacing));
		(*itr)->blockTexture->drawImage(140, 140);
	}

	//=============================================
	// LogicBank Instructions (bottom bar)
	itr = logicBank->begin();
	for(; itr != logicBank->end(); itr++)
	{
		int i = std::distance(logicBank->begin(), itr);
		(*itr)->blockTexture->mY = bottomBarY + 5;
		(*itr)->blockTexture->mX = bottomBarXOffset + ((bottomBarX + 30) + (i * 140) + (i * instructionSpacing));
		(*itr)->blockTexture->drawImage(140, 140);
	}

	if(draggedBlock != NULL)
	{
		draggedBlock->blockTexture->drawImage(140, 140);
	}
}

void LogicInterface::processMouse(int x, int y)
{
	if(isMouseDragging == true
		&& draggedBlock != NULL)
	{
		draggedBlock->blockTexture->mX = x - 70;
		draggedBlock->blockTexture->mY = y - 70;
	}
}

void LogicInterface::processMouseClick(int button, int state, int x, int y)
{
	// Click & Drag
	// When the user clicks, we want them to be able to select an
	// instruction to drag over into the robot's instruction list.
	// Loop through the list of bank instructions and check x/y
	if(button == GLUT_LEFT
		&& state == GLUT_DOWN)
	{
		// If the left mouse button is down
		std::vector<logicBlock*>::iterator itr = logicBank->begin();
		for(; itr != logicBank->end(); itr++)
		{
			if((*itr)->checkInBounds(x, y, 140, 140))
			{
				draggedBlock = new logicBlock(*(*itr));
				isMouseDragging = true;
			}
		}
	}


	if(button == GLUT_LEFT
		&& state == GLUT_DOWN)
	{
		if(isMouseDragging == true
			&& draggedBlock != NULL)
		{
			if(GameVars->getPlaceInstructionBlock()->checkInBounds(x, y, 140, 140))
			{
				executionList.pop_back();
				executionList.push_back(new logicBlock(*(draggedBlock)));
				executionList.push_back(GameVars->getPlaceInstructionBlock());
				delete draggedBlock;
				draggedBlock = NULL;
			}
		}
	}
}


