#include "helpScreenState.h" 
#include "GameStateManager.h"

bool helpScreenState::Update()
{
	GSM->setAllButTopPassive();

	if(myMenu != NULL)
		myMenu->Update();

	return true;
}

bool helpScreenState::Draw()
{
	clearBackground();
	logoImage->drawImage();
	backgroundImage->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();

	offsetAmt = 0;
	scale = 0.5;
	glColor3ub(0, 0, 0);

	tempStringStream.str("");
	tempStringStream << "Page " << pageNum+1 << "/" << maxPage+1;
	GameVars->fontArial24.drawText(750, textOffsetY, tempStringStream.str().c_str());

	// this entire function should draw information in the middle of the background
	switch(pageNum)
	{
	case 0: // condensed help
		drawPage0();
		break;
	case 1: // user interface
		drawPage1();
		break;
	case 2:	// instructions help
		drawPage2();
		break;
	case 3: // scoring and subroutines
		drawPage3();
		break;
	case 4: // tile list page 1?
		drawPage4();
		break;
	case 5: // tile list page 2?
		drawPage5();
		break;
	case 6: // tile list page 3?
		drawPage6();
		break;
	case 7: // tile list page 4?
		drawPage7();
		break;

	default:
		break;
	}
	return true;
}

bool helpScreenState::next()
{
	pageNum++;
	if(pageNum > maxPage)
	{
		pageNum = 0;
	}
	return true;
}

bool helpScreenState::previous()
{
	pageNum--;
	if(pageNum < 0)
	{
		pageNum = maxPage;
	}
	return true;
}

bool helpScreenState::clickOKCallback()
{
	this->setStatus(DeleteMe);
	return true;
}

void helpScreenState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void helpScreenState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}

void helpScreenState::keyboardInput(unsigned char c, int x, int y)
{
	switch(c)
	{
	case 27:
		this->setStatus(DeleteMe);
		break;
	default:
		break;
	}
}

void helpScreenState::init()
{
	// load in info that will need to be displayed
	// instructions
	// tiles

	// vector of tiles
	mapTile* temp;
	for(int x = 0; x <= numTileTypes; x++)
	{
		temp = new mapTile((tileTypeEnum)x, true);
		tileList.push_back(temp);
	}

	// load tile images
	oglTexture2D* tempTile;
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TEmpty.png",		 144, 144); tileImages.push_back(tempTile);		
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TDefault.png",	 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TRaised1.png",	 144, 144); tileImages.push_back(tempTile);
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TRaised2.png",	 144, 144); tileImages.push_back(tempTile);
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TRaised3.png",	 144, 144); tileImages.push_back(tempTile);
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TRaised4.png",	 144, 144); tileImages.push_back(tempTile);
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/THalfTopL.png",	 144, 144); tileImages.push_back(tempTile);
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/THalfTopR.png",	 144, 144); tileImages.push_back(tempTile);
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/THalfBottomL.png", 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/THalfBottomR.png", 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TGap.png",		 144, 144); tileImages.push_back(tempTile);		
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TElectric.png",	 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TElectricTL.png",	 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TElectricTR.png",	 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TElectricBL.png",	 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TElectricBR.png",	 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TIce.png",		 144, 144); tileImages.push_back(tempTile);		
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TWater.png",		 144, 144); tileImages.push_back(tempTile);		
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TSwitchTL.png",	 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TSwitchTR.png",	 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TSwitchBL.png",	 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TSwitchBR.png",	 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TSwitch.png",		 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TProgramTL.png",	 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TProgramTR.png",	 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TProgramBL.png",	 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TProgramBR.png",	 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TProgram.png",	 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TBreakableTL.png", 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TBreakableTR.png", 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TBreakableBL.png", 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TBreakableBR.png", 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TSolid.png",		 144, 144); tileImages.push_back(tempTile);		
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TBreakable.png",	 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TStart.png",		 144, 144); tileImages.push_back(tempTile);		
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TEnd.png",		 144, 144); tileImages.push_back(tempTile);		
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TDoorTL.png",		 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TDoorTR.png",		 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TDoorBL.png",		 144, 144); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TDoorBR.png",		 144, 144); tileImages.push_back(tempTile);			
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TTeleport.png",	 144, 144); tileImages.push_back(tempTile);	

	// robot
	robotImage = new oglTexture2D;
	robotImage->loadImage("object\\robotDefault.png", 195*0.45, 110*2*0.45);

	logicInterfaceHelp = new oglTexture2D;
	logicInterfaceHelp->loadImage("interfacehelp.png", 725, 403);
}

