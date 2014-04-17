#include <QApplication>
#include <CoreWindow.h>


int main( int argc, char *argv[])
{
	QApplication app(argc, argv);
	CoreWindow coreWindow;
	//coreWindow.resize( coreWindow.sizeHint());
	coreWindow.resize( 400, 300 );

	coreWindow.show();

	return app.exec();
}

