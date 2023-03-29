#pragma once
#include <ostream>
#include <string>

#include "Math.h"

class Vector3d
{
	double x = 0;
	double y = 0;
	double z = 0;

	friend std::ostream& operator<<(std::ostream& os, const Vector3d& v);

public:
	Vector3d(double x, double y, double z) :
		x(x), y(y), z(z)
	{}
	Vector3d(double array[]) :
		x(array[0]), y(array[1]), z(array[2])
	{}
	Vector3d() = default;

	double GetX() const { return x; }
	double GetY() const { return y; }
	double GetZ() const { return z; }

	double operator*(const Vector3d& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}
	Vector3d operator+(const Vector3d& v) const
	{
		return { x + v.x, y + v.y, z + v.z };
	}
	Vector3d operator-(const Vector3d& v) const
	{
		return { x - v.x, y - v.y, z - v.z };
	}
	bool operator==(const Vector3d& v) const
	{
		return IsEqualsZero(x - v.x) && IsEqualsZero(y - v.y) && IsEqualsZero(z - v.z);
	}
	double operator[](int i) const
	{
		if (i == 0) return x;
		if (i == 1) return y;
		if (i == 2) return z;
		throw std::exception("Vector3d: out of range");
	}
	double& operator[](int i)
	{
		if (i == 0) return x;
		if (i == 1) return y;
		if (i == 2) return z;
		throw std::exception("Vector3d: out of range");
	}


	double GetLength() const
	{
		return sqrt(x * x + y * y + z * z);
	}
	bool IsCollinear(const Vector3d& v) const
	{
		double len = CrossProduct(v).GetLength();
		return IsEqualsZero(len);
	}
	Vector3d CrossProduct(const Vector3d& v) const
	{
		return { y * v.z - z * v.y, -x * v.z + z * v.x, x * v.y - y * v.x };
	}
	double TripleProduct(const Vector3d& v1, const Vector3d& v2) const
	{
		return x * (v1.y * v2.z - v1.z * v2.y) - y * (v1.x * v2.z - v1.z * v2.x) + z * (v1.x * v2.y - v1.y * v2.x);
	}
	std::string ToString() const
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
	}
};

inline std::ostream& operator<<(std::ostream& os, const Vector3d& v)
{
	return os << v.ToString() << std::endl;
}
