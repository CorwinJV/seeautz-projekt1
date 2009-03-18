#ifndef SELECTPROFILESTATE_H
#define SELECTPROFILESTATE_H

#include "GameState.h" 
#include "GameStateManager.h"
#include "oglTexture2D.h"
#include "playGame.h"
#include "clickOKState.h"


class selectProfileState : public GameState
{
public:
	selectProfileState() {};
	selectProfileState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		selectingProfile = true;
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
	void selectProfileState::keyboardInput(unsigned char c, int x, int y);
	bool selectProfileState::Update();
	bool selectProfileState::Draw();
	bool selectProfileState::doesNameAlreadyExists(std::string);
	void selectProfileState::setPlayerInfo(std::string name, int, int, int);
	
	int checked;
	std::string tempString; 

private:
	oglTexture2D* img;
	bool selectingProfile;
	// add private stuff here

};

#endif