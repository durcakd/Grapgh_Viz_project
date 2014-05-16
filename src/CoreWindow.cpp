#include "CoreWindow.h"
#include "layout/CoreGLWidget.h"


CoreWindow::CoreWindow(QGLWidget *glWidget, QWidget *parent)
	: QMainWindow(parent)
{

	glWidget->setParent( this );
	setCentralWidget( glWidget );

	_coreGLWidget = glWidget;
}

void CoreWindow::createMenus()
 {
	 //fileMenu = menuBar()->addMenu(tr("&File"));
	 //fileMenu->addAction(newAct);
}

void CoreWindow::createToolBars()
{
	//fileToolBar = addToolBar(tr("File"));
	//fileToolBar->addAction(newAct);
}
