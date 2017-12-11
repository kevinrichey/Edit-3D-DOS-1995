// prim3d.h

#ifndef __PRIM3D_H
#define __PRIM3D_H

#include "object3d.h"

// Base class for 3D primatives
class Primative3D: public Object3D{

public:
	Primative3D(const char *n):Object3D(n) {}
	virtual ~Primative3D(){}

	virtual void Render(const Camera &cam,
											const AffineTransform &xf,
											int flags=ALL_FLAGS) = 0;
};

#endif
