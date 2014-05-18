/*!
 * Manager.cpp
 * Projekt 3DVisual
 */

#include "data/Manager.h"
#include "data/GraphMLImporter.h"


#include <QFile>
#include <QIODevice>
#include <QDebug>



Manager *Manager::_manager;


Manager::Manager()
{
	_manager = this;
}

Manager::~Manager(){ }


Graph* Manager::loadGraph(QString filepath)
{
	Graph *graph = new Graph();

	qDebug() << "Manager: load file:  " << filepath;
	//otvaranie suboru
	bool ok = true;

	// vytvorenie infoHandler
	GraphMLImporter *importer = new GraphMLImporter;


	// vytvorenie nacitavaneho streamu
	std::auto_ptr<QIODevice> stream (NULL);
	stream.reset (new QFile (filepath));

	ok = (stream->open (QIODevice::ReadOnly));
	if(!ok) { qDebug() << "Unable to open the input file."; return NULL;}



	ok = importer->import ( &(*stream), graph );
	if(!ok) { qDebug() << "Unable import graph."; }

	// ukoncenie streamu
	if (stream.get() != NULL) {
		stream->close ();
	}
	if(!ok) { return NULL; }
	return graph;
}


Manager* Manager::getInstance()
{
	if(_manager == NULL){
		_manager = new Manager();
	}
	return _manager;
}

