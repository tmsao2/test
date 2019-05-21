#pragma once
#include "Geometry.h"
#include <vector>

class Peripheral;

enum class E_LEG_STATE {
	NORMAL,
	PUNCH,
	OCT_INK,
	SWEEP,
	DAMAGE,
	DETH,
};

struct E_Leg {
	Vector2 tip;	//先端座標
	Vector2 vel;
	std::vector<Vector2> joint;	//関節座標
	std::vector<MATRIX> mat;	//関節ごとの回転角
	const int T = 4;	//関節数
	E_LEG_STATE state;	//状態
	int angle;		//目標までの角度
};

struct Oct {
	float r;		//足の長さ
	Vector2 center;	//中心座標
	Vector2 root;	//足の根元
	std::vector<E_Leg> legs;	//足
};


class Octopus
{
private:
	int wait;
	int angle;
	int joint;
	std::vector<int> test;
	void Ik_Ccd(E_Leg& leg, Vector2 pos);
	void Fk(E_Leg& leg, Vector2 pos);
	void LegTranslate(E_Leg& leg,int idx);
	void OctInk(E_Leg& leg, Vector2 pos);
	void Sweep(E_Leg& leg, Vector2 pos);
	Oct _oct;
public:
	Octopus();
	~Octopus();
	void Update(Vector2 pos);
	void Draw();
	void Move(Oct oct, int effector, Vector2 target,int numMaxIteration);
};

