#include "oglGameVars.h"
#include<fstream>
#include<iostream>
#include <string>
using namespace std;

oglGameVars* oglGameVars::pinstance = 0;// initialize pointer

oglGameVars* oglGameVars::Instance () 
{
	if (pinstance == 0)  // is it the first call?
	{  
	  pinstance = new oglGameVars; // create sole instance
	}
	return pinstance; // address of sole instance
}

oglGameVars::oglGameVars()
: mTotalScore(0), mPlayerName("")
{ 
	loadAllLogicBlocks();

	mTotalScore = 0;
	currentLevel = 1;
	maxLevel = 1;
	playerMaxLevel = 1;
	levelScore = 0;
	currentLevelBytes = 1;
	levelSpecified = -1;
	inGame = false;
	commandsProcessed = 0;
	totalCommandsProcessed = 0;
	
	// font loading
	fontArial32.open	("fonts\\arial.ttf", 32);
	fontArial24.open	("fonts\\arial.ttf", 24);
	fontArial12.open	("fonts\\arial.ttf", 12);
	fontDigital64.open	("fonts\\DIGIRU__.ttf", 32);
	fontDigital200.open	("fonts\\DIGIRU__.ttf", 200);
	fontDigital32.open  ("fonts\\DIGIRU__.ttf", 32);
	fontDigital16.open  ("fonts\\DIGIRU__.ttf", 16);
	fontOurs.open		("fonts\\Schwaben_Alt_Bold.ttf", 32);
	fontTimes.open		("fonts\\times.ttf", 32);
	currentLogicBank = NULL;

	levelData* tempLevel;
	oglTexture2D* tempArt;

	tempLevel = new levelData("DEBUG MAP", "THIS IS FOR DAVE TO DEBUG MAP TILES", "maps\\testMap1.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\tutorialMap1.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Instruction Tutorial 1", "Using Activate to Open a Door", "maps\\tutorialMap1.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\tutorialMap1.png", 300, 150);
	levelArt.push_back(tempArt);
	
	tempLevel = new levelData("Instruction Tutorial 2", "Moving and Turning", "maps\\tutorialMap2.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\tutorialMap2.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Instruction Tutorial 3", "Moving Forward Until Unable", "maps\\tutorialMap3.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\tutorialMap3.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Instruction Tutorial 4", "Crouching", "maps\\tutorialMap4.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\tutorialMap4.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Instruction Tutorial 5", "Climbing and Jumping", "maps\\tutorialMap5.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\tutorialMap5.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Instruction Tutorial 6", "Punching", "maps\\tutorialMap6.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\tutorialMap6.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Instruction Tutorial 7", "Complete Instructions Tutorial", "maps\\tutorialMap7.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\tutorialMap7.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Tile Tutorial Map 1", "Climb Up to Higher Levels", "maps\\tileTutorialMap1.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\tileTutorialMap1.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Tile Tutorial Map 2", "Ice is Slippery.", "maps\\tileTutorialMap2.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\tileTutorialMap2.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Tile Tutorial Map 3", "Switches Control Things and Electricity Hurts", "maps\\tileTutorialMap3.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\tileTutorialMap3.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Tile Tutorial Map 4", "Teleporting", "maps\\tileTutorialMap4.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\tileTutorialMap4.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Tile Tutorial Map 1 - Re-Visit", "Climb Up to Higher Levels - Subroutine Required", "maps\\tileTutorialMap1b.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\tileTutorialMap1b.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Map 1", "Map #1", "maps\\Map1.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\Map1.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Map 2", "Map #2", "maps\\Map2.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\Map2.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Map 3", "Map #3", "maps\\Map3.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\Map3.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Map 4", "Map #4", "maps\\Map4.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\Map4.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Map 5", "Map #5", "maps\\Map5.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\Map5.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Map 6", "6 #6", "maps\\Map6.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\Map6.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Map 7", "7 #7", "maps\\Map7.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\Map7.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Map 8", "H2O #8", "maps\\Map8.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\Map8.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Map 9", "9 #9", "maps\\Map9.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\Map9.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Map 10", "10 #10", "maps\\Map10.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\Map10.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Map 11", "Insanity #1", "maps\\Map11.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\Map11.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Map 12", "Insanity #2", "maps\\Map12.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\Map12.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Map 13", "Insanity #3", "maps\\Map13.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\Map13.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Map 14", "Insanity #4", "maps\\Map14.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\Map14.png", 300, 150);
	levelArt.push_back(tempArt);

	tempLevel = new levelData("Map 15", "Insanity #5", "maps\\Map15.txt");
	levelList.push_back(tempLevel);
	tempArt = new oglTexture2D;
	tempArt->loadImage("maps\\Map15.png", 300, 150);
	levelArt.push_back(tempArt);

	maxLevel = levelList.size();
	// stupid sound stuff
	//GenericSound = new OALSound;
}

