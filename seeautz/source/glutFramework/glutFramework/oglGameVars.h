#ifndef OGLGAMEVARS_H
#define OGLGAMEVARS_H

#include <string>
#include <vector>
#include "logicBlock.h"

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
	std::string		getPlayerName();
	void			setPlayerName(std::string name);

private:
	std::string mPlayerName;
	int mTotalScore;
	std::vector<logicBlock> allLogicBlocks;

};

#endif // OGLGAMEVARS_H