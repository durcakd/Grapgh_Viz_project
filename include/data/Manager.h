#ifndef MANAGER_H
#define MANAGER_H


#include "data/Graph.h"
#include <QObject>
#include <QtOpenGL>
#include <QString>

class Manager : public QObject
{
	Q_OBJECT
public:
	~Manager();


	Graph *loadGraph(QString filepath);
	static	Manager* getInstance();

	Graph *getGraph() const {return _graph;}


	GLfloat getAlphaCoef();
	GLuint	getHeightCoef();
	GLfloat getGapCoef();
	GLuint getCurveWidthCoef();
	bool getSelectAdjNodes();

public slots:
	void setAlphaCoef( int value );
	void setHeightCoef( GLuint heightCoef );
	void setGapCoef( int value );
	void setCurveWidthCoef( int width );
	void setSelectAdjNodes( bool select);

private:

	Manager();
	static Manager *_manager;
	Graph *_graph;

	GLuint _heightCoef;
	GLfloat _gapCoef;
	GLint _curvewidth;
	bool _selectAdjNodes;
	GLfloat _alpha;

};

#endif
