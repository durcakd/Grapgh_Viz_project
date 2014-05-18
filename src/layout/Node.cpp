#include "layout/Node.h"
#include <QtOpenGL>
#include <QDebug>


Node::Node()
{
	//qDebug() << "Node constructor";
	setColor();
}

void Node::draw()
{
	glPushMatrix();
	//glTranslated(0.0, 0.0, 5.0);   // zle uz je to srotovane
	drawMe();
	drawChildren();
	glPopMatrix();

}

void Node::computeLayout()
{
	qDebug() << "COMP METRICS";
	compMetrics();								qDebug() << "COMP REAL HEIGHT";

	compRealHeight(0);							qDebug() << "FIND MAX REAL HEGHT  ";
	int maxHeight = findMaxRealHeight();		qDebug() << "    = " << maxHeight;
	setMaxRealHeight( maxHeight + 1);			qDebug() << "COMP MAXED SCALE";



	QVector<double> maxScales;
	compMaxedScale( _realScale, maxScales );	qDebug() << "COMP MOST MAXED SCALE";
	compMostMaxedScale( maxScales );			qDebug() << "SET VIZ SCALE";
	maxScales.clear();

	switchVizScale( REALSCALE );				qDebug() << "COMP CHILD POS"; // REALSCALE, MAXEDSCALE, MOSTMAXED

	qDebug() << "INFO";
	//printInfo();
}

// METRICS
void Node::compMetrics()
{

	if( _children.size() == 0 ){
		_depth = 1;
		_allChildN = 0;
		_xcount = 0;
		_ycount = 0;
		_realScale = 1;

	}else {
		_allChildN = 0;
		_maxRealChildScale = 0;
		int maxDepth = 0;

		NodeList::const_iterator it;
		for( it = _children.cbegin(); it != _children.cend(); it++ ){
			(*it)->compMetrics();

			_allChildN += ((*it)->getAllChildN() + 1);
			if( maxDepth < (*it)->getDepth()) {
				maxDepth = (*it)->getDepth(); }
			if( _maxRealChildScale < (*it)->getRealScale()) {
				_maxRealChildScale = (*it)->getRealScale(); }
		}
		_xcount = (int) ceil(sqrt( (double) getChildN()));
		_ycount = getChildN() / _xcount;
		if(getChildN() >  _xcount * _ycount)
			_ycount++;


		_depth = maxDepth + 1;
		_realScale = _maxRealChildScale * _xcount;
	}
	//qDebug() << _name << "   " << _depth << "  " << _allChildN << "    -    " << getChildN() << "  " << _xcount << "x" << _ycount << "    " << _scale;
}

void Node::compMaxedScale(double scale, QVector<double> &maxScales)
{
	if( maxScales.size() > _realHeight) {
		if( maxScales.at(_realHeight) < scale ){
			maxScales[_realHeight] = scale;
		}
	} else {
		maxScales.push_back( scale );
	}

	_maxedScale = scale;

	// set all children to max scale
	if( _children.size() > 0){
		NodeList::const_iterator it;
		for( it = _children.cbegin(); it != _children.cend(); it++ ){
			(*it)->compMaxedScale( _maxRealChildScale, maxScales );
		}
	}
}

void Node::compMostMaxedScale( const QVector<double> &maxScales)
{
	_mostMaxedScale = maxScales.at(_realHeight);

	// set all children to max scale
	if( _children.size() > 0){
		NodeList::const_iterator it;
		for( it = _children.cbegin(); it != _children.cend(); it++ ){
			(*it)->compMostMaxedScale( maxScales );
		}
	}
}


void Node::setVizScale( int scaleType ){
	// REALSCALE, MAXEDSCALE, MOSTMAXED
	if( scaleType == REALSCALE ){
		_vizScale = _realScale;
	} else if( scaleType == MAXEDSCALE ){
		_vizScale = _maxedScale;
	} else if( scaleType == MOSTMAXED ){
		_vizScale = _mostMaxedScale;
	}

	NodeList::const_iterator it;
	for( it = _children.cbegin(); it != _children.cend(); it++ ){
		(*it)->setVizScale( scaleType );
	}
}

