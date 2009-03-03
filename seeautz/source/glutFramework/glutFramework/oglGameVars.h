#ifndef OGLGAMEVARS_H
#define OGLGAMEVARS_H
#include<fstream>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include "logicBlock.h"
#include "aiInstructionEnums.h"
#include "GLFT_Font.h"

#define GameVars oglGameVars::Instance()

using namespace std;


//===========================
// oglGameVars
//    This class is based on
// the singleton design pattern
// popularized in the GoF book:
// "Design Patterns".
// - CJV

class oglGameVars 
{
public:
    static oglGameVars* Instance();
protected:
    oglGameVars();
    oglGameVars(const oglGameVars&);
    oglGameVars& operator= (const oglGameVars&);
private:
    static oglGameVars* pinstance;

	//===============================================
	// Non singleton functions and data members here
	//===============================================
public:
	std::string					getPlayerName();
	void						setPlayerName(std::string name);
	void						loadAllLogicBlocks();
	std::vector<logicBlock*>*	oglGameVars::getAllLogicBlocks();
	logicBlock*					getPlaceInstructionBlock();
	bool						LoadPlayerGame(string name);
	bool						SavePlayerGame(string name);
	int							getTotalScore();
	int							getLevelScore();
	void						setLevelScore(int score);
	void						setTotalScore(int score);
	void						setMaxLevel(int newMax);
	void						setPlayerMaxLevel(int level);
	int							getMaxLevel();
	int							getCurrentLevel();
	int							getCurrentLevelBytes();
	void						setLevel(int);
	void						setCurrentLevelBytes(int newBytes);
	void						setCurrentLogicBank(bool moveForwardAvail, bool moveForwardUntilAvail, bool turnLeftAvail, bool turnRightAvail,
													bool punchAvail, bool climbAvail, bool crouchAvail, bool jumpAvail, bool activateAvail, bool sub1Avail, bool sub2Avail);
	std::vector<logicBlock*>*	GetCurrentMapLogicBank();
	vector<logicBlock*>			*currentLogicBank;
	GLFT_Font					fontTimes;
	GLFT_Font					fontArial;
	GLFT_Font					fontArial12;
	GLFT_Font					fontDigital;
	GLFT_Font					fontOurs;
	GLFT_Font					fontDigital200;

private:				
	std::string mPlayerName;
	int mTotalScore;
	int currentLevel;
	int maxLevel;
	int playerMaxLevel;
	int levelScore;
	int currentLevelBytes;
	std::vector<logicBlock*>	allLogicBlocks;
	logicBlock*					placeInstructionBlock;
	
};

struct levelData
{
private:
	std::string		levelName;
	std::string		description;
	std::string		fileName;

public:
	levelData(std::string lvlName, std::string desc, std::string file)
	{
		levelName = lvlName;
		description = desc;
		fileName = file;
	}

	~levelData()
	{
		
	}

	std::string getName()
	{
		return levelName;
	};

	std::string getDesc()
	{
		return description;
	};

	std::string getFile()
	{
		return fileName;
	};

};

#endif // OGLGAMEVARS_H