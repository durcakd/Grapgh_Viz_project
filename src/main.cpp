#include <QApplication>
#include <CoreWindow.h>

#include "CoreController.h"

#include "data/Manager.h"

int main( int argc, char *argv[])
{
	QApplication app(argc, argv);

	//CoreController coreController;

	Manager::getInstance()->loadGraph("D:\\qtWorkspace\\Grapgh_Viz_project\\graphs\\colored.graphml" );
	//Manager::getInstance()->loadGraph("colored.graphml" );
	//Manager::getInstance()->loadGraph("veolia.graphml" );

	return 0; //return app.exec();
}

