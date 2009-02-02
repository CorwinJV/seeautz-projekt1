#ifndef PREGAMESTATE_H
#define PREGAMESTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"


class PreGameState : public GameState
{
public:
	PreGameState() {};
	PreGameState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	//	img = new pixmap("statescreens/startnewgame.bmp");
	//	img->mY = 618;
		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\maingameloop.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &PreGameState::MainGameCallback));
		Update();
	}

	bool PreGameState::Update();
	bool PreGameState::Draw();
	bool MainGameCallback();

private:

	//add private stuff here

};




#endif