#ifndef COREGLWIDGET_H
#define COREGLWIDGET_H

#include <QGLWidget>
#include "CoreDrawer.h"

#include <QVector3D>

class CoreGLWidget : public QGLWidget
{
	Q_OBJECT        // must include this if you use Qt signals/slots

public:
	CoreGLWidget(CoreDrawer *coreDrawer, QWidget *parent = NULL);

protected:

	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);


private:
	void makeCube();

	 QVector<QVector3D> vertices;
	CoreDrawer *_coreDrawer;

};

#endif
