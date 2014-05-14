#include "Node.h"
#include <QtOpenGL>
#include <QDebug>


Node::Node()
{
//qDebug() << "Node constructor";

}

void Node::draw()
{
	glPushMatrix();
	drawMe();
	drawChildren();
	glPopMatrix();

}

void Node::computeLayout()
{
	compMetrics();
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
	qDebug() << _name << "   " << _depth << "  " << _allChildN << "    -    " << getChildN() << "  " << _xcount << "x" << _ycount << "    " << _scale;
}

void	compPosition()
{

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

int	Node::getScale() const
{
	return _scale;
}
