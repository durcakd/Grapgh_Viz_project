#include "data/Graph.h"




Graph::Graph()
{
	_nodeCount = 0;
	_edgeCount = 0;

}

Graph::~Graph()
{
	_nodes.clear();
	_edges.clear();
}


void Graph::addNode(const QString id, const QString params)
{
	GrNode *newNode = new GrNode(id, params);
	_nodes[id] = newNode;
	_nodeCount++;
}

void Graph::addEdge( const QString sourceId, const QString targetId, bool directed, const QString params )
{
	GrEdge *newEdge = new GrEdge( _nodeCount, sourceId, targetId, directed, params );
	_edges[_nodeCount] = newEdge;


	(*(_nodes.find( sourceId )))->addEdge( _nodeCount );
	(*(_nodes.find( targetId )))->addEdge( _nodeCount );


	_nodeCount++;
}
