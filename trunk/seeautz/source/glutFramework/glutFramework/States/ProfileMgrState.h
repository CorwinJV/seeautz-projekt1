#ifndef PROFILEMGRSTATE_H
#define PROFILEMGRSTATE_H

#include ".\..\GameState.h" 
#include ".\..\GameStateManager.h"
#include ".\..\oglTexture2D.h"
#include "MainMenuState.h"
#include "StartNewGameState.h"
#include "LoadGameState.h"
#include ".\..\playGame.h"

class ProfileMgrState : public GameState
{
public:
	ProfileMgrState() {};
	ProfileMgrState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		img = new oglTexture2D();
		if(img != NULL)
			img->loadImage("..\\Content\\statescreens\\profilemanagement.png", 1024, 120);
		img->mY = 618;

		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\returntomainmenu.png", "..\\Content\\buttons\\returntomainmenuhover.png", "button1over.png", CreateFunctionPointer0R(this, &ProfileMgrState::MainMenuStateCallback));
		myMenu->addButton("..\\Content\\buttons\\startnewgame.png", "..\\Content\\buttons\\startnewgamehover.png", "button1over.png", CreateFunctionPointer0R(this, &ProfileMgrState::StartNewGameStateCallback));
		myMenu->addButton("..\\Content\\buttons\\loadgame.png", "..\\Content\\buttons\\loadgamehover.png", "button1over.png", CreateFunctionPointer0R(this, &ProfileMgrState::LoadGameStateCallback));
		myMenu->addButton("..\\Content\\buttons\\savegame.png", "..\\Content\\buttons\\savegamehover.png", "button1over.png", CreateFunctionPointer0R(this, &ProfileMgrState::SaveGameStateCallback));
		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	bool ProfileMgrState::Update();
	bool ProfileMgrState::Draw();
	bool MainMenuStateCallback();
	bool StartNewGameStateCallback();
	bool LoadGameStateCallback();
	bool SaveGameStateCallback();

private:
	oglTexture2D* img;
	// add private stuff here

};

#endif