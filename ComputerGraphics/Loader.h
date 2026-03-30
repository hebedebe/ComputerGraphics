#pragma once

#include <concepts>

class NodeTree;

class Loader
{
public:
	virtual ~Loader() = default;

public:
	void Load(NodeTree* tree = nullptr);
	void Preload();
	void ApplyPreload(NodeTree*& target) const;

	virtual void OnLoad(NodeTree* tree) = 0;

	template<typename T>
	static void StaticLoad(NodeTree* tree = nullptr)
		requires (std::is_base_of_v<Loader, T>)
	{
		T* loader = new T;
		loader->Load(tree);
		delete loader;
	}

protected:
	NodeTree* m_preloadTree = nullptr;
};

