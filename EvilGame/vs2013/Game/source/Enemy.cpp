
#include "Enemy.h"
#include "Util.h"
#include "IngameScene.h"
#include "BulletFactory.h"
#include "Health.h"

using namespace uth;
using namespace pmath;
using namespace util;

Enemy::Enemy() : Component("Enemy")
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
}

void Enemy::Update(float dt)
{
	const Vec2& from = parent->transform.GetPosition();
	auto& rbody = *parent->GetComponent<Rigidbody>();
	
	if (parent->GetComponent<Health>()->m_Health.isMin())
	{
		parent->Remove();
	}

	m_Reload += m_ReloadSpeed * dt;

	if (!m_target)
	{
		// Component -> GameObject -> Layer -> Scene
		auto& scene = *util::UtH::getGrandparent<IngameScene>(parent);
		auto children = scene.getLayer("Props").Children("Base");
		if (children.size() > 0)
		{
			m_target = static_cast<GameObject*>(children[0].get());
		}

		float range = 
			m_target != nullptr
			? static_cast<float>(Vec2::distance(from, m_target->transform.GetPosition()))
			: FLT_MAX;

		for (const auto& e : scene.getLayer("Drones").Children("Drone"))
		{
			const auto go = static_cast<GameObject*>(e.get());
			const auto& to = go->transform.GetPosition();
			const auto newRange = static_cast<float>(Vec2::distance(from, to));

			if (range > newRange)
			{
				range = newRange;
				m_target = go;
			}
		}

		if (m_IsIdle)
		{
			m_IsIdle = false;

			const Vec2 direction(Random::next(-1.0f, 1.0f), Random::next(-1.0f, -0.5f));
			rbody.SetAngle(Math::lerp(0.0f, 25.0f, direction.y * (std::signbit(-direction.x) ? 1 : -1)));
			rbody.SetVelocity(direction * (m_speed * dt));
			

		}
	}

	if (m_target)
	{
		if (m_target->IsRemoved())
		{
			m_target = nullptr;
			m_IsIdle = true;
		}
		else
		{
			const Vec2& to = m_target->transform.GetPosition();
			const Vec2& direction = (to - from).normalize();
			const float distance = static_cast<float>(Vec2::distance(from, to));

			// Move towards the target, slow down and stop when near
			const float phase = Math::clamp((distance - m_minRange) / m_breakDist);
			const float actualSpeed = Math::lerp(0.0f, m_speed, phase);
			rbody.SetVelocity(direction * (actualSpeed * dt));
			rbody.SetAngle(Math::lerp(0.0f, 25.0f, direction.y * (std::signbit(-direction.x) ? 1 : -1)));

			// If the weapon is reloaded, and the enemy is within firing range
			if ((m_Reload.isMax()) &&
				(distance <= m_firingRange))
			{
				static size_t DEBUG_COUNTER_ENEMY_FIRE = 0u;
				DEBUG_COUNTER_ENEMY_FIRE++;

				auto& scene = *util::UtH::getGrandparent<IngameScene>(parent);
				scene.getLayer("Bullets").AddChild(BulletFactory::CreateTorpedo(from, m_target, 100.0f, 100.0f));
				m_Reload.setValuePercent(0);
			}
		}
	}

	{
		const Vec2& direction = Vec2(rbody.GetVelocity()).normalize();
		const Vec2& scale = parent->transform.GetScale();
		const float multiplier = (std::signbit(scale.x) != std::signbit(-direction.x)) ? 1 : -1;



		parent->transform.SetScale(scale.x * multiplier, scale.y);
		//
		//THIS CANT BE HERE IT BREAKS THE GAME! don't know why.
		//rbody.SetAngle(Math::lerp(0.0f, 25.0f, direction.y * (std::signbit(-direction.x) ? 1 : -1)));
	
		//
	}
}

void Enemy::Draw(RenderTarget& target)
{
	
}

void Enemy::SetTarget(uth::GameObject& target)
{
	m_target = &target;
}
