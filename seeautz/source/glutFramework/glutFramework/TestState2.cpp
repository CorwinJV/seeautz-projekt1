#include "TestState2.h"
#include <iostream>

TestState2::TestState2() : GameState() // constructor
{
}

TestState2::TestState2(GameStateManager &Parent, int newID) : GameState() // constructor
{
	stateID = newID;
    //graphics = new GraphicsDeviceManager(this);
    //content = new ContentManager(Services);
    // graphics.IsFullScreen = true;

	img = new pixmap("awesome.bmp");

    initialize();
}
TestState2::~TestState2()
{

}

bool TestState2::Update()
{
    int vPort[4];
    glGetIntegerv(GL_VIEWPORT, vPort);

	img->mX += 5;
	if(img->mX > vPort[2])
		img->mX = 0;

	img->mY += 7;
	if(img->mY > vPort[3])
		img->mY = 0;

	std::cout << img->mX  << std::endl;

	return true;
}

bool TestState2::Draw()
{
	if(img != NULL)
		img->drawPixMap();

	return true;
}