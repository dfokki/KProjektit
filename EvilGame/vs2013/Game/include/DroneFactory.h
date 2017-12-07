
#include <UtH/UtHEngine.hpp>

struct DroneFactory
{
	static uth::GameObject* CreateBasicDrone(uth::PhysicsWorld& pworld, const pmath::Vec2& position, const pmath::Vec2& lookDirection);
};