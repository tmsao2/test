#pragma once
//���Ӌ@��̓��͐���N���X

class Peripheral
{
	int _padState;//���݂̓��͏�
	int _lostPadState;//���O�t���[���̓��͏��
public:
	Peripheral();
	~Peripheral();

	///���͏��̍X�V
	void Update();

	///���݂̉�����Ԃ̌��o
	///@param keyid ���ׂ����L�[�ԍ�
	///@retval true �����Ă���
	///@retval false �����Ă��Ȃ�
	const bool IsPressing(int keyid)const;

	///���݂̃g���K�[��Ԃ̌��o
	///@param keyid ���ׂ����L�[�ԍ�
	///@retval true �����Ă���
	///@retval false �����Ă��Ȃ�
	const bool IsTrigger(int keyid)const;
};

