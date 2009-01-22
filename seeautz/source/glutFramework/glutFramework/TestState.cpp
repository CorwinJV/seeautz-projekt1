#include "TestState.h"
#include <iostream>
#include "GameStateManager.h"

TestState::TestState() : GameState() // constructor
{
}

TestState::TestState(GameStateManager &Parent, int newID) : GameState() // constructor
{
	GSM = &Parent;
	stateID = newID;
    //graphics = new GraphicsDeviceManager(this);
    //content = new ContentManager(Services);
    // graphics.IsFullScreen = true;

	img = new pixmap("awesome.bmp");

    initialize();
}
TestState::~TestState()
{

}

bool TestState::Update()
{
    int vPort[4];
    glGetIntegerv(GL_VIEWPORT, vPort);

	img->mX += 2;
	if(img->mX > vPort[2])
		img->mX = 0;

	if(img->mX % 50 == 0)
	{
		if(GSM->getNumStates() < 7)
		{
			std::cout << "TestState - attempting to add a new teststate2" << std::endl;
			GSM->addGameState<TestState2>();
		}
	}

	img->mY += 2;
	if(img->mY > vPort[3])
		img->mY = 0;

	std::cout << "TestState - ID:" << stateID << " img->mX = " << img->mX  << endl;

	return true;
}

bool TestState::Draw()
{
	if(img != NULL)
		img->drawPixMap();

	return true;
}