#ifndef SUCCEEDSTATE_H
#define SUCCEEDSTATE_H

#include ".\..\GameState.h" 

class SucceedState : public GameState
{
public:
	SucceedState() {};
	SucceedState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	}

	bool SucceedState::Update();
	bool SucceedState::Draw();

private:
	// add private stuff here
};

#endif