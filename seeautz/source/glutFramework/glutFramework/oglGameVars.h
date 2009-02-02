#ifndef OGLGAMEVARS_H
#define OGLGAMEVARS_H

#include <string>
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
	std::string getPlayerName();
protected:
    oglGameVars();
    oglGameVars(const oglGameVars&);
    oglGameVars& operator= (const oglGameVars&);
private:
    static oglGameVars* pinstance;
};

#endif // OGLGAMEVARS_H