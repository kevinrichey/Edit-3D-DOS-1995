// vector.cpp

#include "vector.h"

// Matrix functions

Matrix::Matrix()
{
	for(int r=0; r<NUM_ROW; r++)
		for(int c=0; c<NUM_COL; c++)
			matx[r][c] = (r==c) ? 1 : 0;
}

Matrix &Matrix::operator=(const Matrix &m)
{
	for(int r=0; r<NUM_ROW; r++)
		for(int c=0; c<NUM_COL; c++)
			matx[r][c] = m.matx[r][c];
	return(*this);
}

Matrix Matrix::operator*(const Matrix &m) const
{
	Matrix result;
	result.Clear();

	for(int r=0; r<NUM_ROW; r++){
		for(int c=0; c<NUM_COL; c++){
			result.matx[r][c] += matx[r][0] * m.matx[0][c];
			result.matx[r][c] += matx[r][1] * m.matx[1][c];
			result.matx[r][c] += matx[r][2] * m.matx[2][c];
			result.matx[r][c] += matx[r][3] * m.matx[3][c];
		}
	}

	return(result);
}

Scalar &Matrix::operator()(int r,int c)
{
	return(matx[r][c]);
}

const Scalar &Matrix::operator()(int r,int c) const
{
	return(matx[r][c]);
}

void Matrix::Clear(void)
{
	for(int r=0; r<NUM_ROW; r++)
		for(int c=0; c<NUM_COL; c++)
			matx[r][c] = 0;
}

istream &operator>>(istream &is, Matrix &m)
{
	for(int r=0; r<NUM_ROW; r++)
		for(int c=0; c<NUM_COL; c++)
			is >> m(r,c);
	return(is);
}

ostream &operator<<(ostream &os, Matrix &m)
{
	int w = os.width();

	for(int r=0; r<NUM_ROW; r++){
		for(int c=0; c<NUM_COL; c++)
			os << setw(w) << m(r,c);
		os << endl;
	}

	return(os);
}

// Vector functions

Vector::Vector(Scalar i, Scalar j, Scalar k):
x(i),
y(j),
z(k)
{}

Vector &Vector::operator=(const Vector &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return(*this);
}

Vector Vector::operator*(const Matrix &m) const
{
	return( Vector(
		(x*m(0,0)) + (y*m(1,0)) + (z*m(2,0)) + m(3,0),
		(x*m(0,1)) + (y*m(1,1)) + (z*m(2,1)) + m(3,1),
		(x*m(0,2)) + (y*m(1,2)) + (z*m(2,2)) + m(3,2)
	) );
}

Vector Vector::operator-(const Vector &v)
{
	return(Vector(x-v.x, y-v.y, z-v.z));
}

int Vector::operator*(const Vector &v)
{
	return((x*v.x) + (y*v.y) + (z*v.z));
}

Vector Vector::Cross(const Vector &v)
{
	return(Vector(  (y*v.z) - (v.y*z),
								-((x*v.z) - (v.x*z)),
									(x*v.y) - (v.x*y)) );
}

istream &operator>>(istream &is, Vector &v)
{
	is >> v.x >> v.y >> v.z;
	return(is);
}

ostream &operator<<(ostream &os, Vector &v)
{
	int w = os.width();

	os << setw(w) << v.x;
	os << setw(w) << v.y;
	os << setw(w) << v.z;

	return(os);
}

// global constants
const Vector ORIGIN(0,0,0);
