#ifndef COREGLWIDGET_H
#define COREGLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include "layout/CoreDrawer.h"

#include <QVector3D>

class CoreGLWidget : public QGLWidget
{
	Q_OBJECT        // must include this if you use Qt signals/slots

public:
	CoreGLWidget(CoreDrawer *coreDrawer, QWidget *parent = NULL);

public slots:
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);

protected:

	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

	void paint();


	GLuint faceAtPosition(const QPoint &pos);


private:
	void makeCube();

	 QVector<QVector3D> vertices;
	CoreDrawer *_coreDrawer;

	int _width;
	int _height;
	GLfloat _frusMax;
	GLfloat _posZ;
	int xRot;
	int yRot;
	int zRot;
	GLfloat rotationX;
   GLfloat rotationY;
   GLfloat rotationZ;
	QPoint lastPos;
	QPoint actPos;

};

#endif
