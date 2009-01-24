#ifndef LOGICVIEWSTATE_H
#define LOGICVIEWSTATE_H

#include ".\..\GameState.h" 

class LogicViewState : public GameState
{
public:
	LogicViewState() {};
	LogicViewState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	}

	bool LogicViewState::Update();
	bool LogicViewState::Draw();

private:
	// add private stuuf here

};
#endif