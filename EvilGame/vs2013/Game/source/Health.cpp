
#include "Health.h"

using namespace uth;
using namespace pmath;

Health::Health()
	: Component("defaultHealth")
	, m_Health(0, 100, 100)
{
}

Health::Health(float min, float max)
	: Component("Health")
	, m_Health(min, max, max)
{
}

void Health::Init()
{
}

void Health::Draw(uth::RenderTarget& target)
{
}

void Health::Update(float delta)
{
}
