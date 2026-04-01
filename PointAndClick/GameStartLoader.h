#pragma once

#include "PlayerNode.h"

#include "../ComputerGraphics/Loader.h"
#include "../ComputerGraphics/CameraNode.h"
#include "../ComputerGraphics/LightNode.h"
#include "../ComputerGraphics/MeshNode.h"
#include "../ComputerGraphics/UINode.h"

#include "../ComputerGraphics/ComputerGraphicsApp.h"

class GameStartLoader : public Loader
{
public:
	void OnLoad(NodeTree* tree) override
	{
		tree->environment.backgroundColor = vec3(0.25f);
		tree->environment.ambientLight = _VEC3_ONE;
		tree->environment.sunLight.diffuse = _VEC3_ONE;

		CameraNode* playerCamera = tree->CreateNode<CameraNode>();
		playerCamera->SetActive(true);

		LightNode* playerLight = tree->CreateNode<LightNode>();
		playerLight->lightData.diffuse = _RED;
		playerLight->lightData.intensity = 20.f;

		PlayerNode* player = tree->CreateNode<PlayerNode>();
		player->AddChild(playerCamera);
		player->AddChild(playerLight);

		PathNode* pathNode1 = tree->CreateNode<PathNode>();
		PathNode* pathNode2 = tree->CreateNode<PathNode>(Transform({ 0,0,-10 }));
		PathNode* pathNode3 = tree->CreateNode<PathNode>(Transform({0,0,10}));

		pathNode1->Connect(PathNode::Facing::NORTH, pathNode2);
		pathNode1->Connect(PathNode::Facing::SOUTH, pathNode3);

		player->currentPathNode = pathNode2;
		player->facing = PathNode::Facing::SOUTH;

		LightNode* yellowLight = tree->CreateNode<LightNode>();
		yellowLight->lightData.diffuse = _YELLOW;
		yellowLight->lightData.intensity = 20.f;
		yellowLight->transform.Move({ -3,-3,0 });

		LightNode* greenLight = tree->CreateNode<LightNode>();
		greenLight->lightData.diffuse = _GREEN;
		greenLight->lightData.intensity = 20.f;
		greenLight->transform.Move({ 3,-3,0 });


		MeshNode* spear1 = tree->CreateNode<MeshNode>();
		spear1->LoadMesh("./models/soulspear/soulspear.obj", true, true);
		spear1->InitialiseStandardShader();
		spear1->transform.Move({ -1,-3,0 });

		MeshNode* spear2 = tree->CreateNode<MeshNode>();
		spear2->LoadMesh("./models/soulspear/soulspear.obj", true, true);
		spear2->InitialiseStandardShader();
		spear2->transform.Move({ 1,-3,0 });

		MeshNode* bunny = tree->CreateNode<MeshNode>();
		bunny->LoadMesh("./models/bunny.obj");
		bunny->InitialiseStandardShader();
		bunny->transform.Move({ 0,0,40 });
		bunny->transform.SetScale(vec3(0.3f));

		UiNode* ui = tree->CreateNode<UiNode>();
		ui->windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;
		ui->AddPreWindowFunction([](float delta, size_t index)
		{
				const auto app = ComputerGraphicsApp::Get();
				ImGui::SetNextWindowPos({ (float)app->GetWindowWidth() / 2.f, 50 });
		});
		ui->AddContents([](float delta, size_t index)
		{
				ImGui::Text("Press ~ to debug. Arrow keys to move.");
		});

		player->transform.Move(vec3(0, 3, 0));
		pathNode1->transform.Move(vec3(0, 3, 0));
		pathNode2->transform.Move(vec3(0, 3, 0));
		pathNode3->transform.Move(vec3(0, 3, 0));
		spear1->transform.Move(vec3(0, 3, 0));
		spear2->transform.Move(vec3(0, 3, 0));
		bunny->transform.Move(vec3(0, 3, 0));
		yellowLight->transform.Move(vec3(0, 3, 0));
		greenLight->transform.Move(vec3(0, 3, 0));
	}
};
