#include "CoreWindow.h"
#include "CoreGLWidget.h"


CoreWindow::CoreWindow(QWidget *parent)
	: QMainWindow(parent)
{

	mCoreGLWidget = new CoreGLWidget(this);
	this->setCentralWidget( mCoreGLWidget );
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
