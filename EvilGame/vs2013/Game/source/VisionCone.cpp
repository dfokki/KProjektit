
#include "VisionCone.h"

using namespace uth;
using namespace pmath;

VisionCone::VisionCone() : Component("defaultVision")
{
}

VisionCone::VisionCone(float angle, float range)
	: Component("VisionCone")
	, m_Angle(angle)
	, m_Range(range)
{
}

VisionCone::~VisionCone()
{
}

void VisionCone::Init()
{
}

void VisionCone::Draw(uth::RenderTarget& target)
{
	/*
		TODO:
			Draw a semi-transparent, gray triangle by connecting the 3 points, calculated in Update
	*/
}

void VisionCone::Update(float delta)
{
	/*
		TODO:
			Get parent transform's angle
			Calculate two points, by offsetting the angle with +/- m_Angle and m_Range
			(The third point is always at the parent transform position)
	*/
}
