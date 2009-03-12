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
		creatingProfile = false; 
		img = new oglTexture2D();
		if(img != NULL)
			img->loadImage("statescreens\\profilemanagement.png", 1024, 120);
		img->mY = 618;

		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("buttons\\returntomainmenu.png", "buttons\\returntomainmenuhover.png", "buttons\\returntomainmenuhover.png", CreateFunctionPointer0R(this, &ProfileMgrState::MainMenuStateCallback));
		myMenu->addButton("buttons\\deleteprofile.png", "buttons\\deleteprofilehover.png", "buttons\\deleteprofilehover.png", CreateFunctionPointer0R(this, &ProfileMgrState::DeleteProfile));
		myMenu->addButton("buttons\\createprofile.png", "buttons\\createprofilehover.png", "buttons\\createprofilehover.png", CreateFunctionPointer0R(this, &ProfileMgrState::CreateProfile));
		myMenu->addButton("buttons\\selectprofile.png", "buttons\\selectprofilehover.png", "buttons\\selectprofilehover.png", CreateFunctionPointer0R(this, &ProfileMgrState::SelectProfile));
		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	void ProfileMgrState::keyboardInput(unsigned char c, int x, int y);
	bool ProfileMgrState::Update();
	bool ProfileMgrState::Draw();
	bool MainMenuStateCallback();
	bool DeleteProfile();
	bool CreateProfile();
	bool SelectProfile();
	int getMaxLevels();
	int getNumProfiles();
	void setMaxLevels(int);
	void setNumProfiles(int);
	bool ProfileMgrState::doesNameAlreadyExists(string);
	void ProfileMgrState::setPlayerName(string name);
	bool creatingProfile;
	bool checked;

private:
	oglTexture2D* img;
	int maxLevels;
	int numProfiles;
	// add private stuff here

};

#endif