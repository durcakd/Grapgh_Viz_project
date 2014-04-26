#ifndef CUBE_H
#define CUBE_H

#include "Node.h"



class Cube : public Node
{

public:
	Cube();

protected:

	void drawMe() const;

	void createCube() const;


};

#endif
