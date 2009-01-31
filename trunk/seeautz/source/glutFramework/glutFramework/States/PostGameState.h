#ifndef POSTGAMESTATE_H
#define POSTGAMESTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"

class PostGameState : public GameState
{
public:
	PostGameState() {};
	PostGameState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	//	img = new pixmap("statescreens/startnewgame.bmp");
	//	img->mY = 618;
		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("newlevel.png", "button1down.bmp", "button1over.bmp", CreateFunctionPointer0R(this, &PostGameState::NewLevelCallback));
		Update();
	}

	bool PostGameState::Update();
	bool PostGameState::Draw();
	bool NewLevelCallback();

private:
	// add private stuff here

};

#endif
