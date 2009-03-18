#ifndef CREATEPROFILESTATE_H
#define CREATEPROFILESTATE_H

#include "GameState.h" 
#include "GameStateManager.h"
#include "oglTexture2D.h"
#include "playGame.h"
#include "clickOKState.h"


class createProfileState : public GameState
{
public:
	createProfileState() {};
	createProfileState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		creatingProfile = true;
		checked = 0;
		img = new oglTexture2D();
		/*if(img != NULL)
			img->loadImage("statescreens\\profilemanagement.png", 1024, 120);
		img->mY = 618;*/
		myMenu = new MenuSys(250, 250, "blankmenu.png", Auto);
		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	void createProfileState::keyboardInput(unsigned char c, int x, int y);
	bool createProfileState::Update();
	bool createProfileState::Draw();
	bool createProfileState::doesNameAlreadyExists(std::string);
	void createProfileState::setPlayerInfo(std::string name, int, int, int);
	
	int checked;
	std::string tempString; 

private:
	oglTexture2D* img;
	bool creatingProfile;
	// add private stuff here

};

#endif