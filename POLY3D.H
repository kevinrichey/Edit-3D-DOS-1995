// poly3d.h
// 3D polygons

#ifndef __POLY3D_H
#define __POLY3D_H

#include "prim3d.h"

class Polygon3D: public Primative3D{

public:
	Polygon3D(int num);
	~Polygon3D();

	Vector &operator[](int i);
	const Vector &operator[](int i) const;
	operator int();

	virtual void Render(const Camera &cam,
											const AffineTransform &xf);

private:
	int num_vertices;
	Vertex *vertices;

};

#endif
