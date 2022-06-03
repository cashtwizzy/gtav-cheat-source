#pragma once
#include <cmath>
#include "includes.h"
#pragma warning(disable: 4996)

struct Vector2D
{
	float x{};
	float y{};

	Vector2D(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float DistanceFrom(Vector2D pointB)
	{
		double d1 = x - pointB.x;
		double d2 = y - pointB.y;

		return (float)sqrt(d1 * d1 + d2 * d2);
	}
};

struct Vector2
{
	float x;
	float y;

	Vector2() {}
	Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
};
struct _Vector3
{
	float x{};
	float y{};
	float z{};
};
struct Vector4
{
	float x{};
	float y{};
	float z{};
	float w{};
};

class Vector3
{
public:
	float x, y, z;

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3()
	{
		x = y = z = 0;
	}
	float length()
	{
		return (float)sqrt(x * x + y * y + z * z);
	}
	float dotproduct(Vector3 dot)
	{
		return (x * dot.x + y * dot.y + z * dot.z);
	}

	float Distance(Vector3& from, Vector3& to)
	{
		return Vector3(from.x - to.x, from.y - to.y, from.z - to.z).length();
	}

	static Vector3 FromM128(__m128 in) { return Vector3(in.m128_f32[0], in.m128_f32[1], in.m128_f32[2]); }
};


#pragma pack(push, 1)
class scrVector
{
public:
	scrVector() = default;
	scrVector(float x, float y, float z) : x(x), y(y), z(z) {}
public:
	float x{};
private:
	char m_padding1[0x04];
public:
	float y{};
private:
	char m_padding2[0x04];
public:
	float z{};
private:
	char m_padding3[0x04];
};
#pragma pack(pop)

namespace Tools
{
	float Get3dDistance(Vector3 to, Vector3 from)
	{
		return (sqrt(
			((to.x - from.x) * (to.x - from.x)) +
			((to.y - from.y) * (to.y - from.y)) +
			((to.z - from.z) * (to.z - from.z))
		));
	}

#ifdef _WIN64
#define PTRMAXVAL ((PVOID)0x000F000000000000)
#else
#define PTRMAXVAL ((PVOID)0xFFF00000)
#endif
	BOOLEAN IsValid(PVOID ptr)
	{
		return (ptr >= (PVOID)0x10000) && (ptr < PTRMAXVAL) && ptr != nullptr;
	}

	bool isW2SValid(Vector3 p) {
		return (p.x > 1.0f && p.y > 1.0f);
	}

	float GetDistance(float Xx, float Yy, float xX, float yY)
	{
		return sqrt((yY - Yy) * (yY - Yy) + (xX - Xx) * (xX - Xx));
	}

}