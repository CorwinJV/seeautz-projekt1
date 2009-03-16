#include "profileManager.h"

#include <string>
#include <vector>
using namespace std;

string profileManager::getPlayerName()
{
	return playerName;
}

int profileManager::getPlayerHighestLevel()
{
	return playerHighestLevel;
}

int profileManager::getPlayerCurrentLevel()
{
	return playerCurrentLevel;
}
	
void profileManager::getPlayerLevelInfo()
{
}
	
void profileManager::setPlayerName(string name)
{
	playerName = name;
}
	
void profileManager::setPlayerHighestLevel(int level)
{
	playerHighestLevel = level;
}
	
void profileManager::setPlayerCurrentLevel(int level)
{
	playerCurrentLevel = level;
}
	
void profileManager::setPlayerLevelInfo(int commands, int instructs, int level, int score)
{
}