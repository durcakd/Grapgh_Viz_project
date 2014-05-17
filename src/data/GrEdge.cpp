#include "data/GrEdge.h"

#include <QStringListIterator>
#include <QMapIterator>
#include <QDebug>


GrEdge::GrEdge(int id, const QString sourceId, const QString targetId, bool directed, const QString params)
{
	_id			= id;
	_directed	= directed;
	_sourceId	= sourceId;
	_targetId	= targetId;

	createParameters( params );

	// control output
	//toString();
}

GrEdge::~GrEdge(){
	_params.clear();
}


void GrEdge::createParameters(const QString params)
{
	_params["weight"] = "1";

	QStringList pList = params.split(" | ");
	if( pList.size() > 1){
		if( pList.size() % 2 != 0 ){ qDebug() << "ERROR: GrEdge:: pList is not odd !"; return; }

		QStringListIterator i(pList);
		while( i.hasNext() ){
			QString key = i.next();
			QString val = i.next();
			_params[ key ] = val;
			//qDebug() << ">> " << key << "  " << val;
		}
	}

	_weight = _params["weight"].toInt();
}

void GrEdge::toString() const
{
	qDebug() << "  EDGE " << _id << "    " << _sourceId << "->" << _targetId;// << "  -- " << _directed;
	QMapIterator< QString, QString > im(_params);
	while (im.hasNext()) {
		im.next();
		qDebug() <<  "       " << im.key() << "= " << im.value();
	}
}

int  GrEdge::getId() const
{
	return _id;
}
int  GrEdge::getWeight() const
{
	return _weight;
}

bool  GrEdge::isDirected() const
{
	return _directed;
}

QString GrEdge::getSourceId() const
{
	return _sourceId;
}

QString  GrEdge::getTargetId() const
{
	return _targetId;
}

QMap< QString, QString >  GrEdge::getParams() const
{
	return _params;
}
