#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include ".\..\GameState.h"
#include ".\..\FunctionPointer.h"
#include ".\..\pixmap.h"
#include <iostream>


using namespace BE;

class MainMenuState : public GameState
{
public:
	MainMenuState() {};
	MainMenuState(GameStateManager &Parent, int newID) : GameState(Parent, newID),
		img(NULL)
	{
		//myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		//myMenu->addButton("startnewgame.png", "button1down.bmp", "button1over.bmp", CreateFunctionPointer0R(this, &MainMenuState::StartNewGameCallback));
		//myMenu->addButton("profilemanagement.png", "button2down.bmp", "button2over.bmp", CreateFunctionPointer0R(this, &MainMenuState::ProfileManagerCallback));
		//myMenu->addButton("loadgame.png", "button3down.bmp", "button3over.bmp", CreateFunctionPointer0R(this, &MainMenuState::LoadGameCallback));
		//myMenu->addButton("options.png", "button4down.bmp", "button4over.bmp", CreateFunctionPointer0R(this, &MainMenuState::OptionsCallback));

		//img = new pixmap("statescreens/mainmenu.bmp");
		//img->mY = 618;
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

	pixmap* img;
	// add private stuff here
	
};

#endif

