#include "GameStartScene.h"
#include "PropFactory.h"
#include "Button.h"
#include "UIFactory.h"

using namespace uth;
using namespace pmath;

void GameStartScene::createLayers(const std::vector<std::string>& layers)
{
	for (const auto& e : layers)
		AddChild(new uth::Layer({ "Layer", std::string(e) }, this));
};

uth::Layer& GameStartScene::getLayer(const std::string& name)
{
	const auto& layers = Children(name);

	if (layers.size() == 1)
		return *layers[0];

	if (layers.size() == 0)
	{
		std::fprintf(stderr, "Error: No such layer\n");
		std::abort();
	}

	std::fprintf(stderr, "Error: Ambiguous layer");
	std::abort();
}

GameStartScene::GameStartScene()
{
}

GameStartScene::~GameStartScene()
{
}

bool GameStartScene::Init()
{
	auto& wnd = uthEngine.GetWindow();
	auto wndSize = uthEngine.GetWindowResolution();

	const Vec2 aspectRatio = Vec2(1.0f, wndSize.y / wndSize.x);
	const float viewSize = 800.0f;

	auto& cam = wnd.GetCamera();
	cam.SetPosition(0, 0);
	cam.SetSize(aspectRatio * viewSize);

	createLayers({ "Props","UI" });

	getLayer("Props").AddChildren(
	{
		PropFactory::CreateMenuBackground()
	
	});

	getLayer("UI").AddChild(
		UIFactory::CreateButton(
		pmath::Rect(Vec2(cam.transform.GetSize().x*0.35, cam.transform.GetSize().y*-0.25), cam.GetSize() * 0.20f),
		"Buttons/Play.png",
		ButtonType::Click,
		[&](GameObject& go) -> void
	{
		uthSceneM.GoToScene(1);

	}));
	return true;
}

bool GameStartScene::DeInit()
{
	return true;
}

void GameStartScene::Update(float dt)
{

	// InputEvent type = uthInput.Common.Event();

#if defined(UTH_SYSTEM_WINDOWS)

	// Dismiss GameoverScreen
	if (uthInput.Mouse.IsButtonDown(Mouse::LEFT))
	{
	}
	
#elif defined(UTH_SYSTEM_ANDROID)


#endif // For Input

	Scene::Update(dt);
}

void GameStartScene::Draw(RenderTarget& target, RenderAttributes attributes)
{
	Scene::Draw(target, attributes);
}
