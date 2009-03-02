#include "oglGameVars.h"
#include<fstream>
#include<iostream>
//#include<cstring>
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
	
	// font loading
	fontArial.open		("fonts\\arial.ttf", 32);
	fontArial12.open	("fonts\\arial.ttf", 12);
	fontDigital.open	("fonts\\DIGIRU__.ttf", 32);
	fontDigital200.open	("fonts\\DIGIRU__.ttf", 200);
	fontOurs.open		("fonts\\Schwaben_Alt_Bold.ttf", 32);
	fontTimes.open		("fonts\\times.ttf", 32);
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

bool oglGameVars::SavePlayerGame(string playerGame) 
{
	if (playerGame == ".txt")
	{
		playerGame = "defaultgame.txt";
	}

	cout << "Saving Game...  " << playerGame << endl;
	
	ofstream PlayerInfo;
	string tempString;
	int level;
	int score;

	tempString = "savedGames\\";
	tempString += playerGame.c_str();

	PlayerInfo.open(tempString.c_str());

	if(!PlayerInfo)
		return false;

	level = GameVars->currentLevel;
	if(level > playerMaxLevel)
		playerMaxLevel = level;

	GameVars->setPlayerMaxLevel(level);

	score = GameVars->getTotalScore();

	// code for saving stats here
	PlayerInfo << level << endl;
	PlayerInfo << score << endl;

	PlayerInfo.close();

	return true;
}

bool oglGameVars::LoadPlayerGame(string playerGame) 
{	
	cout << "Loading Game...: " << playerGame <<std::endl;
	ifstream PlayerInfo;
	string tempString;
	int score;
	int level;

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

	PlayerInfo.close();
	
	return true;
}

void oglGameVars::loadAllLogicBlocks()
{
	logicBlock* tmpBlock;

	tmpBlock = new logicBlock("instructions/moveforward.png", 130, 130, "Use this instruction to moveforward one   tile.", 2, MOVE_FORWARD1);
	tmpBlock->addInstruction(MOVE_FORWARD1);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/moveforwarduntilunable.png", 130, 130, "Use this instruction to moveforward until you are unable.", 2, MOVE_FORWARD_UNTIL_UNABLE);
	tmpBlock->addInstruction(MOVE_FORWARD_UNTIL_UNABLE);
	allLogicBlocks.push_back(tmpBlock);
	
	tmpBlock = new logicBlock("instructions/turnleft.png", 130, 130, "Use this instruction to turn left.", 2, TURN_LEFT1);
	tmpBlock->addInstruction(TURN_LEFT1);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/turnright.png", 130, 130, "Use this instruction to turn right.", 2, TURN_RIGHT1);
	tmpBlock->addInstruction(TURN_RIGHT1);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/punch.png", 130, 130, "Use this instruction to break breakable   walls.", 2, PUNCH);
	tmpBlock->addInstruction(PUNCH);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/climb.png", 130, 130, "Use this instruction to climb over small  inclines.", 2, CLIMB);
	tmpBlock->addInstruction(CLIMB);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/crouch.png", 130, 130, "Use this instruction to crouch in order tocrawl through small  spaces.", 2, CROUCH);
	tmpBlock->addInstruction(CROUCH);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/jump.png", 130, 130, "Use this instruction to jump up a level.", 2, JUMP);
	tmpBlock->addInstruction(JUMP);
	allLogicBlocks.push_back(tmpBlock);

	//tmpBlock = new logicBlock("instructions/loop.png", 130, 130, "Use this instruction to loop.", 2, LOOP);
	//tmpBlock->addInstruction(LOOP);
	//allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/activate.png", 130, 130, "Use this instruction to activate whatever is infront of you.", 2, ACTIVATE);
	tmpBlock->addInstruction(ACTIVATE);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/sub1.png", 130, 130, "Use this instruction to call Subroutine 1.", 2, SUBR1);
	tmpBlock->addInstruction(SUBR1);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/sub2.png", 130, 130, "Use this instruction to call Subroutine 2.", 2, SUBR2);
	tmpBlock->addInstruction(SUBR2);
	allLogicBlocks.push_back(tmpBlock);

	placeInstructionBlock = new logicBlock("instructions/place_new_instruction.png", 130, 130, "Place a new instruction here.", 2, DO_NOT_PROCESS);
}

std::vector<logicBlock*>* oglGameVars::getAllLogicBlocks()
{
	return &allLogicBlocks;
}

logicBlock*	oglGameVars::getPlaceInstructionBlock()
{
	return placeInstructionBlock;
}

int oglGameVars::getTotalScore()
{
	return mTotalScore;
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
	mTotalScore = score;
}
	
void oglGameVars::setTotalScore(int score)
{
	levelScore = score;
}