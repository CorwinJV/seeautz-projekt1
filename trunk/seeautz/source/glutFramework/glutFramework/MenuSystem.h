#ifndef MENUSYS_H
#define MENUSYS_H
#include "oglUtility.h"
#include "GameState.h"
#include "pixmap.h"

class MenuSys : public GameState
{
protected:
    int menuHeight;
    int menuWidth;
	int menuXPos;
	int menuYPos;

public:
	MenuSys();
	~MenuSys();
	
	virtual void setMenuXPos(int position);
	virtual void setMenuYPos(int position);
	virtual int getXPos();
	virtual int getYPos();
	virtual bool Initialize();
	virtual bool Update();
    virtual bool Draw();
	virtual bool Remove();
};

#endif