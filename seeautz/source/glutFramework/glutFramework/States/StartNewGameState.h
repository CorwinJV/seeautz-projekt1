#ifndef STARTNEWGAMESTATE_H
#define STARTNEWGAMESTATE_H

#include ".\..\GameState.h" 

class StartNewGameState : public GameState
{
public:
	StartNewGameState() {};
	StartNewGameState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	}

	bool StartNewGameState::Update();
	bool StartNewGameState::Draw();

private:

	// add private stuff here

};

#endif