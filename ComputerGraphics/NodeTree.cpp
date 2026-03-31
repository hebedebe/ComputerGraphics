#include "NodeTree.h"

#include "ComputerGraphicsApp.h"
#include "Node.h"


NodeTree::NodeTree() = default;

NodeTree::~NodeTree()
{
	Clear();
}

void NodeTree::Tick(const float deltaTime)
{
	const float scaledDelta = deltaTime * timeScale;

	for (const auto node : m_addQueue)
	{
		RegisterNode(node);
	}
	m_addQueue.clear();

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

	const auto app = ComputerGraphicsApp::Get();

	app->setBackgroundColour
	(
		environment.backgroundColor.r,
		environment.backgroundColor.g,
		environment.backgroundColor.b
	);
	app->clearScreen();

	if (not m_activeCamera) return;

	for (const auto node : m_nodes)
	{
		if (node->visible)
			node->Draw();
	}
}

void NodeTree::PostDraw()
{
	for (const auto node : m_postDrawNodes)
	{
		node->PostDraw();
	}
}

void NodeTree::OverwriteFromLoader(Loader& loader)
{
	Clear();
	loader.Load(this);
}

void NodeTree::Clear()
{
	for (Node*& node : m_nodes)
	{
		printf("Cleared node %s\n", node->GetUniqueName().c_str());
		delete node;
		//node = nullptr;
	}

	for (Node*& node : m_freeQueue)
	{
		printf("Cleared node %s\n", node->GetUniqueName().c_str());
		delete node;
		//node = nullptr;
	}

	m_nodes.clear();
	m_postDrawNodes.clear();
	m_preDrawNodes.clear();
	m_activeCamera = nullptr;
	m_addQueue.clear();
	m_freeQueue.clear();
}

void NodeTree::AddToFreeQueue(Node* node)
{
	m_freeQueue.emplace_back(node);
}

void NodeTree::QueueRegisterNode(Node* node)
{
	m_addQueue.emplace_back(node);
}

void NodeTree::RegisterNode(Node* node)
{
	printf("Registered node\n");
	m_nodes.emplace_back(node);
	node->SetTree(this);
	node->Ready();
}

void NodeTree::RemoveNode(Node* node)
{
	m_nodes.erase(std::ranges::find(m_nodes, node));
	RemovePreDraw(node);
	RemovePostDraw(node);
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

void NodeTree::RegisterPostDraw(Node* node)
{
	m_postDrawNodes.emplace_back(node);
}

void NodeTree::RemovePostDraw(Node* node)
{
	const auto iter = std::ranges::find(m_postDrawNodes, node);
	if (iter != m_postDrawNodes.end())
		m_postDrawNodes.erase(iter);
}
