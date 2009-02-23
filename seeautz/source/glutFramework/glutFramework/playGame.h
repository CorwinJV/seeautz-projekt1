#ifndef TUTORIALMAP1_H
#define TUTORIALMAP1_H

#include "GameState.h" 
#include "oglUtility.h"
//#include "pixmap.h"
#include "gameBoard.h"
#include "LogicInterface.h"
#include "oglGameVars.h"
#include "GLFT_Font.h"
#include "Button.h"

class playGame : public GameState
{
private:
	gameBoard *gamePlay;
	int timer;
	vector<levelData*> levelList;
	MenuSys* myMenu;
	oglTexture2D* img;
	GameBoardState curState;
	vector<Button*> buttonList;
	bool gameSaved;

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
	void exitGame();
	void advance();
	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	void keyboardInput(unsigned char c, int x, int y);
	LogicInterface mInterface;

};


#endif

