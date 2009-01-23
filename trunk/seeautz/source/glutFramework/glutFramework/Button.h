#ifndef BUTTONS_H
#define BUTTONS_H
#include "GameState.h"
#include "pixmap.h"
#include <cstring>
#include <iostream>

//class Button; 

class Button 
{
protected:
   // int buttonHeight;
   // int buttonWidth;
	int		buttonXPos;
	int		buttonYPos;
	State	buttonStatus;
	pixmap* normal;
	pixmap* clicked;
	pixmap* hover;

public:
	Button();
	Button(int, int, std::string, std::string, std::string);
	~Button();
	
	virtual void	setButtonStatus(State buttonStatus);
	virtual int		getHeight();
	virtual int		getWidth();
	virtual State	getButtonStatus();
	virtual void	setButtonXPos(int position);
	virtual void	setButtonYPos(int position);
	virtual void	setButtonXYPos(int xPos, int yPos);
	virtual int		getXPos();
	virtual int		getYPos();
	virtual bool	Initialize();
	virtual bool	Update();
    virtual bool	Draw();
	virtual bool	Remove();
};

#endif
