#include "NodeTree.h"

#include "Node.h"


NodeTree::NodeTree() = default;

NodeTree::~NodeTree()
{
	for (int i = 0; i < m_nodes.size(); i++)
	{
		m_nodes[i]->Free();
	}
}

void NodeTree::Tick(const float deltaTime)
{
	const float scaledDelta = deltaTime * timeScale;

	for (const auto node : m_nodes)
	{
		node->Tick(scaledDelta);
	}

	for (const auto node : m_freeQueue)
	{
		node->Free();
	}
	m_freeQueue.clear();
}

void NodeTree::PreDraw()
{
	environment.Update();

	for (const auto node : m_preDrawNodes)
	{
		node->PreDraw();
	}
}

void NodeTree::Draw() const
{
	for (const auto node : m_nodes)
	{
		if (node->visible)
			node->Draw();
	}
}

void NodeTree::AddToFreeQueue(Node* node)
{
	m_freeQueue.emplace_back(node);
}

void NodeTree::RegisterNode(Node* node)
{
	m_nodes.emplace_back(node);
	node->SetTree(this);
}

void NodeTree::RemoveNode(Node* node)
{
	m_nodes.erase(std::ranges::find(m_nodes, node));
}

void NodeTree::RegisterPreDraw(Node* node)
{
	m_preDrawNodes.emplace_back(node);
}

void NodeTree::RemovePreDraw(Node* node)
{
	const auto iter = std::ranges::find(m_preDrawNodes, node);
	if (iter != m_preDrawNodes.end())
		m_preDrawNodes.erase(iter);

}