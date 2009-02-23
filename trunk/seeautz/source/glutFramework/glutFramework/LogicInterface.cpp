#include "LogicInterface.h"


LogicInterface::LogicInterface()
	: myMenu(NULL), isButtonBeingClicked(false),
		sideBarBox(), bottomBarBox(), sideBarColumnCount(3),
		instructionBlockW(140 / 3), instructionBlockH(140 / 3),
		instructionSpacing(3), logicBankBox(), instructionListBox(),
		logicBankNumColumns(4), logicBankNumRowsOnScreen(3), 
		instructionListNumColumns(6), instructionListNumRowsOnScreen(3)
{
	sideBarBox.width = 150;
	sideBarBox.height = 618;
	sideBarBox.x = 874;
	sideBarBox.y = 0;

	bottomBarBox.width = 1024 + 13;
	bottomBarBox.height = 150 + 40;
	bottomBarBox.x = -10;
	bottomBarBox.y = 618 - 40;

	logicBankBox.width = instructionSpacing  + ((instructionSpacing  + instructionBlockW)* logicBankNumColumns);
	logicBankBox.height = bottomBarBox.height - 20;
	logicBankBox.x = bottomBarBox.x + 40;
	logicBankBox.y = bottomBarBox.y + 25;

	instructionListBox.width = instructionSpacing + ((instructionSpacing + instructionBlockW) * instructionListNumColumns);
	instructionListBox.height = logicBankBox.height;
	instructionListBox.x = logicBankBox.x + logicBankBox.width + 25;
	instructionListBox.y = logicBankBox.y;

	//=============================================
	// Menu buttons (scrolling the instruction lists)
	myMenu = new MenuSys(0, 0, "blank.png", None);
	myMenu->addButton("arrow_up.png", "arrow_up.png", "arrow_up.png", BE::CreateFunctionPointer0R(this, &LogicInterface::UpArrowButtonClick));
	myMenu->setLastButtonDimensions(sideBarBox.width, 25);
	myMenu->setLastButtonPosition(sideBarBox.x, 0);

	myMenu->addButton("arrow_down.png", "arrow_down.png", "arrow_down.png", BE::CreateFunctionPointer0R(this, &LogicInterface::DownArrowButtonClick));
	myMenu->setLastButtonDimensions(sideBarBox.width, 25);
	myMenu->setLastButtonPosition(sideBarBox.x, bottomBarBox.y -25);

	myMenu->addButton("arrow_left.png", "arrow_left.png", "arrow_left.png", BE::CreateFunctionPointer0R(this, &LogicInterface::LeftArrowButtonClick));
	myMenu->setLastButtonDimensions(25, bottomBarBox.height);
	myMenu->setLastButtonPosition(0, bottomBarBox.y);

	myMenu->addButton("arrow_right.png", "arrow_right.png", "arrow_right.png", BE::CreateFunctionPointer0R(this, &LogicInterface::RightArrowButtonClick));
	myMenu->setLastButtonDimensions(25, bottomBarBox.height);
	myMenu->setLastButtonPosition(bottomBarBox.width - 40, bottomBarBox.y);

	myMenu->addButton("buttons\\execute.png", "buttons\\execute.png", "buttons\\execute.png", BE::CreateFunctionPointer0R(this, &LogicInterface::ExecuteButtonClick));
	myMenu->setLastButtonDimensions(100, 50);
	myMenu->setLastButtonPosition(sideBarBox.x - 100, bottomBarBox.y - 50);

	myMenu->addButton("buttons\\abort.png", "buttons\\abort.png", "buttons\\abort.png", BE::CreateFunctionPointer0R(this, &LogicInterface::AbortButtonClick));
	myMenu->setLastButtonDimensions(100, 50);
	myMenu->setLastButtonPosition(sideBarBox.x - 205, bottomBarBox.y - 50);


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
	menuBar->mX = bottomBarBox.x;
	menuBar->mY = bottomBarBox.y;
	menuBar->drawImage(bottomBarBox.width, bottomBarBox.height);

	//=============================================
	// Robot Instructios (sidebar)
	int rowCount = 0;
	int columnIndex = 0;
	itr = executionList.begin();
	for(; itr != executionList.end(); itr++)
	{
		int i = std::distance(executionList.begin(), itr);

		if(((i % instructionListNumColumns) == 0)
			&& (i > 0))
		{
			rowCount++;
		}

		(*itr)->blockTexture->mX = instructionListBox.x + (instructionSpacing * columnIndex) + (instructionBlockW * columnIndex);
		(*itr)->blockTexture->mY = sideBarYOffset + ((instructionListBox.y + instructionSpacing) + (rowCount * instructionBlockH) + (rowCount * instructionSpacing));
		(*itr)->blockTexture->drawImage(instructionBlockW, instructionBlockH);

		columnIndex++;
		if(columnIndex >= instructionListNumColumns)
			columnIndex = 0;
	}

	//=============================================
	// LogicBank Instructions (bottom bar)
	rowCount = 0;
	columnIndex = 0;
	itr = logicBank->begin();
	for(; itr != logicBank->end(); itr++)
	{
		int i = std::distance(logicBank->begin(), itr);

		if(((i % logicBankNumColumns) == 0)
			&& (i > 0))
		{
			rowCount++;
		}

		(*itr)->blockTexture->mX = logicBankBox.x + + (instructionSpacing * columnIndex) + (instructionBlockW * columnIndex);
		(*itr)->blockTexture->mY = bottomBarXOffset + ((logicBankBox.y + instructionSpacing) + (rowCount * instructionBlockH) + (rowCount * instructionSpacing));
		(*itr)->blockTexture->drawImage(instructionBlockW, instructionBlockH);

		columnIndex++;
		if(columnIndex >= logicBankNumColumns)
			columnIndex = 0;
	}

	//=============================================
	// Dragged Block
	if(draggedBlock != NULL)
	{
		draggedBlock->blockTexture->drawImage(instructionBlockW, instructionBlockH);
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
		draggedBlock->blockTexture->mX = x - (instructionBlockW / 2);
		draggedBlock->blockTexture->mY = y - (instructionBlockH / 2);
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
				if((*itr)->checkInBounds(x, y, instructionBlockW, instructionBlockH))
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
			if(GameVars->getPlaceInstructionBlock()->checkInBounds(x, y, instructionBlockW, instructionBlockH))
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
				int overallHeight = (instructionListBox.y + instructionSpacing) + (i * instructionBlockH) + (i * instructionSpacing);
				//sideBarYOffset = 768 - 150 - overallHeight;
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
	//isButtonBeingClicked = true;
	//sideBarYOffset += 50;
	//if(sideBarYOffset > 0)
	//	sideBarYOffset = 0;

	return true;
}

//============================================
// Down Arrow Callback
bool LogicInterface::DownArrowButtonClick()
{
	//int i = executionList.size();
	//int overallHeight = (instructionListBox.y + instructionSpacing) + (i * instructionBlockH) + (i * instructionSpacing);
	//isButtonBeingClicked = true;

	//if(executionList.size() > 3)
	//{
	//	sideBarYOffset -= 50;
	//	if(sideBarYOffset + overallHeight < 768 - 130)
	//	{
	//		sideBarYOffset = 768 - 150 - overallHeight;
	//	}
	//}
	return true;
}

//============================================
// Left Arrow Callback
bool LogicInterface::LeftArrowButtonClick()
{
	//isButtonBeingClicked = true;
	//bottomBarXOffset += 50;
	//if(bottomBarXOffset > 0)
	//	bottomBarXOffset = 0;

	return true;
}

//============================================
// Right Arrow Callback
bool LogicInterface::RightArrowButtonClick()
{
	//int i = logicBank->size();
	//int overallWidth = (logicBankBox.x + instructionSpacing) + (i * instructionBlockW) + (i * instructionSpacing);
	//isButtonBeingClicked = true;

	//bottomBarXOffset -= 50;
	//if(bottomBarXOffset + overallWidth < 1024 - 70)
	//{
	//	bottomBarXOffset = 1024 - 70 - overallWidth;
	//}
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

void LogicInterface::ClearExecutionList()
{
	executionList.clear();
	executionList.push_back(GameVars->getPlaceInstructionBlock());
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



