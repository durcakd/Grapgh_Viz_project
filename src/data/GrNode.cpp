#include "data/GrNode.h"

#include <QStringListIterator>
#include <QMapIterator>
#include <QDebug>

GrNode::GrNode(const QString id, int glId, const QString params){
	_id		= id;
	_glId	= glId;

	createParameters( params );



	// control output
	//toString();
}

GrNode::~GrNode()
{
	_params.clear();
}



void GrNode::addEdge( int id )
{
	_edges.append( id );
}

void GrNode::createParameters(const QString params)
{
	QStringList pList = params.split(" | ", QString::SkipEmptyParts);
	if( pList.size() > 1){
		if( pList.size() % 2 != 0 ){ qDebug() << "ERROR: GrNode:: pList is not odd !"; return; }

		QStringListIterator i(pList);
		while( i.hasNext() ){
			QString key = i.next();
			QString val = i.next();
			_params[ key ] = val;
			//qDebug() << ">> " << key << "  " << val;
		}
	}


	// color
	QStringList colors = _params["color"].split(",");
	if( colors.size() != 3 ){
		_params["color"] = "1,1,250";
		colors = _params["color"].split(",");
	}
	_r = (GLfloat) colors.at(0).toFloat() / 255;
	_g = (GLfloat) colors.at(1).toFloat() / 255;
	_b = (GLfloat) colors.at(2).toFloat() / 255;
	_a = 0.2f;

}

void GrNode::toString() const
{
	qDebug() << "  NODE  " << _id  << "     " << _r << "-" << _g << "-" << _b << "-" << _a;
	QMapIterator< QString, QString > im(_params);
	while( im.hasNext()) {
		im.next();
		qDebug() <<  "       " << im.key() << "= " << im.value();
	}
}


QString  GrNode::getId() const
{
	return _id;
}

int GrNode::getGlId() const
{
	return _glId;
}

QMap< QString, QString >  GrNode::getParams() const
{
	return _params;
}

int GrNode::getEdgeCount() const
{
	return _edges.size();
}

const QVector<int> &GrNode::getEdges() const
{
	return _edges;
}

GLfloat GrNode::r() const
{
	return _r;
}
GLfloat GrNode::g() const
{
	return _g;
}
GLfloat GrNode::b() const
{
	return _b;
}
GLfloat GrNode::a() const
{
	return _a;
}
