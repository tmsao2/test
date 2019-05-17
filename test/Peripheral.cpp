#include "Peripheral.h"
#include <DxLib.h>


Peripheral::Peripheral()
{
}


Peripheral::~Peripheral()
{
}

void Peripheral::Update()
{
	_lostPadState = _padState;
	_padState = DxLib::GetJoypadInputState(DX_INPUT_KEY_PAD1);
}

///現在の押下状態の検出
const bool Peripheral::IsPressing(int keyid) const
{
	return (_padState & keyid);
}

///現在のトリガー状態の検出
const bool Peripheral::IsTrigger(int keyid) const
{
	return ((_padState & keyid) & ~(_lostPadState & keyid));
}
