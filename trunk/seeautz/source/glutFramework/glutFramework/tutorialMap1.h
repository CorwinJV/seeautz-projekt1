#ifndef TUTORIALMAP1_H
#define TUTORIALMAP1_H

#include "GameState.h" 
#include "oglUtility.h"
#include "pixmap.h"
#include "gameBoard.h"


class tutorialMap1 : public GameState
{
private:

	gameBoard *tutorialmap1;
	int timer;


public:

	tutorialMap1();
	tutorialMap1(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		initialize();
		
	}
	bool initialize();
	bool tutorialMap1::Update();
	bool tutorialMap1::Draw();

};


#endif

