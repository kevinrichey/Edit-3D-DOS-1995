// camera.h

#ifndef __CAMERA_H
#define __CAMERA_H

#include "viewport.h"
#include "affine.h"

struct Vertex{
	Vector cam_space;
	Scalar world_x, world_y;
	int screen_x, screen_y;
};

// Perspective Projection Camera class
class Camera{

public:
	Camera(int x1, int y1, int x2, int y2, int d=10);

	void Transform(const AffineTransform &t);
	void Zoom(Scalar z);
	void ScalePlane(Scalar x, Scalar y);
	void ShiftPlane(Scalar x, Scalar y);
	Vertex Project(const Vector &v) const;

private:
	Scalar distance;
	AffineTransform orientation;
	Viewport plane;
};

#endif
