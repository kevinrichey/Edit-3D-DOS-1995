// affine.h

#ifndef __AFFINE_H
#define __AFFINE_H

#include <math.h>
#include "vector.h"

// Affine transformation classe
class AffineTransform{

	friend ostream &operator<<(ostream &os, AffineTransform &t);
	friend istream &operator>>(istream &is, AffineTransform &t);

public:
	AffineTransform(){}
	AffineTransform(const Matrix &m);

	void Translate(Scalar x, Scalar y, Scalar z);
	void Scale(Scalar x, Scalar y, Scalar z);
	void RotateX(Scalar r);
	void RotateY(Scalar r);
	void RotateZ(Scalar r);
	void Rotate(Scalar x, Scalar y, Scalar z);
	AffineTransform operator*(const AffineTransform &t) const;

	Vector Transform(const Vector &v) const;

private:
	Matrix xform;

};

ostream &operator<<(ostream &os, AffineTransform &t);
istream &operator>>(istream &is, AffineTransform &t);

#endif
