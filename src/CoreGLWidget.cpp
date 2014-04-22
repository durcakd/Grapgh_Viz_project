#include "CoreGLWidget.h"

CoreGLWidget::CoreGLWidget( CoreDrawer *coreDrawer, QWidget *parent)
	: QGLWidget(parent)
{
	_coreDrawer = coreDrawer;
}



void CoreGLWidget::initializeGL()
{
	// Set up the rendering context, define display lists etc.:

	//glClearColor(0.0, 0.0, 0.0, 0.0);
	//glEnable(GL_DEPTH_TEST);

}

void CoreGLWidget::resizeGL(int w, int h)
{
	// setup viewport, projection etc.:
	//glViewport(0, 0, (GLint)w, (GLint)h);

	//glFrustum(...);

}

void CoreGLWidget::paintGL()
{
	// draw the scene:

	//glRotatef(...);
	//glMaterialfv(...);
	//glBegin(GL_QUADS);
	//glVertex3f(...);
	//glVertex3f(...);

	//glEnd();

}