//========================================
// Non singleton functions here wee.
string oglGameVars::getPlayerName()
{
	return mPlayerName;
}

void oglGameVars::setPlayerName(string sname)
{
	mPlayerName = sname;
}

void oglGameVars::setLevelSpecified(int level)
{
	levelSpecified = level;
}

int oglGameVars::getLevelSpecified()
{
	return levelSpecified;
}

int oglGameVars::getRobotX()
{
	return robotXPos;
}

int oglGameVars::getRobotY()
{
	return robotYPos;
}

void oglGameVars::setRobotX(int x)
{
	robotXPos = x;
}

void oglGameVars::setRobotY(int y)
{
	robotYPos = y;
}

void oglGameVars::setLevelHeight(int height)
{
	levelHeight = height;
}

void oglGameVars::setLevelWidth(int width)
{
	levelWidth = width;
}

int oglGameVars::getLevelHeight()
{
	return levelHeight;
}

int oglGameVars::getLevelWidth()
{
	return levelWidth;
}

bool oglGameVars::getTileActive(int x, int y)
{
	return tileActive;
}

std::string oglGameVars::getFilename(int level)
{

	return levelList[level]->getFile();
}

std::string oglGameVars::getDesc(int level)
{
	return levelList[level]->getDesc();
}

std::string oglGameVars::getLevelName(int level)
{
	return levelList[level]->getName();
}

void oglGameVars::setBytesUsed(int val)
{
	curBytesUsed = val;
}

int oglGameVars::getBytesUsed()
{
	return curBytesUsed;
}


bool oglGameVars::SavePlayerGame() 
{
	//bool saved = false;
	string playerGame;

	playerGame = GameVars->getPlayerName() + ".txt";

	if (playerGame == ".txt")
	{
		playerGame = "defaultgame.txt";
	}

	cout << "Saving Game...  " << playerGame << endl;
	
	ofstream PlayerInfo;
	string tempString;
	int level;
	int score;
	bool inGame;
	string playerName;
	
					// below are varible that will need to functions implemented for them to work properly
					// once we are able to save our position on the map
					// also need functionality for what switches have been flipped if saved in midlevel
					// and possibly number of reprogrammable squares used and bytes remaining
	int xPos = 0;
	int yPos = 0;
	int remainingBytes = 0;
	int playerMaxLevel = 0;
	int levelBytes = 0;
	int bytesUsed = 0;
	int isActive = -1;
	int height;
	int width;
	bool activeTile;
	

	inGame = GameVars->getGameStatus();

	tempString = "savedGames\\";
	tempString += playerGame.c_str();

	PlayerInfo.open(tempString.c_str());

	if(!PlayerInfo)
		return false;

	playerMaxLevel = GameVars->getPlayerMaxLevel();
	level = GameVars->getCurrentLevel();

	if(level > playerMaxLevel)
	{
		playerMaxLevel = level;
		GameVars->setPlayerMaxLevel(level);
	}

	// unless we are saving in the middle of a level, increment the level. 
	// otherwise store the map information.
	if(!inGame)
		level++;
	else
	{
		xPos = GameVars->getRobotX();
		yPos = GameVars->getRobotY();
		bytesUsed = GameVars->getBytesUsed();
		levelBytes = GameVars->getCurrentLevelBytes();
		int remaingingBytes = levelBytes - bytesUsed;

		width = GameVars->getLevelWidth();
		height = GameVars->getLevelHeight();
		for(int i = 0; i < width; i++)
		{
			for(int j = 0; j < height; j++)
			{

				// see if tile is active or not based off of the gameboard info
				// by implementing a function in oglGameVars 
			}
		}

	}

	GameVars->setPlayerMaxLevel(level);

	score = GameVars->getTotalScore();
	playerName = GameVars->getPlayerName();

	// code for saving stats here
	PlayerInfo << level << endl;
	PlayerInfo << score << endl;
	PlayerInfo << playerName << endl;

	if(inGame)
	{
		PlayerInfo << xPos << " ";
		PlayerInfo << yPos << " ";
	}

	PlayerInfo.close();

	//saved = true;
	//if (playerGame == ".txt")
	//{
	//	playerGame = "defaultgame.txt";
	//}

	//cout << "Saving Game...  " << playerGame << endl;
	//
	//ofstream PlayerInfo;
	//string tempString;
	//int level;
	//int score;
	//string playerName;
	//
	//// below are varible that will need to functions implemented for them to work properly
	//// once we are able to save our position on the map
	//// also need functionality for what switches have been flipped if saved in midlevel
	//// and possibly number of reprogrammable squares used and bytes remaining
	//int xPos = 0;
	//int yPos = 0;
	//int switchesFlipped = 0;
	//int remainingBytes = 0;
	//int playerMaxLevel = 0;

	//tempString = "savedGames\\";
	//tempString += playerGame.c_str();

	//PlayerInfo.open(tempString.c_str());

	//if(!PlayerInfo)
	//	return false;

	//playerMaxLevel = GameVars->getPlayerMaxLevel();
	//level = GameVars->getCurrentLevel();

	//if(level > playerMaxLevel)
	//	playerMaxLevel = level;

	//GameVars->setPlayerMaxLevel(level);

	//score = GameVars->getTotalScore();
	//playerName = GameVars->getPlayerName();

	//// code for saving stats here
	//PlayerInfo << level << endl;
	//PlayerInfo << score << endl;
	//PlayerInfo << playerName << endl;

	//PlayerInfo.close();

	return true;
}