void Node::compRealHeight(int height)
{
	_realHeight = height;

	if( getChildN() != 0 ){
		NodeList::const_iterator it;
		for( it = _children.cbegin(); it != _children.cend(); it++ ){
			(*it)->compRealHeight( height+1);
		}
	}
}

int	Node::findMaxRealHeight() const
{
	int maxRealHeight = 0;
	if( getChildN() != 0 ){
		int height;
		NodeList::const_iterator it;
		for( it = _children.cbegin(); it != _children.cend(); it++ ){
			height = (*it)->findMaxRealHeight();
			if(height > maxRealHeight ){
				maxRealHeight = height;
			}
		}
	} else {
		maxRealHeight = _realHeight;
	}
	return maxRealHeight;
}

void Node::setMaxRealHeight(int maxRealHeight)
{
	_maxRealHeight = maxRealHeight;

	if( getChildN() != 0 ){
		NodeList::const_iterator it;
		for( it = _children.cbegin(); it != _children.cend(); it++ ){
			(*it)->setMaxRealHeight( maxRealHeight );
		}
	}
}

void Node::compVerticalPos(double height)
{
	_realHeight = height;

	if( getChildN() != 0 ){
		NodeList::const_iterator it;
		for( it = _children.cbegin(); it != _children.cend(); it++ ){
			(*it)->compRealHeight( height+1);
		}
	}
}


double Node::compMaxVizChildScale()
{
	_maxVizChildScale = 0.0;
	if( _children.size() != 0 ){
		NodeList::const_iterator it;
		for( it = _children.cbegin(); it != _children.cend(); it++ ){
			double childScale =  (*it)->compMaxVizChildScale();
			if( _maxVizChildScale < childScale) {
				_maxVizChildScale = childScale; }
		}
	}
	return _vizScale;
}
void Node::switchVizScale(int scaleType){
													qDebug() << "SET VIZ SCALE";
	setVizScale( scaleType );						qDebug() << "COMP MAX VIZ CHILD SCALES";
	compMaxVizChildScale();							qDebug() << "COMP CHILD POS";
	compChildPos( 0, 0 );

}
void Node::compChildPos( double xpos, double ypos)
{
	_xpos = xpos;
	_ypos = ypos;
	//qDebug() << _name << " " << _scale << "       " << _xpos << " " << _ypos;

	if( getChildN() != 0 ){
		NodeList::const_iterator it;
		int i = 0;



		for( it = _children.cbegin(); it != _children.cend(); it++ ){
			double xchpos = xpos + _vizScale/2 - _maxVizChildScale/2   - _maxVizChildScale * (i % _xcount);
			double ychpos = ypos + _vizScale/2 - _maxVizChildScale/2   - _maxVizChildScale * (i / _xcount);
			i++;
			//qDebug() << _name << " " << _scale << " " << _maxChildScale << " " << _xcount << "        " << _xpos << "x" << _ypos << "    " << xchpos << "x" << ychpos ;

			(*it)->compChildPos( xchpos, ychpos );
		}
	}
}





void Node::printInfo() const
{
	//qDebug() << _name << "   " << _depth << "  " << _allChildN << "    -    " << getChildN() << "  " << _xcount << "x" << _ycount << "    " << _scale;
	qDebug() << _name << "   " << getChildN() << "  " << _xcount << "x" << _ycount << "  " << _vizScale << "       "   << _xpos << " " << _ypos;


	NodeList::const_iterator it;

	for( it = _children.cbegin(); it != _children.cend(); it++ ){
		(*it)->printInfo();
	}

}

void Node::drawChildren()
{
	//qDebug() << "Node drawChildren";

	NodeList::const_iterator it;

	for( it = _children.cbegin(); it != _children.cend(); it++ ){
		(*it)->draw();
	}

}




void Node::addChil(Node *child)
{
	_children.push_back( child );
}

void Node::clearChildren()
{
	_children.clear();
}

int	 Node::getChildN() const
{
	return _children.size();
}

bool Node::hasChildren() const
{
	return ! _children.empty();
}
int	Node::getDepth() const
{
	return _depth;
}

int	Node::getAllChildN() const
{
	return _allChildN;
}

double	Node::getRealScale() const
{
	return _realScale;
}
void Node::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	_r = r;
	_g = g;
	_b = b;
	_a = a;
}
