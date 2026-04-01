#include "UINode.h"

#include "imgui.h"

void UiNode::Tick(const float delta)
{
	Node::Tick(delta);

	if (!visible) return;

	for (size_t i = 0; i < m_preWindow.size(); i++)
		m_preWindow[i](delta, i);

	ImGui::Begin(GetUniqueName().c_str(), &open, windowFlags);
	for (size_t i = 0; i < m_uiContents.size(); i++)
		m_uiContents[i](delta, i);
	ImGui::End();
}

void UiNode::AddContents(const ui_func& func)
{
	m_uiContents.emplace_back(func);
}

void UiNode::AddPreWindowFunction(const ui_func& func)
{
	m_preWindow.emplace_back(func);
}
