#ifndef STARTNEWGAMESTATE_H
#define STARTNEWGAMESTATE_H

#include ".\..\GameState.h" 
//#include ".\..\pixmap.h"
#include "MainMenuState.h"
#include "..\playGame.h"
#include ".\..\oglTexture2D.h"
#include<fstream>
#include<iostream>
#include <string>

using namespace std;

class StartNewGameState : public GameState
{
public:
	StartNewGameState() {};
	StartNewGameState(GameStateManager &Parent, int newID) : GameState(Parent, newID), img(NULL)
	{
		/*img = new oglTexture2D();
		if(img != NULL)
			img->loadImage("..\\Content\\statescreens\\startnewgame.png", 1024, 120);
		img->mY = 618;

		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\pregame.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &StartNewGameState::PreGameCallback));
		myMenu->addButton("..\\Content\\buttons\\something.png", "button2down.png", "button2over.png", CreateFunctionPointer0R(this, &StartNewGameState::tutorialCallback));*/
		finished = false;
		checked = false;
		Update();
	}

	bool StartNewGameState::Update();
	bool StartNewGameState::Draw();

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	void keyboardInput(unsigned char c, int x, int y);
	/*bool PreGameCallback();
	bool tutorialCallback();*/
	void setPlayerName(string);
	bool doesNameAlreadyExists(string);
	
	string tempString;

private:
	oglTexture2D* img;
	bool finished;
	bool checked;
	// add private stuff here
};

#endif