bool oglGameVars::LoadPlayerGame(string playerGame) 
{	
	cout << "Loading Game...: " << playerGame <<std::endl;
	ifstream PlayerInfo;
	string tempString;
	int score;
	int level;
	string playerName;

	tempString = "savedGames\\";
	tempString += playerGame.c_str();
	
	if(!PlayerInfo)
		return false;

	PlayerInfo.open(tempString.c_str());

	// code for loading player stats here
	PlayerInfo >> level;
	GameVars->setPlayerMaxLevel(level);

	PlayerInfo >> score;
	GameVars->setTotalScore(score);

	PlayerInfo >> playerName;
	GameVars->setPlayerName(playerName);

	PlayerInfo.close();
	
	return true;
}

void oglGameVars::setCurrentLevel(int level)
{
	currentLevel = level;
}

void oglGameVars::setGameStatus(bool status)
{
	inGame = status;
}

bool oglGameVars::getGameStatus()
{
	return inGame;
}

void oglGameVars::loadAllLogicBlocks()
{
	logicBlock* tmpBlock;

	tmpBlock = new logicBlock("instructions/moveforward.png", 130, 130, "Use this instruction to moveforward one   tile.", 2, MOVE_FORWARD1);
	tmpBlock->addInstruction(MOVE_FORWARD1);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/moveforwarduntilunable.png", 130, 130, "Use this instruction to moveforward until you are unable.", 8, MOVE_FORWARD_UNTIL_UNABLE);
	tmpBlock->addInstruction(MOVE_FORWARD_UNTIL_UNABLE);
	allLogicBlocks.push_back(tmpBlock);
	
	tmpBlock = new logicBlock("instructions/turnleft.png", 130, 130, "Use this instruction to turn left.", 2, TURN_LEFT1);
	tmpBlock->addInstruction(TURN_LEFT1);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/turnright.png", 130, 130, "Use this instruction to turn right.", 2, TURN_RIGHT1);
	tmpBlock->addInstruction(TURN_RIGHT1);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/punch.png", 130, 130, "Use this instruction to break breakable   walls.", 4, PUNCH);
	tmpBlock->addInstruction(PUNCH);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/climb.png", 130, 130, "Use this instruction to climb over small  inclines.", 4, CLIMB);
	tmpBlock->addInstruction(CLIMB);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/crouch.png", 130, 130, "Use this instruction to crouch in order tocrawl through small  spaces.", 4, CROUCH);
	tmpBlock->addInstruction(CROUCH);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/jump.png", 130, 130, "Use this instruction to jump up a level.", 8, JUMP);
	tmpBlock->addInstruction(JUMP);
	allLogicBlocks.push_back(tmpBlock);

	//tmpBlock = new logicBlock("instructions/loop.png", 130, 130, "Use this instruction to loop.", 2, LOOP);
	//tmpBlock->addInstruction(LOOP);
	//allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/activate.png", 130, 130, "Use this instruction to activate Doors, Switches and Reprogram Tiles.", 2, ACTIVATE);
	tmpBlock->addInstruction(ACTIVATE);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/sub1.png", 130, 130, "Use this instruction to call Subroutine 1.", 2, SUBR1);
	tmpBlock->addInstruction(SUBR1);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/sub2.png", 130, 130, "Use this instruction to call Subroutine 2.", 2, SUBR2);
	tmpBlock->addInstruction(SUBR2);
	allLogicBlocks.push_back(tmpBlock);

	placeInstructionBlock = new logicBlock("instructions/place_new_instruction.png", 130, 130, "Place a new instruction here.", 0, DO_NOT_PROCESS);
}

