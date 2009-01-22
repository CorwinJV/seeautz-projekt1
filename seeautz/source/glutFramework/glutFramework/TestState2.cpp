#include "TestState2.h"
#include <iostream>
#include "GameStateManager.h"

TestState2::TestState2() : GameState() // constructor
{
}

TestState2::TestState2(GameStateManager &Parent, int newID) : GameState() // constructor
{
	GSM = &Parent;
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

	img->mX += 1;
	if(img->mX > vPort[2])
		img->mX = 0;

	img->mY += 5;
	if(img->mY > vPort[3])
		img->mY = 0;

<<<<<<< .mine
	//std::cout << "TestState2 - ID:" << stateID << " img->mX = " << img->mX  << endl;
=======
	std::cout << "TestState2 - ID:" << stateID << " img->mX = " << img->mX  << endl;
>>>>>>> .r39

<<<<<<< .mine
	if(img->mX >= 800)
	{
		//std::cout << "TestState 2 - ID: " << stateID << " Setting currentStatus to DeleteMe" << std::endl;
		currentStatus = DeleteMe;
	}

=======
	if(img->mX >= 200)
	{
		std::cout << "TestState 2 - ID: " << stateID << " Setting currentStatus to DeleteMe" << std::endl;
		currentStatus = DeleteMe;
	}

>>>>>>> .r39
	return true;
}

bool TestState2::Draw()
{
	if(img != NULL)
		img->drawPixMap();

	return true;
}