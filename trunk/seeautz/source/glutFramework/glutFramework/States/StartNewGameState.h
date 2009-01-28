#ifndef STARTNEWGAMESTATE_H
#define STARTNEWGAMESTATE_H

#include ".\..\GameState.h" 
#include ".\..\pixmap.h"

class StartNewGameState : public GameState
{
public:
	StartNewGameState() {};
	StartNewGameState(GameStateManager &Parent, int newID) : GameState(Parent, newID), img(NULL)
	{
		img = new pixmap("statescreens/startnewgame.bmp");
		img->mY = 618;
	}

	bool StartNewGameState::Update();
	bool StartNewGameState::Draw();

private:
	pixmap* img;
	// add private stuff here
};

#endif