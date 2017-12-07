
#pragma once 

#include <UtH/UtHEngine.hpp>
#include "UIFactory.h"
#include "Stat.h"

class Health : public uth::Component
{
public:
	Stat<float> m_Health;

	Health();
	Health(float min, float max);
	~Health() = default;

	void Init() override;
	void Draw(uth::RenderTarget& target) override;
	void Update(float delta) override;

	void change(float value);
};

