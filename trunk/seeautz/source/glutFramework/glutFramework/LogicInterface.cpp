#include "LogicInterface.h"


LogicInterface::LogicInterface()
	: myMenu(NULL), isButtonBeingClicked(false),
		sideBarBox(), bottomBarBox(), sideBarColumnCount(3),
		instructionBlockW(140 / 3), instructionBlockH(140 / 3),
		instructionSpacing(2), logicBankBox(), instructionListBox(),
		logicBankNumColumns(4), logicBankNumRowsOnScreen(3), 
		instructionListNumColumns(8), instructionListNumRowsOnScreen(3),
		mouseX(0), mouseY(0), currentHoverBlockIndex(-1),
		curInstrTab(TAB_MAIN), isExecuting(false), resetMenu(NULL),
		curExecutionListYOffset(NULL), executionListYOffset(0), 
		executionListSub1YOffset(0), executionListSub2YOffset(0),
		scrollBar(NULL), mapByteLimit(0), usedBytes(0), drawInsertionLine(false),
		insertionLineColumn(0), insertionLineRow(0), insertionLine(NULL)
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
	//logicBankBox.x = bottomBarBox.x + 40;
	//logicBankBox.y = bottomBarBox.y + 25;
	logicBankBox.x = 34;
	logicBankBox.y = 768-190+15;

	instructionListBox.width = instructionSpacing + ((instructionSpacing + instructionBlockW) * instructionListNumColumns);
	instructionListBox.height = logicBankBox.height;
	//instructionListBox.x = logicBankBox.x + logicBankBox.width + 50;
	//instructionListBox.y = logicBankBox.y;
	instructionListBox.x = 345;
	instructionListBox.y = 600;

	//=============================================
	// Menu buttons (scrolling the instruction lists)
	myMenu = new MenuSys(0, 0, "blank.png", None);
	myMenu->addButton("scrollbarUp.png", "scrollbarUp.png", "scrollbarUpLit.png", BE::CreateFunctionPointer0R(this, &LogicInterface::LogicBankUpArrowButtonClick));
	myMenu->setLastButtonDimensions(25, 25);
	myMenu->setLastButtonPosition(logicBankBox.x + logicBankBox.width, logicBankBox.y);

	myMenu->addButton("scrollbarDown.png", "scrollbarDown.png", "scrollbarDownLit.png", BE::CreateFunctionPointer0R(this, &LogicInterface::LogicBankDownArrowButtonClick));
	myMenu->setLastButtonDimensions(25, 25);
	myMenu->setLastButtonPosition(logicBankBox.x + logicBankBox.width, logicBankBox.y + logicBankBox.height - 45);

	myMenu->addButton("scrollbarUp.png", "scrollbarUp.png", "scrollbarUpLit.png", BE::CreateFunctionPointer0R(this, &LogicInterface::ExecutionListUpArrowButtonClick));
	myMenu->setLastButtonDimensions(25, 25);
	myMenu->setLastButtonPosition(instructionListBox.x + instructionListBox.width, instructionListBox.y);

	myMenu->addButton("scrollbarDown.png", "scrollbarDown.png", "scrollbarDownLit.png", BE::CreateFunctionPointer0R(this, &LogicInterface::ExecutionListDownArrowButtonClick));
	myMenu->setLastButtonDimensions(25, 25);
	myMenu->setLastButtonPosition(instructionListBox.x + instructionListBox.width, instructionListBox.y + instructionListBox.height - 45);

	myMenu->addButton("buttons\\execute.png", "buttons\\execute.png", "buttons\\execute.png", BE::CreateFunctionPointer0R(this, &LogicInterface::ExecuteButtonClick));
	myMenu->setLastButtonDimensions(100, 50);
	myMenu->setLastButtonPosition(instructionListBox.x+45 + instructionListBox.width +  100, logicBankBox.y+25);

	myMenu->addButton("blank.png", "blank.png", "blank.png", BE::CreateFunctionPointer0R(this, &LogicInterface::MainTabButtonClick));
	myMenu->setLastButtonDimensions(50, 20);
	myMenu->setLastButtonPosition(instructionListBox.x + 25 + 3, instructionListBox.y - 25);

	myMenu->addButton("blank.png", "blank.png", "blank.png", BE::CreateFunctionPointer0R(this, &LogicInterface::Sub1TabButtonClick));
	myMenu->setLastButtonDimensions(50, 20);
	myMenu->setLastButtonPosition(419,575);

	myMenu->addButton("blank.png", "blank.png", "blank.png", BE::CreateFunctionPointer0R(this, &LogicInterface::Sub2TabButtonClick));
	myMenu->setLastButtonDimensions(50, 20);
	myMenu->setLastButtonPosition(469,575);
	
	myMenu->addButton("buttons\\clear.png", "buttons\\clear.png", "buttons\\clear.png", BE::CreateFunctionPointer0R(this, &LogicInterface::ClearButtonClick));
	myMenu->setLastButtonDimensions(50, 25);
	myMenu->setLastButtonPosition(instructionListBox.x + instructionListBox.width + 25, instructionListBox.y + (instructionListBox.height / 2) - (25 / 2));

	resetMenu = new MenuSys(0, 0, "blank.png", None);
	resetMenu->addButton("buttons\\reset.png", "buttons\\reset.png", "buttons\\reset.png", BE::CreateFunctionPointer0R(this, &LogicInterface::ResetButtonClick));
	resetMenu->setLastButtonDimensions(100, 50);
	resetMenu->setLastButtonPosition(instructionListBox.x +45+ instructionListBox.width +  100, logicBankBox.y + 70 +15);

	executingMenu = new MenuSys(0, 0, "blank.png", None);
	executingMenu->addButton("buttons\\abort.png", "buttons\\abort.png", "buttons\\abort.png", BE::CreateFunctionPointer0R(this, &LogicInterface::AbortButtonClick));
	executingMenu->setLastButtonDimensions(100, 50);
	executingMenu->setLastButtonPosition(instructionListBox.x +45 + instructionListBox.width +  100, logicBankBox.y+25);

	panelArt = new oglTexture2D();
	panelArt->loadImage("Panel.png", 1024, 190);
	panelArt->mX = 0;
	panelArt->mY = 768-190;

	commandBackdrop = new oglTexture2D();
	commandBackdrop->loadImage("CommandList.png", 228, 181);

	commandBackdrop2 = new oglTexture2D();
	commandBackdrop2->loadImage("logicinterface.png", 228, 181);

	insertionLine = new oglTexture2D();
	insertionLine->loadImage("black.png", 3, instructionBlockH - 4);

	//=============================================
	// All other initialization
	menuBar = new oglTexture2D();
	menuBar->loadImage("CommandList.png", 1024, 768);
	//menuBar->loadImage("blank.png", 1024, 768);
	scrollBar = new oglTexture2D();
	scrollBar->loadImage("scrollbarBG.png", 100, 100);

	logicBank = GameVars->GetCurrentMapLogicBank(); //GameVars->getAllLogicBlocks();
	executionList.push_back(new logicBlock((*GameVars->getPlaceInstructionBlock())));
	executionList.back()->curButtonState = BS_ACTIVE;
	
	executionListSub1.push_back(new logicBlock((*GameVars->getPlaceInstructionBlock())));
	executionListSub1.back()->curButtonState = BS_ACTIVE;

	executionListSub2.push_back(new logicBlock((*GameVars->getPlaceInstructionBlock())));
	executionListSub2.back()->curButtonState = BS_ACTIVE;

	draggedBlock = NULL;

	logicBankYOffset = 0;
	executionListYOffset = 0;

	isMouseDragging = false;
}

