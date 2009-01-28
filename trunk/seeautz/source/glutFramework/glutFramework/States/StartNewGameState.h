#ifndef STARTNEWGAMESTATE_H
#define STARTNEWGAMESTATE_H

#include ".\..\GameState.h" 
#include ".\..\pixmap.h"
#include "MainMenuState.h"

class StartNewGameState : public GameState
{
public:
	StartNewGameState() {};
	StartNewGameState(GameStateManager &Parent, int newID) : GameState(Parent, newID), img(NULL)
	{
		img = new pixmap("statescreens/startnewgame.bmp");
		img->mY = 618;
		myMenu = new MenuSys(250, 50, "blankmenu.bmp", Auto);
		myMenu->addButton("button1normal.bmp", "button1down.bmp", "button1over.bmp", CreateFunctionPointer0R(this, &StartNewGameState::button5Callback));
		Update();
	}

	bool StartNewGameState::Update();
	bool StartNewGameState::Draw();

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	bool button5Callback();

private:
	pixmap* img;
	// add private stuff here
};

#endif