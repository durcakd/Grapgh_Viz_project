#ifndef GRAPH_H
#define GRAPH_H

#include <QString>
#include <QMap>

#include "data/GrNode.h"
#include "data/GrEdge.h"


class Graph
	{
public:
	Graph();
	~Graph();

	void addNode( const QString id, const QString params );
	void addEdge( const QString sourceId, const QString targetId, bool directed, const QString params);

private:
	//void nodeDefVal( const QString id );
	//void edgeDefVal( const QString sourceId, const QString targetId );


	int _nodeCount;
	int _edgeCount;
	QMap< QString, GrNode* > _nodes;
	QMap< int, GrEdge* > _edges;

};

#endif
