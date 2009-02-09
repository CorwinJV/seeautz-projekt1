#include "objectManager.h"


objectManager::objectManager()
{
	curObjects = 0;
	allObjects = 0;
}

objectManager::~objectManager()
{
	dumpTruck();
}

int  objectManager::getCurrentNumObjects()
{
	return curObjects;
};

int  objectManager::getOverallNumObjects()
{
	return allObjects;
};

void objectManager::removeObjectsAt(int index){};
void objectManager::removeObjectsID(int nukeObject){};

template <class T>
inline void objectManager::addNewObject(int x, int y, int direction)
{
	allObjects++;

	T* newObj = new T(x, y, direction);

	objectsToAdd.push_back(newObj);
};

void objectManager::update()
{
	//update objects here
}; 

void objectManager::draw()
{
	//draw objects here
}; 

void objectManager::dumpTruck()
{
	vector<object*>::iterator itr = objectList.begin();

	// delete buttonlist contents
	for (; itr != objectList.end(); itr++)
    {
		(*itr)->~object();
    }
	objectList.clear();
};

void objectManager::startOver()
{
	vector<object*>::iterator itr = objectList.begin();

	for (; itr != objectList.end(); itr++)
    {
		(*itr)->startOver();
    }
};