#pragma once

#include <vector>
#include "Environment.h"

class CameraNode;
class Node;

class NodeTree
{
	friend class ComputerGraphicsApp;

public:
	NodeTree();
	~NodeTree();

public:
	void Tick(float deltaTime);
	void PreDraw();
	void Draw() const;

public:
	void AddToFreeQueue(Node* node);
	void RegisterNode(Node* node);
	void RemoveNode(Node* node);
	void RegisterPreDraw(Node* node);
	void RemovePreDraw(Node* node);

public:
	void SetActiveCamera(CameraNode* camera) { m_activeCamera = camera; }
	CameraNode* GetActiveCamera() const { return m_activeCamera; }

public:
	Environment environment;

	float timeScale = 1.f;

protected:
	std::vector<Node*> m_nodes; // List of nodes in the scene
	std::vector<Node*> m_preDrawNodes; // Execute between tick and draw (for objects like the camera which need to update the app's projection matrix)
	std::vector<Node*> m_freeQueue;

protected:
	CameraNode* m_activeCamera;
};

