#include "CameraNode.h"
#include "ComputerGraphicsApp.h"
#include "LightNode.h"
#include "MeshNode.h"
#include "PostProcessNode.h"
#include "ProfilerNode.h"

class TestLoader : public Loader
{
	void OnLoad(NodeTree* tree) override
	{
		const auto mesh = tree->CreateNode<MeshNode>(Transform());
		mesh->LoadMesh("./models/soulspear/soulspear.obj", true, true);
		//a->SetMeshType(MeshNode::MeshType::OBJ);
		mesh->InitialiseStandardShader();

		auto light = tree->CreateNode<LightNode>(Transform());
		light->transform.Move({ 0,0,2 });

		const auto camera = tree->CreateNode<CameraNode>(Transform(vec3(0, 5, 10), vec3(-0.5f, 0, 0)));
		camera->SetActive(true);
		//camera->InitRenderTarget();

		const auto profiler = tree->CreateNode<ProfilerNode>();

		//const auto postProcess = tree->CreateNode<PostProcessNode>(Transform());
		//postProcess->sourceTarget = camera->renderTarget;
		//postProcess->SetEffect("./shaders/post_blur.frag");

		camera->transform.SetPosition(vec3(0, -10, -10));
		camera->transform.SetRotationDegrees(vec3(45, 0, 0));
	}
};

int main() {
	
	// allocation
	auto app = ComputerGraphicsApp::Get();

	app->startupCompleteSignal.ConnectOneshot([] (auto){Loader::StaticLoad<TestLoader>(); });

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}