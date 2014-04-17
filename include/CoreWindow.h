#ifndef COREWINDOW_H
#define COREWINDOW_H

#include <QMainWindow>

class CoreGLWidget;

class CoreWindow : public QMainWindow
{
	Q_OBJECT        // must include this if you use Qt signals/slots

public:
	CoreWindow(QWidget *parent = NULL);

protected:

	void createMenus();
	void createToolBars();

private:

	CoreGLWidget *mCoreGLWidget;

};

#endif
