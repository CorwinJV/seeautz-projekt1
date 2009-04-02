#ifndef HELPSCREENSTATE_H
#define HELPSCREENSTATE_H

#include "GameState.h" 
#include "oglTexture2D.h"
#include "oglGameVars.h"
#include <string>
#include <sstream>
#include <vector>
#include "mapTile.h"

using namespace std;

class helpScreenState : public GameState
{
private:
	// ui stuff
	bool next();
	bool previous();
	bool clickOKCallback();

	// init
	void init();

	// page display stuff
	int pageNum;
	int maxPage;
	std::string tempString;
	std::stringstream tempStringStream;
	int textOffsetX;
	int textOffsetY;
	int offsetAmt;
	int textSpacing;

	// tile stuff
	vector<mapTile*> tileList;
	std::vector<oglTexture2D*> tileImages;
	bool drawTile(tileTypeEnum nType, int txPos, int tyPos, double scale, bool isActive);

public:
	helpScreenState();
	helpScreenState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		pageNum = 0;
		textOffsetX = backgroundImage->mX + 50;
		textOffsetY = backgroundImage->mY + 40;
		offsetAmt = 0;
		textSpacing = 16;
		maxPage = 8;
		myMenu = new MenuSys(250, 250, "blank.png", None);
		myMenu->addButton("arrow_right.png", "arrow_righthover.png", "arrow_righthover.png", CreateFunctionPointer0R(this, &helpScreenState::next));
		myMenu->setLastButtonDimensions(50, 50);
		myMenu->setLastButtonPosition(830-140, textOffsetY-20);
		myMenu->addButton("arrow_left.png", "arrow_lefthover.png", "arrow_lefthover.png", CreateFunctionPointer0R(this, &helpScreenState::previous));
		myMenu->setLastButtonDimensions(50, 50);
		myMenu->setLastButtonPosition(770-140, textOffsetY-20);
		myMenu->addButton("buttons\\exit.png", "buttons\\exithover.png", "buttons\\exithover.png", CreateFunctionPointer0R(this, &helpScreenState::clickOKCallback));
		myMenu->setLastButtonDimensions(100, 50);
		myMenu->setLastButtonPosition(660-140, textOffsetY-20);
		
		//Update();
		init();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	void keyboardInput(unsigned char c, int x, int y);
	bool Update();
	bool Draw();

};

#endif
