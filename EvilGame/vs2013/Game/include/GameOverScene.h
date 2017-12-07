#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include <UtH/UtHEngine.hpp>
#include <map>

class GameOverScene : public uth::Scene
{
	void createLayers(const std::vector<std::string>& layers);

public:
	uth::Layer& getLayer(const std::string& name);

	GameOverScene();
	~GameOverScene() override;

	bool Init() override;
	bool DeInit() override;

	void Update(float dt) override;
	void Draw(uth::RenderTarget& target, uth::RenderAttributes attributes = uth::RenderAttributes()) override;
};
#endif // !GAMEOVERSCENE_H
