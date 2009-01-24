#ifndef DEVLOGOSTATE_H
#define DEVLOGOSTATE_H

#include ".\..\GameState.h" 
#include ".\..\oglUtility.h"
#include ".\..\pixmap.h"


class DevLogoState : public GameState
{
private:
	pixmap* logo;
	int timer;


public:

	DevLogoState() {};
	DevLogoState(GameStateManager &Parent, int newID) : GameState(Parent, newID), logo(NULL)
	{
		logo = new pixmap("seeautslogo.bmp");
		timer = 0;
	}

	bool DevLogoState::Update();
	bool DevLogoState::Draw();

};


#endif

