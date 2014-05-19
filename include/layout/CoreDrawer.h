#ifndef COREDRAWER_H
#define COREDRAWER_H


#include "layout/Node.h"
#include <QtOpenGL>
#include <QMap>
#include <QMapIterator>

class CoreDrawer
{

public:
	CoreDrawer();

	void drawTree() const;
	void addRoot(Node *root);
	void prepareTree() const;

	void setSelectedNode(GLuint glId);

private:

	void createNodeMap();


	Node *_root;
	QMap<GLuint, Node*> _nodes;




};

#endif
