#include "objectManager.h"

//vector<object*> objectList;
//vector<object*> objectsToAdd;
//int				curObjects;
//int				allObjects;


objectManager::objectManager()
{

}

objectManager::~objectManager()
{

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
inline void objectManager::addNewObject(object* newObject)
{
	allObjects++;

	T* newObj = new T(*this, allObjects);
	newObj->setStatus(Active);
	
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

void objectManager::dumpTruck(){};
void objectManager::setList(vector<object*> newlist){};