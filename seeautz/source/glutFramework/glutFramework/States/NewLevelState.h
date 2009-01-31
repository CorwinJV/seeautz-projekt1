#ifndef NEWLEVELSTATE_H
#define NEWLEVELSTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"

class NewLevelState : public GameState
{
public:
	NewLevelState() {};
	NewLevelState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	//	img = new pixmap("statescreens/startnewgame.bmp");
	//	img->mY = 618;
		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("stoploop.png", "button1down.bmp", "button1over.bmp", CreateFunctionPointer0R(this, &NewLevelState::StopLoopCallback));
		Update();
	}

	bool NewLevelState::Update();
	bool NewLevelState::Draw();
	bool StopLoopCallback();

private:
	// add private stuff here

};


#endif