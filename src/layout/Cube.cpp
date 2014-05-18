#include "layout/Cube.h"
#include <QtOpenGL>
#include <QDebug>


Cube::Cube(QString name)
	: Node()
{
	//qDebug() << "Cube constructor";
	_name = name;
}


void Cube::drawMe() const
{
	//qDebug() << "drawme";

	glPushMatrix();




	//glRotatef(35, 0.0, 1.0, 0.0);

	glTranslated( _xpos, _ypos, 0 );
	glTranslated(0.0, 0.0, _realHeight);

	//double scale = 1.0 - 0.15/_scale;
	double _maxHeight = 10;
	double scale = 1.0 - (0.5/_maxHeight)*_realHeight/_vizScale;

	//qDebug() << scale;
	glScaled(scale, scale, 1.0);
	glScaled(_vizScale, _vizScale, _vizScale);

	glScaled(0.5, 0.5, 0.5);



	createCube();
	glPopMatrix();


}


void Cube::createCube() const
{

	/*static const GLfloat r = 0.0f,
			g = 0.0f,
			b = 1.0f,
			a = 0.2f;
			*/
	GLfloat r = _r,
			   g = _g,
			   b = _b,
			   a = _a;
	//qDebug() <<
	static const GLfloat vertices[12*3*3] = {

		//	GLfloat *vertices =  new GLfloat[12*3*3]{
		-1.0f,-1.0f,-1.0f, // -x
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f, // -z
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,


		1.0f,-1.0f, 1.0f, // -y
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f, // -z
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,

		-1.0f,-1.0f,-1.0f, // -x
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f, // -y
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,



		-1.0f, 1.0f, 1.0f, //
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,

		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,

		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	/*
	static const GLfloat colors[] = {
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,

		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,

		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,

		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,

		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,

		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};
*/
	const GLfloat colors[] = {
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,

		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,

		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,
		r,g,b,a,

	};

	static const GLfloat normals[] = {
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(4, GL_FLOAT, 0, colors);
	glNormalPointer(GL_FLOAT, 0, normals);

	glDrawArrays(GL_TRIANGLES, 0, 12*3);


	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState( GL_NORMAL_ARRAY );



}
