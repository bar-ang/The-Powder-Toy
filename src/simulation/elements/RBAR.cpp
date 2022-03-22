#include <iostream>
#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_RBAR()
{
	Identifier = "DEFAULT_PT_RBAR";
	Name = "RBAR";
	Colour = PIXPACK(0xCA4D6B);
	MenuVisible = 1;
	MenuSection = SC_SOLIDS;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.0f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 15;

	Weight = 100;

	DefaultProperties.temp = R_TEMP + 273.15f;
	HeatConduct = 48;
	Description = "rbar is a simple element";

	Properties = TYPE_SOLID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 371.0f;
	LowTemperatureTransition = ST;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &update;
}

//UPDATE_FUNC_ARGS Simulation* sim, int i, int x, int y, int surround_space, int nt, Particle *parts, int pmap[YRES][XRES]

static int update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	for (rx=-1; rx<2; rx++)
		for (ry=-1; ry<2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y+ry][x+rx];
				if (!r)
					continue;

				if (TYP(r) == PT_RBAR)
					continue;

				if (RNG::Ref().chance(1, 5)) {
					sim->part_change_type(i,x,y, TYP(r));
				}
			}

	return 0;
}
