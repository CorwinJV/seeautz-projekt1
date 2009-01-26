#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include ".\..\GameState.h"
#include ".\..\FunctionPointer.h"
#include <iostream>

using namespace BE;

class MainMenuState : public GameState
{
public:
	MainMenuState() {};
	MainMenuState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		myMenu = new MenuSys(250, 50, "blankmenu.bmp", Auto);
		myMenu->addButton("button1normal.bmp", "button1down.bmp", "button1over.bmp", CreateFunctionPointer0R(this, &MainMenuState::button1Callback));
		myMenu->addButton("button2normal.bmp", "button2down.bmp", "button2over.bmp");
		myMenu->addButton("button3normal.bmp", "button3down.bmp", "button3over.bmp");
		myMenu->addButton("button4normal.bmp", "button4down.bmp", "button4over.bmp");
	}

	bool Update();
	bool Draw();
	bool HandleClick();

	bool button1Callback()
	{
		std::cout << " BUTTON 1 CALLBACK WORKING ";
		return true;
	}

private:

	// add private stuff here
	
};

#endif

