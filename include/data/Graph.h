#ifndef GRAPH_H
#define GRAPH_H

#include <QString>

class Graph
	{
public:
	Graph();
	~Graph();

	void addNode( const QString id, const QString params );
	void addEdge(const QString sourceId, const QString targetId, bool directed, const QString params);

private:


};

#endif
