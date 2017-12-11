// viewport.h

#ifndef __VIEWPORT_H
#define __VIEWPORT_H

class Viewport{

public:
	Viewport(int sx1, int sy1, int sx2, int sy2,
					 int wx1, int wy1, int wx2, int wy2);

	void  Scale(float x, float y);
	void  Shift(float x, float y);
	int   ScreenX(float wx) const;
	int   ScreenY(float wy) const;
	float WorldX(int sx) const;
	float WorldY(int sy) const;

private:
	float scale_x, scale_y;
	float Ox, Oy;	 					       // Origin
};

#endif
