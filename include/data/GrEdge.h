#ifndef GREDGE_H
#define GREDGE_H

#include <QString>
#include <QMap>
#include <QtOpenGL>


class GrEdge
	{
public:
	GrEdge( int id, const QString sourceId, const QString targetId, bool directed, const QString params );
	~GrEdge();


	int							getId() const;
	int							getWeight() const;
	bool						isDirected() const;
	QString						getSourceId() const;
	QString						getTargetId() const;
	QMap< QString, QString >	getParams() const;
	void setColor(GLfloat r = 0.1f, GLfloat g = 1.0f, GLfloat b = 0.1f, GLfloat a = 0.8f);



	GLfloat	_sx;
	GLfloat	_sy;
	GLint	_srh;
	GLfloat	_tx;
	GLfloat	_ty;
	GLint	_trh;
	GLfloat	_r, _g, _b, _a;

	void  draw();


private:
	void createParameters(const QString params);
	void toString() const;

	int		_id;
	bool	_directed;
	QString _sourceId;
	QString _targetId;

	int		_weight;



	QMap< QString, QString > _params;
};

#endif
