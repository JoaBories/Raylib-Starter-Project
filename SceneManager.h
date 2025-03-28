#pragma once

enum class Scenes
{
	Menu,
	TwoPlayer,
	PVE,
	Score
};

class SceneManager
{
private:
	Scenes mCurrentScene;

public:
	SceneManager();

	Scenes GetCurrentScene() const;
	void SetCurrentScene(Scenes state);
};
