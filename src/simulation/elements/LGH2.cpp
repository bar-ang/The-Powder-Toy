#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

#define COLOR 0xFCFFC4

void Element::Element_LGH2()
{
	Identifier = "DEFAULT_PT_LGH2";
	Name = "LGH2";
	Colour = PIXPACK(COLOR);
	MenuVisible = 1;
	MenuSection = SC_TOOL;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 30;

	DefaultProperties.temp = R_TEMP - 2.0f + 273.15f;
	HeatConduct = 29;
	Description = "Light. Lighten close particles";

	Properties = TYPE_LIQUID|PROP_CONDUCTS|PROP_LIFE_DEC|PROP_NEUTPASS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 273.15f;
	LowTemperatureTransition = NT;
	HighTemperature = 373.0f;
	HighTemperatureTransition = NT;

	Update = &update;
}

static inline int lighen(int x)
{
	return x << 24;
}

static int update(UPDATE_FUNC_ARGS)
{
	
	return 0;
}
