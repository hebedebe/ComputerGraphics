#pragma once

#include "imgui.h"
#include "LoadingSceneLoader.h"

#include "../ComputerGraphics/CameraNode.h"
#include "../ComputerGraphics/ComputerGraphicsApp.h"
#include "../ComputerGraphics/Loader.h"
#include "../ComputerGraphics/MeshNode.h"
#include "../ComputerGraphics/NodeTree.h"
#include "../ComputerGraphics/ProfilerNode.h"
#include "../ComputerGraphics/UINode.h"

class MainMenu : public Loader
{
public:
	void OnLoad(NodeTree* tree) override
	{
		tree->environment.backgroundColor = vec3(0, 0, 1);

		CameraNode* camera = tree->CreateNode<CameraNode>();
		camera->SetActive(true);

		MeshNode* backgroundMesh = tree->CreateNode<MeshNode>();
		backgroundMesh->GetMesh<Mesh>().InitialiseFullscreenQuad();
		backgroundMesh->SetMeshType(MeshNode::MeshType::PRIMITIVE);
		backgroundMesh->LoadShader(aie::VERTEX, "./shaders/post.vert");
		backgroundMesh->LoadShader(aie::FRAGMENT, "./shaders/main_menu_background.frag");
		backgroundMesh->LinkShader();
		backgroundMesh->SetBindFunction([](aie::ShaderProgram& program, MeshNode* meshNode)
		{
			const auto app = ComputerGraphicsApp::Get();

			program.bindUniform("Time", app->GetTime());
		});


		UiNode* ui = tree->CreateNode<UiNode>();
		ui->name = "Main Menu";
		ui->windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;
		ui->AddPreWindowFunction([](float delta, size_t id)
		{
				ImGui::SetNextWindowPosCenter();
		});
		ui->AddContents([tree](float delta, size_t id)
		{
			if (ImGui::Button("Play"))
			{
				Loader::StaticLoadOverride<LoadingSceneLoader>(tree);
			}
			
			if (ImGui::Button("Quit"))
			{
				ComputerGraphicsApp::Get()->Quit();
			}
		});

		ui->transform.dirtied.Connect(ui, [] {printf("ui node moved"); });

		tree->CreateNode<ProfilerNode>();
	}
};
