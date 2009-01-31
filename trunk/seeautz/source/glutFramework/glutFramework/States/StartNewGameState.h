#ifndef STARTNEWGAMESTATE_H
#define STARTNEWGAMESTATE_H

#include ".\..\GameState.h" 
#include ".\..\pixmap.h"
#include "MainMenuState.h"
#include "..\tutorialMap1.h"

class StartNewGameState : public GameState
{
public:
	StartNewGameState() {};
	StartNewGameState(GameStateManager &Parent, int newID) : GameState(Parent, newID), img(NULL)
	{
		img = new pixmap("statescreens/startnewgame.bmp");
		img->mY = 618;
		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("pregame.png", "button1down.bmp", "button1over.bmp", CreateFunctionPointer0R(this, &StartNewGameState::PreGameCallback));
		myMenu->addButton("button2normal.bmp", "button2down.bmp", "button2over.bmp", CreateFunctionPointer0R(this, &StartNewGameState::tutorialCallback));
		Update();
	}

	bool StartNewGameState::Update();
	bool StartNewGameState::Draw();

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	bool PreGameCallback();
	bool tutorialCallback();

private:
	pixmap* img;
	// add private stuff here
};

#endif