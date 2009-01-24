#ifndef LOADGAMESTATE_H
#define LOADGAMESTATE_H

#include ".\..\GameState.h" 

class LoadGameState : public GameState
{
public:
	LoadGameState() {};
	LoadGameState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	}

	bool LoadGameState::Update();
	bool LoadGameState::Draw();

private:

	// add private stuff here

};

#endif