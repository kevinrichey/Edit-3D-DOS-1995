// wirefram.cpp
// Wire frame 3D editor/viewer

#include <conio.h>
#include <fstream.h>
#include "polyhedr.h"

void translate(AffineTransform &xf);
void scale(AffineTransform &xf);
void rotate(AffineTransform &xf);

main()
{
	char filename[100];
	ifstream polyfile;
	AffineTransform cam_pos, obj_pos;
	Camera eye(0,0,640,480,15);

	// Load 3D object:
	cout << "Enter name of 3D object file to view:" << endl;
	cin >> filename;
	polyfile.open(filename);
	Polyhedron poly(polyfile);

	// Position camera
	Scalar cx, cy, cz;
	cout << "Enter camera position: " << endl;
	cin >> cx >> cy >> cz;
	cam_pos.Translate(cx, cy, cz);
	eye.Transform(cam_pos);

	// Initialize graphics:
	int driver = VGA;
	int mode   = VGAHI;
	initgraph(&driver, &mode, "");
	setbkcolor(BLACK);
	setcolor(WHITE);

	// Main program loop
	int done = 1;
	while(done){
		clearviewport();
		poly.Render(eye, obj_pos);

		char key = getch();
		if(!key) key = getch();
		switch(key){
		case 't':
			translate(obj_pos);
			break;
		case 's':
			scale(obj_pos);
			break;
		case 'r':
			rotate(obj_pos);
			break;
		case 'q':
			done = 0;
			break;
		} // end switch

	} // end while

	closegraph();
	return(0);
}

void translate(AffineTransform &xf)
{
	Scalar x, y, z;

	gotoxy(1,1);
	cout << "Enter translation: ";
	cin >> x >> y >> z;
	xf.Translate(x,y,z);
}

void scale(AffineTransform &xf)
{
	Scalar x, y, z;

	gotoxy(1,1);
	cout << "Enter scaling: ";
	cin >> x >> y >> z;
	xf.Scale(x,y,z);
}

void rotate(AffineTransform &xf)
{
	Scalar x, y, z;

	gotoxy(1,1);
	cout << "Enter rotation: ";
	cin >> x >> y >> z;
	xf.Rotate(x,y,z);
}
