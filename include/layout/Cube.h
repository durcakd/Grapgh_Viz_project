#ifndef CUBE_H
#define CUBE_H

#include "layout/Node.h"



class Cube : public Node
{

public:
	Cube( QString name = "");

protected:

	void drawMe() const;

	void createCube() const;



};

#endif
