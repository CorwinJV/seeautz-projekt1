#include "ogIApp.h"
#ifndef BUTTONS_H
#define BUTTONS_H
#include "GameState.h"
#include "pixmap.h"

//class Button; 

class Button : public GameState
{
protected:
    int buttonHeight;
    int buttonWidth;
	int buttonXPos;
	int buttonYPos;
	State buttonStatus;
	stupidGraphicsType fuckingPointers thisIsForWhenTheButtonIsNotBeingHoveredOverByTheMouseOrBeingClicked ;
	stupidGraphicsType fuckingPointers thisIsUnlikeTheAboveImageAndIsForWhenTheUserClicksOntoTheButtonWithTheMouse ;
	stupidGraphicsType fuckingPointers andFinallyThisIsForWhenTheUserIsNotClickingTheMouseButIsJustHoveringOverItWithTheMouse ;

public:
	Button();
	~Button();
	
	virtual void setButtonStatus(State buttonStatus);
	virtual State getButtonStatus();
	virtual void setButtonXPos(int position);
	virtual void setButtonYPos(int position);
	virtual int getXPos();
	virtual int getYPos();
	virtual bool Initialize();
	virtual bool Update();
    virtual bool Draw();
	virtual bool Remove();
};

#endif


//
//pixmap* hover;
//pixmap* depressed;
//pixmap* unexceptional;