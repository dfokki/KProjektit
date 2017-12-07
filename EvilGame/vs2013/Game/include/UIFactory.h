
#ifndef UIFACTORY_H
#define UIFACTORY_H 

#include <UtH/UtHEngine.hpp>
#include "Button.h"

struct UIFactory
{

	static uth::GameObject* CreateButton(const pmath::Rect& area, const std::string& texture, ButtonType type, const ButtonCallback& callback);
	static uth::GameObject* CreateTurretButton(const pmath::Rect& area, ButtonType type, const ButtonCallback& callback);
	static uth::GameObject* CreateText(const pmath::Rect& area, const std::string& font, float fontSize, const std::string& text, int origin = uth::Origin::Center, const pmath::Vec4& color = pmath::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	static uth::GameObject* CreateBuildGuide();
	static uth::GameObject* CreateGameoverScreen();
};

#endif // !UIFACTORY_H
