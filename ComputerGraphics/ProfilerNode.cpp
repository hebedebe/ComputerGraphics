#include "ProfilerNode.h"

#include "ComputerGraphicsApp.h"
#include "imgui.h"

ProfilerNode::ProfilerNode()
	:Node(Transform(), nullptr, "profiler")
{
}

void ProfilerNode::Tick(float delta)
{
	Node::Tick(delta);

	_IF_NOT_DEBUG return;

	const auto app = ComputerGraphicsApp::Get();

	ImGui::Begin("Profiler");
	ImGui::Text("FPS: %u", app->GetFps());
	ImGui::Text("mspt: %f", delta * 1000);
	ImGui::End();
}
