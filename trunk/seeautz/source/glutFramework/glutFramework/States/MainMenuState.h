#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include ".\..\GameState.h" 

class MainMenuState : public GameState
{
public:
	MainMenuState() {};
	MainMenuState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		myMenu = new MenuSys(250, 50, "blankmenu.bmp", Auto);
		myMenu->addButton( 25, 100, "button1normal.bmp", "button1down.bmp", "button1over.bmp");
		myMenu->addButton( 125, 200, "button2normal.bmp", "button2down.bmp", "button2over.bmp");
		myMenu->addButton( 150, 300, "button3normal.bmp", "button3down.bmp", "button3over.bmp");
		myMenu->addButton( 225, 400, "button4normal.bmp", "button4down.bmp", "button4over.bmp");
	}

	bool MainMenuState::Update();
	bool MainMenuState::Draw();

private:

	// add private stuff here
	
};

#endif

