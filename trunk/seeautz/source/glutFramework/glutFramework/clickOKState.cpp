#include "clickOKState.h" 
#include "GameStateManager.h"

bool clickOKState::Update()
{
	selected = false;
	deleted = false;
	created = false;
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
	default:
		break;
	}

	if(myMenu != NULL)
		myMenu->Update();

	return true;
}

bool clickOKState::Draw()
{
	clearBackground();
	logoImage->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();

	glColor3ub(0, 0, 0);

	if(created)
	{
		GameVars->fontArial24.drawText(270, 300, "Profile has been created,");
		GameVars->fontArial24.drawText(270, 350, "click OK to begin game");
	}
	if(selected)
	{
		GameVars->fontArial24.drawText(270, 300, "Profile has been selected,"); 
		GameVars->fontArial24.drawText(270, 350, "click OK to proceed to select level");
	}
	if(deleted)
		GameVars->fontArial24.drawText(270, 300, "Profile has been deleted, click OK ");

	return true;
}

bool clickOKState::clickOKCallback()
{
	if(selected)
	{
		GSM->addGameState<LevelSelectState>();
	}
	if(deleted)
	{
		GSM->addGameState<MainMenuState>();
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