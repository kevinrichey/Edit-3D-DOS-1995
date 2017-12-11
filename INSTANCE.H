// instance.h

#ifndef __INSTANCE_H
#define __INSTANCE_H

#include <string.h>
#include "object3d.h"

class ObjectInstance: public Object3D{

	friend ostream &operator<<(ostream &os, ObjectInstance &inst);

public:
	ObjectInstance(Object3D *obj, char *n);

	operator Object3D *();
	operator const Object3D *() const;

	void Transform(const AffineTransform &xf);
	virtual void Render(const Camera &cam,
											const AffineTransform &xf,
											int flags=ALL_FLAGS);

	// node operations
	ObjectInstance *GetNext(void);
	void SetNext(ObjectInstance *inst);

private:
	Object3D *object;
	AffineTransform xform;
	ObjectInstance *next;

};

ostream &operator<<(ostream &os, ObjectInstance &inst);

#endif
