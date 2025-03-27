#pragma once

#include <raylib.h>
#include "IObject.h"

class Paddle : public IObject
{
protected:
	Vector2 mPos;
	Vector2 mSize;

public:
	Paddle(Vector2 pos, Vector2 size);

	Vector2 GetSize() const;
	Vector2 GetPos() const;

	// Inherited via IObject
	void Update() override;
	void Draw() const override;
};

