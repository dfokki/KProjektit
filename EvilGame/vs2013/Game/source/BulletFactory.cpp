
#include "BulletFactory.h"
#include "Projectile.h"


using namespace uth;
using namespace pmath;

uth::GameObject* BulletFactory::CreateTorpedo(const Vec2& sourcePos, uth::GameObject* target, float damage, float speed)
{
	GameObject* go = new GameObject();
	go->AddTags({ "Bullet", "Torpedo" });
	go->AddComponent(new Sprite("Rocket.png"));
	go->AddComponent(new Projectile(target, damage, speed));
	go->transform.SetPosition(sourcePos);
	go->transform.ScaleToSize(5,15);
	return go;
}

