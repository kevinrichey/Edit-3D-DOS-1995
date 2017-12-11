// cylgen.cpp
// Generates a cylindar with radius 1 and height 2

#include <fstream.h>
#include "affine.h"

const float TWO_PI = 2.00000 * 3.14159;
typedef int *Facet;

main()
{
	int num_sides, num_facets;
	Vector *vertices;
	Facet  *facets;
	AffineTransform rotator;
	char filename[100];
	ofstream polyfile;
	int i;

	cout << "Enter number of sides: ";
	cin  >> num_sides;
	cout << "Enter name of 3D file: ";
	cin  >> filename;

	num_facets = num_sides + 2;
	vertices   = new Vector[num_sides << 1];
	facets   	 = new Facet[num_facets];
	rotator.RotateY(TWO_PI/(float)num_sides);

	vertices[0] 		 		= Vector(1,1,0);
	vertices[num_sides] = Vector(1,-1,0);
	facets[0]    = new int[num_sides];
	facets[1]    = new int[num_sides];
	facets[0][0] = 0;
	facets[1][0] = num_sides;

	for(i=1; i<num_sides; i++){
		// Calculate vertices
		vertices[i] = rotator.Transform(vertices[i-1]);
		vertices[i+num_sides].x = vertices[i].x;
		vertices[i+num_sides].y = -1;
		vertices[i+num_sides].z = vertices[i].z;

		// Generate facets
		Facet &side = facets[i+1];

		side = new int[4];
		side[3] = i;
		side[2] = i - 1;
		side[1] = i + num_sides - 1;
		side[0] = i + num_sides;

		facets[0][num_sides-i] = i;
		facets[1][i] = i + num_sides;
	}

	// Generate last facet
	Facet &side = facets[i+1];

	side = new int[4];
	side[3] = 0;
	side[2] = i - 1;
	side[1] = i + num_sides - 1;
	side[0] = num_sides;

	// write data to file
	polyfile.open(filename);

	polyfile << (2*num_sides) << endl << num_facets << endl << endl;
	for(i=0; i<(2*num_sides); i++)
		polyfile << setw(15) << vertices[i] << endl;

	polyfile << endl << num_sides << endl;
	for(i=0; i<num_sides; i++)
		polyfile << setw(15) << facets[0][i];

	polyfile << endl << num_sides << endl;
	for(i=0; i<num_sides; i++)
		polyfile << setw(15) << facets[1][i];

	polyfile << endl;
	for(i=2; i<num_facets; i++){
		polyfile << 4 << endl
			<< setw(15) << facets[i][0]
			<< setw(15) << facets[i][1]
			<< setw(15) << facets[i][2]
			<< setw(15) << facets[i][3]
			<< endl;
	}
	polyfile.close();

	for(i=0; i<num_facets; i++)
		delete[] facets[i];

	delete[] facets;
	delete[] vertices;

	return(0);
}