bool helpScreenState::drawTile(tileTypeEnum nType, int txPos, int tyPos, double scale, bool isActive)
{
	glClearColor(0, 0, 0, 0);
	oglTexture2D* toDraw;

	toDraw = tileImages[nType];

	int tempdx = toDraw->dX;
	int tempdy = toDraw->dY;

	toDraw->dX *= scale;
	toDraw->dY *= scale;

	toDraw->mX = txPos;
	toDraw->mY = tyPos;

	if(isActive)
		toDraw->drawImageSegment(0.0, 0.0, 0.5, 0.0, 0.0, 1.0, 0.5, 1.0, 1);
	else
		toDraw->drawImageSegment(0.5, 0.0, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1);

	toDraw->dX = tempdx;
	toDraw->dY = tempdy;

	return true;
}

void helpScreenState::drawPage0()
{
	glColor3ub(0, 0, 0);
	GameVars->fontArial18.drawText(textOffsetX, textOffsetY, "Help Screen - Overview");
	offsetAmt++;offsetAmt++;
	offsetAmt++;offsetAmt++;
	GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing2, 
		"The objective of the game is to bring your robot from the");
	offsetAmt++;
	GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing2, 
		"start square to the end square.  Program the robot with");
	offsetAmt++;
	GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing2, 
		"sequential commands to meet this goal.");
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	drawTile(TStart,  300, 400, 0.5, true);
	drawTile(TEnd,   475, 400, 0.5, true);
	robotImage->mX = 650;
	robotImage->mY = 400;
	tempX = robotImage->dX;
	tempY = robotImage->dY;
	robotImage->dX *= 0.75;
	robotImage->dY *= 0.75;
	robotImage->drawImageSegment(0.0, 0.0,	0.25, 0.0, 0.0, 1.0,  0.25, 1.0, 1);
	glColor3ub(0, 0, 0);
	GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing2, 
		"             Start Square      End Square          Robot");
	robotImage->dX = tempX;
	robotImage->dY = tempY;
	offsetAmt++;
}
void helpScreenState::drawPage1() // user interface
{
	glColor3ub(0, 0, 0);
	GameVars->fontArial18.drawText(textOffsetX, textOffsetY, "Help Screen - User Interface");
	offsetAmt++;		offsetAmt++;
	logicInterfaceHelp->mX = 150;
	logicInterfaceHelp->mY = 285;
	logicInterfaceHelp->drawImage();
}
void helpScreenState::drawPage2() // instructions
{
	glColor3ub(0, 0, 0);
	GameVars->fontArial18.drawText(textOffsetX, textOffsetY, "Help Screen - Instructions");
	//GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "Stuff");
	vector<logicBlock*>* logicBank = GameVars->Instance()->getAllLogicBlocks();

	// draw all the instructions
	for(int x = 0; x < (int)logicBank->size(); x++)
	{
		(*logicBank)[x]->blockTexture->mX = 200;
		(*logicBank)[x]->blockTexture->mY = 290 + 34*x;
		(*logicBank)[x]->blockTexture->drawImageSegment(0.0, 0.0, (double)1/3, 0.0, 0.0, 1.0, (double)1/3, 1.0, 1, 35, 35);
	}

	glColor3ub(0, 0, 0);
	// text for column 1
	textSpacing = 11.5;
	tempX = 100; // extra offset for text
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "Move Forward - Use this instruction to move forward one tile.");
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "-----------------------------------------------------------------------");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "Move Forward (Until Unable) - Use this instruction to move forward until");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "you are unable to move forward any more, or die.");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "-----------------------------------------------------------------------");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "Rotate Left - Use this instruction to rotate left.");
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "-----------------------------------------------------------------------");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "Rotate Right - Use this instruction to rotate right.");
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "-----------------------------------------------------------------------");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "Punch - Use this instruction to break breakable walls.");
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "-----------------------------------------------------------------------");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "Climb - Use this instruction to climb up to a higher level.");
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "-----------------------------------------------------------------------");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "Crouch - Use this instruction to crawl through small holes.");
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "-----------------------------------------------------------------------");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "Jump - Use this instruction to jump over most obstacles.");
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "-----------------------------------------------------------------------");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "Activate - Use this instruction to activate Doors, Switches");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "and to use Reprogram Tiles.");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "-----------------------------------------------------------------------");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "Sub 1 - Use this instruction to call Subroutine 1.");
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "-----------------------------------------------------------------------");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "Sub 2 - Use this instruction to call Subroutine 2.");
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "-----------------------------------------------------------------------");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing-10, "Stop - This command stops all processing.");
	offsetAmt++;

	textSpacing = 16;	

	// now for text

}
void helpScreenState::drawPage3() // scoring and subroutines
{
	glColor3ub(0, 0, 0);
	GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "Help Screen - Scoring and Subs");
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "Scoring");
	offsetAmt++;
	GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing2, "Scoring is based off of how much memory is used versus how");
	offsetAmt++;
	GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing2, "much memory is available.  For example, you get more points");
	offsetAmt++;
	GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing2, "for finishing a level with 16 out of 32 bytes used than you");
	offsetAmt++;
	GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing2, "do for finishing a level with 50 out of 64 bytes used.");
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing2, "Subroutines");
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "Subroutines are a way to save memory.   When you place commands into subroutines");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "they take up the same amount of space as if you were to place the commands in main.");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "The difference is that these commands can now be used at a minimal cost by simply");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "using the subroutine they were placed in.  For example: if you wanted to move forward");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "16 times, you could do that by putting in 16 move forward commands taking up a total");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "of 32 bytes, or you could put four move forward commands into sub 1 using up 8 bytes,");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "then put sub1 into main four times using up another 8 bytes using a total of 16 bytes");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "to perform the same command sequence.");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "You cannot use a subroutine inside of another subroutine.");
	offsetAmt++;
	
}
void helpScreenState::drawPage4() // tile list page 1
{
	glColor3ub(0, 0, 0);
	GameVars->fontArial18.drawText(textOffsetX, textOffsetY, "Help Screen - Tiles (page 1)");
	offsetAmt++;offsetAmt++;
	/*GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "Stuff");
	offsetAmt++;*/

	// draw the tiles
	scale = 0.40;
	// column 1
	// draw blackness behind the empty square
	//solidBlack->drawImage(160, 55, textOffsetX-10, textOffsetY+55+15);

	for(int x = 0; x < 6; x++)
	{
		drawTile(tileList[x]->getType(), (int)textOffsetX              , (int)(textOffsetY+55+ x*160*scale), scale, true);
		drawTile(tileList[x]->getType(), (int)(textOffsetX + 200*scale), (int)(textOffsetY+55+ x*160*scale), scale, false);
	}

	glColor3ub(0, 0, 0);
	offsetAmt-=2;
	// text for column 1
	tempX = 160; // extra offset for text
	tempY = offsetAmt;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Empty Tile - Empty");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Space, you can not");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "enter, jump over or  ");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "pass through this tile.");
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Default Tile - You");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "can always safely");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "move through this");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "tile.");
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Raised Tiles - You");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "can climb to these");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "tiles from a tile that");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "is one level lower or");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "walk off of it to any");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "tile that the same");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "height or lower.");
	offsetAmt++;
	offsetAmt++;
	// column 2
	for(int x = 6; x < 14; x++)
	{
		if(x == THalfBottomL)
		{
			x+=2;
		}
		if(x < THalfBottomL)
		{
			drawTile(tileList[x]->getType(), (int)textOffsetX+375              , (int)(textOffsetY+55+ (x-6)*160*scale), scale, true);
			drawTile(tileList[x]->getType(), (int)(textOffsetX+375 + 200*scale), (int)(textOffsetY+55+ (x-6)*160*scale), scale, false);
		}
		else
		{
			drawTile(tileList[x]->getType(), (int)textOffsetX+375              , (int)(textOffsetY+55+ ((x-6)-2)*160*scale), scale, true);
			drawTile(tileList[x]->getType(), (int)(textOffsetX+375 + 200*scale), (int)(textOffsetY+55+ ((x-6)-2)*160*scale), scale, false);
		}
	}

	glColor3ub(0, 0, 0);
	// text for column 2
	offsetAmt = tempY;
	tempX = 535; // extra offset for text
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Crouch Tiles - If facing");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "the gap, you can crouch");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "to move through the");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "tile to appear on the ");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "other side of this tile.");
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Gap - Moving into this");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "tile will kill your robot.");
	offsetAmt++; 
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Electric Tile - Moving");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "into this tile while it");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "is active will kill your");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "robot.");
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Electric Walls -");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Touching the wall while");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "it is active will kill");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "your robot. You can");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "move through these");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "tiles safely.");
	offsetAmt++;
}

