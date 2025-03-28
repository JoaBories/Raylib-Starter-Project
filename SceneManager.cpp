#include "SceneManager.h"

SceneManager::SceneManager()
{
	mCurrentScene = Scenes::Menu;
}

Scenes SceneManager::GetCurrentScene() const
{
	return mCurrentScene;
}

void SceneManager::SetCurrentScene(Scenes state)
{
	mCurrentScene = state;
}
