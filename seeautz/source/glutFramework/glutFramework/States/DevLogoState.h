#ifndef DEVLOGOSTATE_H
#define DEVLOGOSTATE_H

#include ".\..\GameState.h" 
#include ".\..\oglUtility.h"
#include ".\..\pixmap.h"
#include ".\..\oglTexture2D.h"
#include <ctime>


class DevLogoState : public GameState
{
private:
	oglTexture2D* logo;
	clock_t timer;
	double opacity;


public:

	DevLogoState() {};
	DevLogoState(GameStateManager &Parent, int newID) : GameState(Parent, newID), logo(NULL)
	{
		opacity = 0;
		logo = new oglTexture2D();
		if(logo != NULL)
			logo->loadImage("seeautslogo.png", 1024, 768);

		//logo->mX = -500;
		//logo->mY = 500;
		timer = 0;
	}

	bool DevLogoState::Update();
	bool DevLogoState::Draw();
	DevLogoState::~DevLogoState();

};


#endif

