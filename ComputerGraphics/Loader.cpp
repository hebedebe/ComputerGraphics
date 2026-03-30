#include "Loader.h"

#include "ComputerGraphicsApp.h"
#include "NodeTree.h"

void Loader::Load(NodeTree* tree)
{
	if (!tree) tree = ComputerGraphicsApp::Get()->GetTree();

	OnLoad(tree);
}

void Loader::Preload()
{
	m_preloadTree = new NodeTree;
	Load(m_preloadTree);
}

void Loader::ApplyPreload(NodeTree*& target) const
{
	target = m_preloadTree;
}
