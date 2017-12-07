#ifndef SCENES_H
#define SCENES_H
#define UTHDefaultScene -1

// Enumeration of scenes, giving name for each scene number
enum SceneId
{
	DEFAULT = UTHDefaultScene,
	MAINMENU,
	GAME,
	GAMEOVER,
	CREDITS,
	COUNT // Keep this last, it tells how many scenes there are
};

#endif //SCENES_H

#ifdef NEWSCENEFUNC
#undef NEWSCENEFUNC

#include <IngameScene.h>
#include <GameStartScene.h>
#include <GameOverScene.h>

// Create function for a new scene, having a case for every user made scene
uth::Scene* NewSceneFunc(int SceneID)
{
	switch (SceneID)
	{
	
	case MAINMENU:	return new GameStartScene();
	case GAME:		return new IngameScene();
	case GAMEOVER:	return new GameOverScene();
	default:		return nullptr;
	}
}

#endif // NEWSCENEFUNC