#include "Environment.h"

void Environment::MarkLightingDirty()
{
	lightingDirty = true;
}

void Environment::Update()
{
	if (lightingDirty)
	{
		lightingDirty = false;
		registeredLights = 0;
		buildLights.Emit();
	}
}
