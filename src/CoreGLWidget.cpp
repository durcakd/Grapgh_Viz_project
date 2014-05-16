#include "CoreGLWidget.h"

#include "Cube.h"

CoreGLWidget::CoreGLWidget( CoreDrawer *coreDrawer, QWidget *parent)
	: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	_coreDrawer = coreDrawer;
	xRot = 0;
	yRot = 0;
	zRot = 0;

	Node *root = new Cube("root");
	Node *a = new Cube("a   ");
	Node *aa = new Cube("aa  ");
	Node *aaa = new Cube("aaa ");
	Node *ab = new Cube("ab  ");
	Node *b = new Cube("b   ");
	Node *c = new Cube("c   ");
	Node *ca = new Cube("ca  ");
	Node *cb = new Cube("cb  ");
	Node *cba = new Cube("cba ");
	Node *cbb = new Cube("cbb ");
	Node *cd = new Cube("cd  ");

	root->addChil(a);
	root->addChil(b);
	root->addChil(c);
	a->addChil(aa);
	a->addChil(ab);
	aa->addChil(aaa);
	c->addChil(ca);
	c->addChil(cb);
	c->addChil(cd);
	cb->addChil(cba);
	cb->addChil(cbb);

	_coreDrawer->addRoot( root);
	_coreDrawer->prepareTree();
}

GLfloat ctrlpoints[4][3] = {
	{ -3.5, -3.5, 1.0}, { -3.5, -3.5, 7.0},
	{3.5, 3.5, 7.0}, {3.5, 3.5, 1.0}};


// Set up lighting
void CoreGLWidget::initLight()
{
	GLfloat LightAmbient[]= { 0.2f, 0.2f, 0.2f, 1.0f };// Okolní svìtlo
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightAmbient);

	GLfloat LightDiffuse[]= { 0.9f, 0.9f, 0.9f, 1.0f };// Pøímé svìtlo
	GLfloat LightPosition[]= { 4.0f, 0.0f, 8.0f, 1.0f };// Pozice svìtla
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);// Nastavení pøímého svìtla
	glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);// Nastavení pozice svìtla

	GLfloat LightColor1[]= { 0.5f, 0.2f, 0.2f, 1.0f };// Pøímé svìtlo
	GLfloat LightPosition1[]= { -1.0f, 0.5f, 0.5f, 1.0f };// Pozice svìtla
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);// Nastavení pøímého svìtla
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition1);// Nastavení pozice svìtla
	//glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);// Nastavení pozice svìtla

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_SMOOTH);
	  //
}
void CoreGLWidget::initLight2()
{

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_MULTISAMPLE);
	static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void CoreGLWidget::initializeGL()
{
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);

	//glCullFace(GL_BACK);
	//glFrontFace(GL_CW);


	//initLight();
	//initLight2();


	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);

	// Other
	glClearColor(0,1,1,1);
	glColor4f(0,0,1, 0.2);

	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glDepthFunc(GL_LEQUAL);
	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_GREATER, 0.5);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // straight
	//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);   // premultipled

	//glBlendFunc(GL_ONE_MINUS_DST_ALPHA,GL_DST_ALPHA);
	//glBlendFunc(GL_ONE,GL_ONE);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	//glEnable(GL_ALPHA_TEST);
	//glEnable(GL_CULL_FACE);

	// (minus, L2)


	int ncl = 4;
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, ncl, &ctrlpoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);

}

void CoreGLWidget::paintGL()
{


	// draw the scene:
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// ModelView to WorldView transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -28.0);

	glRotatef(-35, 1.0, 0.0, 0.0);
	glRotatef(-15, 0.0, 0.0, 1.0);

	glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);


	// curva
	glColor3f(0.0f, 1.0f, 0.0f);
	glLineWidth(3.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 30; i++)
		glEvalCoord1f((GLfloat) i/30.0);
	glEnd();

	// curva point
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 4; i++)
		glVertex3fv(&ctrlpoints[i][0]);
	glEnd();


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
}
void CoreGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(xRot + 8 * dy);
		setYRotation(yRot + 8 * dx);
	} else if (event->buttons() & Qt::RightButton) {
		setXRotation(xRot + 8 * dy);
		setZRotation(zRot + 8 * dx);
	}
	lastPos = event->pos();
}

void CoreGLWidget::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != xRot) {
		xRot = angle;
		updateGL();
	}
}
//! [5]

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
