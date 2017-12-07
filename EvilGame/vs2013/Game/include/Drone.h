#ifndef DRONE_H
#define DRONE_H

#include <UtH/UtHEngine.hpp>
#include "Stat.h"

class Drone : public uth::Component
{
	uth::GameObject* m_target = nullptr;

	uth::Timer m_clock;

	Stat<float> m_Reload{ 0, 100 };
	float m_ReloadSpeed = 75.0f;
	float m_maxRange = 250.0f;
	float m_FiringAngleTolerance = 10.0f;

	float m_fieldOfView = 0.25f;
	float m_turnRate = 0.025f;
	float m_speed;

	pmath::Vec2 m_lookDirection;

public:
	Drone() = default;
	Drone(const pmath::Vec2& lookDirection, float fieldOfView);
	~Drone() = default;

	void Init() override;
	void Update(float delta) override;
	void Draw(uth::RenderTarget& target) override;

	void SetTarget(uth::GameObject& target);
	void SetDirection(pmath::Vec2 lookAt);
};

#endif
