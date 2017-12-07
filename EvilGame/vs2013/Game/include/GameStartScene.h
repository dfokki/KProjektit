#ifndef GAMESTARTSCENE_H
#define GAMESTARTSCENE_H

#include <UtH/UtHEngine.hpp>
#include <map>

class GameStartScene : public uth::Scene
{
	void createLayers(const std::vector<std::string>& layers);

public:
	uth::Layer& getLayer(const std::string& name);

	GameStartScene();
	~GameStartScene() override;

	bool Init() override;
	bool DeInit() override;

	void Update(float dt) override;
	void Draw(uth::RenderTarget& target, uth::RenderAttributes attributes = uth::RenderAttributes()) override;
};
#endif // !GAMESTARTSCENE_H
