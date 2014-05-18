#ifndef GREDGE_H
#define GREDGE_H

#include <QString>
#include <QMap>


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