void LogicInterface::Update()
{
	resetMenu->Update();
	myMenu->Update();
	executingMenu->Update();

	// Hover Over Stuff
	currentHoverBlockIndex = -1;
	if(logicBank != NULL)
	{
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

	// Calculating the bytes left
		//  I think there's a loop deficiency
		//  Nothin' sexier than algorithmic efficiency
		//  I want you to iterate
		//  Cus when I see i++, I salivate!
		// -Corwin VanHook, March 09, 2009
	int tmpByteCount = 0;
	std::vector<logicBlock*>::iterator itr = executionList.begin();
	for(; itr != executionList.end(); itr++)
	{
		tmpByteCount += (*itr)->byteCost;
	}
	itr = executionListSub1.begin();
	for(; itr != executionListSub1.end(); itr++)
	{
		tmpByteCount += (*itr)->byteCost;
	}
	itr = executionListSub2.begin();
	for(; itr != executionListSub2.end(); itr++)
	{
		tmpByteCount += (*itr)->byteCost;
	}

	usedBytes = tmpByteCount;
	GameVars->setBytesUsed(usedBytes);


	itr = executionList.begin();
	for(; itr != executionList.end(); itr++)
	{
		if((*itr)->enumInstruction == DO_NOT_PROCESS)
		{
			if(usedBytes == mapByteLimit)
			{
				(*itr)->curButtonState = BS_INACTIVE;
			}
			else
			{
				(*itr)->curButtonState = BS_ACTIVE;
			}
		}
	}
	itr = executionListSub1.begin();
	for(; itr != executionListSub1.end(); itr++)
	{
		if((*itr)->enumInstruction == DO_NOT_PROCESS)
		{
			if(usedBytes == mapByteLimit)
			{
				(*itr)->curButtonState = BS_INACTIVE;
			}
			else
			{
				(*itr)->curButtonState = BS_ACTIVE;
			}
		}
	}
	itr = executionListSub2.begin();
	for(; itr != executionListSub2.end(); itr++)
	{
		if((*itr)->enumInstruction == DO_NOT_PROCESS)
		{
			if(usedBytes == mapByteLimit)
			{
				(*itr)->curButtonState = BS_INACTIVE;
			}
			else
			{
				(*itr)->curButtonState = BS_ACTIVE;
			}
		}
	}
}

void LogicInterface::Draw()
{
	// draw panel background
	panelArt->drawImage();

	// draw left commands background
	commandBackdrop->dX = 200;
	commandBackdrop->dY = 165;
	commandBackdrop->mX = 30;
	commandBackdrop->mY = 768-190+12;
	commandBackdrop->drawImage();
	
	// draw center commands background
	//commandBackdrop->dX = 390;
	//commandBackdrop->dY = 161;
	//commandBackdrop->mX = 340;
	//commandBackdrop->mY = instructionListBox.y;
	//commandBackdrop->drawImage();
	commandBackdrop2->dX = 390;
	commandBackdrop2->dY = 161 + 25;
	commandBackdrop2->mX = 340;
	commandBackdrop2->mY = instructionListBox.y - 25;
	if(curInstrTab == TAB_MAIN)
		commandBackdrop2->drawImageSegment(0.0, 0.0, 1.0, 0.0, 0.0, (double)1/3, 1.0, (double)1/3, 1.0);
	else if(curInstrTab == TAB_SUB1)
		commandBackdrop2->drawImageSegment(0.0, (double)1/3, 1.0, (double)1/3, 0.0, (double)2/3, 1.0, (double)2/3, 1.0); 
	else if(curInstrTab == TAB_SUB2)
		commandBackdrop2->drawImageSegment(0.0, (double)2/3, 1.0, (double)2/3, 0.0, 1.0, 1.0, 1.0, 1.0);
	std::vector<logicBlock*>::iterator itr = executionList.begin();

	//=============================================
	// Menu Bars
	/*menuBar->mX = bottomBarBox.x;
	menuBar->mY = bottomBarBox.y;
	menuBar->drawImage(bottomBarBox.width, bottomBarBox.height);

	menuBar->mX = instructionListBox.x - 7;
	menuBar->mY = instructionListBox.y;
	menuBar->drawImage(instructionListBox.width + 7, instructionListBox.height - 18);

	menuBar->mX = logicBankBox.x - 7;
	menuBar->mY = logicBankBox.y;
	menuBar->drawImage(logicBankBox.width + 7, logicBankBox.height - 18);*/

	//=============================================
	// Robot Instructios (sidebar)
	int rowCount = 0;
	int columnIndex = 0;
	if(this->curInstrTab == TAB_MAIN)
	{
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
			if((*itr)->blockTexture->mY >= instructionListBox.y
				&& (*itr)->blockTexture->mY <= instructionListBox.y + instructionListBox.height - (instructionSpacing + instructionBlockH))
			{
				if((*itr)->curButtonState == BS_ACTIVE)
				{
					(*itr)->blockTexture->drawImageSegment(0.0, 0.0, (double)1/3, 0.0, 0.0, 1.0, (double)1/3, 1.0, 1, instructionBlockW, instructionBlockH);
				}
				else if((*itr)->curButtonState == BS_HIGHLIGHTED)
				{
					(*itr)->blockTexture->drawImageSegment((double)1/3, 0.0, (double)2/3, 0.0, (double)1/3, 1.0, (double)2/3, 1.0, 1, instructionBlockW, instructionBlockH);
				}
				else if((*itr)->curButtonState == BS_INACTIVE)
				{
					(*itr)->blockTexture->drawImageSegment((double)2/3, 0.0, (double)3/3, 0.0, (double)2/3, 1.0, (double)3/3, 1.0, 1, instructionBlockW, instructionBlockH);
				}
			}

			columnIndex++;
			if(columnIndex >= instructionListNumColumns)
				columnIndex = 0;
		}
	}

	//=============================================
	// Robot Instructios (Sub1)
	if(this->curInstrTab == TAB_SUB1)
	{
		itr = executionListSub1.begin();
		for(; itr != executionListSub1.end(); itr++)
		{
			int i = std::distance(executionListSub1.begin(), itr);

			if(((i % instructionListNumColumns) == 0)
				&& (i > 0))
			{
				rowCount++;
			}

			(*itr)->blockTexture->mX = instructionListBox.x + (instructionSpacing * columnIndex) + (instructionBlockW * columnIndex);
			(*itr)->blockTexture->mY = executionListSub1YOffset + ((instructionListBox.y + instructionSpacing) + (rowCount * instructionBlockH) + (rowCount * instructionSpacing));
			if((*itr)->blockTexture->mY >= instructionListBox.y
				&& (*itr)->blockTexture->mY <= instructionListBox.y + instructionListBox.height - (instructionSpacing + instructionBlockH))
			{
				if((*itr)->curButtonState == BS_ACTIVE)
				{
					(*itr)->blockTexture->drawImageSegment(0.0, 0.0, (double)1/3, 0.0, 0.0, 1.0, (double)1/3, 1.0, 1, instructionBlockW, instructionBlockH);
				}
				else if((*itr)->curButtonState == BS_HIGHLIGHTED)
				{
					(*itr)->blockTexture->drawImageSegment((double)1/3, 0.0, (double)2/3, 0.0, (double)1/3, 1.0, (double)2/3, 1.0, 1, instructionBlockW, instructionBlockH);
				}
				else if((*itr)->curButtonState == BS_INACTIVE)
				{
					(*itr)->blockTexture->drawImageSegment((double)2/3, 0.0, (double)3/3, 0.0, (double)2/3, 1.0, (double)3/3, 1.0, 1, instructionBlockW, instructionBlockH);
				}
			}
						
			columnIndex++;
			if(columnIndex >= instructionListNumColumns)
				columnIndex = 0;
		}
	}

	//=============================================
	// Robot Instructios (Sub2)
	if(this->curInstrTab == TAB_SUB2)
	{
		itr = executionListSub2.begin();
		for(; itr != executionListSub2.end(); itr++)
		{
			int i = std::distance(executionListSub2.begin(), itr);

			if(((i % instructionListNumColumns) == 0)
				&& (i > 0))
			{
				rowCount++;
			}

			(*itr)->blockTexture->mX = instructionListBox.x + (instructionSpacing * columnIndex) + (instructionBlockW * columnIndex);
			(*itr)->blockTexture->mY = executionListSub2YOffset + ((instructionListBox.y + instructionSpacing) + (rowCount * instructionBlockH) + (rowCount * instructionSpacing));
			if((*itr)->blockTexture->mY >= instructionListBox.y
				&& (*itr)->blockTexture->mY <= instructionListBox.y + instructionListBox.height - (instructionSpacing + instructionBlockH))
			{
				if((*itr)->curButtonState == BS_ACTIVE)
				{
					(*itr)->blockTexture->drawImageSegment(0.0, 0.0, (double)1/3, 0.0, 0.0, 1.0, (double)1/3, 1.0, 1, instructionBlockW, instructionBlockH);
				}
				else if((*itr)->curButtonState == BS_HIGHLIGHTED)
				{
					(*itr)->blockTexture->drawImageSegment((double)1/3, 0.0, (double)2/3, 0.0, (double)1/3, 1.0, (double)2/3, 1.0, 1, instructionBlockW, instructionBlockH);
				}
				else if((*itr)->curButtonState == BS_INACTIVE)
				{
					(*itr)->blockTexture->drawImageSegment((double)2/3, 0.0, (double)3/3, 0.0, (double)2/3, 1.0, (double)3/3, 1.0, 1, instructionBlockW, instructionBlockH);
				}
			}

			columnIndex++;
			if(columnIndex >= instructionListNumColumns)
				columnIndex = 0;
		}
	}

	//=============================================
	// LogicBank Instructions (bottom bar)
	rowCount = 0;
	columnIndex = 0;
	if(logicBank != NULL)
	{
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
			if((*itr)->curButtonState == BS_ACTIVE)
			{
				(*itr)->blockTexture->drawImageSegment(0.0, 0.0, (double)1/3, 0.0, 0.0, 1.0, (double)1/3, 1.0, 1, instructionBlockW, instructionBlockH);
			}
			else if((*itr)->curButtonState == BS_HIGHLIGHTED)
			{
				(*itr)->blockTexture->drawImageSegment((double)1/3, 0.0, (double)2/3, 0.0, (double)1/3, 1.0, (double)2/3, 1.0, 1, instructionBlockW, instructionBlockH);
			}
			else if((*itr)->curButtonState == BS_INACTIVE)
			{
				(*itr)->blockTexture->drawImageSegment((double)2/3, 0.0, (double)3/3, 0.0, (double)2/3, 1.0, (double)3/3, 1.0, 1, instructionBlockW, instructionBlockH);
			}

			columnIndex++;
			if(columnIndex >= logicBankNumColumns)
				columnIndex = 0;
		}
	}
	//=============================================
	// Menu Bars (Behind Scroll Buttons)
	scrollBar->mX = logicBankBox.x + logicBankBox.width;
	scrollBar->mY = logicBankBox.y;
	scrollBar->drawImage(25, logicBankBox.height - 20);

	scrollBar->mX = instructionListBox.x + instructionListBox.width;
	scrollBar->mY = instructionListBox.y;
	scrollBar->drawImage(25, instructionListBox.height - 20);

	//=============================================
	// Menu Buttons (For scrolling and shizz)
	resetMenu->Draw();
	myMenu->Draw();
	if(isExecuting == true)
		executingMenu->Draw();

	//=============================================
	// Byte Limit Stuff
	glColor3ub(0, 255, 0);
	std::stringstream ss;
	std::string s;
	ss << usedBytes;
	ss << "\\";
	ss << mapByteLimit;
	ss << " BYTES used.";
	s = ss.str();
	GameVars->fontDigital16.drawText(775, logicBankBox.y - 50, s.c_str());

	std::stringstream ss2;
	ss2 << mapByteLimit - usedBytes;
	ss2 << " BYTES remaining.";
	s = ss2.str();
	GameVars->fontDigital16.drawText(775, logicBankBox.y - 50 + 16, s.c_str());

	if(drawInsertionLine == true)
	{
		std::vector<logicBlock*>* curExecutionList = NULL;
		if(curInstrTab == TAB_MAIN)
		{
			curExecutionListYOffset = &executionListYOffset;
			curExecutionList = &executionList;
		}
		else if(curInstrTab == TAB_SUB1)
		{
			curExecutionListYOffset = &executionListSub1YOffset;
			curExecutionList = &executionListSub1;
		}
		else if(curInstrTab == TAB_SUB2)
		{
			curExecutionListYOffset = &executionListSub2YOffset;
			curExecutionList = &executionListSub2;
		}
		// CJV2

		int rowOffset = ((*curExecutionListYOffset) / (instructionSpacing + instructionBlockH));
		int vectorSize = curExecutionList->size();
		
		int lastBlockRow = vectorSize / instructionListNumColumns;
		int lastBlockColumn = vectorSize % instructionListNumColumns;
		
		lastBlockRow += rowOffset;

		if(lastBlockColumn != 0)
			lastBlockColumn--;
		else
		{
			lastBlockColumn = instructionListNumColumns - 1;
			lastBlockRow--;
		}
		if(((insertionLineColumn > lastBlockColumn) && (insertionLineRow > lastBlockRow))
			|| ((insertionLineColumn > lastBlockColumn) && (insertionLineRow == lastBlockRow))
			|| ((insertionLineRow > lastBlockRow)))
		{
			insertionLine->mX = instructionListBox.x + (lastBlockColumn * (instructionSpacing + instructionBlockW)) - 2;
			insertionLine->mY = instructionListBox.y + (lastBlockRow * (instructionSpacing + instructionBlockH)) + 4;
			insertionLine->drawImage();
		}
		else
		{
			insertionLine->mX = instructionListBox.x + (insertionLineColumn * (instructionSpacing + instructionBlockW)) - 2;
			insertionLine->mY = instructionListBox.y + (insertionLineRow * (instructionSpacing + instructionBlockH)) + 4;
			insertionLine->drawImage();
		}
	}

	//=============================================
	// Dragged Block
	if(draggedBlock != NULL)
	{
		//draggedBlock->blockTexture->drawImage(instructionBlockW, instructionBlockH);
		draggedBlock->blockTexture->drawImageSegment((double)0/3, 0, (double)1/3, 0, (double)0/3, 1, (double)1/3, 1, 1, instructionBlockW, instructionBlockH);
	}

	//=============================================
	// Hover Over Screen Tipz0rz
		// If the currentHoverBlockIndex is -1 that 
		// means no block is being hovered over
	if(currentHoverBlockIndex != -1)
	{
		if(logicBank != NULL)
		{
			logicBlock* tmpBlock = (*logicBank)[currentHoverBlockIndex];

			// Draw the background
			menuBar->mX = tmpBlock->blockTexture->mX + 20;
			menuBar->mY = tmpBlock->blockTexture->mY - 170;
			menuBar->drawImageFaded(1.0, 200, 100);

			int MAX_CHARS_PER_LINE = 21;
			int currentLine = 1;
			bool endOfText = false;
			
			glColor3ub(0, 0, 0);
			while(!endOfText)
			{
				if((int)(tmpBlock->blockDescription.length()) > currentLine * MAX_CHARS_PER_LINE)
				{
					GameVars->fontArial12.drawText(menuBar->mX + 10, menuBar->mY + (currentLine * 12), tmpBlock->blockDescription.substr((currentLine - 1) * MAX_CHARS_PER_LINE, MAX_CHARS_PER_LINE));
					currentLine++;
				}
				else
				{
					GameVars->fontArial12.drawText(
						menuBar->mX + 10,
						menuBar->mY + (currentLine * 12),
						tmpBlock->blockDescription.substr(
											(currentLine - 1) * MAX_CHARS_PER_LINE,
											tmpBlock->blockDescription.length() % (currentLine -1 * MAX_CHARS_PER_LINE))
											);
					endOfText = true;
				}
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
	resetMenu->processMouse(x, y);
	myMenu->processMouse(x, y);
	if(isExecuting == true)
		executingMenu->processMouse(x, y);
	
	// Dragging the block
	if(isMouseDragging == true
		&& draggedBlock != NULL)
	{
		draggedBlock->blockTexture->mX = x - (instructionBlockW / 2);
		draggedBlock->blockTexture->mY = y - (instructionBlockH / 2);
	}

	// Dragging & Insertion into the middle of the list
	if(isMouseDragging == true
		&& draggedBlock != NULL)
	{
		
		int localX = x - instructionListBox.x;
		int localY = y - instructionListBox.y;
		int columnPosition = localX / (instructionSpacing + instructionBlockW);
		int rowPosition = localY / (instructionSpacing + instructionBlockH);

		if((columnPosition >= 0)
			&& (columnPosition < instructionListNumColumns)
			&& (rowPosition >= 0)
			&& (rowPosition < instructionListNumRowsOnScreen))
		{
			insertionLineColumn = columnPosition;
			insertionLineRow = rowPosition;
			drawInsertionLine = true;
			// CJV1
		}
		else
		{
			insertionLineColumn = 0;
			insertionLineRow = 0;
			drawInsertionLine = false;
		}
		//instructionListNumColumns
		//instructionListNumRowsOnScreen
		
		// Figure out which column & row the mouse is hovering over 
		// is that coord beyond the processInstructionHere instruction block
			// If so, it doesn't really mean shit
		// else
		// Determine which blocks it's in between and shit

	}
	else
	{
		insertionLineColumn = 0;
		insertionLineRow = 0;
		drawInsertionLine = false;
	}
}

void LogicInterface::processMouseClick(int button, int state, int x, int y)
{
	// Menu buttons
	resetMenu->processMouseClick(button, state, x, y);

	if(isExecuting == true)
		executingMenu->processMouseClick(button, state, x, y);
	else if(isExecuting == false)
		myMenu->processMouseClick(button, state, x, y);

	// Click & Drag
	// When the user clicks, we want them to be able to select an
	// instruction to drag over into the robot's instruction list.
	// Loop through the list of bank instructions and check x/y
	if(!isExecuting)
	{
		if(button == GLUT_LEFT
			&& state == GLUT_DOWN)
		{
			if(isButtonBeingClicked == false)
			{
				// If the left mouse button is down
				if(logicBank != NULL)
				{
					std::vector<logicBlock*>::iterator itr = logicBank->begin();
					for(; itr != logicBank->end(); itr++)
					{
						if((*itr)->checkInBounds(x, y, instructionBlockW, instructionBlockH))
						{
							draggedBlock = new logicBlock(*(*itr));
							draggedBlock->curButtonState = BS_ACTIVE;
							isMouseDragging = true;
						}
					}
				}
			}
		}
	}


	//=====================================
	// Dropping the instruction block into 
	// the correct tabbed execution list
	if(!isExecuting)
	{
		if(button == GLUT_LEFT
			&& state == GLUT_UP)
		{
			if(isMouseDragging == true
				&& draggedBlock != NULL)
			{
				//if(drawInsertionLine == true)
				//{
				//	std::vector<logicBlock*>* curExecutionList = NULL;
				//	if(curInstrTab == TAB_MAIN)
				//	{
				//		curExecutionListYOffset = &executionListYOffset;
				//		curExecutionList = &executionList;
				//	}
				//	else if(curInstrTab == TAB_SUB1)
				//	{
				//		curExecutionListYOffset = &executionListSub1YOffset;
				//		curExecutionList = &executionListSub1;
				//	}
				//	else if(curInstrTab == TAB_SUB2)
				//	{
				//		curExecutionListYOffset = &executionListSub2YOffset;
				//		curExecutionList = &executionListSub2;
				//	}
				//	// CJV2

				//	int rowOffset = ((*curExecutionListYOffset) / (instructionSpacing + instructionBlockH));
				//	int vectorSize = curExecutionList->size();
				//	
				//	int lastBlockRow = vectorSize / instructionListNumColumns;
				//	int lastBlockColumn = vectorSize % instructionListNumColumns;
				//	
				//	lastBlockRow += rowOffset;

				//	if(lastBlockColumn != 0)
				//		lastBlockColumn--;
				//	else
				//	{
				//		lastBlockColumn = instructionListNumColumns - 1;
				//		lastBlockRow--;
				//	}
				//	if(((insertionLineColumn > lastBlockColumn) && (insertionLineRow > lastBlockRow))
				//		|| ((insertionLineColumn > lastBlockColumn) && (insertionLineRow == lastBlockRow))
				//		|| ((insertionLineRow > lastBlockRow)))
				//	{
				//		// Add block to the end of the list
				//		int bytesLeft = mapByteLimit - usedBytes;
				//		if(bytesLeft >= draggedBlock->byteCost)
				//		{
				//			curExecutionList->pop_back();
				//			curExecutionList->push_back(new logicBlock(*(draggedBlock)));
				//			curExecutionList->push_back(new logicBlock((*GameVars->getPlaceInstructionBlock())));
				//			curExecutionList->back()->curButtonState = BS_ACTIVE;
				//			delete draggedBlock;
				//			draggedBlock = NULL;
				//			isMouseDragging = false;
				//		}
				//		delete draggedBlock;
				//		draggedBlock = NULL;
				//		isMouseDragging = false;
				//	}
				//	else
				//	{
				//		//// Insert block within the current list.
				//		//int bytesLeft = mapByteLimit - usedBytes;
				//		//if(bytesLeft >= draggedBlock->byteCost)
				//		//{
				//		//	curExecutionList->insert(
				//		//	curExecutionList->pop_back();
				//		//	curExecutionList->push_back(new logicBlock(*(draggedBlock)));
				//		//	curExecutionList->push_back(new logicBlock((*GameVars->getPlaceInstructionBlock())));
				//		//	curExecutionList->back()->curButtonState = BS_ACTIVE;
				//		//	delete draggedBlock;
				//		//	draggedBlock = NULL;
				//		//	isMouseDragging = false;
				//		//}
				//		//delete draggedBlock;
				//		//draggedBlock = NULL;
				//		//isMouseDragging = false;
				//	}
				//}
				if(curInstrTab == TAB_MAIN)
				{
					if(executionList.back()->checkInBounds(x, y, instructionBlockW, instructionBlockH))
					{
						int bytesLeft = mapByteLimit - usedBytes;
						if(bytesLeft >= draggedBlock->byteCost)
						{
							executionList.pop_back();
							executionList.push_back(new logicBlock(*(draggedBlock)));					
							executionList.push_back(new logicBlock((*GameVars->getPlaceInstructionBlock())));
							executionList.back()->curButtonState = BS_ACTIVE;
							delete draggedBlock;
							draggedBlock = NULL;
						}
					}

					delete draggedBlock;
					draggedBlock = NULL;
					isMouseDragging = false;
				}
				else if(curInstrTab == TAB_SUB1)
				{
					if(executionListSub1.back()->checkInBounds(x, y, instructionBlockW, instructionBlockH))
					{
						executionListSub1.pop_back();
						executionListSub1.push_back(new logicBlock(*(draggedBlock)));
						executionListSub1.push_back(new logicBlock((*GameVars->getPlaceInstructionBlock())));
						executionListSub1.back()->curButtonState = BS_ACTIVE;
						delete draggedBlock;
						draggedBlock = NULL;
					}

					delete draggedBlock;
					draggedBlock = NULL;
					isMouseDragging = false;
				}
				else if(curInstrTab == TAB_SUB2)
				{
					if(executionListSub2.back()->checkInBounds(x, y, instructionBlockW, instructionBlockH))
					{
						executionListSub2.pop_back();
						executionListSub2.push_back(new logicBlock(*(draggedBlock)));
						executionListSub2.push_back(new logicBlock((*GameVars->getPlaceInstructionBlock())));
						executionListSub2.back()->curButtonState = BS_ACTIVE;
						delete draggedBlock;
						draggedBlock = NULL;
					}

					delete draggedBlock;
					draggedBlock = NULL;
					isMouseDragging = false;
				}
			}
		}
	}

	//===============================
	// Pulling an instruction block 
	// out of one of the execution 
	// lists.
	if(!isExecuting)
	{
		if(button == GLUT_LEFT
			&& state == GLUT_DOWN)
		{
			if(curInstrTab == TAB_MAIN)
			{
				if(isButtonBeingClicked == false)
				{
					// If the left mouse button is down
					std::vector<logicBlock*>::reverse_iterator itr = executionList.rbegin();
					for(; itr != executionList.rend(); itr++)
					{
						if((*itr)->enumInstruction != DO_NOT_PROCESS)
						{
							if((*itr)->checkInBounds(x, y, instructionBlockW, instructionBlockH))
							{
								draggedBlock = new logicBlock(*(*itr));
								isMouseDragging = true;

								delete (*itr);
								executionList.erase(itr.base() - 1);
								break;
							}
						}
					}
				}
			}
			else if(curInstrTab == TAB_SUB1)
			{
				if(isButtonBeingClicked == false)
				{
					// If the left mouse button is down
					std::vector<logicBlock*>::reverse_iterator itr = executionListSub1.rbegin();
					for(; itr != executionListSub1.rend(); itr++)
					{
						if((*itr)->enumInstruction != DO_NOT_PROCESS)
						{
							if((*itr)->checkInBounds(x, y, instructionBlockW, instructionBlockH))
							{
								draggedBlock = new logicBlock(*(*itr));
								isMouseDragging = true;

								delete (*itr);
								executionListSub1.erase(itr.base() - 1);
								break;
							}
						}
					}
				}
			}
			else if(curInstrTab == TAB_SUB2)
			{
				if(isButtonBeingClicked == false)
				{
					// If the left mouse button is down
					std::vector<logicBlock*>::reverse_iterator itr = executionListSub2.rbegin();
					for(; itr != executionListSub2.rend(); itr++)
					{
						if((*itr)->enumInstruction != DO_NOT_PROCESS)
						{
							if((*itr)->checkInBounds(x, y, instructionBlockW, instructionBlockH))
							{
								draggedBlock = new logicBlock(*(*itr));
								isMouseDragging = true;

								delete (*itr);
								executionListSub2.erase(itr.base() - 1);
								break;
							}
						}
					}
				}
			}
		}
	}

	isButtonBeingClicked = false;
}

void LogicInterface::SetExecuteHandler(CFunctionPointer3R<bool, std::vector<logicBlock*>, std::vector<logicBlock*>, std::vector<logicBlock*>> clickHandler)
{
	mExecuteHandler = clickHandler;
}

void LogicInterface::SetAbortHandler(CFunctionPointer0R<bool> clickHandler)
{
	mAbortHandler = clickHandler;
}

void LogicInterface::SetResetHandler(CFunctionPointer0R<bool> resetHandler)
{
	mResetHandler = resetHandler;
}

void LogicInterface::GetCurrentMapLogicBank()
{
	logicBank = GameVars->GetCurrentMapLogicBank();
}

void LogicInterface::GetCurrentLevelBytes()
{
	mapByteLimit = GameVars->getCurrentLevelBytes();
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
	if(curInstrTab == TAB_MAIN)
	{
		curExecutionListYOffset = &executionListYOffset;
	}
	else if(curInstrTab == TAB_SUB1)
	{
		curExecutionListYOffset = &executionListSub1YOffset;
	}
	else if(curInstrTab == TAB_SUB2)
	{
		curExecutionListYOffset = &executionListSub2YOffset;
	}

	isButtonBeingClicked = true;
	(*curExecutionListYOffset) += (instructionSpacing + instructionBlockH);
	if((*curExecutionListYOffset) > 0)
		(*curExecutionListYOffset) = 0;

	return true;
}

//============================================
// ExecutionList Down Arrow Callback
bool LogicInterface::ExecutionListDownArrowButtonClick()
{
	std::vector<logicBlock*>* curExecutionList = NULL;
	if(curInstrTab == TAB_MAIN)
	{
		curExecutionListYOffset = &executionListYOffset;
		curExecutionList = &executionList;
	}
	else if(curInstrTab == TAB_SUB1)
	{
		curExecutionListYOffset = &executionListSub1YOffset;
		curExecutionList = &executionListSub1;
	}
	else if(curInstrTab == TAB_SUB2)
	{
		curExecutionListYOffset = &executionListSub2YOffset;
		curExecutionList = &executionListSub2;
	}

	int i = (*curExecutionList).size();
	int numRows = i / instructionListNumColumns;
	if((i % instructionListNumColumns) > 0)
		numRows++;
	//int overallHeight = (instructionSpacing) + ((i / instructionListNumRowsOnScreen) * instructionBlockH) + ((i / instructionListNumRowsOnScreen) * instructionSpacing);
	int overallHeight = instructionSpacing + (numRows *  instructionBlockH) + (numRows * instructionSpacing);
	isButtonBeingClicked = true;

	(*curExecutionListYOffset) -= (instructionSpacing + instructionBlockH);
	int cmp1 = (*curExecutionListYOffset) + overallHeight;
	int cmp2 = instructionListBox.height;
	if((*curExecutionListYOffset) + overallHeight < instructionListBox.height - 50)
	{
		(*curExecutionListYOffset) += (instructionSpacing + instructionBlockH);
	}
	return true;
}

//============================================
// Execute Button Callback
bool LogicInterface::ExecuteButtonClick()
{
	if(executionList.size() > 1)
	{		
		if(mExecuteHandler)
		{
			isExecuting = true;
			return mExecuteHandler(executionList, executionListSub1, executionListSub2);
		}
	}
	return false;
}

bool LogicInterface::MainTabButtonClick()
{
	curInstrTab = TAB_MAIN;
	return false;
}

bool LogicInterface::Sub1TabButtonClick()
{
	curInstrTab = TAB_SUB1;
	return false;
}

bool LogicInterface::Sub2TabButtonClick()
{
	curInstrTab = TAB_SUB2;
	return false;
}


void LogicInterface::ClearExecutionList()
{
	executionListYOffset = 0;
	executionListSub1YOffset = 0;
	executionListSub2YOffset = 0;
	curInstrTab = TAB_MAIN;

	executionList.clear();
	executionList.push_back(new logicBlock((*GameVars->getPlaceInstructionBlock())));
	executionList.back()->curButtonState = BS_ACTIVE;
	
	executionListSub1.clear();
	executionListSub1.push_back(new logicBlock((*GameVars->getPlaceInstructionBlock())));
	executionListSub1.back()->curButtonState = BS_ACTIVE;

	executionListSub2.clear();
	executionListSub2.push_back(new logicBlock((*GameVars->getPlaceInstructionBlock())));
	executionListSub2.back()->curButtonState = BS_ACTIVE;
}

void LogicInterface::ResetExecutionMode()
{
	isExecuting = false;
}

bool LogicInterface::CommandAdvanced(instructionTab instrTab, logicBlock* curBlock)
{
	curInstrTab = instrTab;
	std::vector<logicBlock*>* curExecutionList = NULL;
	if(curInstrTab == TAB_MAIN)
	{
		curExecutionList = &executionList;
		curExecutionListYOffset = &executionListYOffset;
	}
	else if(curInstrTab == TAB_SUB1)
	{
		curExecutionList = &executionListSub1;
		curExecutionListYOffset = &executionListSub1YOffset;

	}
	else if(curInstrTab == TAB_SUB2)
	{
		curExecutionList = &executionListSub2;
		curExecutionListYOffset = &executionListSub2YOffset;
	}

	std::vector<logicBlock*>::iterator itr = (*curExecutionList).begin();
	for(; itr != (*curExecutionList).end(); itr++)
	{
		(*itr)->curButtonState = BS_ACTIVE;
		// TODO: When tracking execution, make the command list scrolling 
			// stay with the current highlighted command
	}
	curBlock->curButtonState = BS_HIGHLIGHTED;
	
	return true;
}


//============================================
// Abort Button Callback
bool LogicInterface::AbortButtonClick()
{
	isExecuting = false;
	if(mAbortHandler)
	{
		return mAbortHandler();
	}
	return false;
}

//============================================
// Reset Button Callback
bool LogicInterface::ResetButtonClick()
{
	//ClearExecutionList();
	// Clear the status of the instructions so there
	// is no highlighted square.
	std::vector<logicBlock*>::iterator itr = executionList.begin();
	for(; itr != executionList.end(); itr++)
	{
		(*itr)->curButtonState = BS_ACTIVE;
	}

	itr = executionListSub1.begin();
	for(; itr != executionListSub1.end(); itr++)
	{
		(*itr)->curButtonState = BS_ACTIVE;
	}

	itr = executionListSub2.begin();
	for(; itr != executionListSub2.end(); itr++)
	{
		(*itr)->curButtonState = BS_ACTIVE;
	}

	isExecuting = false;
	if(mResetHandler)
	{
		return mResetHandler();
	}
	return false;
}


//============================================
// Clear Button Callback
bool LogicInterface::ClearButtonClick()
{
	ClearExecutionList();
	return true;
}