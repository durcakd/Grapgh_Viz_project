#include "Node.h"

Node::Node()
{


}

void Node::draw()
{
	drawMe();
	drawChildren();
}

void Node::drawChildren()
{
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

int	 Node::childrenCount() const
{
	return _children.size();
}

bool Node::hasChildren() const
{
	return ! _children.empty();
}
