#include "CoreController.h"
#include "data/Manager.h"

CoreController::CoreController()
{

	_coreDrawer = new CoreDrawer;
	_coreGLWidget = new CoreGLWidget(_coreDrawer );
	_coreWindow = new CoreWindow( _coreGLWidget );


	QObject::connect( _coreWindow, SIGNAL(openGraph(QString)),
					 _coreDrawer, SLOT(openNewGraph(QString)) );

	QObject::connect( _coreWindow->getHeightCoefSL(), SIGNAL(valueChanged(int)),
					 _coreDrawer, SLOT(computeHeightCoef(int))  );


	Manager *man = Manager::getInstance();
	QObject::connect( _coreDrawer, SIGNAL(sentHeightCoef(GLuint)),
					 man, SLOT(setHeightCoef(GLuint))  );
	QObject::connect( _coreWindow->getAlphaCoefSL(), SIGNAL(valueChanged(int)),
					 man, SLOT(setAlphaCoef(int))  );
	QObject::connect( _coreWindow->getCurveWidthCoefSL(), SIGNAL(valueChanged(int)),
					 man, SLOT(setCurveWidthCoef(int))  );
	QObject::connect( _coreWindow->getGapCoefSL(), SIGNAL(valueChanged(int)),
					 man, SLOT(setGapCoef(int))  );
	QObject::connect( _coreWindow->getSelectAdjNodesCB(), SIGNAL(clicked(bool)),
					 man, SLOT(setSelectAdjNodes(bool))  );

	_coreWindow->resize( 800, 800 );
	_coreWindow->show();

}


