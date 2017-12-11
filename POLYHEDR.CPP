// shape.cpp

#include "polyhedr.h"

// *** Facet class ***

Facet::Facet():
num_vertices(0),
vertex_list(NULL)
{}

Facet::~Facet()
{
	delete[] vertex_list;
}

void Facet::Init(int n)
{
	num_vertices = n;

	if(!vertex_list)
		vertex_list = new int[n];
}

int &Facet::operator[](int i)
{
	return(vertex_list[i]);
}

const int &Facet::operator[](int i) const
{
	return(vertex_list[i]);
}

Facet::operator int() const
{
	return(num_vertices);
}

// *** Polyhedron class ***

Polyhedron::Polyhedron(int v, int f, const char *name):
Primative3D(name),
vertices(new Vector[v]),
facets(new Facet[f]),
num_vertices(v),
num_facets(f),
next_vertex(0),
next_facet(0)
{}

Polyhedron::Polyhedron(istream &is, const char *name):
Primative3D(name),
next_vertex(0),
next_facet(0)
{
	int i, num_points;

	is >> num_vertices >> num_facets;

	vertices = new Vector[num_vertices];
	facets   = new Facet[num_facets];

	// read in vertices
	for(i=0; i<num_vertices; i++)
		is >> vertices[i];

	// read in facets
	for(i=0; i<num_facets; i++){
		is >> num_points;
		facets[i].Init(num_points);
		for(int j=0; j<num_points; j++)
			is >> facets[i][j];
	}
}

Polyhedron::~Polyhedron()
{
	delete[] vertices;
	delete[] facets;
}

Vector &Polyhedron::operator[](int i)
{
	return(vertices[i]);
}

Vector const &Polyhedron::operator[](int i) const
{
	return(vertices[i]);
}

Facet &Polyhedron::GetFacet(int i)
{
	return(facets[i]);
}

const Facet &Polyhedron::GetFacet(int i) const
{
	return(facets[i]);
}

int Polyhedron::FindVertex(const Vector &v, int &i)
{
	int retval = 1;

	for(i=0; i<next_vertex; i++){
		if((vertices[i].x == v.x) &&
			 (vertices[i].y == v.y) &&
			 (vertices[i].z == v.z))
			break;
	}

	if(i == num_vertices)
		retval = 0;

	else if(i == next_vertex)
		vertices[next_vertex++] = v;


	return(retval);
}

void Polyhedron::Render(const Camera &cam,
												const AffineTransform &xf,
												int flags)
{
	int i, j, x1, y1, x2, y2, n;
	Vector a, b;

	Vertex *raster = new Vertex[num_vertices];

	for(i=0; i<num_vertices; i++)
		raster[i] = cam.Project(xf.Transform(vertices[i]));

	for(i=0; i<num_facets; i++){

		// backface removal
		if((flags & CULLING_FLAG) &&
			 ((raster[facets[i][2]].world_x - raster[facets[i][1]].world_x) *
				(raster[facets[i][0]].world_y - raster[facets[i][1]].world_y)) -
			 ((raster[facets[i][0]].world_x - raster[facets[i][1]].world_x) *
				(raster[facets[i][2]].world_y - raster[facets[i][1]].world_y))
					<= 0) continue;

		n  = (int)facets[i];
		x1 = raster[facets[i][n-1]].screen_x;
		y1 = raster[facets[i][n-1]].screen_y;

		for(j=0; j<n; j++){
			x2 = raster[facets[i][j]].screen_x;
			y2 = raster[facets[i][j]].screen_y;
			line(x1,y1,x2,y2);
			x1 = x2;
			y1 = y2;
		}
	}

	delete[] raster;
}

ostream &operator<<(ostream &os, Polyhedron &poly)
{
	int i, n;

	os << poly.num_vertices << endl;
	os << poly.num_facets   << endl;
	os << endl;

	for(i=0; i<poly.num_vertices; i++)
		os << setw(10) << poly.vertices[i] << endl;

	os << endl;

	for(i=0; i<poly.num_facets; i++){
		n = (int)poly.facets[i];
		os << n << endl;

		for(int j=0; j<n; j++)
			os << setw(10) << poly.facets[i][j] << endl;

		os << endl;
	}

	return(os);
}
