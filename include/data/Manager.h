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

	Graph *getGraph() const {return _graph;}

	GLint _heightCoef;//	= 1;  //(0 - _realScale of root
	GLfloat _gapCoef;//		= 0.3;     //(0 - 1.0)


private:

	Manager();
	static Manager *_manager;
	Graph *_graph;
};

#endif
