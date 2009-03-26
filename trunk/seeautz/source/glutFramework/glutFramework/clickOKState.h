#ifndef CLICKOKSTATE_H
#define CLICKOKSTATE_H

#include "GameState.h" 
#include ".\States\MainMenuState.h"
#include "oglTexture2D.h"
#include "oglGameVars.h"
#include<fstream>
#include<iostream>
#include <string>

using namespace std;

class clickOKState : public GameState
{
public:
	clickOKState();
	clickOKState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		myMenu = new MenuSys(250, 250, "blankmenu.png");
		myMenu->addButton("buttons\\ok.png", "buttons\\okhover.png", "buttons\\okhover.png", CreateFunctionPointer0R(this, &clickOKState::clickOKCallback));
		myMenu->setLastButtonDimensions(100, 100);
		myMenu->setLastButtonPosition((int)1024/2, 400);
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
