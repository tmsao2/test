#include "Geometry.h"
#include <cmath>

void Vector2::Zero()
{
	x = y = 0;
}

float Vector2::Magnitude() const
{
	return sqrt(x * x + y * y);
}

void Vector2::Normalize()
{
	float m = Magnitude();
	x = x / m;
	y = y / m;
}

Vector2 Vector2::Normalized()
{
	float size = Magnitude();
	return Vector2(x / size, y / size);
}

VECTOR Vector2::V_Cast()
{
	return VGet(x, y, 0);
}

Vector2 operator+(const Vector2 & lv, const Vector2 rv)
{
	return Vector2(lv.x + rv.x, lv.y + rv.y);
}

Vector2 operator-(const Vector2 & lv, const Vector2 rv)
{
	return Vector2(lv.x - rv.x, lv.y - rv.y);
}

Vector2 operator-(const Vector2 & lv, const float rv) {
	return Vector2(lv.x - rv, lv.y - rv);
}

Vector2 operator-(const Vector2 & lv)
{
	return Vector2(-lv.x, -lv.y);
}

Vector2 operator*(const Vector2 & lv, const float rv)
{
	return Vector2(lv.x * rv, lv.y * rv);
}

Vector2 operator*(const float lv, const Vector2 rv)
{
	return Vector2(lv * rv.x, lv * rv.y);
}

Vector2 operator/(const Vector2 & lv, const float rv)
{
	return Vector2(lv.x / rv, lv.y / rv);
}

Vector2 operator/(const Vector2 & lv, const Vector2 & rv) {
	return Vector2(lv.x / rv.x, lv.y / rv.y);
}

bool operator==(const Vector2 lv, const Vector2 rv)
{
	if (lv.x == rv.x&&lv.y == rv.y) {
		return true;
	}
	return false;
}

bool operator!=(const Vector2 lv, const Vector2 rv)
{
	if (lv.x == rv.x&&lv.y == rv.y) {
		return true;
	}
	return false;
}

float Dot(const Vector2 & v1, const Vector2 & v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

Vector2 Cross(const Vector2 & v1)
{
	return Vector2(v1.y, - v1.x);
}

//������
Size::Size() : width(0), height(0) {}
Size::Size(int inx, int iny) : width(inx), height(iny) {}

Rect::Rect() : center(0, 0), size(0, 0) {}
Rect::Rect(int x, int y, int w, int h) {}
Rect::Rect(Position2& p, Size & s) : center(p), size(s) {}

const int Rect::Left() const
{
	return (center.x - size.width / 2);
}

const int Rect::Right() const
{
	return (center.x + size.width / 2);
}

const int Rect::Top() const
{
	return (center.y - size.height / 2);
}

const int Rect::Bottom() const
{
	return (center.y + size.height / 2);
}

