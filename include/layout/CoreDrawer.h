#ifndef COREDRAWER_H
#define COREDRAWER_H


#include "layout/Node.h"
#include <QtOpenGL>
#include <QMap>
#include <QMapIterator>
#include "data/GrNode.h"
#include "data/GrEdge.h"
#include "data/Graph.h"

class CoreDrawer
{

public:
	CoreDrawer();

	void drawTree();
	void addRoot(Node *root);
	void prepareTree();

	void setSelectedNode(GLuint glId);
	void setGraph( Graph *graph) { _graph = graph;}
	void prepareEdges();
	void drawEdges();

private:

	void drawEdge(GrEdge *grEdge);
	void prepareEdge(GrEdge *grEdge);
	void createNodeMap();


	Node *_root;
	QMap<GLuint, Node*> _nodes;


	QMap< QString, GrNode* > _grNodes;
	QMap< int, GrEdge* > _noTreeGrEdges;
	Graph *_graph;

};

#endif
