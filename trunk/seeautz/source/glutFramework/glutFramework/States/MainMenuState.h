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
		if(img != NULL)
			img->loadImage("..\\Content\\statescreens\\mainmenu.png", 1024, 120);
		img->mY = 618;

		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\startnewgame.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &MainMenuState::StartNewGameCallback));
		myMenu->addButton("..\\Content\\buttons\\profilemanagement.png", "button2down.png", "button2over.png", CreateFunctionPointer0R(this, &MainMenuState::ProfileManagerCallback));
		myMenu->addButton("..\\Content\\buttons\\loadgame.png", "button3down.png", "button3over.png", CreateFunctionPointer0R(this, &MainMenuState::LoadGameCallback));
		myMenu->addButton("..\\Content\\buttons\\options.png", "button4down.png", "button4over.png", CreateFunctionPointer0R(this, &MainMenuState::OptionsCallback));
	}

	bool Update();
	bool Draw();
	bool HandleClick();
	void MainMenuState::processMouse(int x, int y);
	void MainMenuState::processMouseClick(int button, int state, int x, int y);
	bool StartNewGameCallback();
	bool ProfileManagerCallback();
	bool LoadGameCallback();
	bool OptionsCallback();

private:
	oglTexture2D* img;
	// add private stuff here
	
};

#endif

