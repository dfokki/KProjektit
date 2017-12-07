
#pragma once

#include <UtH/UtHEngine.hpp>

class Projectile : public uth::Component
{
public:
	Projectile(uth::GameObject* target, float damage, float speed);
	
	Projectile();
	~Projectile();
	

	void Init() override;
	void Draw(uth::RenderTarget& target) override;
	void Update(float delta) override;

	uth::GameObject* m_TargetObj = nullptr;
	pmath::Vec2 m_TargetPos;
	float m_Damage = 1.0f;
	float m_Speed = 1.0f;
};
