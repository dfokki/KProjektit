#include "EnemyFactory.h"
#include "Enemy.h"
#include "Health.h"

using namespace uth;
using namespace pmath;
using namespace std;

GameObject* EnemyFactory::CreateEnemy(uth::PhysicsWorld& pworld, const std::string& texture, const pmath::Vec2& position)
{
	auto go = new GameObject();
	go->AddTags({ "Enemy", /* "BasicEnemy" */ });
	go->AddComponent(new uth::Sprite(texture));
	go->transform.SetPosition(position);

	auto size = uthRS.LoadTexture(texture)->GetSize()/6;

	go->transform.ScaleToSize(size);

	go->AddComponent(new Health(0, 30));
	go->AddComponent(new uth::Rigidbody(pworld, uth::COLLIDER_BOX, size));
	go->AddComponent(new Enemy());
	return go;
}