#include "LogicInterface.h"


LogicInterface::LogicInterface()
	: myMenu(NULL), isButtonBeingClicked(false),
		sideBarBox(), bottomBarBox(), sideBarColumnCount(3),
		instructionBlockW(140 / 3), instructionBlockH(140 / 3),
		instructionSpacing(3), logicBankBox(), instructionListBox(),
		logicBankNumColumns(4), logicBankNumRowsOnScreen(3), 
		instructionListNumColumns(8), instructionListNumRowsOnScreen(3),
		mouseX(0), mouseY(0), currentHoverBlockIndex(-1)
{
	//sideBarBox.width = 150;
	//sideBarBox.height = 618;
	//sideBarBox.x = 874;
	//sideBarBox.y = 0;

	bottomBarBox.width = 1024 + 13;
	bottomBarBox.height = 190;
	bottomBarBox.x = -10;
	bottomBarBox.y = 618 - 40;

	logicBankBox.width = instructionSpacing  + ((instructionSpacing  + instructionBlockW)* logicBankNumColumns);
	logicBankBox.height = bottomBarBox.height - 20;
	logicBankBox.x = bottomBarBox.x + 40;
	logicBankBox.y = bottomBarBox.y + 25;

	instructionListBox.width = instructionSpacing + ((instructionSpacing + instructionBlockW) * instructionListNumColumns);
	instructionListBox.height = logicBankBox.height;
	instructionListBox.x = logicBankBox.x + logicBankBox.width + 50;
	instructionListBox.y = logicBankBox.y;

	//=============================================
	// Menu buttons (scrolling the instruction lists)
	myMenu = new MenuSys(0, 0, "blank.png", None);
	myMenu->addButton("arrow_up.png", "arrow_up.png", "arrow_up.png", BE::CreateFunctionPointer0R(this, &LogicInterface::LogicBankUpArrowButtonClick));
	myMenu->setLastButtonDimensions(25, 25);
	myMenu->setLastButtonPosition(logicBankBox.x + logicBankBox.width, logicBankBox.y);

	myMenu->addButton("arrow_down.png", "arrow_down.png", "arrow_down.png", BE::CreateFunctionPointer0R(this, &LogicInterface::LogicBankDownArrowButtonClick));
	myMenu->setLastButtonDimensions(25, 25);
	myMenu->setLastButtonPosition(logicBankBox.x + logicBankBox.width, logicBankBox.y + logicBankBox.height - 45);

	myMenu->addButton("arrow_up.png", "arrow_up.png", "arrow_up.png", BE::CreateFunctionPointer0R(this, &LogicInterface::ExecutionListUpArrowButtonClick));
	myMenu->setLastButtonDimensions(25, 25);
	myMenu->setLastButtonPosition(instructionListBox.x + instructionListBox.width, instructionListBox.y);

	myMenu->addButton("arrow_down.png", "arrow_down.png", "arrow_down.png", BE::CreateFunctionPointer0R(this, &LogicInterface::ExecutionListDownArrowButtonClick));
	myMenu->setLastButtonDimensions(25, 25);
	myMenu->setLastButtonPosition(instructionListBox.x + instructionListBox.width, instructionListBox.y + instructionListBox.height - 45);

	myMenu->addButton("buttons\\execute.png", "buttons\\execute.png", "buttons\\execute.png", BE::CreateFunctionPointer0R(this, &LogicInterface::ExecuteButtonClick));
	myMenu->setLastButtonDimensions(100, 50);
	myMenu->setLastButtonPosition(instructionListBox.x + instructionListBox.width +  100, logicBankBox.y);

	myMenu->addButton("buttons\\abort.png", "buttons\\abort.png", "buttons\\abort.png", BE::CreateFunctionPointer0R(this, &LogicInterface::AbortButtonClick));
	myMenu->setLastButtonDimensions(100, 50);
	myMenu->setLastButtonPosition(instructionListBox.x + instructionListBox.width +  100, bottomBarBox.y + 100);

	//=============================================
	// All other initialization
	menuBar = new oglTexture2D();
	menuBar->loadImage("blankmenu.png", 1024, 768);

	logicBank = GameVars->getAllLogicBlocks();
	executionList.push_back(GameVars->getPlaceInstructionBlock());
	draggedBlock = NULL;

	logicBankYOffset = 0;
	executionListYOffset = 0;

	isMouseDragging = false;
}

void LogicInterface::Update()
{
	myMenu->Update();

	// Hover Over Stuff
	currentHoverBlockIndex = -1;
	std::vector<logicBlock*>::iterator itr = logicBank->begin();
	for(; itr != logicBank->end(); itr++)
	{
		if((*itr)->checkInBounds(mouseX, mouseY, instructionBlockW, instructionBlockH))
		{
			// You're hovering over, YAY! LOLZ
			currentHoverBlockIndex = std::distance(logicBank->begin(), itr);
		}
	}

}

