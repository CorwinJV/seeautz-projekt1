#ifndef PREGAMESTATE_H
#define PREGAMESTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"
#include ".\..\oglTexture2D.h"

class PreGameState : public GameState
{
public:
	PreGameState() {};
	PreGameState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		img = new oglTexture2D();
		if(img != NULL)
			img->loadImage("..\\Content\\statescreens\\pregame.png", 1024, 120);
		img->mY = 618;

		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\maingameloop.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &PreGameState::MainGameCallback));
		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	bool PreGameState::Update();
	bool PreGameState::Draw();
	bool MainGameCallback();

private:
	oglTexture2D* img;
	//add private stuff here

};




#endif