#include "data/Graph.h"

#include <QMapIterator>
#include <QSet>
//#include <QSetIterator>
#include <QList>
#include <QMutableListIterator>
#include "layout/Cube.h"

Graph::Graph()
{
	_nodeCount = 0;
	_edgeCount = 0;
}

Graph::~Graph()
{
	_nodes.clear();
	_edges.clear();
	_noTreeEdges.clear();
	_eTree.clear();
	_nTree.clear();

}


void Graph::addNode(const QString id, int glId, const QString params)
{
	GrNode *newNode = new GrNode(id, glId, params);
	_nodes[id] = newNode;
	_nodeCount++;
}

void Graph::addEdge( const QString sourceId, const QString targetId, bool directed, const QString params )
{
	GrEdge *newEdge = new GrEdge( _edgeCount, sourceId, targetId, directed, params );
	_edges[_edgeCount] = newEdge;


	(*(_nodes.find( sourceId )))->addEdge( _edgeCount );
	(*(_nodes.find( targetId )))->addEdge( _edgeCount );


	_edgeCount++;
}



Node* Graph::createSpanningTree(){

	// *******************************************************************************
	//    Primov-Jarníkov algoritmus for finding spannig tree ************************

	//PriorQueue eQueue(true);
	PriorQueue eQueue(false);

	QString actNode = "";
	int		actEdge;

	// find start node with least one edge
	QMapIterator< QString, GrNode* > in(_nodes);
	while(in.hasNext()){
		QString id = in.next().key();
		int edgeCount = _nodes[id]->getEdgeCount();
		if (edgeCount > 0) {
			actNode = id;
			break;
		}
	}

	_nTree.insert( actNode );

	while( !actNode.isEmpty()){

		// add edges of actual node to queue
		const QVector<int>& nodeEdges = _nodes[ actNode ]->getEdges();
		QVectorIterator<int> inE(nodeEdges);
		while(inE.hasNext()){
			int id = inE.next();
			int weight = _edges[id]->getWeight();
			eQueue.push( std::make_pair( id, weight ));
		}

		// get new actual node, that is not in tree yet
		actNode = "";
		while(actNode.isEmpty() && ! eQueue.empty() ) {
			actEdge		= eQueue.top().first;
			eQueue.pop();

			QString souId = _edges[actEdge]->getSourceId();
			QString tarId = _edges[actEdge]->getTargetId();

			if(_nTree.find(souId) == _nTree.constEnd()) {
				actNode = souId;
				_nTree.insert( actNode );
				_eTree.insert( actEdge);  }
			if(_nTree.find(tarId) == _nTree.constEnd()) {
				actNode = tarId;
				_nTree.insert( actNode );
				_eTree.insert( actEdge); }
		}
	}

	qDebug() << "NODES " << _nodes.size();
	qDebug() << "nTree " << _nTree.size();
	qDebug() << "EDGES " << _edges.size();
	qDebug() << "eTree " << _eTree.size();



	// *****************************************
	// finding center **************************

	QList<QString> nodeList = _nTree.toList();
	QSet<int> edgeList(_eTree);

	while(nodeList.size() > 2){

		qDebug() << "  Node to remove left " << nodeList.size();
		QList<int> edgeToRemove;

		QMutableListIterator<QString> inl(nodeList);

		// remove nodes with 1 edge
		while(inl.hasNext()){
			QString id = inl.next();
			int counter = 0;
			int oneEdge;

			// count edges in tree
			const QVector<int>& nodeEdges = _nodes[ id ]->getEdges();
			QVectorIterator<int> inE(nodeEdges);
			while(inE.hasNext()){
				int id = inE.next();

				if(edgeList.find(id) != edgeList.constEnd()) {
					counter++;
					oneEdge = id;
				}
			}
			if(counter == 1){
				inl.remove();
				edgeToRemove.push_back(oneEdge);
				//qDebug() << "removing";
			}
		}

		foreach (int idr, edgeToRemove) {
			edgeList.remove(idr);
		}
		edgeToRemove.clear();
	}

	QString centerNodeId = nodeList.first();

	qDebug() << "Center node" << centerNodeId << "     edges:" <<  _nodes[centerNodeId]->getEdgeCount();



	// *****************************************
	// creating TREE

	return createVizNodeFromTree( centerNodeId );

}


Node* Graph::createVizNodeFromTree( QString parId ){
	// create new Viz Node
	_nTree.remove( parId );
	//qDebug() << ">>> " << parId;

	GrNode *node = _nodes[parId];
	Node *vizNode = new Cube( node->getGlId(), parId );

	vizNode->setColor(  node->r(), node->g(), node->b(), node->a());

	// count edges in tree
	const QVector<int>& nodeEdges = node->getEdges();
	QVectorIterator<int> inE(nodeEdges);
	while(inE.hasNext()){
		int ide = inE.next();

		if(_eTree.find(ide) != _eTree.constEnd()) { // is tree edge
			QString souId = _edges[ide]->getSourceId();
			QString tarId = _edges[ide]->getTargetId();
			QString childId = souId != parId ? souId : tarId;

			if( _nTree.find(childId) != _nTree.constEnd() ){
				vizNode->addChil( createVizNodeFromTree( childId ));
			}
		}else{
			GrEdge* edge = _edges.find(ide).value();
			_noTreeEdges.insert(ide, edge);

		}
	}
	//qDebug() << "<<< " << parId;
	return vizNode;
}

QMap< QString, GrNode* > Graph::getNodes() const
{
	return _nodes;
}
QMap< int, GrEdge* > Graph::getNoTreeEdges() const
{
	return _noTreeEdges;
}

































