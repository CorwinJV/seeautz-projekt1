#include "profileManager.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

bool profileManager::createProfile(string name)
{

	string tempName = name;

	if(name == "")
		return false;

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
	currentRecord++;
	maxRecords++;
	saveProfile();

	return true;
}

bool profileManager::deleteProfile(string name)
{
	string tempName = name;
	vector<playerInfo*>::iterator itr = allPlayerInfo.begin();

	for(; itr != allPlayerInfo.end(); itr++)
	{
		if(name == (*itr)->getPlayerName())
		{
			delete(*itr);
			allPlayerInfo.erase(itr);
			maxRecords--;
			//currentRecord--;
			if(currentRecord > maxRecords)
			{
				currentRecord = maxRecords;
			}
			if(currentRecord < 0)
			{
				currentRecord = 0;
			}
			saveProfile();
			return true;
		}
	}
	
	return false;
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

	if(maxRecords > 0)
	{
		for(int i = 0; i < maxRecords; i++)
		{
			if(name == allPlayerInfo[i]->getPlayerName())
			{
				currentRecord = i;
				return true;
			}
		}
	}

	return false;

}

int profileManager::getPlayerTotalScore()
{
	int max;
	int score = 0;
	int levelScore = 0;
	max = allPlayerInfo[currentRecord]->getPlayerHighestLevel();

	for(int i = 0; i < max; i++)
	{
		levelScore = allPlayerInfo[currentRecord]->getPlayerLevelScore(i);
		if(levelScore > 0)
		{
			score += allPlayerInfo[currentRecord]->getPlayerLevelScore(i);
		}
	}

	return score;
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

		createSaveFile << maxLevel << endl;
		createSaveFile << maxRecords << endl;
		createSaveFile.close();
		saveFile.open("savedGames\\savefile.txt");
	}

	saveFile >> maxLevel;
	saveFile >> maxRecords;

	allPlayerInfo.clear();

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