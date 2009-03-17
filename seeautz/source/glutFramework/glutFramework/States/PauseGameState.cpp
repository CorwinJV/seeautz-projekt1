#include "PauseGameState.h"

bool PauseGameState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	GSM->setAllButTopPassive();
	return true;
}

bool PauseGameState::Draw()
{
	if(myMenu != NULL)
		myMenu->Draw();
	
	return false;
}

bool PauseGameState::SaveCallback()
{
	GameVars->SavePlayerGame();
	//GSM->addGameState<SaveGameState>();
	return true;
}

bool PauseGameState::SaveQuitCallback()
{
	GameVars->SavePlayerGame();
	/*this->setStatus(DeleteMe);
	GSM->removeTopGameState();
	GSM->addGameState<SaveGameState>();*/
	exit(0);

	return true;
}
	
bool PauseGameState::QuitCallback()
{
	this->setStatus(DeleteMe);
	exit(0);

	return true;
}
	
bool PauseGameState::LevelSelectCallback()
{
	this->setStatus(DeleteMe);
	GSM->setAllButTopPassive();
	GSM->addGameState<LevelSelectState>();

	return true;
}
	
bool PauseGameState::MainMenuCallback()
{
	GSM->returnToMainMenu();

	return true;
}
	
bool PauseGameState::ReturnToGameCallback()
{
	this->setStatus(DeleteMe);

	return true;
}

void PauseGameState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void PauseGameState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}

void PauseGameState::keyboardInput(unsigned char c, int x, int y)
{
	switch(c)
	{
	case 27:
		this->setStatus(DeleteMe);
		break;
	default:
		break;
	}
}