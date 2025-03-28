#include "Player.h"

Player::Player(Vector2 pos, Vector2 size, Vector2 screenPos, Vector2 screenSize, int upKey, int downKey, Color color):
	Paddle{pos, size},
	mMoveSpeed{ CONSTS::PADDLE::SPEED },
	mScreenPos{ screenPos },
	mScreenSize{ screenSize },
	mUpKey{ upKey },
	mDownKey{ downKey },
	mColor{ color }
{
}

void Player::Update()
{	
	if (IsKeyDown(mUpKey) && mPos.y >= mScreenPos.y)
	{
		mPos.y -= mMoveSpeed;
	}
	else if (IsKeyDown(mDownKey) && mPos.y + mSize.y <= mScreenPos.y + mScreenSize.y)
	{
		mPos.y += mMoveSpeed;
	}
}

void Player::Draw() const
{
	DrawRectangle(mPos.x, mPos.y, mSize.x, mSize.y, mColor);
}
