
#include "UIFactory.h"
#include "Button.h"
#include "VisionCone.h"

using namespace uth;
using namespace pmath;

GameObject* UIFactory::CreateButton(const Rect& area, const std::string& texture, ButtonType type, const ButtonCallback& callback)
{
	auto go = new GameObject();
	go->AddTags({ "UI", "Text" });
	go->AddComponent(new Sprite(texture));
	go->AddComponent(new Button(type, callback));
	go->transform.SetPosition(area.position);
	go->transform.ScaleToSize(area.size);
	return go;

}

uth::GameObject* UIFactory::CreateText(const Rect& area, const std::string& font, float fontSize, const std::string& text, int origin, const Vec4& color)
{
	auto go = new GameObject();

	/* DISABLED until engine update /
	std::fprintf(stderr, "[DEPRACTED] UIFactory::CreateText is depracted, until further notice.");
	std::abort();
	/ ---------------------------- */
	go->AddTags({ "UI", "Text" });

	{
	auto c = new Text(font, fontSize);
	c->SetColor(color);
	c->SetText(text);
	go->AddComponent(c);
	}

	go->transform.SetPosition(area.position);
	go->transform.ScaleToSize(area.size);
	go->transform.SetOrigin(origin);

	/* ---------------------------- */

	return go;
}

uth::GameObject* UIFactory::CreateBuildGuide()
{
	auto go = new GameObject();
	go->AddTags({ "UI", "BuildGuide" });
	go->AddComponent(new VisionCone());
	
	{
		auto tex = new Sprite("Drone2_Bottom.png");
		tex->SetColor(1.0f, 1.0f, 1.0f, 0.5f);
		go->AddComponent(tex);
	}

	go->transform.ScaleToSize(32.0f, 32.0f);
	go->SetActive(false);
	return go;
}

GameObject* UIFactory::CreateTurretButton(const Rect& area, ButtonType type, const ButtonCallback& callback)
{
	auto go = new GameObject();
	go->AddTags({ "UI", "BuildIcon" });
	go->AddComponent(new Sprite(uthRS.LoadTexture("BlueBox.png")));
	go->AddComponent(new Sprite(uthRS.LoadTexture("BasicDrone_Base.png")));
	go->AddComponent(new Sprite(uthRS.LoadTexture("BasicDrone_Cannon.png")));

	go->AddComponent(new Button(type, callback));
	go->transform.SetPosition(area.position);
	go->transform.ScaleToSize(area.size);
	return go;
}

uth::GameObject* UIFactory::CreateGameoverScreen()
{
	auto overlay = new GameObject();
	overlay->AddTags({ "UI", "GameoverScreen", "Overlay" });
	overlay->AddComponent(new Sprite(Vec4{ 0.0f, 0.0f, 0.0f, 0.5f }, Vec2{ 1, 1 }, "Overlay"));
	overlay->transform.ScaleToSize(uthEngine.GetWindow().GetCamera().GetSize());

	auto picture = new GameObject();
	picture->AddTags({ "UI", "GameoverScreen", "Picture" });
	picture->AddComponent(new Sprite("GameOverText.png", "Picture"));
	picture->transform.ScaleToSize(0.5f, 0.2f);
	
	overlay->AddChild(picture);
	return overlay;
}
