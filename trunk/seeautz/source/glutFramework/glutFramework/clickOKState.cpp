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
	case 3:
		noProfile = true;
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
		GameVars->fontArial24.drawText(350, 350, "Profile has been created,");
		GameVars->fontArial24.drawText(350, 400, "click OK to begin game");
	}
	if(selected)
	{
		GameVars->fontArial24.drawText(350, 350, "Profile has been selected,"); 
		GameVars->fontArial24.drawText(350, 400, "click OK to select level");
	}
	if(deleted)
	{
		GameVars->fontArial24.drawText(350, 350, "Profile has been deleted, ");
		GameVars->fontArial24.drawText(350, 400, "click OK to continue ");
	}
	if(noProfile)
	{
		GameVars->fontArial24.drawText(350, 350, "There are no existing profiles ");
		GameVars->fontArial24.drawText(350, 400, "to load click OK to continue ");
	}
	return true;
}

bool clickOKState::clickOKCallback()
{
	if(selected)
	{
		GSM->addGameState<LevelSelectState>();
	}
	if((deleted)||(noProfile))
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