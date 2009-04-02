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
	fontArial18.open	("fonts\\arial.ttf", 18);
	fontArial12.open	("fonts\\arial.ttf", 12);
	//fontCourier24.open	("fonts\\cour.ttf", 24);
	//fontCourier18.open	("fonts\\cour.ttf", 18);
	//fontCourier12.open	("fonts\\cour.ttf", 12);
	fontDigital64.open	("fonts\\DIGIRU__.ttf", 32);
	fontDigital200.open	("fonts\\DIGIRU__.ttf", 200);
	fontDigital32.open  ("fonts\\DIGIRU__.ttf", 32);
	fontDigital16.open  ("fonts\\DIGIRU__.ttf", 16);
	fontOurs.open		("fonts\\Schwaben_Alt_Bold.ttf", 32);
//	fontTimes.open		("fonts\\times.ttf", 32);
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

	tempLevel = new levelData("Instruction Tutorial 5", "Jumping", "maps\\tutorialMap5.txt");
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
	PI = new playerInfo(maxLevel);
	PM = new profileManager(maxLevel);
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


bool oglGameVars::updatePlayerFile() 
{
	// get the players name and ensure it isn't set to blank which would 
	// break our vector
	string playerGame;
	playerGame = GameVars->getPlayerName();

	if (playerGame == "")
	{
		playerGame = "defaultgame.txt";
		GameVars->setPlayerName(playerGame);
	}

	//cout << "Saving Game...  " << playerGame << endl;

	//should this go through a for loop here to check the player name 
	//against the database for a match?

	ofstream PlayerInfo;
	string tempString;
	int highLevel;
	int curLevel;
	int levelHighScore;
	int playerLevelScore;
	int leastAmtCmds;
	int playerCmds;
	//int leastAmtInstructs;		// this will get used once implemented
	//int playerInstructs;		// this too
	bool inGame;
	
		// below are varible that will need to functions implemented for them to work properly
		// once we are able to save our position on the map
		// also need functionality for what switches have been flipped if saved in midlevel
		// and possibly number of reprogrammable squares used and bytes remaining
	int xPos = 0;
	int yPos = 0;
	int remainingBytes = 0;
	int levelBytes = 0;
	int bytesUsed = 0;
	int isActive = -1;
	int height;
	int width;
	//bool activeTile;
	
	// see if we are saving in game or between levels
	inGame = GameVars->getGameStatus();

	curLevel = getCurrentLevel();

	// get which level the player just completed for stat comparisons
	// initialize variables for max level, level score, least amount of 
	// commands used and least instructions used to compare against the 
	// stats in the vector

	playerLevelScore = GameVars->getLevelScore();
	levelHighScore = GameVars->PM->getPlayerLevelScore(curLevel);

	leastAmtCmds = GameVars->PM->getPlayerLeastCmd(curLevel);
	playerCmds = GameVars->getLevelCommands();

	//uncomment these once functionality is in place
	/*leastAmtInstructs = GameVars->PM->getPlayerLeastInst();
	playerInstructs = GameVars->getLevelInstructions();*/

	highLevel = getPlayerMaxLevel();
	//curLevel = getCurrentLevel();

	//in all cases, keep the better stats by replacing them
	//also if stats are set to the initialized value of -1
	//save over them
	
	if(playerLevelScore > levelHighScore)
	{
		GameVars->PM->setPlayerLevelScore(curLevel, playerLevelScore);
	}

	if((playerCmds < leastAmtCmds) || (leastAmtCmds == -1))
	{
		GameVars->PM->setPlayerLeastCmd(curLevel, playerCmds);
	}

	//following can be uncommented once we implement it
	/*if((playerInstructs < leastAmtInstructs) || (leastAmtInstructs == -1))
	{
		GameVars->PM->setPlayerLeastInst(level, playerInstructs);
	}*/
	

	//below only needs to be implemented if/when we do in game saves
	/*if(inGame)
	{
		PlayerInfo << xPos << " ";
		PlayerInfo << yPos << " ";
	}*/

	// unless we are saving in the middle of a level, increment the level. 
	// otherwise store the map information.
	if(!inGame)
		curLevel++;
	else
	{
		// following is only used should we implement in game saves
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
				// by implementing a function in oglGameVars probably reading off a dump file 
				// that uses the players name
			}
		}
	}

	if(curLevel > highLevel)
	{
		highLevel = curLevel;
		GameVars->setPlayerMaxLevel(highLevel);
		GameVars->PM->setPlayerHighestLevel(highLevel);
	}

	GameVars->PM->saveProfile();

	return true;
}

