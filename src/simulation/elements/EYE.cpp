#include <iostream>
#include <cmath>
#include "common/tpt-minmax.h"
#include "simulation/ElementCommon.h"

#define _USE_MATH_DEFINES

static void create(ELEMENT_CREATE_FUNC_ARGS);
static int update(UPDATE_FUNC_ARGS);
static bool createAllowed(ELEMENT_CREATE_ALLOWED_FUNC_ARGS);

void Element::Element_EYE()
{
	Identifier = "DEFAULT_PT_EYE";
	Name = "EYE";
	Colour = PIXPACK(0xFFF1F1);
	MenuVisible = 1;
	MenuSection = SC_HUMAN;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 20;
	Explosive = 0;
	Meltable = 0;
	Hardness = 15;

	Weight = 100;

	HeatConduct = 164;
	Description = "Wood, flammable.";

	Properties = TYPE_SOLID | PROP_NEUTPENETRATE;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 873.0f;
	HighTemperatureTransition = NT;

	Update = &update;
	Create = &create;
	CreateAllowed = &createAllowed;
}

#define OPAC (0xff << 24) 


static inline float distance(int x1, int y1, int x2, int y2) {
	auto d2 = pow(x1 - x2, 2) + pow(y1 - y2, 2);
	return float(sqrt(d2));
}

static void create(ELEMENT_CREATE_FUNC_ARGS)
{
	eyest eye = {
		x,
		y,
		30,					//size
		10,					//pup_dist
		0,      			//pup_rot
		3,					//pup_size
		true,				//visible
		ID(sim->pmap[y][x]),//spawnID
		sim->NUM_PARTS-1 	//lookAt
	};
 
	sim->eyes[sim->eyecount] = eye;
	sim->parts[i].st = sim->eyes + sim->eyecount;
	sim->eyecount++;
}

static bool createAllowed(ELEMENT_CREATE_ALLOWED_FUNC_ARGS)
{
	int r;
	eyest *e;
	for (r = 0; r < sim->eyecount; r++)
	{
		e = &sim->eyes[r];
		if (distance(x, y, e->x, e->y) <= e->size)
			return false;
	}
	return true;
}

static int get_pup_x(eyest *eye)
{
	return int(eye->pup_dist * cos(eye->pup_rot));
}

static int get_pup_y(eyest *eye)
{
	return int(eye->pup_dist * sin(eye->pup_rot));
}


void pupil_look_to_point(eyest *eye, float x, float y)
{
	eye->pup_rot = M_PI + atan((eye->y - y)/(eye->x - x));
	if (eye->x < x)
		eye->pup_rot = eye->pup_rot + M_PI;
}

static void delete_eye_parts(Simulation *sim, eyest *eye) {
	while (!eye->eye_parts.empty())
	{
		int idx = eye->eye_parts.back();
		eye->eye_parts.pop_back();

		sim->kill_part(idx);
	}
}

static int update(UPDATE_FUNC_ARGS)
{
	auto eye = (eyest*)parts[i].st;
	int rx, ry;
	int res = 1;

	auto size = eye->size;
	auto pup_x = get_pup_x(eye);
	auto pup_y = get_pup_y(eye);
	auto pup_size = eye->pup_size;

	delete_eye_parts(sim, eye);
	for (rx = -size/2; rx <= size/2; rx++)
		for (ry = -size/2; ry <= size/2; ry++)
		{
			if (rx == 0 && ry == 0)
				continue;

			if ((pow(rx, 2) + pow(ry, 2) < pow(size / 2 ,2)) &&
				(pow(rx-pup_x, 2) + pow(ry-pup_y, 2) > pow(pup_size, 2)))
				{
					auto idx = sim->create_part(-1, x+rx, y+ry, PT_BONE, 0);  // TODO: eyes are not made of bone :)
					res &= idx;
					eye->eye_parts.push_back(idx);
				}
		}

	return 0;
}
