#ifndef FRACTALTRIANGLEBRUSH_H_
#define FRACTALTRIANGLEBRUSH_H_

#include <cmath>
#include <iostream>
#include "Brush.h"

class FractalTriangleBrush: public Brush
{

public:
	FractalTriangleBrush(ui::Point size): Brush(size)
	{
		SetRadius(size);
	}

	void drawTriangle(int cx, int cy, double len, bool erase = false, bool flip = true)
	{
		double rx, ry;
		double sqrt3 = sqrt(3);
		bool cond;
		for(int x = 0; x < size.X; x++)
			for(int y = 0; y < size.Y; y++)
			{
				rx = (double)(x - cx);
				ry = (double)(y - cy);

				if (!flip)
					cond = 6 * rx >= -sqrt3*len && 3*(rx - sqrt3*ry) <= sqrt3*len && 3*(rx + sqrt3*ry) <= sqrt3*len;
				else
					cond = 6 * rx <= sqrt3*len && 3*(rx - sqrt3*ry) >= -sqrt3*len && 3*(rx + sqrt3*ry) >= -sqrt3*len;

				if (cond)
					bitmap[x*(size.X)+y] = erase ? 0 : 255;
			}
	}

	void fractallizeTriangle(int cx, int cy, double len, int num_iters=6)
	{
		if (!num_iters)
			return;

		drawTriangle(cx, cy, len/2, true, false);

		double down = sqrt(3) * len / 12;
		double lr = len / 4;

		fractallizeTriangle(cx + down, cy - lr, len/2, num_iters-1);
		fractallizeTriangle(cx + down, cy + lr, len/2, num_iters-1);
		fractallizeTriangle(cx - sqrt(3) * len /6, cy, len/2, num_iters-1);
	}

	void GenerateBitmap() override
	{
		delete[] bitmap;
		bitmap = new unsigned char[size.X*size.Y];
		
		std::fill(bitmap, bitmap + size.X*size.Y, 0);

		int min_size = size.X < size.Y ? size.X : size.Y;
		drawTriangle(size.X/2, size.Y/2, min_size, false);
		fractallizeTriangle(size.X/2, size.Y/2, min_size);
	}
};

#endif /* FRACTALTRIANGLEBRUSH_H_ */
