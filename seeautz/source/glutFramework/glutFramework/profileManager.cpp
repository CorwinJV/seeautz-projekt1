#include "profileManager.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

bool profileManager::createProfile(string name)
{
	string tempName = name;

	for(int i = 0; i < maxRecords; i++)
	{
		if(name == allPlayerInfo[i]->getPlayerName())
		{
			return false;
		}
	}

	playerInfo* tempPlayerInfo;
	tempPlayerInfo = new playerInfo(maxLevel);
	tempPlayerInfo->setPlayerName(tempName);
	allPlayerInfo.push_back(tempPlayerInfo);
	maxRecords++;
	saveProfile();

	return true;
}

void profileManager::deleteProfile()
{

}

void profileManager::saveProfile()
{
	ofstream saveFile;
	string tempName;
	int	tempInt;
	int highScore;
	int leastCmds;
	int leastInstructs;

	saveFile.open("savedGames\\savefile.txt");

	saveFile << maxLevel << endl;
	saveFile << maxRecords << endl;

	for (int i = 0; i < maxRecords; i++)
	{
		tempName = allPlayerInfo[i]->getPlayerName();
		saveFile << tempName << endl;
		
		tempInt = allPlayerInfo[i]->getPlayerHighestLevel();
		saveFile << tempInt << endl;

		tempInt = allPlayerInfo[i]->getPlayerCurrentLevel();
		saveFile << tempInt << endl;

		for (int j = 0; j < maxLevel; j++)
		{
			tempInt = allPlayerInfo[i]->getPlayerLevel(j);
			highScore = allPlayerInfo[i]->getPlayerLevelScore(j);
			leastCmds = allPlayerInfo[i]->getPlayerLeastCmd(j);
			leastInstructs = allPlayerInfo[i]->getPlayerLeastInst(j);
			saveFile << tempInt << " ";
			saveFile << highScore << " ";
			saveFile << leastCmds << " ";
			saveFile << leastInstructs << endl;
		}
	}
	saveFile.close();
}

bool profileManager::selectProfile(string name)
{
	string tempName = name;

	for(int i = 0; i < maxRecords; i++)
	{
		if(name == allPlayerInfo[i]->getPlayerName())
		{
			currentRecord = i;
			return true;
		}
	}

	return false;

}

void profileManager::loadAllProfiles()
{
	playerInfo* tempPlayerInfo;

	ifstream saveFile;
	ofstream createSaveFile;
	string tempName;
	int	tempInt;
	int highScore;
	int leastCmds;
	int leastInstructs;

	saveFile.open("savedGames\\savefile.txt");

	if(!saveFile)
	{
		saveFile.close();
		createSaveFile.open("savedGames\\savefile.txt");
		maxRecords = 0;

		createSaveFile << maxLevel;
		createSaveFile << maxRecords;
		createSaveFile.close();
		saveFile.open("savedGames\\savefile.txt");
	}

	saveFile >> maxLevel;
	saveFile >> maxRecords;

	for (int i = 0; i < maxRecords; i++)
	{
		tempPlayerInfo = new playerInfo(maxLevel);

		saveFile >> tempName;
		tempPlayerInfo->setPlayerName(tempName);

		saveFile >> tempInt;
		tempPlayerInfo->setPlayerHighestLevel(tempInt);

		saveFile >> tempInt;
		tempPlayerInfo->setPlayerCurrentLevel(tempInt);

		for (int j = 0; j < maxLevel; j++)
		{
			saveFile >> j;
			saveFile >> highScore;
			saveFile >> leastCmds;
			saveFile >> leastInstructs;
			tempPlayerInfo->setPlayerLevelInfo(j, highScore, leastCmds, leastInstructs);
		}
		allPlayerInfo.push_back(tempPlayerInfo);
	}
	saveFile.close();
}