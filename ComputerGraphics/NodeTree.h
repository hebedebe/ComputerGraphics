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
	void PostDraw();

public:
	void AddToFreeQueue(Node* node);
	void QueueRegisterNode(Node* node);
	
	void RegisterNode(Node* node);
	void RemoveNode(Node* node);

	void RegisterPreDraw(Node* node);
	void RemovePreDraw(Node* node);

	void RegisterPostDraw(Node* node);
	void RemovePostDraw(Node* node);

public:
	void SetActiveCamera(CameraNode* camera) { m_activeCamera = camera; }
	CameraNode* GetActiveCamera() const { return m_activeCamera; }

public:
	Environment environment;

	float timeScale = 1.f;

protected:
	std::vector<Node*> m_nodes; // List of nodes in the scene
	std::vector<Node*> m_preDrawNodes; // Execute between tick and draw (for objects like the camera which need to update the app's projection matrix)
	std::vector<Node*> m_postDrawNodes; 
	std::vector<Node*> m_freeQueue;
	std::vector<Node*> m_addQueue;

protected:
	CameraNode* m_activeCamera = nullptr;
};

