#ifndef OGLGAMEVARS_H
#define OGLGAMEVARS_H
#include <fstream>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include "logicBlock.h"
#include "aiInstructionEnums.h"
#include "GLFT_Font.h"
#include "gameBoard.h"
#include "profileManager.h"
#include <cstring>
#include "switchManager.h"

#define GameVars oglGameVars::Instance()

using namespace std;

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
	};

	~levelData()
	{
		
	};

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
	playerInfo* PI;
	profileManager* PM;
	switchManager* SM;

	vector<string> didYouKnow;
	vector<string>::iterator didYouKnowI;
protected:
    oglGameVars();
    oglGameVars(const oglGameVars&);
    oglGameVars& operator= (const oglGameVars&);
private:
    static oglGameVars* pinstance;
	vector<levelData*> levelList;
	void loadAllLevels();
	void loadDidYouKnow();
	void loadFonts();

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
	bool						updatePlayerFile();
	int							getTotalScore();
	int							getLevelScore();
	void						setLevelScore(int score);
	void						setTotalScore(int score);
	void						setMaxLevel(int newMax);
	void						setPlayerMaxLevel(int level);
	void						setLevelSpecified(int level);
	int							getLevelSpecified();
	int							getMaxLevel();
	int							getPlayerMaxLevel();
	int							getCurrentLevel();
	int							getCurrentLevelBytes();
	bool						getGameStatus();
	void						setGameStatus(bool);
	void						setLevel(int);
	void						setPMStatus(int);
	int							getPMStatus();
	int							getRobotX();
	int							getRobotY();
	void						setRobotX(int);
	void						setRobotY(int);
	int							getLevelHeight();
	int							getLevelWidth();
	void						setLevelHeight(int);
	void						setLevelWidth(int);
	void						setLevelCommands(int);
	void						setLevelInstructions(int);
	int							getLevelCommands();
	int							getLevelInstructions();
	bool						getTileActive(int, int);
	std::string					getFilename(int);
	std::string					getDesc(int);
	std::string					getLevelName(int);
	void						setBytesUsed(int);
	int							getBytesUsed();
	void						setCurrentLevel(int);
	void						setCurrentLevelBytes(int newBytes);
	int							commandsProcessed;
	int							totalCommandsProcessed;
	void						setCurrentLogicBank(bool moveForwardAvail, bool moveForwardUntilAvail, bool turnLeftAvail, bool turnRightAvail,
													bool punchAvail, bool climbAvail, bool crouchAvail, bool jumpAvail, bool activateAvail, bool sub1Avail, bool sub2Avail);
	std::vector<logicBlock*>*	GetCurrentMapLogicBank();
	vector<logicBlock*>			*currentLogicBank;
	vector<oglTexture2D*> levelArt;
	int							numTutorialLevels;

//	GLFT_Font					fontTimes;
	GLFT_Font					fontArial32;
	GLFT_Font					fontArial24;
	GLFT_Font					fontArial18;
	GLFT_Font					fontArial16;
	GLFT_Font					fontArial12;
	GLFT_Font					fontDigital64;
	GLFT_Font					fontOurs;
	GLFT_Font					fontDigital200;
	GLFT_Font					fontDigital32;
	GLFT_Font					fontDigital16;
	GLFT_Font					fontDigital12;
	//GLFT_Font					fontCourier12;
	//GLFT_Font					fontCourier18;
	//GLFT_Font					fontCourier24;


private:				
	std::string mPlayerName;
	int mTotalScore;
	int currentLevel;
	int maxLevel;
	int playerMaxLevel;
	int levelScore;
	int levelCommands;
	int levelInstructions;
	int currentLevelBytes;
	int levelSpecified;
	bool inGame;
	int curBytesUsed;
	int robotXPos;
	int robotYPos;
	int levelHeight;
	int levelWidth;
	bool tileActive;
	int pmStatus;
	std::vector<logicBlock*>	allLogicBlocks;
	logicBlock*					placeInstructionBlock;	
};

#endif // OGLGAMEVARS_H
