#pragma once

#include "Paddle.h"
#include "Const.h"

class Player : public Paddle
{
private:
	int mMoveSpeed;
	Vector2 mScreenSize;
	Vector2 mScreenPos;
	int mUpKey;
	int mDownKey;
	Color mColor;

public:
	Player(Vector2 pos, Vector2 size, Vector2 screenPos, Vector2 screenSize, int upKey, int downKey, Color color);

	// Inherited via IObject
	void Update() override;
	void Draw() const override;
};

