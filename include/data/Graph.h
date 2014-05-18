#ifndef GRAPH_H
#define GRAPH_H

#include <QString>
#include <QMap>
#include <queue>
#include <algorithm>

#include "data/GrNode.h"
#include "data/GrEdge.h"
#include "layout/Node.h"

class mycomp
{
	bool reverse;
public:
	mycomp(const bool& revparam=false)   // true = from smaaler,  false=biggest on top
	{reverse=revparam;}
	bool operator() (const std::pair<int,int>& l, const std::pair<int,int>& r) const{
		if (reverse){
			return l.second > r.second;
		}else{
			return  l.second < r.second;
		}
	}
};

typedef std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int> >, mycomp > PriorQueue;

class Graph
	{
public:
	Graph();
	~Graph();

	void addNode( const QString id, const QString params );
	void addEdge( const QString sourceId, const QString targetId, bool directed, const QString params);
	Node *createSpanningTree();

private:
	Node *createVizNodeFromTree( QString parId );

	int _nodeCount;
	int _edgeCount;
	QMap< QString, GrNode* > _nodes;
	QMap< int, GrEdge* > _edges;
	QSet<int> _eTree;
	QSet<QString> _nTree;



};

#endif
