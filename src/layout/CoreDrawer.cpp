#include "layout/CoreDrawer.h"

#include <QDebug>

CoreDrawer::CoreDrawer()
{
	_root = NULL;
}

void CoreDrawer::drawTree() const
{
_root->draw();
}

void CoreDrawer::prepareTree() const
{
_root->computeLayout();
}


void CoreDrawer::addRoot( Node *root)
{
	delete _root;
	_root = root;
	createNodeMap();

}


void CoreDrawer::createNodeMap()
{
	_root->createNodeMap( _nodes );
}


void CoreDrawer::setSelectedNode(GLuint glId)
{
	GLuint key;
	Node *node;
	QMapIterator<GLuint, Node*> it(_nodes);
	while(it.hasNext()){
		it.next();
		key = it.key();
		node = it.value();
		if(key == glId){
			node->setVizColor( SELECTED );
		} else {
			node->setVizColor( ORIGCOLOR );
		}
	}
}








