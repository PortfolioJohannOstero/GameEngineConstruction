#include "SheepRender.h"

using namespace Sheep;

Render::Render(unsigned int maxLayers)
	: mMaxLayers(maxLayers)
{

}


void Render::DisplayFPS(bool state, int x, int y)
{
	HAPI->SetShowFPS(state, x, y);
}

void Render::clearScreen(const HAPI_TColour& colour)
{

}
