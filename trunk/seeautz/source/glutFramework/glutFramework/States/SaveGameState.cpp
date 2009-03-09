#include "SaveGameState.h" 
#include "PostGameState.h"
#include<fstream>
#include<iostream>
#include <string>

using namespace std;

bool SaveGameState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool SaveGameState::Draw()
{
	if(img != NULL)
		img->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();
	return false;
}

bool SaveGameState::SavePlayerGame(string playerGame) 
{
	if (playerGame == ".txt")
	{
		playerGame = "defaultgame.txt";
	}

	cout << "Saving Game...  " << playerGame << endl;
	
	ofstream PlayerInfo;
	string tempString;
	int level;
	int score;
	bool inGame;
	string playerName;
	
	// below are varible that will need to functions implemented for them to work properly
	// once we are able to save our position on the map
	// also need functionality for what switches have been flipped if saved in midlevel
	// and possibly number of reprogrammable squares used and bytes remaining
	int xPos = 0;
	int yPos = 0;
	int remainingBytes = 0;
	int playerMaxLevel = 0;
	int isActive = -1;
	

	inGame = GameVars->getGameStatus();

	tempString = "savedGames\\";
	tempString += playerGame.c_str();

	PlayerInfo.open(tempString.c_str());

	if(!PlayerInfo)
		return false;

	playerMaxLevel = GameVars->getPlayerMaxLevel();
	level = GameVars->getCurrentLevel();

	if(level > playerMaxLevel)
		playerMaxLevel = level;

	// unless we are saving in the middle of a level, increment the level. 
	if(!inGame)
		level++;
	else
	{
		xPos = GameVars->getRobotX();
		yPos = GameVars->getRobotY();
		//also save remaining bytes here
	}

	GameVars->setPlayerMaxLevel(level);

	score = GameVars->getTotalScore();
	playerName = GameVars->getPlayerName();

	// code for saving stats here
	PlayerInfo << level << endl;
	PlayerInfo << score << endl;
	PlayerInfo << playerName << endl;

	if(inGame)
	{
		PlayerInfo << xPos << " ";
		PlayerInfo << yPos << " ";
	}

	PlayerInfo.close();

	return true;
}

//this probably doesn't need to be here...
bool SaveGameState::PostGameCallback()
{
	GSM->addGameState<PostGameState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}

void SaveGameState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void SaveGameState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}