#include "Paddle.h"

Paddle::Paddle(Vector2 pos, Vector2 size) :
	mPos{ pos },
	mSize{ size }
{
}

Vector2 Paddle::GetSize() const
{
	return mSize;
}

Vector2 Paddle::GetPos() const
{
	return mPos;
}

void Paddle::Update()
{
}

void Paddle::Draw() const
{
	DrawRectangle(mPos.x, mPos.y, mSize.x, mSize.y, WHITE);
}
