// affine.cpp

#include "affine.h"

AffineTransform::AffineTransform(const Matrix &m):
xform(m)
{}

void AffineTransform::Translate(Scalar x, Scalar y, Scalar z)
{
	Matrix trans;

	trans(3,0) = x;
	trans(3,1) = y;
	trans(3,2) = z;
	xform = xform * trans;
}

void AffineTransform::Scale(Scalar x, Scalar y, Scalar z)
{
	Matrix scale;

	scale(0,0) = x;
	scale(1,1) = y;
	scale(2,2) = z;
	xform = xform * scale;
}

void AffineTransform::RotateX(Scalar r)
{
	Matrix rotx;

	rotx(1,1) = rotx(2,2) = cos(r);
	rotx(2,1) = -(rotx(1,2) = sin(r));

	xform = xform * rotx;
}

void AffineTransform::RotateY(Scalar r)
{
	Matrix roty;

	roty(0,0) = roty(2,2) = cos(r);
	roty(0,2) = -(roty(2,0) = sin(r));

	xform = xform * roty;
}

void AffineTransform::RotateZ(Scalar r)
{
	Matrix rotz;

	rotz(0,0) = rotz(1,1) = cos(r);
	rotz(1,0) = -(rotz(0,1) = sin(r));

	xform = xform * rotz;
}

void AffineTransform::Rotate(Scalar x, Scalar y, Scalar z)
{
	RotateX(x);
	RotateY(y);
	RotateZ(z);
}

AffineTransform AffineTransform::
	operator*(const AffineTransform &t) const
{
	return(AffineTransform(xform * t.xform));
}

Vector AffineTransform::Transform(const Vector &v) const
{
	return(v * xform);
}

ostream &operator<<(ostream &os, AffineTransform &t)
{
	os << t.xform;
	return(os);
}

istream &operator>>(istream &is, AffineTransform &t)
{
	is >> t.xform;
	return(is);
}
