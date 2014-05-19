#ifndef COREDRAWER_H
#define COREDRAWER_H


#include "layout/Node.h"
#include <QtOpenGL>
#include <QMap>
#include <QMapIterator>
#include "data/GrNode.h"
#include "data/GrEdge.h"
#include "data/Graph.h"
#include <QObject>

class CoreDrawer :  public QObject
{
	Q_OBJECT
public:
	CoreDrawer();
	~CoreDrawer();


	void drawTree();
	void drawEdges();
	void setSelectedNode(GLuint glId);

signals:
	void sentHeightCoef( GLuint heightCoef );

public slots:
	void openNewGraph(QString fileName);
	void computeHeightCoef(int value );

private:

	void cleanData();

	void prepareEdges();
	void prepareEdge(GrEdge *grEdge);


	Node *_root;
	QMap<GLuint, Node*> _nodes;


	QMap< QString, GrNode* > _grNodes;
	QMap< int, GrEdge* > _noTreeGrEdges;
	Graph *_graph;

};

#endif
