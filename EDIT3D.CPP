// wirefram.cpp
// Wire frame 3D editor/viewer

#include <conio.h>
#include <fstream.h>
#include "polyhedr.h"
#include "struct3d.h"

typedef ObjectInstance *InstPtr;

void WaitKey(void);
char GetKey(void);
void LoadShape(ObjectStructure &dbase);
void SaveScene(ObjectStructure &scene);
void AddObject(InstPtr &act, ObjectStructure &dbase,
							 ObjectStructure &scene);
void EditObject(InstPtr &obj, ObjectStructure &dbase);
void SetCamera(ObjectInstance &scale_cam,
							 ObjectInstance &rotate_cam,
							 ObjectInstance &translate_cam);
void translate(AffineTransform &xf);
void scale(AffineTransform &xf);
void rotate(AffineTransform &xf);

main()
{
	AffineTransform dummy_xform;
	ObjectStructure dbase("dbase"), scene("scene");
	ObjectInstance *active = NULL;
	int flags = ALL_FLAGS;

	// initialize camera
	Camera eye(0,0,480,480,15);
	ObjectInstance scale_cam(&scene, "scale_cam");
	ObjectInstance rotate_cam(&scale_cam, "rotate_cam");
	ObjectInstance trans_cam(&rotate_cam, "trans_cam");

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
		trans_cam.Render(eye, dummy_xform, flags);
		gotoxy(1,1);
		if(active) cout << "(l,w,a,e,c,t,s,r,b,q)";
		else		   cout << "(l,w,a,e,c,b,q)";

		char key = GetKey();
		switch(key){
		case 'l':
		case 'L':
			LoadShape(dbase);
			break;
		case 'w':
		case 'W':
			SaveScene(scene);
			break;
		case 'a':
		case 'A':
			AddObject(active, dbase, scene);
			break;
		case 'e':
		case 'E':
			EditObject(active, scene);
			break;
		case 'c':
		case 'C':
			SetCamera(scale_cam, rotate_cam, trans_cam);
			break;
		case 't':
		case 'T':{
			if(!active){
				cout << "No active object.";
				WaitKey();
				break;
			}
			AffineTransform obj_pos;
			translate(obj_pos);
			active->Transform(obj_pos);
			break;
		}
		case 'S':
		case 's':{
			if(!active){
				cout << "No active object.";
				WaitKey();
				break;
			}
			AffineTransform obj_pos;
			scale(obj_pos);
			active->Transform(obj_pos);
			break;
		}
		case 'r':
		case 'R':{
			if(!active){
				cout << "No active object.";
				WaitKey();
				break;
			}
			AffineTransform obj_pos;
			rotate(obj_pos);
			active->Transform(obj_pos);
			break;
		}
		case 'b':
		case 'B':
			if((flags&CULLING_FLAG)) flags &= ~CULLING_FLAG;
			else flags |= CULLING_FLAG;
			break;
		case 'q':
		case 'Q':
			done = 0;
			break;
		} // end switch

	} // end while

	closegraph();
	return(0);
}

void WaitKey(void)
{
	if(!getch()) getch();
}

char GetKey(void)
{
	char key = getch();
	if(!key) key = getch();
	return(key);
}

void LoadShape(ObjectStructure &dbase)
{
	char shape[30], type[40], filename[100];
	ifstream polyfile;

	// Load 3D object:
	gotoxy(1,1);
	cout << "Enter name of 3D shape: ";
	cin >> shape;
	strcat(strcpy(filename,shape), ".3d");

	polyfile.open(filename);

	if(polyfile){
		// Determine type of shape
		polyfile >> type;
		if(strcmp(type,"Polyhedron") == 0){
			Polyhedron *poly = new Polyhedron(polyfile, shape);
			dbase.AddObject(poly, shape);

		} else if(strcmp(type, "ObjectStructure") == 0){
			ObjectStructure *obj_struct =
				new ObjectStructure(polyfile, dbase, shape);
			dbase.AddObject(obj_struct, shape);

		} else{
			cout << "Shape type not recognized.";
			WaitKey();
		}

	} else{
		gotoxy(1,1);
		cout << "Shape " << shape << " not found                     ";
		WaitKey();
	}
}

void SaveScene(ObjectStructure &scene)
{
	char filename[100];
	ofstream struct_file;

	gotoxy(1,1);
	cout << "Enter name to save under: ";
	cin  >> filename;
	strcat(filename, ".3D");

	struct_file.open(filename);

	if(struct_file)
		struct_file << scene;

	else{
		gotoxy(1,1);
		cout << "Cant save file.        													";
		WaitKey();
	}
}

void AddObject(InstPtr &act, ObjectStructure &dbase,
							 ObjectStructure &scene)
{
	char inst_name[30], shape_name[30];
	InstPtr shape;

	gotoxy(1,1);
	cout << "Name and shape of object: ";
	cin  >> inst_name >> shape_name;

	if((shape = dbase[shape_name]) != NULL){
		scene.AddObject(*shape, inst_name);
		act = scene[inst_name];

	} else{
		gotoxy(1,1);
		cout << "Shape " << shape_name << " not found                   ";
		WaitKey();
	}
}

void EditObject(InstPtr &obj, ObjectStructure &scene)
{
	char obj_name[30];
	InstPtr temp;

	gotoxy(1,1);
	cout << "Enter instance to edit: ";
	cin  >> obj_name;

	temp = scene[obj_name];
	if(temp)
		obj = temp;

	else{
		gotoxy(1,1);
		cout << "Instance " << obj_name << " not found.";
		WaitKey();
	}
}

void SetCamera(ObjectInstance &scale_cam,
							 ObjectInstance &rotate_cam,
							 ObjectInstance &translate_cam)
{
	AffineTransform cam_pos;

	gotoxy(1,1);
	cout << "Camera (s,r,t) ";
	char key = GetKey();

	switch(key){
	case 't':
	case 'T':
		translate(cam_pos);
		translate_cam.Transform(cam_pos);
		break;
	case 's':
	case 'S':
		scale(cam_pos);
		scale_cam.Transform(cam_pos);
		break;
	case 'r':
	case 'R':
		rotate(cam_pos);
		rotate_cam.Transform(cam_pos);
		break;
	default:
		cout << "Unknown camera operation.";
		WaitKey();
	}
}

void translate(AffineTransform &xf)
{
	Scalar x, y, z;

	cout << "Enter translation: ";
	cin >> x >> y >> z;
	xf.Translate(x,y,z);
}

void scale(AffineTransform &xf)
{
	Scalar x, y, z;

	cout << "Enter scaling: ";
	cin >> x >> y >> z;
	xf.Scale(x,y,z);
}

void rotate(AffineTransform &xf)
{
	Scalar x, y, z;

	cout << "Enter rotation: ";
	cin >> x >> y >> z;
	xf.Rotate(x,y,z);
}
