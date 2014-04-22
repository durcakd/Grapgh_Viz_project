#include "CoreDrawer.h"



CoreDrawer::CoreDrawer()
{

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