bool oglGameVars::LoadPlayerGame(string playerGame) 
{	
	
	//cout << "Loading Game...: " << playerGame <<std::endl;
	//ifstream PlayerInfo;
	//string tempString;
	//int score;
	//int level;
	//string playerName;
	//int tempInt;

	//tempString = "savedGames\\";
	//tempString += playerGame.c_str();
	//
	//if(!PlayerInfo)
	//	return false;

	//PlayerInfo.open(tempString.c_str());

	//// code for loading player stats here
	//PlayerInfo >> level;
	//GameVars->setPlayerMaxLevel(level);

	//PlayerInfo >> score;
	//GameVars->setTotalScore(score);

	//PlayerInfo >> playerName;
	//GameVars->setPlayerName(playerName);

	//PlayerInfo.close();
	
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

	tmpBlock = new logicBlock("instructions/moveforward.png", 130, 130, "Move Forward         Use this instruction to move forward one  tile.", 2, MOVE_FORWARD1);
	tmpBlock->addInstruction(MOVE_FORWARD1);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/moveforwarduntilunable.png", 130, 130, "Move Forward Until   Use this instruction to move forward untilyou are unable to    move forward any     more, or die.", 8, MOVE_FORWARD_UNTIL_UNABLE);
	tmpBlock->addInstruction(MOVE_FORWARD_UNTIL_UNABLE);
	allLogicBlocks.push_back(tmpBlock);
	
	tmpBlock = new logicBlock("instructions/turnleft.png", 130, 130, "Rotate Left          Use this instruction to rotate left.", 2, TURN_LEFT1);
	tmpBlock->addInstruction(TURN_LEFT1);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/turnright.png", 130, 130, "Rotate Right         Use this instruction to rotate right.", 2, TURN_RIGHT1);
	tmpBlock->addInstruction(TURN_RIGHT1);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/punch.png", 130, 130, "Punch                Use this instruction to break breakable   walls.", 4, PUNCH);
	tmpBlock->addInstruction(PUNCH);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/climb.png", 130, 130, "Climb                Use this instruction to climb up to a     higher level.", 4, CLIMB);
	tmpBlock->addInstruction(CLIMB);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/crouch.png", 130, 130, "Crouch               Use this instruction to crawl through     small holes.", 4, CROUCH);
	tmpBlock->addInstruction(CROUCH);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/jump.png", 130, 130, "Jump                 Use this instruction to jump over most    obstacles.", 8, JUMP);
	tmpBlock->addInstruction(JUMP);
	allLogicBlocks.push_back(tmpBlock);

	//tmpBlock = new logicBlock("instructions/loop.png", 130, 130, "Use this instruction to loop.", 2, LOOP);
	//tmpBlock->addInstruction(LOOP);
	//allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/activate.png", 130, 130, "Activate             Use this instruction to activate Doors,   Switches and to use  Reprogram Tiles.", 2, ACTIVATE);
	tmpBlock->addInstruction(ACTIVATE);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/sub1.png", 130, 130, "Sub 1                Use this instruction to call Subroutine 1.", 2, SUBR1);
	tmpBlock->addInstruction(SUBR1);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/sub2.png", 130, 130, "Sub 2                Use this instruction to call Subroutine 2.", 2, SUBR2);
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

	for(int i = 0; i < (int)allLogicBlocks.size(); i++)
	{
		allLogicBlocks[i]->isUsable = true;
		allLogicBlocks[i]->isCurrentlyUsable = true;
	}

	currentLogicBank->push_back(allLogicBlocks[0]);
	if(!moveForwardAvail)
	{
		currentLogicBank->back()->isUsable = false;
	}
	
	currentLogicBank->push_back(allLogicBlocks[1]);
	if(!moveForwardUntilAvail)
	{
		currentLogicBank->back()->isUsable = false;
	}
	
	currentLogicBank->push_back(allLogicBlocks[2]);
	if(!turnLeftAvail)
	{
		currentLogicBank->back()->isUsable = false;
	}

	currentLogicBank->push_back(allLogicBlocks[3]);
	if(!turnRightAvail)
	{
		currentLogicBank->back()->isUsable = false;
	}	

	currentLogicBank->push_back(allLogicBlocks[4]);
	if(!punchAvail)
	{
		currentLogicBank->back()->isUsable = false;
	}
	
	currentLogicBank->push_back(allLogicBlocks[5]);	
	if(!climbAvail)
	{
		currentLogicBank->back()->isUsable = false;
	}

	currentLogicBank->push_back(allLogicBlocks[6]);
	if(!crouchAvail)	
	{
		currentLogicBank->back()->isUsable = false;
	}
	
	currentLogicBank->push_back(allLogicBlocks[7]);
	if(!jumpAvail)
	{
		currentLogicBank->back()->isUsable = false;
	}

	currentLogicBank->push_back(allLogicBlocks[8]);
	if(!activateAvail)
	{
		currentLogicBank->back()->isUsable = false;
	}	
	
	currentLogicBank->push_back(allLogicBlocks[9]);
	if(!sub1Avail)
	{
		currentLogicBank->back()->isUsable = false;
	}	

	currentLogicBank->push_back(allLogicBlocks[10]);	
	if(!sub2Avail)
	{
		currentLogicBank->back()->isUsable = false;
	}
}

void oglGameVars::setPMStatus(int status)
{
	pmStatus = status;
}

int oglGameVars::getPMStatus()
{
	return pmStatus;
}

void oglGameVars::setLevelCommands(int commands)
{
	levelCommands = commands;
}

void oglGameVars::setLevelInstructions(int instructions)
{
	levelInstructions = instructions;
}

int oglGameVars::getLevelCommands()
{
	return levelCommands;
}

int oglGameVars::getLevelInstructions()
{
	return levelInstructions;
}