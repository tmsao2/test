#include "Octopus.h"
#include <DxLib.h>
#include <math.h>
#include <random>

const int length = 30;
const int limit = 1;
const int nodeSize = 6;
const int width = 40;

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
			for (int itr = j; itr <= leg.T; ++itr) {
				leg.joint[itr] = VTransform(leg.joint[itr].V_Cast(), mat);
			}
			leg.tip = leg.joint[leg.T];
		}
	}
}

void Octopus::Fk(E_Leg & leg, Vector2 pos)
{
	for (int j = 0; j < joint; --j) {
		auto v = leg.joint[j] - _oct.root;
		auto p = pos - _oct.root;



	}
	if (joint == leg.T) {
		joint = 0;
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
	_oct.center = Vector2(1000, 256);
	_oct.root = _oct.center + Vector2(-20,0);
	_oct.r = 500;
	_oct.legs.resize(8);
	auto radian = 2.0f * DX_PI_F / (float)_oct.legs.size();
	for (int i = 0; i < _oct.legs.size(); ++i) {
		auto c = cos(radian * i);
		auto s = sin(radian * i);
		LEG(i).tip.x = _oct.root.x + c * _oct.r;
		LEG(i).tip.y = _oct.root.y + s * _oct.r;
		for (int j = 0; j <= LEG(i).T; ++j) {
			LEG(i).joint.push_back(_oct.root + Vector2(c, s)*(_oct.r / LEG(i).T*(j+1)));
		}
		LEG(i).state = E_LEG_STATE::NORMAL;
	}
	joint = 0;
	angle = 0;
	wait = 0;
}


Octopus::~Octopus()
{
}

void Octopus::Update(Vector2 pos)
{
	if (++wait>limit) {
		wait = 0;
	}
	++angle;
	++joint;
	Move(_oct, nodeSize, pos, 6);

}

void Octopus::Draw()
{
	for (int i = 0; i < _oct.legs.size(); ++i) {
		if (i == 3) {
			int j = 0;
			auto v = LEG(i).joint[j] - LEG(i).joint[j + 1];
			auto mat = MGetRotZ(DX_PI_F / 180 * 90.0f);
			v = VTransform(v.V_Cast(), mat);
			auto p = v.Normalized() * width;
			v = LEG(i).joint[j] - LEG(i).joint[j + 1];
			mat = MGetRotZ(DX_PI_F / 180 * (-90.0f));
			v = VTransform(v.V_Cast(), mat);
			auto _p = v.Normalized() * width;
			auto p1 = LEG(i).joint[j] + p;
			auto p2 = LEG(i).joint[j + 1] + p;
			auto p3 = LEG(i).joint[j + 1] + _p;
			auto p4 = LEG(i).joint[j] + _p;
			DrawQuadrangleAA(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, 0xaa0000, true);
			for (j = 1; j < LEG(i).T; ++j) {

				v = LEG(i).joint[j] - LEG(i).joint[j + 1];
				mat = MGetRotZ(DX_PI_F / 180 * 90.0f);
				v = VTransform(v.V_Cast(), mat);
				p = v.Normalized() * (width - (width / (LEG(i).T - j)) + 1);
				v = LEG(i).joint[j] - LEG(i).joint[j + 1];
				mat = MGetRotZ(DX_PI_F / 180 * (-90.0f));
				v = VTransform(v.V_Cast(), mat);
				_p = v.Normalized() * (width - (width / (LEG(i).T - j)) + 1);

				p1 = p2;
				p2 = LEG(i).joint[j + 1] + p;
				p4 = p3;
				p3 = LEG(i).joint[j + 1] + _p;
				DrawQuadrangleAA(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, 0xaa0000, true);
				DrawLineAA(LEG(i).joint[j].x, LEG(i).joint[j].y, LEG(i).joint[j + 1].x, LEG(i).joint[j + 1].y, 0xffffff, 2);
				DrawCircle(LEG(i).joint[j].x, LEG(i).joint[j].y, 5, 0x0000ff, true);
			}
		}
		//DrawFormatString(LEG(i).tip.x , LEG(i).tip.y , 0xffffff, "%d", i);
	}
	/*DrawOval(_oct.center.x , _oct.center.y , 50, 25, 0xaa0000, true);
	DrawOval(_oct.center.x , _oct.center.y, 50, 25, 0x111111, false);*/
}

void Octopus::Move(Oct oct, int effector, Vector2 target, int numMaxIteration)
{
	LEG(3).state = E_LEG_STATE::SWEEP;

	for (int i = 0; i < _oct.legs.size(); ++i) {
		if (LEG(i).state == E_LEG_STATE::NORMAL) {
			if (LEG(i).angle == 0) {
				LEG(i).angle = 180;
			}
			auto radian = 2.0f * DX_PI_F / (float)_oct.legs.size();
			auto rad = radian * i;

			auto ang = abs(angle % LEG(i).angle - LEG(i).angle / 2);
			rad = rad + DX_PI_F / 180 * ang;
			auto c = _oct.root.x + cos(rad)*_oct.r;
			auto s = _oct.root.y + sin(rad)*_oct.r;
			auto p_pos = Vector2(c, s);
			Fk(LEG(i), p_pos);
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


	//for (int i = 0; i < _oct.legs.size(); ++i) {
	//	auto begin = _oct.legs[i]._pos.begin();
	//	auto itr = _oct.legs[i]._pos.end() - 2;
	//	auto tip = _oct.legs[i]._pos.end() - 1;
	//	for (int it = 0; it < numMaxIteration; ++it) {
	//		for (auto n = tip; n != begin; --n) {		//角度計算
	//			auto p_vec = target - *(n - 1);			//目標→関節
	//			auto e_vec = *tip - *(n - 1);		//先端→関節
	//			auto mat = MGetTranslate((-*(n - 1)).V_Cast());		//平行移動行列
	//			mat = MMult(mat, MGetRotVec2(e_vec.V_Cast(), p_vec.V_Cast()));						//回転行列
	//			mat = MMult(mat, MGetTranslate((*(n - 1)).V_Cast()));	//平行移動行列	
	//			for (auto nv = n; nv != _oct.legs[i]._pos.end(); ++nv) {		//座標計算
	//				*nv = VTransform((*nv).V_Cast(), mat);
	//			}
	//		}
	//	}
	//}
}

