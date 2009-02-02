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
{ 
	//... perform necessary instance initializations 
}

//========================================
// Non singleton functions here wee.
std::string oglGameVars::getPlayerName()
{
	return "tmpString yay";
}