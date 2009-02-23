#ifndef TUTORIALMAP1_H
#define TUTORIALMAP1_H

#include "GameState.h" 
#include "oglUtility.h"
//#include "pixmap.h"
#include "gameBoard.h"
#include "LogicInterface.h"
#include "oglGameVars.h"
#include "GLFT_Font.h"

class playGame : public GameState
{
private:
	gameBoard *gamePlay;
	int timer;
	vector<levelData*> levelList;

public:
	playGame();
	playGame(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		initialize();		
	}
	~playGame();

	bool initialize();
	bool playGame::Update();
	bool playGame::Draw();
	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	void keyboardInput(unsigned char c, int x, int y);
	LogicInterface mInterface;
};


#endif

