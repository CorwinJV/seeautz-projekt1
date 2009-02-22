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
:myMenu(NULL), isButtonBeingClicked(false)
{
	//=============================================
	// Menu buttons (scrolling the instruction lists)
	myMenu = new MenuSys(0, 0, "", None);
	myMenu->addButton("arrow_up.png", "arrow_up.png", "arrow_up.png", BE::CreateFunctionPointer0R(this, &LogicInterface::UpArrowButtonClick));
	myMenu->setLastButtonDimensions(sideBarW, 25);
	myMenu->setLastButtonPosition(sideBarX, 0);

	myMenu->addButton("arrow_down.png", "arrow_down.png", "arrow_down.png", BE::CreateFunctionPointer0R(this, &LogicInterface::DownArrowButtonClick));
	myMenu->setLastButtonDimensions(sideBarW, 25);
	myMenu->setLastButtonPosition(sideBarX, bottomBarY-25);

	myMenu->addButton("arrow_left.png", "arrow_left.png", "arrow_left.png", BE::CreateFunctionPointer0R(this, &LogicInterface::LeftArrowButtonClick));
	myMenu->setLastButtonDimensions(25, bottomBarH);
	myMenu->setLastButtonPosition(0, bottomBarY);

	myMenu->addButton("arrow_right.png", "arrow_right.png", "arrow_right.png", BE::CreateFunctionPointer0R(this, &LogicInterface::RightArrowButtonClick));
	myMenu->setLastButtonDimensions(25, bottomBarH);
	myMenu->setLastButtonPosition(bottomBarW-40, bottomBarY);

	myMenu->addButton("buttons\\execute.png", "buttons\\execute.png", "buttons\\execute.png", BE::CreateFunctionPointer0R(this, &LogicInterface::ExecuteButtonClick));
	myMenu->setLastButtonDimensions(100, 50);
	myMenu->setLastButtonPosition(sideBarX-100, bottomBarY-50);

	myMenu->addButton("buttons\\abort.png", "buttons\\abort.png", "buttons\\abort.png", BE::CreateFunctionPointer0R(this, &LogicInterface::AbortButtonClick));
	myMenu->setLastButtonDimensions(100, 50);
	myMenu->setLastButtonPosition(sideBarX-205, bottomBarY-50);


	//=============================================
	// All other initialization
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
	std::vector<logicBlock*>::iterator itr = executionList.begin();

	//=============================================
	// Menu Bars
	menuBar->mX = sideBarX;
	menuBar->mY = sideBarY;
	menuBar->drawImage(sideBarW, sideBarH);

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
	// Menu Bars
	menuBar->mX = bottomBarX;
	menuBar->mY = bottomBarY;
	menuBar->drawImage(bottomBarW, bottomBarH);

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

	//=============================================
	// Dragged Block
	if(draggedBlock != NULL)
	{
		draggedBlock->blockTexture->drawImage(140, 140);
	}

	//=============================================
	// Menu Buttons (For scrolling and shizz)
	myMenu->Draw();
}

void LogicInterface::processMouse(int x, int y)
{
	// Menu buttons
	myMenu->processMouse(x, y);

	if(isMouseDragging == true
		&& draggedBlock != NULL)
	{
		draggedBlock->blockTexture->mX = x - 70;
		draggedBlock->blockTexture->mY = y - 70;
	}
}

void LogicInterface::processMouseClick(int button, int state, int x, int y)
{
	// Menu buttons
	myMenu->processMouseClick(button, state, x, y);

	// Click & Drag
	// When the user clicks, we want them to be able to select an
	// instruction to drag over into the robot's instruction list.
	// Loop through the list of bank instructions and check x/y
	if(button == GLUT_LEFT
		&& state == GLUT_DOWN)
	{
		if(isButtonBeingClicked == false)
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
	}

	if(button == GLUT_LEFT
		&& state == GLUT_UP)
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

			delete draggedBlock;
			draggedBlock = NULL;
			isMouseDragging = false;

			// You just dropped a new element into the list,
			// if the list has more than what can be displayed
			// then scroll down to the bottom of the list
			int i = executionList.size();
			if(i > 3)
			{
				int overallHeight = (sideBarY + 30) + (i * 140) + (i * instructionSpacing);
				sideBarYOffset = 768 - 150 - overallHeight;
			}
		}
	}

	isButtonBeingClicked = false;
}

void LogicInterface::SetExecuteHandler(CFunctionPointer1R<bool, std::vector<logicBlock*>> clickHandler)
{
	mExecuteHandler = clickHandler;
}

void LogicInterface::SetAbortHandler(CFunctionPointer0R<bool> clickHandler)
{
	mAbortHandler = clickHandler;
}

//============================================
// Up Arrow Callback
bool LogicInterface::UpArrowButtonClick()
{
	isButtonBeingClicked = true;
	sideBarYOffset += 50;
	if(sideBarYOffset > 0)
		sideBarYOffset = 0;

	return true;
}

//============================================
// Down Arrow Callback
bool LogicInterface::DownArrowButtonClick()
{
	int i = executionList.size();
	int overallHeight = (sideBarY + 30) + (i * 140) + (i * instructionSpacing);
	isButtonBeingClicked = true;

	if(executionList.size() > 3)
	{
		sideBarYOffset -= 50;
		if(sideBarYOffset + overallHeight < 768 - 130)
		{
			sideBarYOffset = 768 - 150 - overallHeight;
		}
	}
	return true;
}

//============================================
// Left Arrow Callback
bool LogicInterface::LeftArrowButtonClick()
{
	int i = logicBank->size();
	int overallWidth = (bottomBarX + 30) + (i * 140) + (i * instructionSpacing);
	isButtonBeingClicked = true;

	bottomBarXOffset -= 50;
	if(bottomBarXOffset + overallWidth < 1024 - 70)
	{
		bottomBarXOffset = 1024 - 70 - overallWidth;
	}
	return true;
}

//============================================
// Right Arrow Callback
bool LogicInterface::RightArrowButtonClick()
{
	isButtonBeingClicked = true;
	bottomBarXOffset += 50;
	if(bottomBarXOffset > 0)
		bottomBarXOffset = 0;

	return true;
}

//============================================
// Execute Button Callback
bool LogicInterface::ExecuteButtonClick()
{
	if(mExecuteHandler)
	{
		return mExecuteHandler(executionList);
	}
	return false;
}

//============================================
// Abort Button Callback
bool LogicInterface::AbortButtonClick()
{
	if(mAbortHandler)
	{
		return mAbortHandler();
	}
	return false;
}



