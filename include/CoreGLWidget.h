#ifndef COREGLWIDGET_H
#define COREGLWIDGET_H

#include <QGLWidget>

class CoreGLWidget : public QGLWidget
{
	Q_OBJECT        // must include this if you use Qt signals/slots

public:
	CoreGLWidget(QWidget *parent);

protected:

	void initializeGL();

	void resizeGL(int w, int h);

	void paintGL();

};

#endif
