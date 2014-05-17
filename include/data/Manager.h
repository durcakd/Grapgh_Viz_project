#ifndef MANAGER_H
#define MANAGER_H


#include "data/Graph.h"


#include <QString>

class Manager
	{
public:
	~Manager();


	Graph *loadGraph(QString filepath);
	static	Manager* getInstance();

private:

	Manager();
	static Manager *_manager;

};

#endif
