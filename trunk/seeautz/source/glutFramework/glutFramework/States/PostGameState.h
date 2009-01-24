#ifndef POSTGAMESTATE_H
#define POSTGAMESTATE_H

#include ".\..\GameState.h"  

class PostGameState : public GameState
{
public:
	PostGameState() {};
	PostGameState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	}

	bool PostGameState::Update();
	bool PostGameState::Draw();

private:
	// add private stuff here

};

#endif
