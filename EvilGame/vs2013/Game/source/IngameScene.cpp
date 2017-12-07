#include "IngameScene.h"
#include "UIFactory.h"
#include "EnemyFactory.h"
#include "DroneFactory.h"
#include "Drone.h"
#include "Enemy.h"
#include "PropFactory.h"
#include "Base.h"
#include "Button.h"
#include "Util.h"

#include <sstream>

using namespace uth;
using namespace pmath;


void IngameScene::createLayers(const std::vector<std::string>& layers)
{
	for (const auto& e : layers)
		AddChild(new uth::Layer({ "Layer", std::string(e) }, this));
};

uth::Layer& IngameScene::getLayer(const std::string& name)
{
	const auto& layers = Children(name);

	if (layers.size() == 1)
		return *layers[0];

	if (layers.size() == 0)
	{
		std::fprintf(stderr, "Error: No such layer\n");
		std::abort();
	}

	std::fprintf(stderr, "Error: Ambiguous layer");
	std::abort();
}

IngameScene::IngameScene()
	: m_physicsWorld(0, 0)
{
}

IngameScene::~IngameScene()
{
}

bool IngameScene::Init()
{
	auto& wnd = uthEngine.GetWindow();
	auto wndSize = uthEngine.GetWindowResolution();

	const Vec2 aspectRatio = Vec2(1.0f, wndSize.y / wndSize.x);
	const float viewSize = 800.0f;

	auto& cam = wnd.GetCamera();
	cam.SetPosition(0, 0);
	cam.SetSize(aspectRatio * viewSize);

	std::stringstream ss;
	ss << "Camera: " << cam.GetPosition() << ", " << cam.GetSize() << std::endl;
	WriteLog(ss.str().c_str());

	createLayers({ "Props", "Enemies", "Drones", "Bullets", "UI" });

	getLayer("Props").AddChildren(
	{
		(uth::Object*) // <- Using explicit overload
		PropFactory::CreateBackground(),
		PropFactory::CreateBase(),
	});

	/**/
	getLayer("Enemies").AddChildren(
	{
	(uth::Object*) // <- Using explicit overload
	EnemyFactory::CreateEnemy(m_physicsWorld, "Submarine2.png", { -450, -175 }),
	EnemyFactory::CreateEnemy(m_physicsWorld, "Submarine2.png", { 450, -175 }),
	});
	/**/

	getLayer("UI").AddChildren(
	{
		m_BuildGuide = UIFactory::CreateBuildGuide(),

	});

	getLayer("UI").AddChildren(
	{
		m_MoneyText = UIFactory::CreateText(pmath::Rect(Vec2(cam.transform.GetSize().x*-0.3, cam.transform.GetSize().y*0.4), cam.GetSize() * 0.10f), "kenpixel.ttf", 50.0f, std::to_string(m_money)),
	});

	

	getLayer("UI").AddChildren(
	{
		
		m_NextWaveText = UIFactory::CreateText(pmath::Rect(Vec2(cam.transform.GetSize().x, cam.transform.GetSize().y*0), cam.GetSize() * 0.5f ), "kenpixel.ttf", 70.0f, "Next Wave Incoming!"),
		
	});

	m_NextWaveText->SetActive(false);

	getLayer("UI").AddChild(
		UIFactory::CreateButton(
		pmath::Rect(Vec2(cam.transform.GetSize().x*-0.4, cam.transform.GetSize().y*0.4), cam.GetSize() * 0.10f),
		"Buttons/Coin_Single.png",
		ButtonType::Toggle,
		[&](GameObject& go) -> void
	{
		uthSceneM.GoToScene(0,false);
	}));





	//--------Turret Buttons---------//

	for (size_t i = 0; i < 1; i++)
	{
		const Rect rect
		(
			cam.GetSize().x * (0.4f + i * 0.06f),
			cam.GetSize().y * 0.4f,
			cam.GetSize().x * 0.1f,
			cam.GetSize().y * 0.1f
		);

		m_BuildButtons.push_back(
			getLayer("UI").AddChild(
			UIFactory::CreateTurretButton(rect, ButtonType::Click,
			[&](GameObject& goBtnEvent) -> void
		{
			auto cBtn = goBtnEvent.GetComponent<Button>();

			if (!cBtn->isPressed())
			m_IsBuildModeEnabled = true;

		})).get());
	}
	//--------Turret Buttons end---------//
	
	return true;
}

