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
	string playerName;
	
	// below are varible that will need to functions implemented for them to work properly
	// once we are able to save our position on the map
	// also need functionality for what switches have been flipped if saved in midlevel
	// and possibly number of reprogrammable squares used and bytes remaining
	int xPos;
	int yPos;
	int switchesFlipped;
	int remainingBytes;
	int numOfRepos;
	int playerMaxLevel;

	tempString = "savedGames\\";
	tempString += playerGame.c_str();

	PlayerInfo.open(tempString.c_str());

	if(!PlayerInfo)
		return false;

	playerMaxLevel = GameVars->getPlayerMaxLevel();
	level = GameVars->getCurrentLevel();

	if(level > playerMaxLevel)
		playerMaxLevel = level;

	GameVars->setPlayerMaxLevel(level);

	score = GameVars->getTotalScore();
	playerName = GameVars->getPlayerName();

	// code for saving stats here
	PlayerInfo << level << endl;
	PlayerInfo << score << endl;
	PlayerInfo << playerName << endl;

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