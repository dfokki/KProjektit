
#include <UtH/UtHEngine.hpp>

struct BulletFactory
{
	static uth::GameObject* CreateTorpedo(const pmath::Vec2& sourcePos, uth::GameObject* target, float damage = 10.0f, float speed = 100.0f);
	//static uth::GameObject* CreateLaserBeam(uth::GameObject* target);
};