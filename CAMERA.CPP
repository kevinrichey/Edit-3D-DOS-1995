// camera.cpp

#include "camera.h"

Camera::Camera(int x1, int y1, int x2, int y2, int d):
plane(x1, y1, x2, y2, -10, 10, 10, -10),
distance(d)
{}

void Camera::Transform(const AffineTransform &t)
{
	orientation = orientation * t;
}

void Camera::Zoom(Scalar z)
{
	distance *= z;
}

void Camera::ScalePlane(Scalar x, Scalar y)
{
	plane.Scale(x,y);
}

void Camera::ShiftPlane(Scalar x, Scalar y)
{
	plane.Shift(x,y);
}

Vertex Camera::Project(const Vector &v) const
{
	Vertex result;
	result.cam_space = orientation.Transform(v);

	result.world_x = (result.cam_space.x/result.cam_space.z) *
		distance;
	result.world_y = (result.cam_space.y/result.cam_space.z) *
		distance;

	result.screen_x = plane.ScreenX(result.world_x);
	result.screen_y = plane.ScreenY(result.world_y);

	return(result);
}
