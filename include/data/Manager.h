#ifndef MANAGER_H
#define MANAGER_H 1



//#include <QtXml/QDomElement>
//#include <QFile>
//#include <qfileinfo.h>

#include <QString>

class Manager
	{
public:
	~Manager();


	int		loadGraph(QString filepath);
	static	Manager* getInstance();

private:

	Manager();
	static Manager * manager;

};

#endif
