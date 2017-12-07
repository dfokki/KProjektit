#pragma once

#include <UtH/UtHEngine.hpp>

struct EnemyFactory
{
	static uth::GameObject* CreateEnemy(uth::PhysicsWorld& pworld, const std::string& texture, const pmath::Vec2& position);
};

