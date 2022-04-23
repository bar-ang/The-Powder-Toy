#include <iostream>
#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);
static bool createAllowed(ELEMENT_CREATE_ALLOWED_FUNC_ARGS);

void Element::Element_RIGD()
{
	Identifier = "DEFAULT_PT_RIGD";
	Name = "RIGD";
	Colour = PIXPACK(0x44bb00);
	MenuVisible = 1;
	MenuSection = SC_SOLIDS;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
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
	Description = "Rigid.";

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
	Create = &create;
	CreateAllowed = &createAllowed;
}

static int update(UPDATE_FUNC_ARGS)
{
	return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS)
{
	Rigid rigid(x, y, PT_RIGD);
	sim->rigids[sim->rigidcount] = rigid;
	sim->rigidcount++;
	std::cout << "rigid created " << sim->rigidcount << " rigids in existance." << std::endl;
}

static bool createAllowed(ELEMENT_CREATE_ALLOWED_FUNC_ARGS)
{
	return sim->rigidcount < MAX_RIGIDS;
}