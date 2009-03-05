#ifndef LOADGAMESTATE_H
#define LOADGAMESTATE_H

#include ".\..\GameState.h" 
#include "MainMenuState.h"
#include "..\playGame.h"
#include ".\..\oglTexture2D.h"
#include<fstream>
#include<iostream>
#include <string>

using namespace std;

class LoadGameState : public GameState
{
public:
	LoadGameState() {};
	LoadGameState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		img = new oglTexture2D();
		if(img != NULL)
			img->loadImage("..\\Content\\statescreens\\loadgame.png", 1024, 120);
		img->mY = 618;

		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\pregame.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &LoadGameState::MainMenuCallback));
		myMenu->addButton("..\\Content\\buttons\\something.png", "button2down.png", "button2over.png", CreateFunctionPointer0R(this, &LoadGameState::tutorialCallback));

		finished = false;

		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	void LoadGameState::keyboardInput(unsigned char c, int x, int y);
	bool LoadGameState::Update();
	bool LoadGameState::Draw();
	bool MainMenuCallback();
	bool tutorialCallback();
	bool loadGame(string);

private:
	oglTexture2D* img;
	std::string tempString;
	bool finished;
	// add private stuff here

};

#endif