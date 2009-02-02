#include "oglGameVars.h"

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
	//... perform necessary instance initializations 
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