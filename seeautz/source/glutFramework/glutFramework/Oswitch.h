#ifndef OSWITCH_H
#define OSWITCH_H

#include "oglTexture2D.h"
#include "aiInstructionEnums.h"
#include <vector>
#include "objectEnums.h"
#include "object.h"

using namespace std;

class Oswitch : public object
{
	vector<int> targetX;
	vector<int>::iterator Xitr;
	vector<int> targetY;
	vector<int>::iterator Yitr;
	int numTargets;
	
public:
	Oswitch();
	Oswitch(int x, int y, int newDirection = 0, objectEnum newType = OSwitch) 
		: object(x, y, newDirection, newType)
	{
		numTargets = 0;
		Xitr = targetX.begin();
		Yitr = targetY.begin();
		//std::cout << "switch created at " << x << ", " << y << endl;
	}
	void addTarget(int x, int y);
	int getNumTargets();
	int getNextX();
	int getNextY();

	
};

#endif