#include "Oswitch.h"

void Oswitch::addTarget(int x, int y)
{
	targetX.push_back(x);
	targetY.push_back(y);
	numTargets++;
	Xitr = targetX.begin();
	Yitr = targetY.begin();
	//std::cout << "switch target added at " << x << ", " << y << " total targets for this switch is now " << numTargets << endl;
}
int Oswitch::getNumTargets()
{
	return numTargets;
}

int Oswitch::getNextX()
{
	int tempx;
	tempx = (*Xitr);
	Xitr++;
	if(Xitr == targetX.end())
	{
		Xitr = targetX.begin();
	}
	return tempx;
}
int Oswitch::getNextY()
{
	int tempy;
	tempy = (*Yitr);
	Yitr++;
	if(Yitr == targetY.end())
	{
		Yitr = targetY.begin();
	}
	return tempy;
}