#include "layout/CoreDrawer.h"

#include <QDebug>
#include <QMapIterator>

CoreDrawer::CoreDrawer()
{
	_root = NULL;
}

void CoreDrawer::drawTree()
{
	_root->draw();



}



void CoreDrawer::prepareTree()
{
	_root->computeLayout();
	prepareEdges();
}


void CoreDrawer::addRoot( Node *root)
{
	delete _root;
	_root = root;
	createNodeMap();
	_grNodes = _graph->getNodes();
	_noTreeGrEdges = _graph->getNoTreeEdges();

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


void CoreDrawer::prepareEdges()
{
	// draw edges
	QMapIterator< int, GrEdge* > ei( _noTreeGrEdges);
	while( ei.hasNext()){
		ei.next();
		//int id = ei.key();
		GrEdge *grEdge = ei.value();

		prepareEdge( grEdge );
	}
}
void CoreDrawer::drawEdges()
{
	// draw edges
	QMapIterator< int, GrEdge* > ei( _noTreeGrEdges);
	while( ei.hasNext()){
		ei.next();
		//int id = ei.key();
		GrEdge *grEdge = ei.value();

		grEdge->draw();
	}
}
void CoreDrawer::prepareEdge( GrEdge *grEdge)
{
	QString sourceId = grEdge->getSourceId();
	QString targetId = grEdge->getTargetId();

	GLuint sglId =_grNodes[sourceId]->getGlId();
	GLuint tglId =_grNodes[targetId]->getGlId();

	grEdge->_sx	= _nodes[sglId]->getXpos();
	grEdge->_sy	= _nodes[sglId]->getYpos();
	grEdge->_srh = _nodes[sglId]->getRealHeight();
	grEdge->_tx	= _nodes[tglId]->getXpos();
	grEdge->_ty	= _nodes[tglId]->getYpos();
	grEdge->_trh = _nodes[tglId]->getRealHeight();

}

void CoreDrawer::drawEdge( GrEdge *grEdge)
{




}






