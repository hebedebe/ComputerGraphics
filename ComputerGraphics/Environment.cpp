#include "Environment.h"

void Environment::MarkLightingDirty()
{
	lightingDirty = true;
	printf("Marked lighting dirty\n");
}

void Environment::Update()
{
	if (lightingDirty)
	{
		lightingDirty = false;
		registeredLights = 0;
		buildLights.Emit();
		printf("Built lights\n");
	}
}
