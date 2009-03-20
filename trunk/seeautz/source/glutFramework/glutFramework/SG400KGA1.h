#ifndef SG400KGA1_H
#define SG400KGA1_H

#include "GameState.h"
//#include ".\..\pixmap.h"
#include "States\\MainMenuState.h"
#include "playGame.h"
#include "oglTexture2D.h"
#include "GameStateManager.h"

class SG400KGA1 : public GameState
{
public:
	SG400KGA1() {};
	SG400KGA1(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		imgSG400 = new oglTexture2D();
	}

	bool SG400KGA1::Update();
	bool SG400KGA1::Draw();
	void SG400KGA1::keyboardInput(unsigned char c, int x, int y);
	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);

private:
	vector<string*> commandList;
	oglTexture2D* imgSG400;
	std::string* tString;
	std::string tempString;
	int finished;
	void interpret(string);
	// add private stuff here

};

#endif