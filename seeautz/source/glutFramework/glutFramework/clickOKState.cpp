#include "clickOKState.h" 
#include "GameStateManager.h"

bool clickOKState::Update()
{
	selected = false;
	deleted = false;
	created = false;
	noProfile = false;
	saved = false;
	GSM->setAllButTopPassive();

	int check = GameVars->getPMStatus();
	switch(check)
	{
	case 0:
		selected = true;
		break;
	case 1:
		deleted = true;
		break;
	case 2:
		created = true;
		break;
	case 3:
		noProfile = true;
		break;
	case 4:
		saved = true;
		break;
	default:
		break;
	}

	if(myMenu != NULL)
		myMenu->Update();

	return true;
}

bool clickOKState::Draw()
{
	if(!saved)
	{
		clearBackground();
		logoImage->drawImage();
	}

	if(myMenu != NULL)
		myMenu->Draw();

	glColor3ub(0, 0, 0);

	if(created)
	{
		GameVars->fontArial24.drawText(350, 350, "Profile has been created.");
		GameVars->fontArial24.drawText(350, 400, "Click OK to begin game, or");
		GameVars->fontArial24.drawText(350, 450, "Click help for helpful info");
	}
	if(selected)
	{
		GameVars->fontArial24.drawText(350, 350, "Profile has been selected."); 
		GameVars->fontArial24.drawText(350, 400, "Click OK to select level.");
	}
	if(deleted)
	{
		GameVars->fontArial24.drawText(350, 350, "Profile has been deleted.");
		GameVars->fontArial24.drawText(350, 400, "Click OK to continue.");
	}
	if(noProfile)
	{
		GameVars->fontArial24.drawText(350, 350, "There are no existing profiles.");
		GameVars->fontArial24.drawText(350, 400, "to load click OK to continue.");
	}
	if(saved)
	{
		GameVars->fontArial24.drawText(350, 350, "Profile has been saved.");
		GameVars->fontArial24.drawText(350, 400, "Click OK to continue.");
	}
	return true;
}

bool clickOKState::clickOKCallback()
{
	if(selected)
	{
		GSM->addGameState<LevelSelectState>();
		selected = false;
	}
	else if((deleted)||(noProfile))
	{
		GSM->addGameState<MainMenuState>();
		deleted = false;
		noProfile = false;
	}
	else if(created)
	{
		GSM->addGameState<playGame>();
		created = false;
	}
	this->setStatus(DeleteMe);
	return true;
}

void clickOKState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void clickOKState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}

bool clickOKState::helpCallback()
{
	GSM->addGameState<helpScreenState>();
	/*GSM->addGameState<playGame>();
	this->setStatus(DeleteMe);
	created = false;*/

	return true;
}