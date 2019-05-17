#pragma once
#include "Geometry.h"

class Peripheral;

class Player
{
private:
	Vector2 _pos;
public:
	Player();
	~Player();
	void Draw();
	void Update(Peripheral& p);
	const Vector2 GetPos();
};

