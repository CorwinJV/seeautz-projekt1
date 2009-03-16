#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

struct levelInfo
{
	int level;
	int levelHighScore;
	int leastAmtCommands;
	int leastAmtInstructs;
};

class playerInfo
{
private:
	string playerName;
	int playerHighestLevel;
	int playerCurrentLevel;
	int maxLevel;
	vector<levelInfo*> playerLevelInfo;

public:
	playerInfo(int newMaxLevel)
	{
		maxLevel = newMaxLevel;
		playerName = "";
		playerHighestLevel = 1;
		playerCurrentLevel = 1;
		
		levelInfo* tempPlayerLevelInfo;
		for(int i = 0; i < maxLevel; i++)
		{
			tempPlayerLevelInfo = new levelInfo;
			tempPlayerLevelInfo->leastAmtCommands = -1;
			tempPlayerLevelInfo->leastAmtInstructs = -1;
			tempPlayerLevelInfo->level = i;
			tempPlayerLevelInfo->levelHighScore = -1;
			playerLevelInfo.push_back(tempPlayerLevelInfo);
		}
	};
	string			getPlayerName(){return playerName;};
	int				getPlayerHighestLevel(){return playerHighestLevel;};
	int				getPlayerCurrentLevel(){return playerCurrentLevel;};
	int				getPlayerLevel(int level){return playerLevelInfo[level]->level;};
	int				getPlayerLevelScore(int level){return playerLevelInfo[level]->levelHighScore;};
	int				getPlayerLeastCmd(int level){return playerLevelInfo[level]->levelHighScore;};
	int				getPlayerLeastInst(int level){return playerLevelInfo[level]->leastAmtInstructs;};
	void			setPlayerName(string name){playerName = name;};
	void			setPlayerHighestLevel(int level){playerHighestLevel = level;};
	void			setPlayerCurrentLevel(int level){playerCurrentLevel = level;};
	void			setPlayerLevelInfo(int newLevel, int score, int commands, int instructs)
	{	
		playerLevelInfo[newLevel]->level = newLevel;
		playerLevelInfo[newLevel]->levelHighScore = score;
		playerLevelInfo[newLevel]->leastAmtCommands = commands;
		playerLevelInfo[newLevel]->leastAmtInstructs = instructs;
	};

};

class profileManager
{	
private:
	vector<playerInfo*> allPlayerInfo;
	playerInfo* tempPlayerInfo;
	int	maxRecords;
	int	currentRecord;
	int maxLevel;

public:
	profileManager(int newMaxLevel)
	{
		maxRecords = 0;
		currentRecord = 0;
		maxLevel = newMaxLevel;
		tempPlayerInfo = new playerInfo(maxLevel);
		loadAllProfiles();
	};
	void		saveProfile();
	bool		selectProfile(string);
	void		deleteProfile();
	bool		createProfile(string);
	void		loadAllProfiles();

	
	string		getPlayerName(){return allPlayerInfo[currentRecord]->getPlayerName();};
	int			getPlayerHighestLevel(){return allPlayerInfo[currentRecord]->getPlayerHighestLevel();};
	int			getPlayerCurrentLevel(){return allPlayerInfo[currentRecord]->getPlayerCurrentLevel();};
	int			getPlayerLevelScore(int level){return allPlayerInfo[currentRecord]->getPlayerLevelScore(level);};
	int			getPlayerLeastCmd(int level){return allPlayerInfo[currentRecord]->getPlayerLeastCmd(level);};
	int			getPlayerLeastInst(int level){return allPlayerInfo[currentRecord]->getPlayerLeastInst(level);};
	void		setPlayerName(string name){allPlayerInfo[currentRecord]->setPlayerName(name);};
	void		setPlayerHighestLevel(int level){allPlayerInfo[currentRecord]->setPlayerHighestLevel(level);};
	void		setPlayerCurrentLevel(int level){allPlayerInfo[currentRecord]->setPlayerCurrentLevel(level);};
	void		setPlayerLevelInfo(int level, int score, int commands, int instructs)
	{
		allPlayerInfo[currentRecord]->setPlayerLevelInfo(level, score, commands, instructs);
	};
};


#endif