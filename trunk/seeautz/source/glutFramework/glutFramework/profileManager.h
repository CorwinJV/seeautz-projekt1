#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

class levelInfo
{
public:
	int level;
	int levelHighScore;
	int leastAmtCommands;
	int leastAmtInstructs;
};

class profileManager
{	
private:
	string playerName;
	int playerHighestLevel;
	int playerCurrentLevel;
	vector<levelInfo*> playerLevelInfo;

public:
	profileManager()
	{
		playerName = "";
		playerHighestLevel = -1;
		playerCurrentLevel = -1;
		playerLevelInfo.leastAmtCommands = -1;
		playerLevelInfo.leastAmtInstructs = -1;
		playerLevelInfo.level = -1;
		playerLevelInfo.levelHighScore = -1;
	};

	~profileManager();

	string					getPlayerName();
	int						getPlayerHighestLevel();
	int						getPlayerCurrentLevel();
	vector<levelInfo>		getPlayerLevelInfo();
	void					setPlayerName(string);
	void					setPlayerHighestLevel(int);
	void					setPlayerCurrentLevel(int);
	void					setPlayerLevelInfo(int, int, int, int);
};

#endif