#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include ".\..\GameState.h"
#include ".\..\FunctionPointer.h"
#include <iostream>
#include ".\..\oglTexture2D.h"

using namespace BE;

class MainMenuState : public GameState
{
public:
	MainMenuState() {};
	MainMenuState(GameStateManager &Parent, int newID) : GameState(Parent, newID),
		img(NULL)
	{
		img = new oglTexture2D();
		/*if(img != NULL)
			img->loadImage("logoprojekt1narrow.png", 1024, 150);
		img->mY = 50;*/

		myMenu = new MenuSys(220, 250, "blankmenu.png", Auto);
		myMenu->addButton("buttons\\startnewgame.png", "buttons\\startnewgamehover.png", "buttons\\startnewgamehover.png", CreateFunctionPointer0R(this, &MainMenuState::StartNewGameCallback));
		myMenu->addButton("buttons\\profilemanagement.png", "buttons\\profilemanagementhover.png", "buttons\\profilemanagementhover.png", CreateFunctionPointer0R(this, &MainMenuState::ProfileManagerCallback));
		myMenu->addButton("buttons\\loadgame.png", "buttons\\loadgamehover.png", "buttons\\loadgamehover.png", CreateFunctionPointer0R(this, &MainMenuState::LoadGameCallback));
		myMenu->addButton("buttons\\credits.png", "buttons\\creditshover.png", "buttons\\creditshover.png", CreateFunctionPointer0R(this, &MainMenuState::Credits));
		myMenu->addButton("buttons\\quit.png", "buttons\\quithover.png", "buttons\\quithover.png", CreateFunctionPointer0R(this, &MainMenuState::Quit));
	}

	bool Update();
	bool Draw();
	bool HandleClick();
	void MainMenuState::processMouse(int x, int y);
	void MainMenuState::processMouseClick(int button, int state, int x, int y);
	bool StartNewGameCallback();
	bool ProfileManagerCallback();
	bool LoadGameCallback();
	bool Quit();
	bool Credits();

private:
	oglTexture2D* img;
	// add private stuff here
	
};

#endif

