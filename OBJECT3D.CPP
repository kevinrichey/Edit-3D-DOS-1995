// object3d.cpp

#include "object3d.h"

const int CULLING_FLAG = 1;
const int ALL_FLAGS = CULLING_FLAG;

Object3D::Object3D(const char *n)
{
	strcpy(name, n);
}

const char *Object3D::Name(void)
{
	return(name);
}
