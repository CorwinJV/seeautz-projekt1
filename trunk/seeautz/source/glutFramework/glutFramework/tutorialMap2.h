#ifndef TUTORIALMAP2_H
#define TUTORIALMAP2_H

#include "GameState.h" 
#include "oglUtility.h"
#include "pixmap.h"
#include "gameBoard.h"


class tutorialMap2 : public GameState
{
private:
	gameBoard *tutorialmap2;
	int timer;

public:

	tutorialMap2();
	tutorialMap2(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		initialize();
	}
	bool initialize();
	bool tutorialMap2::Update();
	bool tutorialMap2::Draw();
	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	void keyboardInput(unsigned char c, int x, int y);
};


#endif

