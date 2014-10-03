#ifndef SCENES_H
#define SCENES_H

// Enumeration of scenes, giving name for each scene number
enum SceneName
{
	DEFAULT = -1,
	HELLO = 0,
	COUNT // Keep this last, it tells how many scenes there are
};

#endif //SCENES_H

#ifdef NEWSCENEFUNC
#undef NEWSCENEFUNC

#include <TemplateScene.hpp>

// Create function for a new scene, having a case for every user made scene
uth::Scene* NewSceneFunc(int SceneID)
{
	switch (SceneID)
	{
	case HELLO:		return new TemplateScene();
	default:		return nullptr;
	}
}

#endif // NEWSCENEFUNC