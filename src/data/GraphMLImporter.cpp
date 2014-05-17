#include "data/GraphMLImporter.h"

#include <QDebug>


bool GraphMLImporter::import(QIODevice *stream , Graph *graph)
{
	qDebug() << "IMPORTER: import ...";


	_stream	= stream;
	_graph	= graph;




	bool ok = true;

	// ziskame graph element
	QDomElement graphElement;
	if (ok) {
		QDomNode graphNode;

		QDomDocument doc("graphMLDocument");
		if (doc.setContent( _stream ))
		{
			QDomElement docElem = doc.documentElement();
			if (!docElem.isNull() && docElem.nodeName() == "graphml")
			{
				QDomNodeList graphNodes = docElem.elementsByTagName("graph");
				if (graphNodes.length() > 0)
				{
					graphNode = graphNodes.item(0);
					if (!graphNode.isNull() && graphNode.parentNode() == docElem && graphNode.isElement())
					{
						graphElement = graphNode.toElement();
					}
				}
			}
		}

		ok = !graphElement.isNull();

		if(!ok) {
			qDebug() << "Zvoleny subor nie je validny GraphML subor.";
			return ok;
		}
	}

	// for progress reporting
	_entitiesProcessed = 0;
	_nodestr = (graphElement.elementsByTagName("node").size() > graphElement.elementsByTagName("NODE").size()) ? "node" : "NODE";
	_edgestr = (graphElement.elementsByTagName("edge").count() > graphElement.elementsByTagName("EDGE").count()) ? "edge" : "EDGE";

	_entitiesCount = graphElement.elementsByTagName(_nodestr).size() + graphElement.elementsByTagName(_edgestr).count();
	qDebug() << "Nodes: " << graphElement.elementsByTagName(_nodestr).size();
	qDebug() << "Edges: " << graphElement.elementsByTagName(_edgestr).count();

	return  processGraph( graphElement );
}

bool GraphMLImporter::processGraph( QDomElement &graphElement )
{
	return	processGraph_Nodes( graphElement )
			&&
			processGraph_Edges( graphElement );
}

bool GraphMLImporter::processGraph_Nodes( QDomElement &graphElement )
{
	bool ok = true;

	// nodes
	for (QDomElement nodeElement = graphElement.firstChildElement(_nodestr); ok && !nodeElement.isNull(); nodeElement = nodeElement.nextSiblingElement(_nodestr))
	{

		QString params = "";

		QString nameId = nodeElement.attribute("id");
		//qDebug() << " NODE  " << _entitiesProcessed << "    id: " << nameId;

		// pozerame sa na data ktore nesie
		QDomNodeList nodeDataList = nodeElement.elementsByTagName("data");
		for (unsigned int j = 0; j < nodeDataList.length(); j++){

			QDomNode nodeData = nodeDataList.item(j);
			if (!nodeData.isNull() && nodeData.isElement())
			{
				QDomElement nodeDataElement = nodeData.toElement();
				QString dataName = nodeDataElement.attribute("key");
				QString dataValue = nodeDataElement.text();
				//qDebug() << "       " << dataName << "  -  " << dataValue;

				if(params.isEmpty()) {
					params = dataName+" | "+dataValue;
				}else{
					params += " | "+dataName+" | "+dataValue;
				}


			}
		}
		//qDebug() << "   > " << params;

		_graph->addNode( nameId, params );

		// subgraphs -- we not support them
		for (QDomElement subgraphElement = nodeElement.firstChildElement("graph"); ok && !subgraphElement.isNull(); subgraphElement = subgraphElement.nextSiblingElement("graph")) {
			qDebug() << " ------- warning! : node: subgraphElement exist";
		}

		_entitiesProcessed++;
	}

	return ok;
}

bool GraphMLImporter::processGraph_Edges( QDomElement &graphElement )
{
	bool ok = true;

	// default direction
	bool defaultDirection = (graphElement.attribute("edgedefault") == "directed") ? true : false;

	// edges
	for (QDomElement edgeElement = graphElement.firstChildElement(_edgestr); ok && !edgeElement.isNull(); edgeElement = edgeElement.nextSiblingElement(_edgestr))
	{

		QString params = "";
		QString sourceId = edgeElement.attribute("source");
		QString targetId = edgeElement.attribute("target");
		//qDebug() << " EDGE  " << _entitiesProcessed << "     " << sourceId << " -> " << targetId;


		bool directed = false;
		QString direction = edgeElement.attribute("directed");
		if(direction == NULL ) {
			directed = defaultDirection;
			if(directed)
				direction = "_directed";
			else
				direction = "";
		} else {
			if(direction == "true"){
				direction = "_directed";
				directed = true;
			} else {
				direction = "";
				directed = false;
			}
		}

		// pozerame sa na data ktore hrana nesie
		QDomNodeList edgeDataList = edgeElement.elementsByTagName("data");
		for (unsigned int j = 0; j < edgeDataList.length(); j++){
			QDomNode edgeData = edgeDataList.item(j);
			if (!edgeData.isNull() && edgeData.isElement())
			{
				QDomElement edgeDataElement = edgeData.toElement();
				QString dataName = edgeDataElement.attribute("key");
				QString dataValue = edgeDataElement.text();
				//qDebug() << "       " << dataName << "  -  " << dataValue;

				if(params.isEmpty()) {
					params = dataName+" | "+dataValue;
				}else{
					params += " | "+dataName+" | "+dataValue;
				}
			}
		}
		//qDebug() << "     " << params;

		_graph->addEdge( sourceId, targetId, directed, params );

		// vnorene grafy
		for (QDomElement subgraphElement = edgeElement.firstChildElement("graph"); ok && !subgraphElement.isNull(); subgraphElement = subgraphElement.nextSiblingElement("graph")) {
			qDebug() << " ------- warning! : egde: subgraphElement exist";
		}

		_entitiesProcessed++;
	}

	return ok;
}

