#ifndef CLICKOKSTATE_H
#define CLICKOKSTATE_H

#include "GameState.h" 
#include ".\States\MainMenuState.h"
//#include "LevelSelectState.h"
//#include "..\playGame.h"
#include "oglTexture2D.h"
#include "oglGameVars.h"
#include<fstream>
#include<iostream>
#include <string>

using namespace std;

class clickOKState : public GameState
{
public:
	clickOKState() 
	{
		selected = false;
		deleted = false;
		created = false;
		int check = 0;
		check = GameVars->getPMStatus();
		switch(check)
		{
		case 0:
			selected = true;
			break;
		case 1:
			deleted = true;
			break;
		case 2:
			created = true;
			break;
		default:
			break;
		}

	};
	clickOKState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		img = new oglTexture2D();
		if(img != NULL)
			img->loadImage("statescreens\\loadgame.png", 1024, 120);
		img->mY = 618;

		myMenu = new MenuSys(220, 250, "blankmenu.png");
		myMenu->addButton("buttons\\ok.png", "buttons\\okhover.png", "buttons\\okhover.png", CreateFunctionPointer0R(this, &clickOKState::clickOKCallback));

		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	bool clickOKState::Update();
	bool clickOKState::Draw();
	bool clickOKCallback();
	bool selected;
	bool created;
	bool deleted;

private:
	oglTexture2D* img;
	std::string tempString;
	
	// add private stuff here

};

#endif
