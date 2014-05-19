#include "layout/CoreDrawer.h"

#include <QDebug>
#include <QMapIterator>
#include "data/Manager.h"

CoreDrawer::CoreDrawer()
{
	_root = NULL;
	_graph = NULL;
}

CoreDrawer::~CoreDrawer()
{
	cleanData();
}

void CoreDrawer::cleanData()
{
	if(_root != NULL){

		QMapIterator<GLuint, Node*> itN(_nodes);
		while(itN.hasNext()){
			Node *node = itN.next().value();
			delete node;
		}
		_nodes.clear();

		QMapIterator< QString, GrNode* > itGN(_grNodes);
		while(itGN.hasNext()){
			GrNode *grnode = itGN.next().value();
			delete grnode;
		}
		_grNodes.clear();

		QMapIterator< int, GrEdge* > itE(_noTreeGrEdges);
		while(itE.hasNext()){
			GrEdge *gredge = itE.next().value();
			delete gredge;
		}
		_noTreeGrEdges.clear();

		delete _graph ;
	}
}

void CoreDrawer::drawTree()
{
	if(_root != NULL){
		_root->draw();
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

void CoreDrawer::openNewGraph(QString fileName){

	cleanData();

	_root	= Manager::getInstance()->loadGraph(fileName)->createSpanningTree();
	_graph	= Manager::getInstance()->getGraph();

	// create data for edges;
	_root->createNodeMap( _nodes );
	_grNodes		= _graph->getNodes();
	_noTreeGrEdges	= _graph->getNoTreeEdges();


	_root->computeLayout();
	computeHeightCoef( 50);

	prepareEdges();



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

void CoreDrawer::setSelectedNode(GLuint glId)
{

	GLfloat a = Manager::getInstance()->getAlphaCoef();
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
		if(Manager::getInstance()->getSelectAdjNodes()){
			// clear edges

			QMapIterator< int, GrEdge* > ine(_noTreeGrEdges);
			while(ine.hasNext()){
				ine.next();
				//qDebug() << " >" << ine.key();
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



void CoreDrawer::computeHeightCoef(int value )
{
	if(_root != NULL){
		emit sentHeightCoef( (((GLfloat)value)/100.0f) * (GLfloat) _root->getRealScale() );
	}
}







