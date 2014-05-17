#include "data/Graph.h"

#include <QMapIterator>
#include <QSet>
//#include <QSetIterator>
#include <QList>
#include <QMutableListIterator>

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
	GrEdge *newEdge = new GrEdge( _edgeCount, sourceId, targetId, directed, params );
	_edges[_edgeCount] = newEdge;


	(*(_nodes.find( sourceId )))->addEdge( _edgeCount );
	(*(_nodes.find( targetId )))->addEdge( _edgeCount );


	_edgeCount++;
}



void Graph::createSpanningTree(){

	// *******************************************************************************
	//    Primov-Jarníkov algoritmus for finding spannig tree ************************

	PriorQueue eQueue(false);
	QSet<int> eTree;
	QSet<QString> nTree;
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

	nTree.insert( actNode );

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

			if(nTree.find(souId) == nTree.constEnd()) {
				actNode = souId;
				nTree.insert( actNode );
				eTree.insert( actEdge);  }
			if(nTree.find(tarId) == nTree.constEnd()) {
				actNode = tarId;
				nTree.insert( actNode );
				eTree.insert( actEdge); }
		}
	}

	qDebug() << "NODES " << _nodes.size();
	qDebug() << "nTree " << nTree.size();
	qDebug() << "EDGES " << _edges.size();
	qDebug() << "eTree " << eTree.size();



	// *****************************************
	// finding center **************************

	QList<QString> nodeList = nTree.toList();
	QSet<int> edgeList(eTree);

	while(nodeList.size() > 2){

		qDebug() << "  Node to remove left " << nodeList.size();
		QList<int> edgeToRemove;

		QMutableListIterator<QString> inl(nodeList);

		// remove nodes with 1 edge
		while(inl.hasNext()){
			QString id = inl.next();
			int counter = 0;
			int oneEdge;

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

	QString centerNode = nodeList.first();

	qDebug() << "Center node" << centerNode << "     edges:" <<  _nodes[centerNode]->getEdgeCount();



	// *****************************************
	// creating TREE









}















