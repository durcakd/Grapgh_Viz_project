#ifndef NODE_H
#define NODE_H


#include <list>
#include <QString>
#include <QtOpenGL>

class Node;

typedef std::list< Node* > NodeList;

enum { REALSCALE, MAXEDSCALE, MOSTMAXED };

class Node
{

public:
	Node();
	void draw();
	void computeLayout();
	void addChil(Node *child);
	void setColor(GLfloat r = 0.1f, GLfloat g = 0.1f, GLfloat b = 1.0f, GLfloat a = 0.2f);


protected:
	virtual void drawMe() const = 0;

	void	clearChildren();
	int		getChildN() const;
	bool	hasChildren() const;
	int		getDepth() const;
	int		getAllChildN() const;
	double	getRealScale() const;



	void	compMetrics();
	void	compMaxedScale(double scale, QVector<double> &maxScales);
	void	compMostMaxedScale( const QVector<double> &maxScales);
	double	compMaxVizChildScale();
	void	setVizScale(int scaleType);
	void	compRealHeight(int height);
	int		findMaxRealHeight() const;
	void	setMaxRealHeight(int maxRealHeight);
	void	compVerticalPos(double height);

	void	switchVizScale(int scaleType);

	void	compChildPos(double xpos, double ypos);


	void	printInfo() const;
	void	drawChildren();


	NodeList	_children;

	QString _name;
	GLfloat _a,_r,_g,_b;

	// metrics
	double		_realScale;
	double		_maxedScale;
	double		_mostMaxedScale;
	double		_vizScale;
	double		_maxRealChildScale;
	double		_maxVizChildScale;

	int			_depth;
	int			_realHeight;
	int			_maxRealHeight;
	int			_allChildN;
	int			_xcount;
	int			_ycount;
	double		_xpos;
	double		_ypos;




};

#endif

