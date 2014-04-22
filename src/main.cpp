#include <QApplication>
#include <CoreWindow.h>

#include "CoreController.h"


int main( int argc, char *argv[])
{
	QApplication app(argc, argv);

	CoreController coreController;

	return app.exec();
}