void helpScreenState::drawPage5() // tile list page 2
{
	glColor3ub(0, 0, 0);
	GameVars->fontArial18.drawText(textOffsetX, textOffsetY, "Help Screen - Tiles (page 2)");
	offsetAmt++;offsetAmt++;

	// draw the tiles
	scale = 0.40;

	// column 1
	tempX = 14;
	for(int x = tempX; x < tempX + 6; x++)
	{
		drawTile(tileList[x]->getType(), (int)textOffsetX              , (int)(textOffsetY+55+ (x-tempX)*160*scale), scale, true);
		drawTile(tileList[x]->getType(), (int)(textOffsetX + 200*scale), (int)(textOffsetY+55+ (x-tempX)*160*scale), scale, false);
	}

	glColor3ub(0, 0, 0);
	offsetAmt-=2;
	// text for column 1
	tempX = 160; // extra offset for text
	tempY = offsetAmt;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Electric Walls -");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Touching the wall while");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "it is active will kill");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "your robot. You can");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "move through these");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "tiles safely.");
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Ice Tile - Your");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "robot will slide");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "through this tile.");
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Water Tile - Your");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "robot will die if");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "it enters this tile.");
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Switch Tiles - You");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "can ACTIVATE a switch");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "by facing the dark");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "edge of the tile and");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "using ACTIVATE.");
	offsetAmt++;
	offsetAmt++;

	// column 2
	tempX = 14 + 6;
	for(int x = tempX; x < tempX + 6; x++)
	{
		drawTile(tileList[x]->getType(), (int)textOffsetX +375             , (int)(textOffsetY+55+ (x-tempX)*160*scale), scale, true);
		drawTile(tileList[x]->getType(), (int)(textOffsetX+375 + 200*scale), (int)(textOffsetY+55+ (x-tempX)*160*scale), scale, false);
	}

	glColor3ub(0, 0, 0);
	// text for column 2
	offsetAmt = tempY;
	tempX = 535; // extra offset for text
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Switch Tile - You");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "can ACTIVATE a switch");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "by facing the dark");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "edge of the tile and");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "using ACTIVATE.");
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;

	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Switch Tile - You");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "can ACTIVATE this");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "switch tile by");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "using ACTIVATE.");
	offsetAmt++;
	offsetAmt++;

	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Reprogram Tile - These");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "act as save points. By");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "using ACTIVATE, your");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "robot's start spot is");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "reset to the tile's");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "position and you can");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "re-access your robot's");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "memory.");
	offsetAmt++;
}
void helpScreenState::drawPage6() // tile list page 3
{
	glColor3ub(0, 0, 0);
	GameVars->fontArial18.drawText(textOffsetX, textOffsetY, "Help Screen - Tiles (page 3)");
	offsetAmt++;offsetAmt++;

	// draw the tiles
	scale = 0.40;

	// column 1
	tempX = 26;
	for(int x = tempX; x < tempX + 6; x++)
	{
		drawTile(tileList[x]->getType(), (int)textOffsetX              , (int)(textOffsetY+55+ (x-tempX)*160*scale), scale, true);
		drawTile(tileList[x]->getType(), (int)(textOffsetX + 200*scale), (int)(textOffsetY+55+ (x-tempX)*160*scale), scale, false);
	}

	glColor3ub(0, 0, 0);
	offsetAmt-=2;
	// text for column 1
	tempX = 160; // extra offset for text
	tempY = offsetAmt;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Reprogram Tile - These");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "act as save points. By");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "using ACTIVATE, your");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "robot's start spot is");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "reset to the tile's");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "position and you can");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "re-access your robot's");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "memory.");
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Breakable Walls -");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "You can PUNCH a wall");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "to remove the wall,");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "this will also break");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "or deactivate whatever");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "is behind the wall.");
	offsetAmt++;

	// column 2
	tempX = 26+6;
	for(int x = tempX; x < tempX + 6; x++)
	{
		drawTile(tileList[x]->getType(), (int)textOffsetX +375             , (int)(textOffsetY+55+ (x-tempX)*160*scale), scale, true);
		drawTile(tileList[x]->getType(), (int)(textOffsetX+375 + 200*scale), (int)(textOffsetY+55+ (x-tempX)*160*scale), scale, false);
	}

	glColor3ub(0, 0, 0);
	// text for column 2
	offsetAmt = tempY;
	tempX = 535; // extra offset for text
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Solid Tile - This");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "tile is a solid wall.");
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;

	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Breakable Tile - You");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "can PUNCH this tile");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "to destroy it.");
	offsetAmt++;
	offsetAmt++;

	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Start Tile - This");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "is where your robot");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "starts the level.");
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "End Tile - The");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "goal is to reach");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "this tile while it");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "is active (Red).");
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Door Tiles - You");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "can only pass through");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "a door if it is open.");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "You can use switches");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "or ACTIVATE to open");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "a door.");
	offsetAmt++;
	offsetAmt++;
}
void helpScreenState::drawPage7() // tile list page 4
{
	glColor3ub(0, 0, 0);
	GameVars->fontArial18.drawText(textOffsetX, textOffsetY, "Help Screen - Tiles (page 4)");
	offsetAmt++;offsetAmt++;

	// draw the tiles
	scale = 0.40;

	// column 1
	tempX = 38;
	for(int x = tempX; x <= 40; x++)
	{
		drawTile(tileList[x]->getType(), (int)textOffsetX              , (int)(textOffsetY+55+ (x-tempX)*160*scale), scale, true);
		drawTile(tileList[x]->getType(), (int)(textOffsetX + 200*scale), (int)(textOffsetY+55+ (x-tempX)*160*scale), scale, false);
	}

	glColor3ub(0, 0, 0);
	offsetAmt-=2;
	// text for column 1
	tempX = 160; // extra offset for text
	tempY = offsetAmt;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Door Tiles - You");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "can only pass through");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "a door if it is open.");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "You can use switches");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "or ACTIVATE to open");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "a door.");
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Teleporter Tile - When");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "you walk into a teleporter");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "it will bring your robot");
	offsetAmt++;
	GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "somewhere else on the map.");
	offsetAmt++;
	offsetAmt++;

	// column 2
	/*tempX = 38;
	for(int x = 38; x < 41; x++)
	{
		drawTile(tileList[x]->getType(), (int)textOffsetX +375             , (int)(textOffsetY+55+ (x-tempX)*160*scale), scale, true);
		drawTile(tileList[x]->getType(), (int)(textOffsetX+375 + 200*scale), (int)(textOffsetY+55+ (x-tempX)*160*scale), scale, false);
	}*/

	glColor3ub(0, 0, 0);
	// text for column 2
	offsetAmt = tempY;
	//tempX = 535; // extra offset for text
	//GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "Solid Tile - This");
	//offsetAmt++;
}

helpScreenState::~helpScreenState()
{
	vector<mapTile*>::iterator tileListI = tileList.begin();

	for(;tileListI < tileList.end(); tileListI++)
	{
		delete (*tileListI);
	}

	vector<oglTexture2D*>::iterator tileImagesI = tileImages.begin();

	for(;tileImagesI < tileImages.end(); tileImagesI++)
	{
		delete (*tileImagesI);
	}

	delete robotImage;
	delete logicInterfaceHelp;
	delete myMenu;
}