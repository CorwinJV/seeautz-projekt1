// Added 1/21/09

#ifndef ABORTSTATE_H
#define ABORTSTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"



class AbortState : public GameState
{
public:
	AbortState() {};
	AbortState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
//		img = new pixmap("statescreens/startnewgame.bmp");
//		img->mY = 618;
		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\stoploop.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &AbortState::StopLoopCallback));
		Update();
	}

	bool AbortState::Update();
	bool AbortState::Draw();
	bool StopLoopCallback();

private:
	// add private stuff here

};



#endif