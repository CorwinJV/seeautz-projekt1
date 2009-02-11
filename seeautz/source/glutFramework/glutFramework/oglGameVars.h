#ifndef OGLGAMEVARS_H
#define OGLGAMEVARS_H
#include<fstream>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include "logicBlock.h"
#include "aiInstructionEnums.h"



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
private:
	std::string mPlayerName;
	int mTotalScore;
	std::vector<logicBlock*>	allLogicBlocks;
	logicBlock*					placeInstructionBlock;
	
};

#endif // OGLGAMEVARS_H