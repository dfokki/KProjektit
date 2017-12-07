
#pragma once
#include <UtH/UtHEngine.hpp>
#include <map>


class IngameScene : public uth::Scene
{
public:
	IngameScene();
	~IngameScene() override;



	bool Init() override;
	bool DeInit() override;
	void Update(float dt) override;
	void Draw(uth::RenderTarget& target, uth::RenderAttributes attributes = uth::RenderAttributes()) override;
	
	void SpawnEnemyWave(const std::string& EnemyType);
	uth::Layer& getLayer(const std::string& name);

	pmath::Vec2 startPosition = { 0, 0 };
	pmath::Vec2 endPosition = { 0, 0 };

	bool m_IsBuildModeEnabled = false;
private:
	void createLayers(const std::vector<std::string>& layers);

	int EnemyCounter = 0;
	int enemytemp = 2;
	int level = 12;
	unsigned int m_money = 500;

	size_t m_MaxDrones = 5;

	uth::PhysicsWorld m_physicsWorld;
	uth::GameObject* m_BuildGuide;
	uth::GameObject* m_MoneyText;
	uth::GameObject* m_NextWaveText;
	std::vector<uth::GameObject*> m_BuildButtons;
};
