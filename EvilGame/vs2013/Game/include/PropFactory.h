#pragma once

#include <UtH/UtHEngine.hpp>

struct PropFactory
{
	static uth::GameObject* CreateBase();
	static uth::GameObject* CreateBackground();
	static uth::GameObject* CreateMenuBackground();
	static uth::GameObject* CreateGameOverBackground();
};

