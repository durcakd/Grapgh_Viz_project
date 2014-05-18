#ifndef GRNODE_H
#define GRNODE_H

#include <QString>
#include <QMap>
#include <QVector>
#include <QtOpenGL>

class GrNode
	{
public:
	GrNode(const QString id, int glId, const QString params );
	~GrNode();

	void addEdge( int id );

	QString						getId() const;
	int							getGlId() const;
	int							getEdgeCount() const;
	const QVector<int>		   &getEdges() const;
	QMap< QString, QString >	getParams() const;
	GLfloat						r() const;
	GLfloat						g() const;
	GLfloat						b() const;
	GLfloat						a() const;

private:
	void createParameters(const QString params);
	void toString() const;


	QString _id;
	GLint _glId;
	GLfloat _r, _g, _b, _a;

	QMap< QString, QString > _params;
	QVector<int> _edges;

};

#endif
