#ifndef CREATEPROFILESTATE_H
#define CREATEPROFILESTATE_H

#include "GameState.h" 
#include "GameStateManager.h"
#include "oglTexture2D.h"
#include "playGame.h"
#include "clickOKState.h"
#include "profileManager.h"


class createProfileState : public GameState
{
public:
	createProfileState() {};
	createProfileState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		creatingProfile = true;
		checked = 0;
		profileCheck = -3;
		img = new oglTexture2D();
		/*if(img != NULL)
			img->loadImage("statescreens\\profilemanagement.png", 1024, 120);
		img->mY = 618;*/
		myMenu = new MenuSys(250, 450, "blankmenu.png", Auto);
		if(profileCheck >= 0)
		{
			myMenu->addButton("buttons\\selectprofile.png", "buttons\\selectprofilehover.png", "buttons\\selectprofilehover.png", CreateFunctionPointer0R(this, &createProfileState::SelectProfile));
		}
		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	void createProfileState::keyboardInput(unsigned char c, int x, int y);
	bool createProfileState::Update();
	bool createProfileState::Draw();
	int createProfileState::doesNameAlreadyExists(std::string);
	void createProfileState::setPlayerInfo(std::string name, int, int, int);
	bool SelectProfile();
	
	int checked;
	std::string tempString; 
	int profileCheck;

private:
	profileManager* PM;
	oglTexture2D* img;
	bool creatingProfile;
	// add private stuff here

};

#endif