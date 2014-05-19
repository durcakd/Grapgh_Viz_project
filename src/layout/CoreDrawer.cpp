#include "layout/CoreDrawer.h"

#include <QDebug>
#include <QMapIterator>
#include "data/Manager.h"

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

	GLfloat a = Manager::getInstance()->_a;
	GLuint key;
	Node *node, *selected = NULL;
	QMapIterator<GLuint, Node*> it(_nodes);
	while(it.hasNext()){
		it.next();
		key = it.key();
		node = it.value();
		if(key == glId){
			selected = node;
		} else {
			node->setVizColor( UNSELECTED );
		}
	}
	if(selected != NULL){
		selected->setVizColor( SELECTED );

		// clear edges


		// find adj nodes
		if(Manager::getInstance()->_selAdjNodes){
			// clear edges

			QMapIterator< int, GrEdge* > ine(_noTreeGrEdges);
			while(ine.hasNext()){
				ine.next();
				qDebug() << " >" << ine.key();
				GrEdge *nedge = ine.value();
				nedge->setColor( 0.3f, 0.3f, .3f, a );

			}



			// select nnodes
			QString sid = 	selected->_name;
			GrNode *grNode = _grNodes[sid];

			QVector<int> edges = grNode->getEdges();
			QVectorIterator<int> ie(edges);

			while(ie.hasNext()){
				int ekey = ie.next();

				//qDebug() << "  <" << ekey ;
				if(_noTreeGrEdges.find(ekey) != _noTreeGrEdges.end()){
					GrEdge  *grEdge = _noTreeGrEdges[ekey];
					//qDebug() << "  <<" << ekey ;
					grEdge->setColor( 0.1f, 1.0f, 0.0f, a  );


					QString adjId = grEdge->getSourceId();
					if(adjId == sid) { adjId = grEdge->getTargetId(); }

					if(adjId != sid){

						GLuint adjGlId = _grNodes[adjId]->getGlId();
						_nodes[adjGlId]->setVizColor( SELECTED2 );
					}
					// select nodes






				}
			}

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






