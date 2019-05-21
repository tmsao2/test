#include "Octopus.h"
#include <DxLib.h>
#include <math.h>
#include <random>

const int length = 30;
const int limit = 0;
const int nodeSize = 6;
const int width = 20;

#define LEG(x) _oct.legs[x]


void Octopus::Ik_Ccd(E_Leg & leg, Vector2 pos)
{
	for (int it = 0; it < 6; ++it) {
		for (int j = leg.T; j > 0; --j) {
			auto p_vec = pos - leg.joint[j - 1];		//目標→関節
			auto t_vec = leg.tip - leg.joint[j - 1];		//先端→関節
			auto mat = MGetTranslate((-leg.joint[j - 1]).V_Cast());			//原点まで移動
			mat = MMult(mat, MGetRotVec2(t_vec.V_Cast(), p_vec.V_Cast()));	//回転
			mat = MMult(mat, MGetTranslate(leg.joint[j - 1].V_Cast()));		//元の位置に移動
			for (int itr = j; itr < leg.T; ++itr) {
				leg.joint[itr] = VTransform(leg.joint[itr].V_Cast(), mat);
			}
			leg.tip = leg.joint[leg.T-1];
		}
	}
}

void Octopus::Fk(E_Leg & leg, Vector2 pos)
{
	for (int nj = leg.T - 1; nj >= 1; --nj) {
		leg.mat[nj] = leg.mat[nj-1];
		test[nj] = test[nj-1];
	}
	for (int j = 1; j < joint; ++j) {
		auto mat = MGetTranslate((-leg.joint[j-1]).V_Cast());
		mat = MMult(mat, leg.mat[j]);
		mat = MMult(mat, MGetTranslate(leg.joint[j-1].V_Cast()));
		leg.joint[j] = VTransform(leg.joint[j].V_Cast(), mat);
		
		LegTranslate(leg, j);
	}
}

void Octopus::LegTranslate(E_Leg & leg,int idx)
{
	for (int j = idx; j < leg.T-1; ++j) {
		auto vec = leg.joint[j + 1] - leg.joint[j];
		if (vec.Magnitude() > (_oct.r / leg.T) + 0.1f||(vec.Magnitude() < (_oct.r / leg.T) - 0.1f)) {
			leg.joint[j + 1] = leg.joint[j] + vec.Normalized()*(_oct.r / leg.T);
		}
	}
}

void Octopus::OctInk(E_Leg & leg, Vector2 pos)
{
}

void Octopus::Sweep(E_Leg & leg, Vector2 pos)
{
}

Octopus::Octopus()
{
	_oct.center = Vector2(512, 256);
	_oct.root = _oct.center + Vector2(-20,0);
	_oct.r = 250;
	_oct.legs.resize(1);
	auto radian = 2.0f * DX_PI_F / (float)_oct.legs.size();
	for (int i = 0; i < _oct.legs.size(); ++i) {
		auto c = cos(radian * i);
		auto s = sin(radian * i);
		LEG(i).tip.x = _oct.root.x + c * _oct.r;
		LEG(i).tip.y = _oct.root.y + s * _oct.r;
		LEG(i).vel = Vector2(0,0);
		LEG(i).mat.resize(LEG(i).T);
		for (int j = 0; j < LEG(i).T; ++j) {
			LEG(i).joint.push_back(_oct.root + Vector2(c, s)*(_oct.r / LEG(i).T*(j+1)));
		}
		LEG(i).state = E_LEG_STATE::NORMAL;
		LEG(i).angle = GetRand((radian*_oct.legs.size()) / (2.0f*DX_PI_F)*360.0f) ;
	}
	angle = 120;
	wait = 0;
	joint = 0;
	test.resize(4);
}


Octopus::~Octopus()
{
}

void Octopus::Update(Vector2 pos)
{
	if (++wait >= limit) {
		Move(_oct, nodeSize, pos, 6);
		wait = 0;
	}
}

