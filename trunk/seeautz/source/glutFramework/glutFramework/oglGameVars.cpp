#include "oglGameVars.h"
#include<fstream>
#include<iostream>
//#include<cstring>


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
}

//========================================
// Non singleton functions here wee.
std::string oglGameVars::getPlayerName()
{
	return mPlayerName;
}

void oglGameVars::setPlayerName(std::string name)
{
	mPlayerName = name;
}

bool oglGameVars::SavePlayerGame(std::string name) // AC
{
	std::cout << "Saving Game..." << name << std::endl;
	
	std::ofstream PlayerInfo;
	if(!PlayerInfo)
		return false;

	PlayerInfo.open(name.c_str());
	PlayerInfo.close();
	
	
	return true;
	

}
bool oglGameVars::LoadPlayerGame(std::string name) // AC
{
	
	std::cout << "Loading Game...: " << name <<std::endl;
	std::ifstream PlayerInfo;
	
	if(!PlayerInfo)
		return false;

	PlayerInfo.open(name.c_str());
	PlayerInfo.close();
	
	return true;
}
void oglGameVars::loadAllLogicBlocks()
{
	logicBlock* tmpBlock;

	tmpBlock = new logicBlock("instructions/moveforward.png", 130, 130, "Use this instruction to moveforward one tile.", 2, MOVE_FORWARD1);
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

	tmpBlock = new logicBlock("instructions/punch.png", 130, 130, "Use this instruction to break breakable walls.", 2, PUNCH);
	tmpBlock->addInstruction(PUNCH);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/climb.png", 130, 130, "Use this instruction to climb over small inclines.", 2, CLIMB);
	tmpBlock->addInstruction(CLIMB);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/crouch.png", 130, 130, "Use this instruction to crouch in order to crawl through small spaces.", 2, CROUCH);
	tmpBlock->addInstruction(CROUCH);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/jump.png", 130, 130, "Use this instruction to jump up a level.", 2, JUMP);
	tmpBlock->addInstruction(JUMP);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/loop.png", 130, 130, "Use this instruction to loop.", 2, LOOP);
	tmpBlock->addInstruction(LOOP);
	allLogicBlocks.push_back(tmpBlock);

	tmpBlock = new logicBlock("instructions/activate.png", 130, 130, "Use this instruction to activate whatever is infront of you.", 2, ACTIVATE);
	tmpBlock->addInstruction(ACTIVATE);
	allLogicBlocks.push_back(tmpBlock);
}

std::vector<logicBlock*>* oglGameVars::getAllLogicBlocks()
{
	return &allLogicBlocks;
}
