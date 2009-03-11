#ifndef LEVELSELECTSTATE_H
#define LEVELSELECTSTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"
#include ".\..\oglTexture2D.h"
#include ".\..\playGame.h"

class LevelSelectState : public GameState
{
public:
	LevelSelectState() {};
	LevelSelectState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		playerCurrentLevel = GameVars->getPlayerMaxLevel();
			
		//display a menu that shows info and contains advance and exit buttons
		img = new oglTexture2D();
		if(img != NULL)
			img->loadImage("statescreens\\mainmenu.png", 1024, 120);
		img->mY = 618;
		

		myMenu = new MenuSys(250, 50, "blank.png", None);
		myMenu->addButton("arrow_left.png", "arrow_lefthover.png", "arrow_lefthover.png", CreateFunctionPointer0R(this, &LevelSelectState::decrement));
		myMenu->setLastButtonDimensions(100, 100);
		myMenu->setLastButtonPosition(350, 400);
		myMenu->addButton("arrow_right.png",	 "arrow_righthover.png", "arrow_righthover.png", CreateFunctionPointer0R(this, &LevelSelectState::increment));
		myMenu->setLastButtonDimensions(100, 100);
		myMenu->setLastButtonPosition(600, 400);
		myMenu->addButton("buttons\\startthislevel.png",	 "buttons\\startthislevelhover.png", "buttons\\startthislevelhover.png", CreateFunctionPointer0R(this, &LevelSelectState::selectLevel));
		myMenu->setLastButtonDimensions(100, 100);
		myMenu->setLastButtonPosition(480, 400);
		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	bool LevelSelectState::Update();
	bool LevelSelectState::Draw();
	bool LevelSelectState::selectLevel();
	bool LogicViewCallback();
	bool increment();
	bool decrement();
	int  getPlayerCurrentLevel();
	

private:
	oglTexture2D* img;
	int playerCurrentLevel;
	vector<levelData*> levelList;
	// add private stuff here

};

#endif