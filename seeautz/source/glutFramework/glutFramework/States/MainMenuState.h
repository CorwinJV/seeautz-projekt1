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
		myMenu = new MenuSys(250, 50, "blankmenu.bmp", Auto);
		myMenu->addButton("button1normal.bmp", "button1down.bmp", "button1over.bmp", CreateFunctionPointer0R(this, &MainMenuState::button1Callback));
		myMenu->addButton("button2normal.bmp", "button2down.bmp", "button2over.bmp");
		myMenu->addButton("button3normal.bmp", "button3down.bmp", "button3over.bmp");
		myMenu->addButton("button4normal.bmp", "button4down.bmp", "button4over.bmp");

		img = new pixmap("statescreens/mainmenu.bmp");
		img->mY = 618;
	}

	bool Update();
	bool Draw();
	bool HandleClick();
	void MainMenuState::processMouse(int x, int y);
	void MainMenuState::processMouseClick(int button, int state, int x, int y);
	bool button1Callback();

private:

	pixmap* img;
	// add private stuff here
	
};

#endif

