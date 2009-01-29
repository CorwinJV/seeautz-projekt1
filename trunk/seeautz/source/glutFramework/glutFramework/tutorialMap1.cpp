#include "tutorialMap1.h"
#include "GameStateManager.h"



bool tutorialMap1::Update()
{

	return true;
}

bool tutorialMap1::Draw()
{
	tutorialmap1->draw();

	return false;
}

bool tutorialMap1::initialize()
{
	//tutorial1map
	tutorialmap1 = new gameBoard(2, 3);



	tutorialmap1->setTileType(0, 2, TStart);
	tutorialmap1->setTileType(0, 1, TDoorTR);
	tutorialmap1->setTileType(0, 0, TEnd);

	return true;
}