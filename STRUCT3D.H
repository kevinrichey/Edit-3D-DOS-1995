// struct3d.h

#ifndef __STRUCT3D_H
#define __STRUCT3D_H

#include <string.h>
#include "instance.h"

class ObjectStructure: public Object3D{

	friend ostream &operator<<(ostream &os, ObjectStructure &obj);

public:
	ObjectStructure(const char *name);
	ObjectStructure(istream &infile, ObjectStructure &dbase,
									const char *name);
	virtual ~ObjectStructure();

	const ObjectInstance *operator[](char *name) const;
	ObjectInstance *operator[](char *name);

	void AddObject(Object3D *obj, char *name);
	virtual void Render(const Camera &cam,
											const AffineTransform &xf,
											int flags=ALL_FLAGS);

private:
	ObjectInstance *first, *last;

};

ostream &operator<<(ostream &os, ObjectStructure &obj);

#endif
