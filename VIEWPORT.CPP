// viewport.cpp

#include "viewport.h"

Viewport::Viewport(int sx1, int sy1, int sx2, int sy2,
									 int wx1, int wy1, int wx2, int wy2)
{
	scale_x = (sx2-sx1) / (wx2-wx1);
	scale_y = (sy2-sy1) / (wy2-wy1);
	Ox = sx1 - scale_x * wx1;
	Oy = sy1 - scale_y * wy1;
}

void Viewport::Scale(float x, float y)
{
	scale_x /= x;
	scale_y /= y;
}

void Viewport::Shift(float x, float y)
{
	Ox += (x * scale_x);
	Oy += (y * scale_y);
}

int Viewport::ScreenX(float wx) const
{
	return((int)(scale_x * wx + Ox));
}

int Viewport::ScreenY(float wy) const
{
	return((int)(scale_y * wy + Oy));
}

float Viewport::WorldX(int sx) const
{
	return((sx - Ox) / scale_x);
}

float Viewport::WorldY(int sy) const
{
	return((sy - Oy) / scale_y);
}
