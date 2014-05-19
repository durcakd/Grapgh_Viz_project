#include "layout/CoreGLWidget.h"

#include <GL/glu.h>
#include "layout/Cube.h"
#include "data/Manager.h"




CoreGLWidget::CoreGLWidget( CoreDrawer *coreDrawer, QWidget *parent)
	: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
	//: QGLWidget(parent)
{
	//setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

	xRot		= 0;
	yRot		= 0;
	zRot		= 0;
	_frusMax	= 300;
	_posZ		= 50;

	_coreDrawer = coreDrawer;

	//_coreDrawer->openNewGraph( " D://qtWorkspace//Grapgh_Viz_project//graphs//circle.graphml" );


}



void CoreGLWidget::initializeGL()
{
	//glEnable(GL_DEPTH_TEST);


	// Other
	glClearColor(1,1,1,1);
	//glClearColor( 0,0,0,0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // straight
	//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);   // premultipled

	//glBlendFunc(GL_ONE_MINUS_DST_ALPHA,GL_DST_ALPHA);
	//glBlendFunc(GL_ONE,GL_ONE);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	//glEnable(GL_ALPHA_TEST);
	//glEnable(GL_CULL_FACE);

	// (minus, L2)




	int width = 400;
	int height = 400;
	int side = qMin(width, height);
	//glViewport((width - side) / 2, (height - side) / 2, side, side);
	glViewport((width - side) / 2, (height - side) / 2, side, side);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 50);

	glMatrixMode(GL_MODELVIEW);

}

void CoreGLWidget::paintGL()
{
	// draw the scene:
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	paint();
	//draw();
}


static void qNormalizeAngle(int &angle)
{
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360 * 16)
		angle -= 360 * 16;
}
void CoreGLWidget::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
	//qDebug() << "PRESS   " << lastPos.x() << " " << lastPos.y();

}
void CoreGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::RightButton) {
		setXRotation(xRot + 8 * dy);
		setZRotation(zRot + 8 * dx);
		lastPos = event->pos();
	}else{
		lastPos = event->pos();

		GLuint glId =  faceAtPosition(lastPos);
		//qDebug() << ">>   "  << glId;
		_coreDrawer->setSelectedNode( glId);

	}
	updateGL();
}
void CoreGLWidget::wheelEvent(QWheelEvent *event){

	int numDegrees = event->delta() / 8;
	int numTicks = numDegrees / 15;

	if(numTicks > 0){
		_posZ *= 1.2f;
	}else{
		_posZ /= 1.15f;
	}
	_frusMax = _posZ*2.5f;

	qDebug() << "--- " << _posZ;
	qDebug() << "--- " << _frusMax;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat x = GLfloat(_width) / _height;
	glFrustum(-x, x, -1.0, 1.0, 4.0, _frusMax);
	glMatrixMode(GL_MODELVIEW);

	//_frusMax = ;
	//_posZ = ;

	updateGL();
}


void CoreGLWidget::resizeGL(int width, int height)
{
	_width = width;
	_height = height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat x = GLfloat(width) / height;
	glFrustum(-x, x, -1.0, 1.0, 4.0, _frusMax);
	glMatrixMode(GL_MODELVIEW);
}
void CoreGLWidget::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != xRot) {
		xRot = angle;
		updateGL();
	}
}
void CoreGLWidget::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != yRot) {
		yRot = angle;
		updateGL();
	}
}
void CoreGLWidget::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != zRot) {
		zRot = angle;
		updateGL();
	}
}



void CoreGLWidget::paint()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -_posZ);

	//glRotatef(-35, 1.0, 0.0, 0.0);
	//glRotatef(-15, 0.0, 0.0, 1.0);


	glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);


	_coreDrawer->drawTree();
	_coreDrawer->drawEdges();

	//glFlush();

}



GLuint CoreGLWidget::faceAtPosition(const QPoint &pos)
{
	const int MaxSize = 512;
	GLuint buffer[MaxSize];
	GLint viewport[4];

	makeCurrent();

	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(MaxSize, buffer);
	glRenderMode(GL_SELECT);

	glInitNames();
	//glPushName(0);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPickMatrix(GLdouble(pos.x()), GLdouble(viewport[3] - pos.y()),
			5.0, 5.0, viewport);
	GLfloat x = GLfloat(width()) / height();
	glFrustum(-x, x, -1.0, 1.0, 4.0, _frusMax);
	paint();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	if (!glRenderMode(GL_RENDER))
		return -1;
	return buffer[3];
}


