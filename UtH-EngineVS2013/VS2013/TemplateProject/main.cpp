#include <UtH/Engine/UtHEngine.h> //UtHEngine main.
#include <UtH/Engine/DefaultScene.hpp> //Default Scene. (Empty)

#include "TemplateScene.hpp" //Your scene header.

//Names and IDs for all scenes
enum SceneName
{
	DEFAULT = UTHDefaultScene,
	HELLO = 0,
	COUNT // Keep this last, it tells how many scenes there are
};

// Create function for a new scene, having a case for every user made scene
// Makes sure uthSceneM.GoToScene() pickes right scene with ID
void NewSceneFunc(int SceneID, uth::Scene* &CurScene)
{
	switch (SceneID)
	{
	case HELLO:
		CurScene = new TemplateScene();
		break;
	default:
		CurScene = new uth::DefaultScene();
		break;
	}
}

// Basic computer main loop.
// Android version is hidden at UtHEngine/android/jni/main.cpp
int main()
{
	uthSceneM.registerNewSceneFunc(NewSceneFunc, COUNT);

	uthEngine.Init();

	while (uthEngine.Running())
	{
		uthEngine.Update();

		uthEngine.Draw();
	}

	return 0;
}