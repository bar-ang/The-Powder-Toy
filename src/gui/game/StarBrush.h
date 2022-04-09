#ifndef STARBRUSH_H_
#define STARBRUSH_H_

#include <cmath>
#include "Brush.h"

class StarBrush: public Brush
{

public:
	StarBrush(ui::Point size):
		Brush(size)
	{
		SetRadius(size);
	}

	void drawTriangle(int cx, int cy, float len, bool flip = false) {
		double rx, ry;
		double sqrt3 = sqrt(3);
		bool cond;
		for(int x = 0; x < size.X; x++)
		{
			for(int y = 0; y < size.Y; y++)
			{
				rx = (double)(x - cx);
				ry = (double)(y - cy);

				if (!flip)
					cond = 6 * rx >= -sqrt3*len && 3*(rx - sqrt3*ry) <= sqrt3*len && 3*(rx + sqrt3*ry) <= sqrt3*len;
				else
					cond = 6 * rx <= sqrt3*len && 3*(rx - sqrt3*ry) >= -sqrt3*len && 3*(rx + sqrt3*ry) >= -sqrt3*len;

				if (cond)
					bitmap[x*(size.X)+y] = 255;
			}
		}
	}

	void GenerateBitmap() override
	{
		delete[] bitmap;
		bitmap = new unsigned char[size.X*size.Y];
		
		for(int x = 0; x < size.X; x++)
			for(int y = 0; y < size.Y; y++)
				bitmap[x*(size.X)+y] = 0;

		int min_size = size.X < size.Y ? size.X : size.Y;
		drawTriangle(size.X/2, size.Y/2, min_size*0.9, false);
		drawTriangle(size.X/2, size.Y/2, min_size*0.9, true);
	}
};

#endif /* STARBRUSH_H_ */
