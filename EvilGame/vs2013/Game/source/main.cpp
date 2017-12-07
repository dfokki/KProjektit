#include <UtH/uthEngine.hpp>

#define NEWSCENEFUNC
#include <Scenes.hpp>

int main()
{
	uthSceneM.registerNewSceneFunc(NewSceneFunc, SceneId::COUNT);
	uthEngine.Init();
	uthSceneM.GoToScene(0);

	while(uthEngine.Running())
	{
		uthEngine.Update();
		uthEngine.Draw();
	}

	return 0;
}