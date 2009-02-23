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
	bool						LoadPlayerGame(std::string name);
	bool						SavePlayerGame(std::string name);
	int							getTotalScore();
	int							getLevelScore();
	int							getCurrentLevel();
	int							getCurrentLevelBytes();
	void						setLevel(int);
	void						setCurrentLevelBytes(int newBytes);
	GLFT_Font					fontTimes;
	GLFT_Font					fontArial;
	GLFT_Font					fontDigital;
	GLFT_Font					fontOurs;

private:				
	std::string mPlayerName;
	int mTotalScore;
	int currentLevel;
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