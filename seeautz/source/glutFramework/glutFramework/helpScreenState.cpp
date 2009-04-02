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
	double scale = 0.5;
	glColor3ub(0, 0, 0);
	int tempX;
	int tempY;

	tempStringStream.str("");
	tempStringStream << "Page " << pageNum+1 << "/" << maxPage+1;
	GameVars->fontArial24.drawText(750, textOffsetY, tempStringStream.str().c_str());

	// this entire function should draw information in the middle of the background
	switch(pageNum)
	{
	case 0: // condensed help
		glColor3ub(0, 0, 0);
		GameVars->fontArial24.drawText(textOffsetX, textOffsetY, "Overview");
		offsetAmt++;offsetAmt++;
		GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "Stuff");
		offsetAmt++;
		break;
	case 1: // table of contents
		glColor3ub(0, 0, 0);
		GameVars->fontArial24.drawText(textOffsetX, textOffsetY, "Table of Contents");
		offsetAmt++;offsetAmt++;
		GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "Stuff");
		offsetAmt++;
		break;
	case 2:	// basic game concepts
		glColor3ub(0, 0, 0);
		GameVars->fontArial24.drawText(textOffsetX, textOffsetY, "Basic Game Contents");
		offsetAmt++;offsetAmt++;
		GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "Stuff");
		offsetAmt++;
		break;
	case 3: // user interface
		glColor3ub(0, 0, 0);
		GameVars->fontArial24.drawText(textOffsetX, textOffsetY, "User Interface");
		offsetAmt++;offsetAmt++;
		GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "Stuff");
		offsetAmt++;
		break;
	case 4:	// instructions help
		glColor3ub(0, 0, 0);
		GameVars->fontArial24.drawText(textOffsetX, textOffsetY, "Instructions");
		offsetAmt++;offsetAmt++;
		GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "Stuff");
		offsetAmt++;
		
		break;
	case 5: // scoring and subroutines
		glColor3ub(0, 0, 0);
		GameVars->fontArial24.drawText(textOffsetX, textOffsetY, "Scoring and Subroutines");
		offsetAmt++;offsetAmt++;
		GameVars->fontArial18.drawText(textOffsetX, textOffsetY + offsetAmt*textSpacing, "Stuff");
		offsetAmt++;
		break;
	case 6: // tile list page 1?
		glColor3ub(0, 0, 0);
		GameVars->fontArial24.drawText(textOffsetX, textOffsetY, "Tiles (page 1)");
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
		GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "enter or pass through");
		offsetAmt++;
		GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "this tile.");
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
		GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "tile from a tile that");
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

		break;
	case 7: // tile list page 2?
		glColor3ub(0, 0, 0);
		GameVars->fontArial24.drawText(textOffsetX, textOffsetY, "Tiles (page 2)");
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
		break;

	case 8: // tile list page 3?
		glColor3ub(0, 0, 0);
		GameVars->fontArial24.drawText(textOffsetX, textOffsetY, "Tiles (page 3)");
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
		GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "starts the leve.");
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
		break;

	case 9: // tile list page 4?
		glColor3ub(0, 0, 0);
		GameVars->fontArial24.drawText(textOffsetX, textOffsetY, "Tiles (page 4)");
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
		GameVars->fontArial12.drawText(textOffsetX+tempX, textOffsetY+55 + offsetAmt*textSpacing, "starts the leve.");
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
		exit(0);
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
	for(int x = 0; x < numTileTypes; x++)
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