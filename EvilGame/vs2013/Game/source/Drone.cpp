
#include <cfloat>

#include "Drone.h"
#include "IngameScene.h"
#include "Util.h"
#include "UIFactory.h"
#include "Health.h"
#include "BulletFactory.h"


using namespace uth;
using namespace pmath;
using namespace util;

Drone::Drone(const Vec2& lookDirection, float fieldOfView)
	: Component("Drone")
	, m_fieldOfView(fieldOfView)
	, m_lookDirection(lookDirection)
{
}

void Drone::Init()
{
	auto& rbody = *static_cast<GameObject*>(parent)->GetComponent<Rigidbody>();
	rbody.SetKinematic(true);

	const float initialAngle = radiansToDegrees<float>(atan2(m_lookDirection.y, m_lookDirection.x) + (pi * 0.5f));
	rbody.SetAngle(initialAngle);
}

void Drone::Draw(RenderTarget& target)
{
}

void Drone::Update(float dt)
{
	const Vec2& from = parent->Parent()->transform.GetPosition();
	auto& rbody = *static_cast<GameObject*>(parent)->GetComponent<Rigidbody>();
	GameObject* base = parent->Parent<GameObject>();

	if (base->GetComponent<Health>()->m_Health.isMin())
	{
		parent->Remove();
	}

	m_Reload += m_ReloadSpeed * dt;

	if (m_target == nullptr) // If there is no target, look for one
	{
		auto& scene = *util::UtH::getGrandparent<IngameScene>(parent);

		for (const auto& e : scene.getLayer("Enemies").Children("Enemy"))
		{
			const auto go = static_cast<GameObject*>(e.get());
			const auto& to = go->transform.GetPosition();

			const Vec2& direction = (to - from).normalize();
			const float distance = static_cast<float>(Vec2::distance(from, to));
			const float dot = direction.dot(m_lookDirection);

			if ((distance <= m_maxRange) && (dot >= m_fieldOfView))
			{
				m_target = go;
				break;
			}
		}

		// After searching for a target, if there is none, look towards default view angle.
		if (m_target == nullptr)
		{
			const float targetAngle = radiansToDegrees<float>(atan2(m_lookDirection.y, m_lookDirection.x) + (pi * 0.5f));
			const float currentAngle = rbody.GetAngle();
			const float difference = targetAngle - currentAngle;

			rbody.SetAngle(currentAngle + difference * m_turnRate);
		}
	}

	if (m_target != nullptr) // If there is a target
	{
		const Vec2& to = m_target->transform.GetPosition();
		const Vec2& difference = (to - from);
		const Vec2& direction = (to - from).normalize();
		const float distance = static_cast<float>(difference.length());
		const float dot = direction.dot(m_lookDirection);

		if ((distance <= m_maxRange) && (dot >= m_fieldOfView)) // Is the target still within view
		{
			const float targetAngle = radiansToDegrees<float>(atan2(direction.y, direction.x) + (pi * 0.5f));
			const float currentAngle = rbody.GetAngle();
			const float difference = targetAngle - currentAngle;

			rbody.SetAngle(currentAngle + difference * m_turnRate);

			// If the weapon is reloaded, and the enemy is within firing range
			if ((m_Reload.isMax()) &&
				(difference < m_FiringAngleTolerance))
			{
				auto& scene = *util::UtH::getGrandparent<IngameScene>(parent);
				scene.getLayer("Bullets").AddChild(BulletFactory::CreateTorpedo(from, m_target, 10.0f, 100.0f));
				m_Reload.setValuePercent(0);
			}
		}
		else
		{
			m_target = nullptr;
			
		}
	}
}
	
