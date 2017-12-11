// cylgen.cpp
// Generates a cylindar with radius 1 and height 2

#include <fstream.h>
#include "affine.h"

const float PI     = 3.14159;
const float TWO_PI = 2.00000 * PI;
typedef int *Facet;

main()
{
	int num_sides, num_vertices, num_facets;
	Vector *vertices;
	Facet  *facets;
	AffineTransform longitude, latitude;
	char filename[100];
	ofstream polyfile;
	int i, j;
	int belt, next_belt, facet_count;

	cout << "Enter number of sides: ";
	cin  >> num_sides;
	cout << "Enter name of 3D file: ";
	cin  >> filename;

	num_facets   = num_sides * num_sides;
	num_vertices = ((num_sides - 1) * num_sides) + 2;
	vertices     = new Vector[num_vertices];
	facets   	   = new Facet[num_facets];
	longitude.RotateY(TWO_PI/(float)num_sides);
	latitude.RotateX(PI/(float)num_sides);

	vertices[0] = Vector(0,1,0);
	vertices[1] = latitude.Transform(vertices[0]);
	facet_count = 0;

	for(i=2; i<=num_sides; i++){
		// Calculate vertices
		vertices[i] = longitude.Transform(vertices[i-1]);

		// Generate facets
		Facet &side = facets[facet_count++];
		side        = new int[3];
		side[0]     = i;
		side[1]     = i - 1;
		side[2]     = 0;
	}

	{
		// Generate last facet
		Facet &side = facets[facet_count++];
		side    = new int[3];
		side[0] = 1;
		side[1] = i-1;
		side[2] = 0;
	}

//	belt = num_sides + 1;
	belt = 1;

	for(i=0; i<num_sides-2; i++){
		belt += num_sides;
		vertices[belt] = latitude.Transform(vertices[belt-num_sides]);
		for(j=belt+1; j<belt+num_sides; j++){
			vertices[j] = longitude.Transform(vertices[j-1]);

			// Generate facets
			Facet &side = facets[facet_count++];
			side    = new int[4];
			side[0] = j;
			side[1] = j - 1;
			side[2] = j - num_sides - 1;
			side[3] = j - num_sides;
		}

		// Generate facets
		Facet &side = facets[facet_count++];
		side    = new int[4];
		side[0] = j - num_sides;
		side[1] = j - 1;
		side[2] = j - num_sides - 1;
		side[3] = j - num_sides - num_sides;

//		belt += num_sides;
	}

	vertices[num_vertices-1] = Vector(0,-1,0);

	for(i=belt+1; i<belt+num_sides; i++){
		// Generate facets
		Facet &side = facets[facet_count++];
		side        = new int[3];
		side[0]     = num_vertices - 1;
		side[1]     = i - 1;
		side[2]     = i;
	}

	{
		// Generate last facet
		Facet &side = facets[facet_count++];
		side    = new int[3];
		side[0] = num_vertices - 1;
		side[1] = i - 1;
		side[2] = belt;
	}

	// write data to file
	polyfile.open(filename);

	polyfile << num_vertices << endl << num_facets << endl << endl;
	for(i=0; i<num_vertices; i++)
		polyfile << setw(15) << vertices[i] << endl;

	polyfile << endl;
	for(i=0; i<num_sides; i++){
		polyfile << 3 << endl
			<< setw(15) << facets[i][0]
			<< setw(15) << facets[i][1]
			<< setw(15) << facets[i][2]
			<< endl;
	}

	polyfile << endl;
	for(i; i<num_facets-num_sides; i++){
		polyfile << 4 << endl
			<< setw(15) << facets[i][0]
			<< setw(15) << facets[i][1]
			<< setw(15) << facets[i][2]
			<< setw(15) << facets[i][3]
			<< endl;
	}

	polyfile << endl;
	for(i; i<num_facets; i++){
		polyfile << 3 << endl
			<< setw(15) << facets[i][0]
			<< setw(15) << facets[i][1]
			<< setw(15) << facets[i][2]
			<< endl;
	}

	polyfile.close();

	for(i=0; i<num_facets; i++)
		if(facets[i]) delete[] facets[i];

	delete[] facets;
	delete[] vertices;

	return(0);
}
