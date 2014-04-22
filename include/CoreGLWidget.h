#ifndef COREGLWIDGET_H
#define COREGLWIDGET_H

#include <QGLWidget>
#include "CoreDrawer.h"


class CoreGLWidget : public QGLWidget
{
	Q_OBJECT        // must include this if you use Qt signals/slots

public:
	CoreGLWidget(CoreDrawer *coreDrawer, QWidget *parent = NULL);

protected:

	void initializeGL();

	void resizeGL(int w, int h);

	void paintGL();


private:
	CoreDrawer *_coreDrawer;

};

#endif
