#include "simulation/ToolCommon.h"

static int perform(PERFORM_FUNC_ARGS);

void SimTool::Tool_PGRV()
{
	Identifier = "DEFAULT_TOOL_PGRV";
	Name = "PGRV";
	Colour = PIXPACK(0xCCCCFF);
	Description = "Creates a short-lasting gravity well.";
	Perform = &perform;
}

static int perform(PERFORM_FUNC_ARGS)
{
	sim->gravmap[((y/CELL)*(XRES/CELL))+(x/CELL)] = strength*5.0f;
	return 1;
}
