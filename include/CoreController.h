#ifndef COROCONTROLLER_H
#define COROCONTROLLER_H

#include "CoreWindow.h"
#include "CoreGLWidget.h"
#include "CoreDrawer.h"


class CoreController
{
	//Q_OBJECT        // must include this if you use Qt signals/slots

public:
	CoreController();

private:
	CoreWindow		*_coreWindow;
	CoreGLWidget	*_coreGLWidget;
	CoreDrawer		*_coreDrawer;

};

#endif

