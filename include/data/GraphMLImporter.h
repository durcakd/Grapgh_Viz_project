#ifndef GRAPHMLIMPORTER_H
#define GRAPHMLIMPORTER_H

#include <QtXml/QDomElement>
#include <QList>
#include "data/Graph.h"

class GraphMLImporter
{

public:

	~GraphMLImporter (void) {};

	bool import( QIODevice *stream, Graph *graph );

private:

	// Imports one graph (or subgraph) [recursive]
	bool processGraph( QDomElement &graphElement );

	// Imports nodes from a graph (or subgraph).
	bool processGraph_Nodes( QDomElement &graphElement );

	// Imports edges from a graph (or subgraph).
	bool processGraph_Edges( QDomElement &graphElement );


private:

	QIODevice  *_stream;
	QString		_nodestr;
	QString		_edgestr;
	Graph	   *_graph;


	// for progress reporting
	int _entitiesProcessed;
	int _entitiesCount;

};
#endif
