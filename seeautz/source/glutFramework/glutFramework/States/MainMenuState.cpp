#include "MainMenuState.h"
#include "StartNewGameState.h"
#include "ProfileMgrState.h"
#include "LoadGameState.h"
#include "OptionsState.h"
#include "..\GameStateManager.h"
#include "MainGameLoopState.h"
#include "PreGameState.h"

#include "..\tutorialMap1.h"

bool MainMenuState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool MainMenuState::Draw()
{
	if(myMenu != NULL)
		myMenu->Draw();

	if(img != NULL)
		//img->drawPixMap();
		img->drawImage();

	return false;
}

void MainMenuState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void MainMenuState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}

bool MainMenuState::StartNewGameCallback()
{
	GSM->addGameState<StartNewGameState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 0, 0);
	
	//myMenu->addButton("button2normal.bmp", "button2down.bmp", "button2over.bmp", CreateFunctionPointer0R(this, &MainMenuState::button6Callback));

	return true;
} 

bool MainMenuState::ProfileManagerCallback()
{
	GSM->addGameState<ProfileMgrState>();
	this->setStatus(DeleteMe);
	glClearColor(0, 255, 0, 0);
	Update();

	return true;
} 

bool MainMenuState::LoadGameCallback()
{
	GSM->addGameState<LoadGameState>();
	this->setStatus(DeleteMe);
	glClearColor(0, 0, 255, 0);
	Update();

	return true;
} 

bool MainMenuState::OptionsCallback()
{
	GSM->addGameState<OptionsState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
} 

