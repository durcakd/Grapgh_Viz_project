#include "CoreGLWidget.h"

#include "Cube.h"

CoreGLWidget::CoreGLWidget( CoreDrawer *coreDrawer, QWidget *parent)
	: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	_coreDrawer = coreDrawer;

	Node *root = new Cube;

	_coreDrawer->addRoot( root);
}


void CoreGLWidget::initializeGL()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//glCullFace(GL_BACK);
	//glFrontFace(GL_CW);

	//glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_MULTISAMPLE);
	static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);


	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);

	// Other
	glClearColor(0,0,0,1);
	glColor4f(0,0,1, 0.2);

	glDepthFunc(GL_LEQUAL);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	//glEnable(GL_CULL_FACE);

}

void CoreGLWidget::paintGL()
{

	// draw the scene:
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ModelView to WorldView transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -8.0);


	_coreDrawer->drawTree();

	glFlush();

}



void CoreGLWidget::resizeGL(int width, int height)
{
	int side = qMin(width, height);
	//glViewport((width - side) / 2, (height - side) / 2, side, side);
	glViewport((width - side) / 2, (height - side) / 2, side, side);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustum(-1.0, 1.0, -1.0, 1.0, 5, 100);
	//glOrtho(-0.5, +0.5, +0.5, -0.5, 4.0, 15.0);

	glMatrixMode(GL_MODELVIEW);

}
void CoreGLWidget::mousePressEvent(QMouseEvent *event){}
void CoreGLWidget::mouseMoveEvent(QMouseEvent *event){}
