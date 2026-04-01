#pragma once

#include "../ComputerGraphics/Loader.h"

#include "../ComputerGraphics/UINode.h"

class LoadingSceneLoader : public Loader
{
public:
	void OnLoad(NodeTree* tree) override
	{
		UiNode* ui = tree->CreateNode<UiNode>();
		ui->windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;
		ui->AddPreWindowFunction([](float delta, size_t index)
			{
				ImGui::SetNextWindowPosCenter();
				ImGui::SetNextWindowSize({ 100,25 });
			});
		ui->AddContents([tree](float delta, size_t index)
			{
				ImGui::Text("Loading...");
				static int framesPassed = 0;
				framesPassed++;
				if (framesPassed > 1)
					Loader::StaticLoadOverride<GameStartLoader>(tree);
			});
	}
};