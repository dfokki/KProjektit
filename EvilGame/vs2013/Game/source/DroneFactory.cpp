
#include "DroneFactory.h"
#include "Drone.h"
#include "Health.h"

using namespace uth;
using namespace pmath;

GameObject* DroneFactory::CreateBasicDrone(uth::PhysicsWorld& pworld, const pmath::Vec2& position, const pmath::Vec2& lookDirection)
{ 
	static const std::string baseTexture = "BasicDrone_Base.png";
	static const std::string cannonTexture = "BasicDrone_Cannon.png";
	static const Vec2 size = { 32.0f, 32.0f };

	GameObject* base = new GameObject();
	GameObject* cannon = new GameObject();

	base->AddTags({ "Drone", "BasicDrone", "Base" });
	cannon->AddTags({ "Drone", "BasicDrone", "Cannon" });

	base->AddComponent(new Health(0, 10));
	base->AddComponent(new Sprite(uthRS.LoadTexture(baseTexture)));
	cannon->AddComponent(new Sprite(uthRS.LoadTexture(cannonTexture)));

	base->transform.SetPosition(position);
	base->transform.ScaleToSize(size);

	cannon->AddComponent(new Rigidbody(pworld, uth::COLLIDER_BALL, size));
	cannon->AddComponent(new Drone(lookDirection, 0.25f));
	base->AddChild(cannon);
	return base;
}
