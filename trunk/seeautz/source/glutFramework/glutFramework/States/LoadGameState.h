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
		myMenu->addButton("pregame.png", "button1down.bmp", "button1over.bmp", CreateFunctionPointer0R(this, &LoadGameState::PreGameCallback));
		myMenu->addButton("button2normal.bmp", "button2down.bmp", "button2over.bmp", CreateFunctionPointer0R(this, &LoadGameState::tutorialCallback));
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