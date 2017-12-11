// struct3d.cpp

#include "struct3d.h"

ObjectStructure::ObjectStructure(const char *name):
Object3D(name),
first(NULL),
last(NULL)
{}

ObjectStructure::ObjectStructure(istream &infile,
																 ObjectStructure &dbase,
																 const char *name):
Object3D(name),
first(NULL),
last(NULL)
{
	char shape_name[30], inst_name[30];
	ObjectInstance *shape, *object;
	AffineTransform xform;

	infile >> shape_name;
	while(strcmp(shape_name, "end") != 0){
		infile >> inst_name >> xform;

		if((shape = dbase[shape_name]) != NULL){
			object = new ObjectInstance(*shape, inst_name);
			if(!first)
				first = last = object;
			else{
				last->SetNext(object);
				last = object;
			}
			object->Transform(xform);
		}
		infile >> shape_name;
	}
}

ObjectStructure::~ObjectStructure()
{
	ObjectInstance *temp, *inst = first;

	while(inst){
		temp = inst->GetNext();
		delete inst;
		inst = temp;
	}
}

const ObjectInstance *ObjectStructure::operator[](char *name) const
{
	ObjectInstance *inst = first;
	while(inst){
		if(strcmp(name, inst->Name()) == 0) break;
		inst = inst->GetNext();
	}
	return(inst);
}

ObjectInstance *ObjectStructure::operator[](char *name)
{
	ObjectInstance *inst = first;
	while(inst){
		if(strcmp(name, inst->Name()) == 0) break;
		inst = inst->GetNext();
	}
	return(inst);
}

void ObjectStructure::AddObject(Object3D *obj, char *name)
{
	ObjectInstance *node = new ObjectInstance(obj, name);

	if(!first)
		first = last = node;
	else{
		last->SetNext(node);
		last = node;
	}
}

void ObjectStructure::Render(const Camera &cam,
														 const AffineTransform &xf,
														 int flags)
{
	ObjectInstance *inst = first;

	while(inst){
		inst->Render(cam, xf, flags);
		inst = inst->GetNext();
	}
}

ostream &operator<<(ostream &os, ObjectStructure &obj)
{
	ObjectInstance *inst = obj.first;

	os << "ObjectStructure" << endl << endl;
	while(inst){
		os << *inst << endl;
		inst = inst->GetNext();
	}
	os << "end" << endl;

	return(os);
}
