#include "CoreDrawer.h"

#include <QDebug>

CoreDrawer::CoreDrawer()
{
	_root = NULL;
}

void CoreDrawer::drawTree() const
{

_root->draw();


}


void CoreDrawer::addRoot( Node *root)
{
	delete _root;
	_root = root;
}
