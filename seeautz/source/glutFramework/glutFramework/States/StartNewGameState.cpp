#include "StartNewGameState.h"

bool StartNewGameState::Update()
{
	return true;
}

bool StartNewGameState::Draw()
{
	if(img != NULL)
		img->drawPixMap();
	return false;
}