#ifndef COREWINDOW_H
#define COREWINDOW_H

#include <QMainWindow>


class QGLWidget;

class CoreWindow : public QMainWindow
{
	Q_OBJECT        // must include this if you use Qt signals/slots

public:
	CoreWindow( QGLWidget *glWidget, QWidget *parent = NULL);

protected:

	void createMenus();
	void createToolBars();

private:

	QGLWidget *_coreGLWidget;

};

#endif
