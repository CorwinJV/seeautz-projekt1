#ifndef OPTIONSSTATE_H
#define OPTIONSSTATE_H

#include ".\..\GameState.h" 

class OptionsState : public GameState
{
public:
	OptionsState() {};
	OptionsState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	}

	bool OptionsState::Update();
	bool OptionsState::Draw();

private:
	// add private stuff here

};

#endif