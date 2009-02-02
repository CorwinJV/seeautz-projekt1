#ifndef PROFILEMGRSTATE_H
#define PROFILEMGRSTATE_H

#include ".\..\GameState.h" 
#include ".\..\oglTexture2D.h"

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
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	bool ProfileMgrState::Update();
	bool ProfileMgrState::Draw();

private:
	oglTexture2D* img;
	// add private stuff here

};

#endif