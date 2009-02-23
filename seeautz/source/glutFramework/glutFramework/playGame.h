#ifndef TUTORIALMAP1_H
#define TUTORIALMAP1_H

#include "GameState.h" 
#include "oglUtility.h"
//#include "pixmap.h"
#include "gameBoard.h"
#include "LogicInterface.h"


class playGame : public GameState
{
private:
	gameBoard *gamePlay;
	int timer;

public:

	playGame();
	playGame(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		initialize();
	}
	bool initialize();
	bool playGame::Update();
	bool playGame::Draw();
	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	void keyboardInput(unsigned char c, int x, int y);
	LogicInterface mInterface;
};


#endif

