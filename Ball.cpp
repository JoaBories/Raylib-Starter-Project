#include "Ball.h"

#include <iostream>

Ball::Ball(Vector2 screenSize, Vector2 screenPos, Paddle* leftPaddle, Paddle* rightPaddle) :
	mBallSize{ CONSTS::BALL::SIZE },
	mBallPos{ (float)screenSize.x / 2, (float)screenSize.y / 2 },
	mBaseSpeed{ CONSTS::BALL::SPEED },
	mBallSpeed{ CONSTS::BALL::SPEED },
	mScreenSize{ screenSize.x, screenSize.y },
	mScreenPos{ screenPos },
	mNextCollisionIsLeft{ false }
{
	mPaddles[0] = leftPaddle;
	mPaddles[1] = rightPaddle;
	mBallDirection = Utilities::Normalized({ 1, 1 });
}

bool Ball::isOnBorder(bool left) const
{
	if (mBallPos.x + mBallSize / 2 >= mScreenSize.x + mScreenPos.x && !left)
	{
		return true;
	}
	else if (mBallPos.x - mBallSize / 2 <= mScreenPos.x && left)
	{
		return true;
	}

	return false;
}

void Ball::Reset(float dir)
{
	mBallPos = { mScreenSize.x / 2, mScreenSize.y / 2 };
	mNextCollisionIsLeft = (dir == 1.0f) ? false : true ; 
	mBallSpeed = mBaseSpeed;
	mBallDirection = Utilities::Normalized({ dir, 1 });
}

void Ball::Update()
{
	//Update Pos
	mBallPos.x += mBallDirection.x * mBallSpeed;
	mBallPos.y += mBallDirection.y * mBallSpeed;

	//Y collision
	if (mBallPos.y + mBallSize / 2 >= mScreenSize.y + mScreenPos.y) mBallDirection.y = -mBallDirection.y;
	else if (mBallPos.y - mBallSize / 2 <= mScreenPos.y) mBallDirection.y = -mBallDirection.y;

	//Paddle Collision
	if (mNextCollisionIsLeft)
	{
		//Left
		if (mBallPos.x - mBallSize / 2 <= mPaddles[0]->GetPos().x + mPaddles[0]->GetSize().x && mBallPos.x + mBallSize / 2 >= mPaddles[0]->GetPos().x)
		{
			if (mBallPos.y >= mPaddles[0]->GetPos().y && mBallPos.y <= mPaddles[0]->GetPos().y + mPaddles[0]->GetSize().y)
			{
				mBallDirection.x = -mBallDirection.x;
				mBallSpeed++;
				mNextCollisionIsLeft = false;
			}
		}
	}
	else
	{
		//Right
		if (mBallPos.x + mBallSize / 2 <= mPaddles[1]->GetPos().x + mPaddles[1]->GetSize().x && mBallPos.x + mBallSize / 2 >= mPaddles[1]->GetPos().x)
		{
			if (mBallPos.y >= mPaddles[1]->GetPos().y && mBallPos.y <= mPaddles[1]->GetPos().y + mPaddles[1]->GetSize().y)
			{
				mBallDirection.x = -mBallDirection.x;
				mBallSpeed++;
				mNextCollisionIsLeft = true;
			}
		}
	}
}

void Ball::Draw() const
{
	DrawCircle(mBallPos.x, mBallPos.y, mBallSize, WHITE);
}

