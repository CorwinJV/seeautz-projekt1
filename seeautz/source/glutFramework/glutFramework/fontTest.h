#ifndef FONTTEST_H
#define FONTTEST_H

#include "GameState.h" 
#include ".\States\MainMenuState.h"
#include "oglTexture2D.h"
#include "oglGameVars.h"
#include<fstream>
#include<iostream>
#include <string>
#include "oglSpriteFont.h"

class fontTest: public GameState
{
public:
	fontTest()
	{		
	}
	~fontTest();
	fontTest(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		oglSpriteFont* courier;
		for(int x = 12; x < 100; x+=5)
		{
			courier = new oglSpriteFont();
			courier->open("fonts\\courierSpriteFontWhite.png", x);
			fontList.push_back(courier);			
		}
	}

	bool fontTest::Draw()
	{
		vector<oglSpriteFont*>::iterator fitr = fontList.begin();
		int x = 0;
		for(;fitr < fontList.end(); fitr++)
		{
			x++;
			(*fitr)->drawText(15, 25*x, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
		}
		return true;
	}

	
private:
	vector<oglSpriteFont*> fontList;
	void keyboardInput(unsigned char c, int x, int y)
	{
		vector<oglSpriteFont*>::iterator fitr = fontList.begin();
		switch(c)
		{
		case '1':
			for(;fitr < fontList.end(); fitr++)
			{
				(*fitr)->less();
			}
			break;
		case '2':
			for(;fitr < fontList.end(); fitr++)
			{
				(*fitr)->more();
			}
			break;
		case '3':
			for(;fitr < fontList.end(); fitr++)
			{
				(*fitr)->lessb();
			}
			break;
		case '4':
			for(;fitr < fontList.end(); fitr++)
			{
				(*fitr)->moreb();
			}
			break;
		}
	}

};

#endif