#include "CoreWindow.h"
#include "layout/CoreGLWidget.h"
#include <QToolBar>



CoreWindow::CoreWindow(QGLWidget *glWidget, QWidget *parent)
	: QMainWindow(parent)
{
	createToolbar();

	setCentralWidget(glWidget);
	_coreGLWidget = glWidget;
}

void CoreWindow::createToolbar()
{
	_openFilePB			= new QPushButton("Open");
	_heightCoefSL		= new QSlider(Qt::Horizontal);
	_curveWidthCoefSL	= new QSlider(Qt::Horizontal);
	_alphaCoefSL			= new QSlider(Qt::Horizontal);
	_gapCoefSL			= new QSlider(Qt::Horizontal);
	_selectAdjNodesCB	= new QCheckBox;;

	_heightCoefSL->setRange(1, 100);
	_curveWidthCoefSL->setRange(1, 10);
	_alphaCoefSL->setRange(0, 100);
	_gapCoefSL->setRange(1, 100);

	QToolBar *toolbar = new QToolBar();
	addToolBar(Qt::LeftToolBarArea, toolbar);

	toolbar->addWidget(_openFilePB);
	toolbar->addWidget( new QLabel("Height: "));
	toolbar->addWidget( _heightCoefSL );
	toolbar->addWidget( new QLabel("Bezzier width"));
	toolbar->addWidget( _curveWidthCoefSL );
	toolbar->addWidget( new QLabel("Transparency: "));
	toolbar->addWidget( _alphaCoefSL );
	toolbar->addWidget( new QLabel("Gab between nodes"));
	toolbar->addWidget( _gapCoefSL );
	toolbar->addWidget( new QLabel("Select. connect. nodes "));
	toolbar->addWidget( _selectAdjNodesCB );

	QObject::connect(_openFilePB, SIGNAL(clicked()), this, SLOT(open()) );

}


bool CoreWindow::open(){
	const QString fileFilters = tr( "All files (*)");

	QString fileName =
			QFileDialog::getOpenFileName(this, tr("Open"), ".", fileFilters);
	if (fileName.isEmpty()){
		return false;
	}

	emit openGraph( fileName );

	return true;

}

QSlider		*CoreWindow::getHeightCoefSL() const
{
	return _heightCoefSL;
}
QSlider		*CoreWindow::getCurveWidthCoefSL() const
{
	return _curveWidthCoefSL;
}
QSlider		*CoreWindow::getAlphaCoefSL() const
{
	return _alphaCoefSL;
}
QSlider		*CoreWindow::getGapCoefSL() const
{
	return _gapCoefSL;
}
QCheckBox	*CoreWindow::getSelectAdjNodesCB() const
{
	return _selectAdjNodesCB;
}

