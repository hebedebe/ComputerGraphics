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

	const auto app = ComputerGraphicsApp::Get();

	ImGui::Begin("Profiler");
	ImGui::Text("FPS: %u", app->getFPS());
	ImGui::Text("mspt: %f", delta * 1000);
	ImGui::End();
}
