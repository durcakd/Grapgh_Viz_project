#ifndef NODE_H
#define NODE_H


#include <list>
#include <QString>

class Node;

typedef std::list< Node* > NodeList;

class Node
{

public:
	Node();
	void draw();
	void computeLayout();
	void addChil(Node *child);


protected:
	virtual void drawMe() const = 0;

	void	clearChildren();
	int		getChildN() const;
	bool	hasChildren() const;
	int		getDepth() const;
	int		getAllChildN() const;
	int		getScale() const;

	void	drawChildren();
	void	compMetrics();
	void	compPosition();


	NodeList	_children;

	QString _name;
	int		_scale;
	int		_maxChildScale;
	int		_depth;
	int		_childN;
	int		_allChildN;
	int		_xcount;
	int		_ycount;
};

#endif

