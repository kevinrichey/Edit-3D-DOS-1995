// object3d.h

#ifndef __OBJECT3D_H
#define __OBJECT3D_H

#include "camera.h"
#include <string.h>

extern const int CULLING_FLAG;
extern const int ALL_FLAGS;

class Object3D{

public:
	Object3D(const char *n);
	virtual ~Object3D(){}

	const char *Name(void);
	virtual void Render(const Camera &cam,
											const AffineTransform &xf,
											int flags=ALL_FLAGS) = 0;

private:
	char name[30];

};

#endif
