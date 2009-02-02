#ifndef STOPLOOPSTATE_H
#define STOPLOOPSTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"
#include ".\..\oglTexture2D.h"

class StopLoopState : public GameState
{
public:
	StopLoopState() {};
	StopLoopState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		img = new oglTexture2D();
		if(img != NULL)
			img->loadImage("..\\Content\\statescreens\\stoploop.png", 1024, 120);
		img->mY = 618;

		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\pregame.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &StopLoopState::PreGameCallback));
		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	bool StopLoopState::Update();
	bool StopLoopState::Draw();
	bool PreGameCallback();

private:
	oglTexture2D* img;
	// add private stuff here
};

#endif