#ifndef TESTSTATE_H
#define TESTSTATE_H
#include "oglUtility.h"
#include "GameState.h"
#include "pixmap.h"

class TestState : public GameState
{
public:
	TestState();
	~TestState();
	bool Update();
	bool Draw();

private:
	pixmap* img;
};

#endif