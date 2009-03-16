#ifndef PLAYGAME_H
#define PLAYGAME_H

#include "GameState.h" 
#include "oglUtility.h"
#include "gameBoard.h"
#include "LogicInterface.h"
#include "oglGameVars.h"
#include "GLFT_Font.h"
#include "Button.h"
#include "States\\PauseGameState.h"
#include "States\\DevLogoState.h"
#include "States\\SaveGameState.h"

class playGame : public GameState
{
private:
	gameBoard *gamePlay;
	int timer;
	vector<levelData*> levelList;
	vector<oglTexture2D*> endGamePics;
	vector<oglTexture2D*>::iterator endGameAnimation;
	MenuSys* myMenu;
	oglTexture2D* img;
	oglTexture2D* blackImage;
	oglTexture2D* youDiedImage;
	GameBoardState curState;
	vector<Button*> buttonList;
	bool gameSaved;
	bool pregameRunning;

	// pregame text locations
	int preGameTextOffsetX;
	int preGameTextOffsetY;
	int preGameTextSpacing;
	int playerScore;
	void drawLevelInfo();

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
	bool exitGame();
	bool advance();
	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	void keyboardInput(unsigned char c, int x, int y);
	void doEndGameDraw();
	void levelSelect();
	LogicInterface mInterface;

};


#endif

