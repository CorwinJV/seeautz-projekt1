#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <string>

using namespace std;

struct levelInfo
{
	int level;
	int levelHighScore;
	int leastAmtCommands;
	int leastAmtInstructs;
};

class profileManager
{
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
	}

	string getPlayerName();
	int getPlayerHighestLevel();
	int getPlayerCurrentLevel();
	levelInfo getPlayerLevelInfo();
	void setPlayerName(string);
	void setPlayerHighestLevel(int);
	void setPlayerCurrentLevel(int);
	void setPlayerLevelInfo(int, int, int, int);

private:
	string playerName;
	int playerHighestLevel;
	int playerCurrentLevel;
	levelInfo playerLevelInfo;
};

#endif