void Octopus::Draw()
{
	for (int i = 0; i < _oct.legs.size(); ++i) {
		int j = 0;

		auto p1 = _oct.root + Vector2(0,1)*width;
		auto p2 = LEG(i).joint[j] + Vector2(0, 1)*width;
		auto p3 = LEG(i).joint[j] + Vector2(0, -1)*width;
		auto p4 = _oct.root + Vector2(0, -1)*width;
		DrawLineAA(_oct.root.x, _oct.root.y, LEG(i).joint[j].x, LEG(i).joint[j].y, 0xffffff, 2);
		DrawCircle(_oct.root.x, _oct.root.y, 5, 0xff0000, true);
		//DrawQuadrangleAA(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, 0xaa0000, true);
		for (j = 0; j < LEG(i).T-1; ++j) {

			p1 = p2;
			p2 = LEG(i).joint[j + 1] + Vector2(0, 1)*width;
			p4 = p3;
			p3 = LEG(i).joint[j + 1] + Vector2(0, -1)*width;
			//DrawQuadrangleAA(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, 0xaa0000, true);
			DrawLineAA(LEG(i).joint[j].x, LEG(i).joint[j].y, LEG(i).joint[j + 1].x, LEG(i).joint[j + 1].y, 0xffffff, 2);
			DrawCircle(LEG(i).joint[j].x, LEG(i).joint[j].y, 5, 0x0000ff, true);
		}
		DrawCircle(LEG(i).joint[j].x, LEG(i).joint[j].y, 5, 0x0000ff, true);
		//DrawFormatString(LEG(i).tip.x , LEG(i).tip.y , 0xffffff, "%d", i);
	}
	/*DrawOval(_oct.center.x , _oct.center.y , 50, 25, 0xaa0000, true);
	DrawOval(_oct.center.x , _oct.center.y, 50, 25, 0x111111, false);*/
	int cnt = 0;
	for (auto t : test) {
		DrawFormatString(10*cnt, 0, 0xff0000, "%d", t);
		++cnt;
	}
}

void Octopus::Move(Oct oct, int effector, Vector2 target, int numMaxIteration)
{

	for (int i = 0; i < _oct.legs.size(); ++i) {
		
		if (LEG(i).state == E_LEG_STATE::NORMAL) {
			auto radian = 2.0f * DX_PI_F / (float)_oct.legs.size();
			auto rad = radian * i;
			joint = (++joint % LEG(i).T);

			auto ang = abs(++LEG(i).angle % angle - angle / 2);

			rad = rad + DX_PI_F / 180 * ang;
			auto c = _oct.root.x + cos(rad)*_oct.r;
			auto s = _oct.root.y + sin(rad)*_oct.r;
			auto p_pos = Vector2(c, s);
			auto v = LEG(i).joint[0] - _oct.root;
			auto p = p_pos - _oct.root;
			auto mat = MGetTranslate((-_oct.root).V_Cast());
			mat = MMult(mat, MGetRotVec2(v.V_Cast(), p.V_Cast()));
			mat = MMult(mat, MGetTranslate(_oct.root.V_Cast()));


			LEG(i).joint[0] = VTransform(LEG(i).joint[0].V_Cast(), mat);

			LegTranslate(LEG(i),0);

			Fk(LEG(i), p_pos);

			LEG(i).mat[0] = MGetRotVec2(v.V_Cast(), p.V_Cast());
			test[0] = joint;

		}
		if (LEG(i).state == E_LEG_STATE::PUNCH) {

		}
		if (LEG(i).state == E_LEG_STATE::OCT_INK) {

		}
		if (LEG(i).state == E_LEG_STATE::SWEEP) {
			auto p = LEG(i).tip - target;
			auto pos = LEG(i).tip - p.Normalized() * 2;

			Ik_Ccd(LEG(i), pos);
		}

	}
}

