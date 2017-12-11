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

	num_facets = num_sides + 1;
	vertices   = new Vector[num_sides + 1];
	facets   	 = new Facet[num_facets];
	rotator.RotateY(TWO_PI/(float)num_sides);

	vertices[0]  = Vector(0,1,0);
	vertices[1]  = Vector(1,-1,0);
	facets[0]    = new int[num_sides];
	facets[0][0] = 1;

	for(i=2; i<=num_sides; i++){
		// Calculate vertices
		vertices[i] = rotator.Transform(vertices[i-1]);

		// Generate facets
		Facet &side = facets[i-1];
		side = new int[3];
		side[0] = i;
		side[1] = i - 1;
		side[2] = 0;

		facets[0][i-1] = i;
	}

	// Generate last facet
	Facet &side = facets[i-1];
	side = new int[3];
	side[0] = 1;
	side[1] = i-1;
	side[2] = 0;

	// write data to file
	polyfile.open(filename);

	polyfile << "Polyhedron" << endl << endl;

	polyfile << (num_sides+1) << endl << num_facets << endl << endl;
	for(i=0; i<(num_sides+1); i++)
		polyfile << setw(15) << vertices[i] << endl;

	polyfile << endl << num_sides << endl;
	for(i=0; i<num_sides; i++)
		polyfile << setw(15) << facets[0][i];

	polyfile << endl;
	for(i=1; i<num_facets; i++){
		polyfile << 3 << endl
			<< setw(15) << facets[i][0]
			<< setw(15) << facets[i][1]
			<< setw(15) << facets[i][2]
			<< endl;
	}
	polyfile.close();

	for(i=0; i<num_facets; i++)
		delete[] facets[i];

	delete[] facets;
	delete[] vertices;

	return(0);
}
