#ifndef SUCCEEDSTATE_H
#define SUCCEEDSTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"
#include ".\..\oglTexture2D.h"

class SucceedState : public GameState
{
public:
	SucceedState() {};
	SucceedState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		img = new oglTexture2D();
		if(img != NULL)
			img->loadImage("..\\Content\\statescreens\\succeed.png", 1024, 120);
		img->mY = 618;

		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\postgame.png", "succeed.png", "button1over.png", CreateFunctionPointer0R(this, &SucceedState::PostGameCallback));
		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	bool SucceedState::Update();
	bool SucceedState::Draw();
	bool PostGameCallback();

private:
	oglTexture2D* img;
	// add private stuff here
};

#endif