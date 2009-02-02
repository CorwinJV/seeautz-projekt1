#ifndef LOADGAMESTATE_H
#define LOADGAMESTATE_H

#include ".\..\GameState.h" 
#include ".\..\pixmap.h"
#include "MainMenuState.h"
#include "..\tutorialMap1.h"

class LoadGameState : public GameState
{
public:
	LoadGameState() {};
	LoadGameState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	//	img = new pixmap("statescreens/startnewgame.bmp");
	//	img->mY = 618;
		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\pregame.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &LoadGameState::PreGameCallback));
		myMenu->addButton("button2normal.png", "button2down.png", "button2over.png", CreateFunctionPointer0R(this, &LoadGameState::tutorialCallback));
		Update();
	}

	bool LoadGameState::Update();
	bool LoadGameState::Draw();
	bool PreGameCallback();
	bool tutorialCallback();

private:

	// add private stuff here

};

#endif