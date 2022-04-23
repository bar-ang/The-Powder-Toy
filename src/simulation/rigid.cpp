/*
#ifndef RIGID_CPP
#define RIGID_CPP

#include "rigid.h"
#include "Config.h"

#include "Simulation.h"

void Rigid::Refresh()
{
	int rx, int ry;
	for(rx = -10; rx <= 10; rx++)
		for(ry = -10; ry <= 10; ry++){
			sim->create_part(-1, x-rx, y-ry, t)
		}
}

#endif
*/