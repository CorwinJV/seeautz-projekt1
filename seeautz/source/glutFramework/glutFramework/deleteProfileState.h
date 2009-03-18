#ifndef DELETEPROFILESTATE_H
#define DELETEPROFILESTATE_H

#include "GameState.h" 
#include "GameStateManager.h"
#include "oglTexture2D.h"
#include "playGame.h"
#include "clickOKState.h"


class deleteProfileState : public GameState
{
public:
	deleteProfileState() {};
	deleteProfileState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		deletingProfile = true;
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
	void deleteProfileState::keyboardInput(unsigned char c, int x, int y);
	bool deleteProfileState::Update();
	bool deleteProfileState::Draw();
	bool deleteProfileState::doesNameAlreadyExists(std::string);
	void deleteProfileState::setPlayerInfo(std::string name, int, int, int);
	
	int checked;
	std::string tempString; 

private:
	oglTexture2D* img;
	bool deletingProfile;
	// add private stuff here

};

#endif