#include "PropFactory.h"
#include "Base.h"
#include "Health.h"

using namespace uth;
using namespace pmath;

uth::GameObject* PropFactory::CreateBase()
{
	GameObject* go = new GameObject();
	go->AddTags({ "Props", "Base" });
	go->AddComponent(new Health(0, 100));
	go->AddComponent(new uth::Sprite("Base.png"));
	go->AddComponent(new Base());
	go->transform.SetPosition(0,140);
	go->transform.ScaleToSize(300, 150);
	// Possibly do some scaling for the texture later, maybe, ok? ok.
	return go;
}

uth::GameObject* PropFactory::CreateBackground()
{
	GameObject* go = new GameObject();
	go->AddTags({ "Props", "Background" });
	go->AddComponent(new uth::Sprite("BackGround.png"));
	go->transform.ScaleToSize(uthEngine.GetWindow().GetCamera().GetSize());

	return go;
}


uth::GameObject* PropFactory::CreateMenuBackground()
{
	GameObject* go = new GameObject();
	go->AddTags({ "Props", "Background" });
	go->AddComponent(new uth::Sprite("Menu/BackGround.png"));
	go->transform.ScaleToSize(uthEngine.GetWindow().GetCamera().GetSize());

	return go;
}


uth::GameObject* PropFactory::CreateGameOverBackground()
{
	GameObject* go = new GameObject();
	go->AddTags({ "Props", "Background" });
	go->AddComponent(new uth::Sprite("GameOver/GameOver.png"));
	go->transform.ScaleToSize(uthEngine.GetWindow().GetCamera().GetSize());

	return go;
}

