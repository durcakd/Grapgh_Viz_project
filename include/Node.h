#ifndef NODE_H
#define NODE_H


#include <list>

class Node;

typedef std::list< Node* > NodeList;

class Node
{

public:
	Node();
	void draw();

protected:
	virtual void drawMe() const = 0;

	void	addChil(Node *child);
	void	clearChildren();
	int		childrenCount() const;
	bool	hasChildren() const;


private:
	void	drawChildren();

	NodeList	_children;

};

#endif

