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
	compMetrics();
	qDebug() << "COMP CHID POS";
	compChildPos( 0, 0);
	compHeight(0);

	qDebug() << "INFO";
	printInfo();
}

void Node::compMetrics()
{

	if( _children.size() == 0 ){
		_depth = 1;
		_allChildN = 0;
		_xcount = 0;
		_ycount = 0;
		_scale = 1;

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
			if( _maxChildScale < (*it)->getScale()) {
				_maxChildScale = (*it)->getScale(); }
		}
		_xcount = (int) ceil(sqrt( (double) getChildN()));
		_ycount = getChildN() / _xcount;
		if(getChildN() >  _xcount * _ycount)
			_ycount++;


		_depth = maxDepth + 1;
		_scale = _maxChildScale * _xcount;
	}
	//qDebug() << _name << "   " << _depth << "  " << _allChildN << "    -    " << getChildN() << "  " << _xcount << "x" << _ycount << "    " << _scale;
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
			double xchpos = xpos + _scale/2 - _maxChildScale/2   - _maxChildScale * (i % _xcount);
			double ychpos = ypos + _scale/2 - _maxChildScale/2   - _maxChildScale * (i / _xcount);
			i++;
			//qDebug() << _name << " " << _scale << " " << _maxChildScale << " " << _xcount << "        " << _xpos << "x" << _ypos << "    " << xchpos << "x" << ychpos ;

			(*it)->compChildPos( xchpos, ychpos);
		}
	}
}

void Node::compHeight(int height)
{
	_realHeight = height;

	if( getChildN() != 0 ){
		NodeList::const_iterator it;
		for( it = _children.cbegin(); it != _children.cend(); it++ ){
			(*it)->compHeight( height+1);
		}
	}
}

void Node::printInfo() const
{
	//qDebug() << _name << "   " << _depth << "  " << _allChildN << "    -    " << getChildN() << "  " << _xcount << "x" << _ycount << "    " << _scale;
	qDebug() << _name << "   " << getChildN() << "  " << _xcount << "x" << _ycount << "  " << _scale << "       "   << _xpos << " " << _ypos;


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

double	Node::getScale() const
{
	return _scale;
}
void Node::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	_r = r;
	_g = g;
	_b = b;
	_a = a;
}
