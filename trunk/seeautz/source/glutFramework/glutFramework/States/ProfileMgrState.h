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
			img->loadImage("statescreens\\profilemanagement.png", 1024, 120);
		img->mY = 618;

		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("buttons\\returntomainmenu.png", "buttons\\returntomainmenuhover.png", "buttons\\returntomainmenuhover.png", CreateFunctionPointer0R(this, &ProfileMgrState::MainMenuStateCallback));
		myMenu->addButton("buttons\\startnewgame.png", "buttons\\startnewgamehover.png", "buttons\\startnewgamehover.png", CreateFunctionPointer0R(this, &ProfileMgrState::StartNewGameStateCallback));
		myMenu->addButton("buttons\\loadgame.png", "buttons\\loadgamehover.png", "buttons\\loadgamehover.png", CreateFunctionPointer0R(this, &ProfileMgrState::LoadGameStateCallback));
		myMenu->addButton("buttons\\savegame.png", "buttons\\savegamehover.png", "buttons\\savegamehover.png", CreateFunctionPointer0R(this, &ProfileMgrState::SaveGameStateCallback));
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