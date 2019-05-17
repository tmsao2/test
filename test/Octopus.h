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
	Vector2 tip;	//��[���W
	std::vector<Vector2> joint;	//�֐ߍ��W
	const int T = 12;	//�֐ߐ�
	E_LEG_STATE state;	//���
	int angle;		//�ڕW�܂ł̊p�x
};

struct Oct {
	float r;		//���̒���
	Vector2 center;	//���S���W
	Vector2 root;	//���̍���
	std::vector<E_Leg> legs;	//��
};


class Octopus
{
private:
	int wait;
	int angle;
	int joint;
	void Ik_Ccd(E_Leg& leg, Vector2 pos);
	void Fk(E_Leg& leg, Vector2 pos);
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

