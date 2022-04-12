#ifndef MENDELBRUSH_H_
#define MENDELBRUSH_H_

#include <cmath>
#include <iostream>
#include "Brush.h"

class MendelBrush: public Brush
{

public:
	MendelBrush(ui::Point size):
		Brush(size)
	{
		SetRadius(size);
	}

	int mendelbrot(double c_x, double c_y, int max_iter = 15)
	{
		double x = 0;
		double y = 0;
		double tx, ty;
		for (int i = 0; i < max_iter; i++)
		{
			if (x*x + y*y > 4)
				return i;

			tx = x*x - y*y + c_x;
			ty = 2*x*y + c_y;
			x = tx;
			y = ty;
		}

		return -1;
	}

	void GenerateBitmap() override
	{
		double rx, ry;
		delete[] bitmap;
		bitmap = new unsigned char[size.X*size.Y];
		
		for(int x = 0; x < size.X; x++)
		{
			for(int y = 0; y < size.Y; y++)
			{
				rx = (double)(x - size.X/2);
				ry = (double)(y - size.Y/2);

				rx *= 3/(double)size.Y;
				ry *= 3/(double)size.X;

				int explode = mendelbrot(rx, ry);
				if (explode < 0)
					bitmap[y*(size.X)+x] = 255;
				else
					bitmap[y*(size.X)+x] = 0;
			}
		}
	}
};

#endif /* MENDELBRUSH_H_ */
