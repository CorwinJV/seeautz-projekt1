#ifndef EXECUTIONMODESTATE_H
#define EXECUTIONMODESTATE_H

#include ".\..\GameState.h" 

class ExecutionModeState : public GameState
{
public:
	ExecutionModeState() {};
	ExecutionModeState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	}

	bool ExecutionModeState::Update();
	bool ExecutionModeState::Draw();
private:

	// add private stuff here
};

#endif