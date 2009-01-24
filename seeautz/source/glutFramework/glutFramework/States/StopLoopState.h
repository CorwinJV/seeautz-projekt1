#ifndef STOPLOOPSTATE_H
#define STOPLOOPSTATE_H

#include ".\..\GameState.h" 

class StopLoopState : public GameState
{
public:
	StopLoopState() {};
	StopLoopState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	}

	bool StopLoopState::Update();
	bool StopLoopState::Draw();

private:
	// add private stuff here
};

#endif