void LogicInterface::Draw()
{
	std::vector<logicBlock*>::iterator itr = executionList.begin();

	//=============================================
	// Menu Bars
	menuBar->mX = bottomBarBox.x;
	menuBar->mY = bottomBarBox.y;
	menuBar->drawImage(bottomBarBox.width, bottomBarBox.height);

	menuBar->mX = instructionListBox.x - 7;
	menuBar->mY = instructionListBox.y;
	menuBar->drawImage(instructionListBox.width + 7, instructionListBox.height - 18);

	menuBar->mX = logicBankBox.x - 7;
	menuBar->mY = logicBankBox.y;
	menuBar->drawImage(logicBankBox.width + 7, logicBankBox.height - 18);

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
		(*itr)->blockTexture->mY = executionListYOffset + ((instructionListBox.y + instructionSpacing) + (rowCount * instructionBlockH) + (rowCount * instructionSpacing));
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
		(*itr)->blockTexture->mY = logicBankYOffset + ((logicBankBox.y + instructionSpacing) + (rowCount * instructionBlockH) + (rowCount * instructionSpacing));
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
	// Menu Bars (Behind Scroll Buttons)
	menuBar->mX = logicBankBox.x + logicBankBox.width;
	menuBar->mY = logicBankBox.y;
	menuBar->drawImage(25, logicBankBox.height - 20);

	menuBar->mX = instructionListBox.x + instructionListBox.width;
	menuBar->mY = instructionListBox.y;
	menuBar->drawImage(25, instructionListBox.height - 20);

	//=============================================
	// Menu Buttons (For scrolling and shizz)
	myMenu->Draw();

	//=============================================
	// Hover-Over Screen Tipz0rz
		// If the currentHoverBlockIndex is -1 that 
		// means no block is being hovered over
	if(currentHoverBlockIndex != -1)
	{
		logicBlock* tmpBlock = (*logicBank)[currentHoverBlockIndex];

		// Draw the background
		menuBar->mX = tmpBlock->blockTexture->mX + 20;
		menuBar->mY = tmpBlock->blockTexture->mY - 170;
		menuBar->drawImageFaded(0.8, 200, 150);

		int MAX_CHARS_PER_LINE = 20;
		int currentLine = 1;
		for(int i = 0; i < tmpBlock->blockDescription.length(); i++)
		{
			if(i >= (currentLine * MAX_CHARS_PER_LINE)) // if i > 20/40/60/80/etc
			{
				GameVars->fontArial12.drawText(menuBar->mX + 10, menuBar->mY + (currentLine * 12), tmpBlock->blockDescription.substr(i - (MAX_CHARS_PER_LINE * currentLine), MAX_CHARS_PER_LINE * currentLine));					
				currentLine++;
			}

			else if(tmpBlock->blockDescription.length() - i <= MAX_CHARS_PER_LINE)
			{
				// If this is a shorter string we have to print the first half here
				//if(currentLine * i < MAX_CHARS_PER_LINE * currentLine)
				//{
				//	GameVars->fontArial12.drawText(menuBar->mX + 10, menuBar->mY + (currentLine * 12), tmpBlock->blockDescription.substr(0, i));
				//}

				// Display the rest of the line
				GameVars->fontArial12.drawText(menuBar->mX + 10, menuBar->mY + (currentLine * 12), tmpBlock->blockDescription.substr(i, tmpBlock->blockDescription.length() - i));
				currentLine++;
				break;
			}
		}
	}
}

void LogicInterface::processMouse(int x, int y)
{
	// Internal mouse position for hover over stuff
	mouseX = x;
	mouseY = y;

	// Menu buttons
	myMenu->processMouse(x, y);

	// Dragging the block
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
				//executionListYOffset = 768 - 150 - overallHeight;
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
// LogicBank Arrow Callback
bool LogicInterface::LogicBankUpArrowButtonClick()
{
	//isButtonBeingClicked = true;
	//executionListYOffset += 50;
	//if(executionListYOffset > 0)
	//	executionListYOffset = 0;

	return true;
}

//============================================
// LogicBank Down Arrow Callback
bool LogicInterface::LogicBankDownArrowButtonClick()
{
	//int i = executionList.size();
	//int overallHeight = (logicBankBox.y + instructionSpacing) + ((i / logicBankNumRowsOnScreen) * instructionBlockH) + ((i / logicBankNumRowsOnScreen) * instructionSpacing);
	//isButtonBeingClicked = true;

	//if(executionList.size() > 3)
	//{
	//	executionListYOffset -= 50;
	//	if(executionListYOffset + overallHeight < 768 - 130)
	//	{
	//		executionListYOffset = 768 - 150 - overallHeight;
	//	}
	//}
	return true;
}

//============================================
// ExecutionList Up Arrow Callback
bool LogicInterface::ExecutionListUpArrowButtonClick()
{
	isButtonBeingClicked = true;
	executionListYOffset += 50;
	if(executionListYOffset > 0)
		executionListYOffset = 0;

	return true;
}

//============================================
// ExecutionList Down Arrow Callback
bool LogicInterface::ExecutionListDownArrowButtonClick()
{
	int i = executionList.size();
	int overallHeight = (instructionListBox.y + instructionSpacing) + ((i / instructionListNumRowsOnScreen) * instructionBlockH) + ((i / instructionListNumRowsOnScreen) * instructionSpacing);
	isButtonBeingClicked = true;

	executionListYOffset -= 50;
	if(executionListYOffset + overallHeight < instructionListBox.y + instructionListBox.height)
	{
		executionListYOffset += 50;
	}
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



