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
	compMetrics();							qDebug() << "COMP MAXED SCALE";
	compMaxedScale( _realScale );			qDebug() << "SET VIZ SCALE";
	setVizScale( true );					qDebug() << "COMP CHILD POS";

	compChildPos( 0, 0);					qDebug() << "COMP HEIGHT";
	compRealHeight(0);						qDebug() << "FIND MAX REAL HEGHT  ";
	int maxHeight = findMaxRealHeight();	qDebug() << "    = " << maxHeight;
	setMaxRealHeight( maxHeight + 1);

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
		_maxChildScale = 0;
		int maxDepth = 0;

		NodeList::const_iterator it;
		for( it = _children.cbegin(); it != _children.cend(); it++ ){
			(*it)->compMetrics();

			_allChildN += ((*it)->getAllChildN() + 1);
			if( maxDepth < (*it)->getDepth()) {
				maxDepth = (*it)->getDepth(); }
			if( _maxChildScale < (*it)->getRealScale()) {
				_maxChildScale = (*it)->getRealScale(); }
		}
		_xcount = (int) ceil(sqrt( (double) getChildN()));
		_ycount = getChildN() / _xcount;
		if(getChildN() >  _xcount * _ycount)
			_ycount++;


		_depth = maxDepth + 1;
		_realScale = _maxChildScale * _xcount;
	}
	//qDebug() << _name << "   " << _depth << "  " << _allChildN << "    -    " << getChildN() << "  " << _xcount << "x" << _ycount << "    " << _scale;
}

void Node::compMaxedScale(double scale)
{
	_maxedScale = scale;

	// set all children to max scale
	if( _children.size() > 0){
		NodeList::const_iterator it;
		for( it = _children.cbegin(); it != _children.cend(); it++ ){
			(*it)->compMaxedScale( _maxChildScale );
		}
	}
}

void Node::setVizScale(bool maxed){
	_vizScale = maxed ? _maxedScale : _realScale;
	NodeList::const_iterator it;
	for( it = _children.cbegin(); it != _children.cend(); it++ ){
		(*it)->setVizScale( maxed );
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


void Node::compChildPos( double xpos, double ypos)
{
	_xpos = xpos;
	_ypos = ypos;
	//qDebug() << _name << " " << _scale << "       " << _xpos << " " << _ypos;

	if( getChildN() != 0 ){
		NodeList::const_iterator it;
		int i = 0;
		for( it = _children.cbegin(); it != _children.cend(); it++ ){
			double xchpos = xpos + _vizScale/2 - _maxChildScale/2   - _maxChildScale * (i % _xcount);
			double ychpos = ypos + _vizScale/2 - _maxChildScale/2   - _maxChildScale * (i / _xcount);
			i++;
			//qDebug() << _name << " " << _scale << " " << _maxChildScale << " " << _xcount << "        " << _xpos << "x" << _ypos << "    " << xchpos << "x" << ychpos ;

			(*it)->compChildPos( xchpos, ychpos);
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
