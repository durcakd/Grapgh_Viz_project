#include "CoreController.h"

CoreController::CoreController()
{

	_coreDrawer = new CoreDrawer;
	_coreGLWidget = new CoreGLWidget(_coreDrawer );
	_coreWindow = new CoreWindow( _coreGLWidget );

	_coreWindow->resize( 400, 300 );
	_coreWindow->show();

}


