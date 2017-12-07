
#pragma once 

#include <UtH/UtHEngine.hpp>
#include "UIFactory.h"

class VisionCone : public uth::Component
{
	float m_Angle = 25.0f;
	float m_Range = 100.0f;
public:
	VisionCone();
	VisionCone(float angle, float range);
	~VisionCone();

	void Init() override;
	void Draw(uth::RenderTarget& target) override;
	void Update(float delta) override;
};

