/*!
 * Manager.cpp
 * Projekt 3DVisual
 */

#include "data/Manager.h"
#include <QFile>
#include <QIODevice>
#include <QDebug>



Manager * Manager::manager;


Manager::Manager()
{
	manager = this;
}

Manager::~Manager()
{
}

int Manager::loadGraph(QString filepath)
{
	//otvaranie suboru
	bool ok = true;

	// vytvorenie infoHandler
	//GraphMLImporter *importer = new GraphMLImporter;


	// vytvorenie nacitavaneho streamu
	std::auto_ptr<QIODevice> stream (NULL);
	stream.reset (new QFile (filepath));

	ok = (stream->open (QIODevice::ReadOnly));
	if(!ok) { qDebug() << "Unable to open the input file."; return 1;}



	//*stream

	//ok = importer->import ( *stream );
	if(!ok) { qDebug() << "Unable import graph."; }

	// ukoncenie streamu
	if (stream.get() != NULL) {
		stream->close ();
	}
	if(!ok) { return 1; }
	return 0;
}

