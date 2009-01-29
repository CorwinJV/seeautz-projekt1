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
		img->drawPixMap();

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

bool MainMenuState::button1Callback()
{
	GSM->addGameState<StartNewGameState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 0, 0);
	
	//myMenu->addButton("button2normal.bmp", "button2down.bmp", "button2over.bmp", CreateFunctionPointer0R(this, &MainMenuState::button6Callback));
#ifdef buttonWork
	std::cout << " BUTTON 1 CALLBACK WORKING ";
#endif
	return true;
} 

bool MainMenuState::button2Callback()
{
	GSM->addGameState<ProfileMgrState>();
	this->setStatus(DeleteMe);
	glClearColor(0, 255, 0, 0);
	Update();
#ifdef buttonWork
	std::cout << " BUTTON 2 CALLBACK WORKING ";
#endif
	return true;
} 

bool MainMenuState::button3Callback()
{
	GSM->addGameState<LoadGameState>();
	this->setStatus(DeleteMe);
	glClearColor(0, 0, 255, 0);
	Update();
#ifdef buttonWork
	std::cout << " BUTTON 3 CALLBACK WORKING ";
#endif
	return true;
} 

bool MainMenuState::button4Callback()
{
	GSM->addGameState<tutorialMap1>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

#ifdef buttonWork
	std::cout << " BUTTON 4 CALLBACK WORKING ";
#endif
	return true;
} 

bool MainMenuState::button5Callback()
{
	GSM->addGameState<PreGameState>();
	this->setStatus(DeleteMe);
	glClearColor(0, 255, 255, 0);
#ifdef buttonWork
	std::cout << " BUTTON 5 CALLBACK WORKING ";
#endif
	return true;
} 

bool MainMenuState::button6Callback()
{
	GSM->addGameState<MainGameLoopState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 255, 0, 0);
#ifdef buttonWork
	std::cout << " BUTTON 6 CALLBACK WORKING ";
#endif
	return true;
} 