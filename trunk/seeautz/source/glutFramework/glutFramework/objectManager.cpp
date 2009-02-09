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

bool objectManager::removeObjectsAt(int index)
{
	if (index < 0) 
		return false;

	// erase the object at this index
	vector<object*>::iterator itr = objectList.begin();
	for(int i = 0; i < index; i++)
	{
		itr++;
		if(itr >= objectList.end()) // lets also make sure that we're working within the confines of the vector
		{
			return false;
		}
	}

	delete (*itr);
	objectList.erase(itr);

	curObjects--;

	return true;
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