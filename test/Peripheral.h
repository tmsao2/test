#pragma once
//周辺機器の入力制御クラス

class Peripheral
{
	int _padState;//現在の入力状況
	int _lostPadState;//直前フレームの入力情報
public:
	Peripheral();
	~Peripheral();

	///入力情報の更新
	void Update();

	///現在の押下状態の検出
	///@param keyid 調べたいキー番号
	///@retval true 押している
	///@retval false 押していない
	const bool IsPressing(int keyid)const;

	///現在のトリガー状態の検出
	///@param keyid 調べたいキー番号
	///@retval true 押している
	///@retval false 押していない
	const bool IsTrigger(int keyid)const;
};

