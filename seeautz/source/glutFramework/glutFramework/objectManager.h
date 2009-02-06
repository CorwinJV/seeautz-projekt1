#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <vector>
#include "object.h"

class objectManager
{
protected:
	vector<object*> objectList;
	vector<object*> objectsToAdd;
	int				curObjects;
	int				allObjects;

public:
	objectManager();
	~objectManager();

	int  getCurrentNumObjects();
	int  getOverallNumObjects();
	template <class T> inline void addNewObject(object*);
    void removeObjectsAt(int index);
	void removeObjectsID(int nukeObject);
    void update(); 
    void draw(); 
	void dumpTruck();
	void setList(vector<object*> newlist);
};

#endif