#include "Player.h"
#include <DxLib.h>
#include "Peripheral.h"

const float p_size = 10.0f;
const float speed = 2.0f;

Player::Player()
{
	_pos = Vector2(0, 0);
}


Player::~Player()
{
}

void Player::Draw()
{
	DxLib::DrawCircle(_pos.x, _pos.y, p_size, 0xffffff, true);
}

void Player::Update(Peripheral& p)
{
	if (p.IsPressing(PAD_INPUT_UP)) {
		_pos.y -= speed;
	}
	if (p.IsPressing(PAD_INPUT_DOWN)) {
		_pos.y += speed;
	}
	if (p.IsPressing(PAD_INPUT_LEFT)) {
		_pos.x -= speed;
	}
	if (p.IsPressing(PAD_INPUT_RIGHT)) {
		_pos.x += speed;
	}
}

const Vector2 Player::GetPos()
{
	return _pos;
}
