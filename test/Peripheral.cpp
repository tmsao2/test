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

///���݂̉�����Ԃ̌��o
const bool Peripheral::IsPressing(int keyid) const
{
	return (_padState & keyid);
}

///���݂̃g���K�[��Ԃ̌��o
const bool Peripheral::IsTrigger(int keyid) const
{
	return ((_padState & keyid) & ~(_lostPadState & keyid));
}
