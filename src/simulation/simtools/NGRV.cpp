#include "simulation/ToolCommon.h"

static int perform(PERFORM_FUNC_ARGS);

void SimTool::Tool_NGRV()
{
	Identifier = "DEFAULT_TOOL_NGRV";
	Name = "NGRV";
	Colour = PIXPACK(0xAACCFF);
	Description = "Creates a short-lasting negative gravity well.";
	Perform = &perform;
}

static int perform(PERFORM_FUNC_ARGS)
{
	sim->gravmap[((y/CELL)*(XRES/CELL))+(x/CELL)] = strength*-5.0f;
	return 1;
}