bool IngameScene::DeInit()
{
	return true;
}

void IngameScene::Update(float dt)
{

	m_MoneyText->GetComponent<Text>()->SetText((std::to_string(m_money)+"$"));
	/**

	/**/

	// InputEvent type = uthInput.Common.Event();
	//

#if defined(UTH_SYSTEM_WINDOWS)

	const Window& wnd = uthEngine.GetWindow();
	const Vec2& mousePos = wnd.PixelToCoords(uthInput.Mouse.Position());
	int enemieskilled = EnemyCounter - enemytemp;
	EnemyCounter = getLayer("Enemies").Children("Enemy").size();


	if ( EnemyCounter == 0)
	{
		m_NextWaveText->SetActive(true);

		SpawnEnemyWave("BasicEnemy");		
	}

	static bool isInitialized = false;

	if (m_IsBuildModeEnabled)
	{
		if (uthInput.Mouse.IsButtonDown(Mouse::LEFT))
		{
			if (!isInitialized)
			{
				startPosition = mousePos;
				isInitialized = true;
				m_BuildGuide->transform.SetPosition(startPosition);
			}

			endPosition = mousePos;
		}
		else
		{
			if (isInitialized && (startPosition != endPosition))
			{
				
				if ( m_money >= 100)
				{
					m_money -= 100;
					getLayer("Drones").AddChild(DroneFactory::CreateBasicDrone(
						m_physicsWorld, startPosition, (endPosition - startPosition).normalize()));
					m_IsBuildModeEnabled = false;
					m_NextWaveText->SetActive(false);
				}
			}
		}
	}
	else
	{
		isInitialized = false;
	}

	m_BuildGuide->SetActive(m_IsBuildModeEnabled && isInitialized);

	
	
	
#elif defined(UTH_SYSTEM_ANDROID)
	
	const Window& wnd = uthEngine.GetWindow();
	const Vec2& touchPos = wnd.PixelToCoords(uthInput.Touch[0].GetPosition());

	bool isInitialized = false;

	if (m_IsBuildModeEnabled)
	{
		if (uthInput.Touch[0].Motion())
		{
			if (!isInitialized)
			{
				startPosition = touchPos;
				isInitialized = true;
				m_BuildGuide->transform.SetPosition(startPosition);
			}

			endPosition = touchPos;
		}
		else
		{
			if (isInitialized && (startPosition != endPosition))
			{
				
					const size_t droneCount = getLayer("Drones").Children().size();

				if (droneCount < m_MaxDrones && m_money >= 100)
				{
					m_money -= 100;
					getLayer("Drones").AddChild(DroneFactory::CreateBasicDrone(
						m_physicsWorld, startPosition, (endPosition - startPosition).normalize()));
					m_IsBuildModeEnabled = false;
				}
			}
		}
	}
	else
	{
		isInitialized = false;
	}

#endif // For Input

	m_physicsWorld.Update(dt);
	Scene::Update(dt);
}

void IngameScene::Draw(RenderTarget& target, RenderAttributes attributes)
{
	Scene::Draw(target, attributes);
}

void IngameScene::SpawnEnemyWave(const std::string& EnemyType)
{
	level++;
	m_NextWaveText->SetActive(true);
	m_money += 500 * level * 0.1;
	if (EnemyType == "BasicEnemy")
		for (int i = 0;i < level; i++)
		{

		int PosX = uth::Randomizer::GetInt(-500, 500);
		int PosY = uth::Randomizer::GetInt(-1000, -400);
		Vec2 Pos(PosX, PosY);

		getLayer("Enemies").AddChildren(
	{ 


	EnemyFactory::CreateEnemy(m_physicsWorld, "Submarine2.png", { Pos }),
	

	});
		}
	
		return;
		}