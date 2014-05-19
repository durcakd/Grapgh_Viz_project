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

	_heightCoef		= 10;
	_gapCoef		= 0.3f;
	_curvewidth		= 3;
	_selectAdjNodes = true;
	_alpha			= 0.2f;
}

Manager::~Manager(){ }


Graph* Manager::loadGraph(QString filepath)
{
	_graph = new Graph();

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



	ok = importer->import ( &(*stream), _graph );
	if(!ok) { qDebug() << "Unable import graph."; }

	// ukoncenie streamu
	if (stream.get() != NULL) {
		stream->close ();
	}
	if(!ok) { return NULL; }
	return _graph;
}


Manager* Manager::getInstance()
{
	if(_manager == NULL){
		_manager = new Manager();
	}
	return _manager;
}

void Manager::setAlphaCoef( int value )
{
	_alpha = ((GLfloat)value)/100.0f;
}
void Manager::setHeightCoef(GLuint heightCoef )
{
	_heightCoef = heightCoef;
}
void Manager::setGapCoef( int value )
{
	_gapCoef = ((GLfloat)value)/100.0f;
}
void Manager::setCurveWidthCoef( int width )
{
	_curvewidth = width;
}
void Manager::setSelectAdjNodes( bool select)
{
	_selectAdjNodes = select;
}

GLfloat Manager::getAlphaCoef()
{
	return _alpha;
}
GLuint Manager::getHeightCoef()
{
	return _heightCoef;
}
GLfloat Manager::getGapCoef()
{
	return _gapCoef;
}
GLuint Manager::getCurveWidthCoef()
{
	return _curvewidth;
}
bool Manager::getSelectAdjNodes()
{
	return _selectAdjNodes;
}


































