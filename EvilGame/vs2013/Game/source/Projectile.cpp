
#include "Projectile.h"
#include "Health.h"

using namespace pmath;
using namespace uth;

Projectile::Projectile(GameObject* target, float damage, float speed)
	: Component("Projectile")
	, m_TargetObj(target)
	, m_Damage(damage)
	, m_Speed(speed)
{
	m_TargetPos = target->transform.GetPosition();
}



Projectile::~Projectile()
{
}

void Projectile::Init()
{
}

void Projectile::Draw(uth::RenderTarget& target)
{
}

void Projectile::Update(float delta)
{
	if (m_TargetObj != nullptr)
	{
		if (m_TargetObj->IsRemoved())
			m_TargetObj = nullptr;
		else
			m_TargetPos = m_TargetObj->transform.GetPosition();
	}

	const Vec2& from = parent->transform.GetPosition();
	const Vec2& to = m_TargetPos;
	const Vec2 difference(to - from);
	const Vec2 direction = difference.unitVector();
	const float distance = static_cast<float>(difference.length());
	const float minDistance = static_cast<float>(parent->transform.GetSize().length()) / 2.0f;

	if (distance <= minDistance)
	{
		if (m_TargetObj)
		{
			m_TargetObj->GetComponent<Health>()->m_Health -= m_Damage;
			
			if (m_TargetObj->GetComponent<Health>()->m_Health.isMin())
			{
				m_TargetObj->Remove();
				m_TargetObj = nullptr;
			}
		}
				parent->Remove();
	}

	else
	{
		const Vec2 direction = (to - from).normalize();
		const float angle = radiansToDegrees<float>(atan2(direction.y, direction.x) + (pi * 0.5f));

		parent->transform.SetRotation(angle);
		parent->transform.SetPosition(from + direction * (m_Speed * delta));
	}
}
