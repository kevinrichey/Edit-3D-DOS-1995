// instance.cpp

#include "instance.h"

ObjectInstance::ObjectInstance(Object3D *obj, char *n):
Object3D(n),
object(obj),
next(NULL)
{}

ObjectInstance::operator Object3D *()
{
	return(object);
}

ObjectInstance::operator const Object3D *() const
{
	return(object);
}

void ObjectInstance::Transform(const AffineTransform &xf)
{
	xform = xform * xf;
}

void ObjectInstance::Render(const Camera &cam,
														const AffineTransform &xf,
														int flags)
{
	object->Render(cam, xform * xf, flags);
}

// node operations
ObjectInstance *ObjectInstance::GetNext(void)
{
	return(next);
}

void ObjectInstance::SetNext(ObjectInstance *inst)
{
	next = inst;
}

ostream &operator<<(ostream &os, ObjectInstance &inst)
{
	os << inst.object->Name()    << endl;
	os << inst.Name() 					 << endl;
	os << setw(15) << inst.xform << endl;
	return(os);
}
