#include "Base.h"
#include "Health.h"
#include "Util.h"
#include "IngameScene.h"
#include "UIFactory.h"

Base::Base() : Component("Base")
{

}

Base::~Base()
{

}


void Base::Init()
{

}

void Base::Update(float dt)
{
	if (parent->GetComponent<Health>()->m_Health.isMin())
	{
	/*	parent->AddComponent(uth::AnimatedSprite("explosion_1.png", 7, 66, 204))*/
		
		parent->Remove();
		uthSceneM.GoToScene(2);
		
		///*Commented for debugging purposes*/
		//auto& scene = *util::UtH::getGrandparent<IngameScene>(parent);
		//scene.getLayer("UI").AddChild(UIFactory::CreateGameoverScreen()); /**/
		
		
	}
}

void Base::Draw(uth::RenderTarget& target)
{

}