std::vector<logicBlock*>* oglGameVars::getAllLogicBlocks()
{
	return &allLogicBlocks;
}

logicBlock*	oglGameVars::getPlaceInstructionBlock()
{
	return placeInstructionBlock;
}

std::vector<logicBlock*>*	oglGameVars::GetCurrentMapLogicBank()
{
	return currentLogicBank;
}


int oglGameVars::getTotalScore()
{
	return mTotalScore;
}

int oglGameVars::getPlayerMaxLevel()
{
	return playerMaxLevel;
}

int	oglGameVars::getLevelScore()
{
	return levelScore;
}

int	oglGameVars::getCurrentLevel()
{
	return currentLevel;
}

void oglGameVars::setLevel(int level)
{
	currentLevel = level;
}

int oglGameVars::getCurrentLevelBytes()
{
	return currentLevelBytes;
}

void oglGameVars::setCurrentLevelBytes(int newBytes)
{
	currentLevelBytes = newBytes;
}

void oglGameVars::setMaxLevel(int newMax)
{
	maxLevel = newMax;
}

void oglGameVars::setPlayerMaxLevel(int level)
{
	playerMaxLevel = level;
}

int oglGameVars::getMaxLevel()
{
	return maxLevel;
}

void oglGameVars::setLevelScore(int score)
{
	levelScore = score;
}
	
void oglGameVars::setTotalScore(int score)
{
	mTotalScore = score;
}

void oglGameVars::setCurrentLogicBank(bool moveForwardAvail, bool moveForwardUntilAvail, bool turnLeftAvail, 
									  bool turnRightAvail, bool punchAvail, bool climbAvail, bool crouchAvail, 
									  bool jumpAvail, bool activateAvail, bool sub1Avail, bool sub2Avail)
{
	if(currentLogicBank != NULL)
		delete currentLogicBank;
	
	currentLogicBank = new vector<logicBlock*>;

	if(moveForwardAvail)
		currentLogicBank->push_back(allLogicBlocks[0]);

	if(moveForwardUntilAvail)
		currentLogicBank->push_back(allLogicBlocks[1]);
	
	if(turnLeftAvail)
		currentLogicBank->push_back(allLogicBlocks[2]);

	if(turnRightAvail)
		currentLogicBank->push_back(allLogicBlocks[3]);

	if(punchAvail)
		currentLogicBank->push_back(allLogicBlocks[4]);

	if(climbAvail)
		currentLogicBank->push_back(allLogicBlocks[5]);

	if(crouchAvail)
		currentLogicBank->push_back(allLogicBlocks[6]);

	if(jumpAvail)
		currentLogicBank->push_back(allLogicBlocks[7]);

	if(activateAvail)
		currentLogicBank->push_back(allLogicBlocks[8]);

	if(sub1Avail)
		currentLogicBank->push_back(allLogicBlocks[9]);

	if(sub2Avail)
		currentLogicBank->push_back(allLogicBlocks[10]);
}