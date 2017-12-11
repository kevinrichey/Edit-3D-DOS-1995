// shape.h

#ifndef __SHAPE_H
#define __SHAPE_H

#include <graphics.h>
#include <iostream.h>
#include "prim3d.h"

class Facet{

public:
	Facet();
	~Facet();

	void Init(int n);
	int &operator[](int i);
	const int &operator[](int i) const;
	operator int() const;

private:
	int num_vertices;
	int *vertex_list;

};

class Polyhedron: public Primative3D{

public:
	Polyhedron(int v, int f, const char *name);
	Polyhedron(istream &is, const char *name);
	~Polyhedron();

	Vector &operator[](int i);
	Vector const &operator[](int i) const;
	Facet &GetFacet(int i);
	const Facet &GetFacet(int i) const;
	int FindVertex(const Vector &v, int &i);

	virtual void Render(const Camera &cam,
											const AffineTransform &xf,
											int flags=ALL_FLAGS);

	friend ostream &operator<<(ostream &os, Polyhedron &poly);

private:
	Vector *vertices;
	Facet *facets;
	int num_vertices, num_facets;
	int next_vertex, next_facet;

};

ostream &operator<<(ostream &os, Polyhedron &poly);

#endif
