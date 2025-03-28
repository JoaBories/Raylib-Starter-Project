#pragma once

#include <raylib.h>
#include <random>
#include "IObject.h"
#include "Utilities.h"
#include "Paddle.h"
#include "Const.h"

using Util::Utilities;

class Ball : public IObject
{
private :
	float mBallSize;
	Vector2 mBallPos;
	Vector2 mBallDirection;
	float mBallSpeed;
	float mBaseSpeed;
	Vector2 mScreenSize;
	Vector2 mScreenPos;
	Paddle* mPaddles[2];
	bool mNextCollisionIsLeft;

public:
	Ball(Vector2 screenSize, Vector2 screenPos, Paddle* leftPaddle, Paddle* rightPaddle);
	bool isOnBorder(bool left) const;
	void Reset(float dir);

	// Inherited via IObject
	void Update() override;
	void Draw() const override;

};

