#ifndef COREDRAWER_H
#define COREDRAWER_H

#include "Node.h"

class CoreDrawer
{

public:
	CoreDrawer();

	void drawTree() const;
	void addRoot(Node *root);


private:

	Node *_root;

};

#endif
