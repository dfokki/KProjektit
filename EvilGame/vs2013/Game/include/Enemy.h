
#ifndef ENEMY_H
#define ENEMY_H

#include <UtH/UtHEngine.hpp>
#include "Stat.h"

class Enemy : public uth::Component
{
	uth::GameObject* m_target = nullptr;
	Stat<float> m_Reload{ 0, 100 };
	float m_ReloadSpeed = 10.0f;
	float m_firingRange = 180.0f;
	float m_minRange = 150.0f;
	float m_speed = 100.00f;
	float m_breakDist = 1.0f;
	bool m_IsIdle = false;
public:
	Enemy();
	~Enemy();

	void Init() override;
	void Update(float dt) override;
	void Draw(uth::RenderTarget& target) override;

	void SetTarget(uth::GameObject& target);
};

#endif
