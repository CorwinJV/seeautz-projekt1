#ifndef PREGAMESTATE_H
#define PREGAMESTATE_H

#include ".\..\GameState.h" 

class PreGameState : public GameState
{
public:
	PreGameState() {};
	PreGameState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	}

	bool PreGameState::Update();
	bool PreGameState::Draw();

private:

	//add private stuff here

};




#endif