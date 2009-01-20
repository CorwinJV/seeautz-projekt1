#include "TestState.h"
#include <iostream>

TestState::TestState() : GameState() // constructor
{
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

	img->mX += 1;
	if(img->mX > vPort[2])
		img->mX = 0;

	img->mY += 2;
	if(img->mY > vPort[3])
		img->mY = 0;

	std::cout << img->mX << std::endl;

	return true;
}

bool TestState::Draw()
{
	if(img != NULL)
		img->drawPixMap();

	return true;
}