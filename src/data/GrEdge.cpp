#include "data/GrEdge.h"

#include <QStringListIterator>
#include <QMapIterator>
#include <QDebug>
#include <QtOpenGL>
#include "data/Manager.h"

GrEdge::GrEdge(int id, const QString sourceId, const QString targetId, bool directed, const QString params)
{
	_id			= id;
	_directed	= directed;
	_sourceId	= sourceId;
	_targetId	= targetId;

	createParameters( params );
	setColor();

	// control output
	//toString();
}

GrEdge::~GrEdge(){
	_params.clear();
}

void GrEdge::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	_r = r;
	_g = g;
	_b = b;
	_a = a;
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

void  GrEdge::draw()
{
	GLfloat heightCoef	= Manager::getInstance()->getHeightCoef();
	GLfloat curvewidth	= Manager::getInstance()->getCurveWidthCoef();


	GLfloat ctrlpoints[4][3] = {
		{ _sx, _sy, _srh*heightCoef+heightCoef/2}, { _sx, _sy, _srh*heightCoef*2},
		{ _tx, _ty, _trh*heightCoef*2}, {_tx, _ty, _trh*heightCoef+heightCoef/2}};


	int ncl = 4;
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, ncl, &ctrlpoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);


	// curva

	glColor4f(_r, _g, _b, _a);
	glLineWidth(curvewidth);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 30; i++)
		glEvalCoord1f((GLfloat) i/30.0);
	glEnd();


}
