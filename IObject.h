#pragma once
class IObject
{
public:
	virtual ~IObject() {};

	virtual void Update() = 0 {};
	virtual void Draw() const = 0;
};

