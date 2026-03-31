#pragma once

#include "Loader.h"
#include "NodeTree.h"
#include "ParticleSystemNode.h"
#include "CameraNode.h"

class TestLoader : public Loader
{
	void OnLoad(NodeTree* tree) override
	{
		const auto camera = tree->CreateNode<CameraNode>();
		camera->SetActive(true);

		const auto particleSystem = tree->CreateNode<ParticleSystemNode>();
		particleSystem->emitter.Initialise(1000, 500, 0.1f, 1.0f, 1, 5,
			1, 0.1f, vec4(1, 0, 0, 1), vec4(1, 1, 0, 1));
	}
};
