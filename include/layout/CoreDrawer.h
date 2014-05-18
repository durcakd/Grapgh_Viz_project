#ifndef COREDRAWER_H
#define COREDRAWER_H

#include "layout/Node.h"

class CoreDrawer
{

public:
	CoreDrawer();

	void drawTree() const;
	void addRoot(Node *root);
	void prepareTree() const;


private:

	Node *_root;

};

#endif
