#ifndef LOADGAMESTATE_H
#define LOADGAMESTATE_H

#include ".\..\GameState.h" 
#include ".\..\pixmap.h"
#include "MainMenuState.h"
#include "..\tutorialMap1.h"
#include ".\..\oglTexture2D.h"

class LoadGameState : public GameState
{
public:
	LoadGameState() {};
	LoadGameState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		img = new oglTexture2D();
		if(img != NULL)
			img->loadImage("..\\Content\\statescreens\\loadgame.png", 1024, 120);
		img->mY = 618;

		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\pregame.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &LoadGameState::PreGameCallback));
		myMenu->addButton("..\\Content\\buttons\\something.png", "button2down.png", "button2over.png", CreateFunctionPointer0R(this, &LoadGameState::tutorialCallback));
		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	bool LoadGameState::Update();
	bool LoadGameState::Draw();
	bool PreGameCallback();
	bool tutorialCallback();

private:
	oglTexture2D* img;
	// add private stuff here

};

#endif