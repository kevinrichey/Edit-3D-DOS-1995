// vector.h

#ifndef __VECTOR_H
#define __VECTOR_H

#include <iostream.h>
#include <iomanip.h>

typedef float Scalar;

#define NUM_ROW 4
#define NUM_COL 4

// 4x4 Matrix class
class Matrix{

public:
	Matrix();
	Matrix &operator=(const Matrix &m);
	Matrix operator*(const Matrix &m) const;
	Scalar &operator()(int r,int c);
	const Scalar &operator()(int r,int c) const;
	void Clear(void);

private:
	Scalar matx[NUM_ROW][NUM_COL];
};

istream &operator>>(istream &is, Matrix &m);
ostream &operator<<(ostream &os, Matrix &m);

//  vector class
class Vector{

public:
	Vector(Scalar x=0, Scalar y=0, Scalar z=0);
	Vector &operator=(const Vector &v);
	Vector operator*(const Matrix &m) const;

	Vector operator-(const Vector &v);
	int operator*(const Vector &v);
	Vector Cross(const Vector &v);

	Scalar x,y,z;
};

istream &operator>>(istream &is, Vector &v);
ostream &operator<<(ostream &os, Vector &v);

// global constants
extern const Vector ORIGIN;

#endif
