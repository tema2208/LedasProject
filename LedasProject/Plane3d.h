#pragma once
#include "Vector3d.h"

class Plane3d
{
	Vector3d firstPoint{};
	Vector3d secondPoint{};
	Vector3d thirdPoint{};

public:
	Plane3d(const Vector3d& p1, const Vector3d& p2, const Vector3d& p3) :
		firstPoint(p1), secondPoint(p2), thirdPoint(p3)
	{
		if((firstPoint - secondPoint).IsCollinear(firstPoint - thirdPoint))
		{
			throw std::exception("Wrong arguments, points lie on the same line");
		}
	}
	Plane3d() = default;

	double PlaneOrientationRelativeToPoint(const Vector3d& point) const
	{
		return (point - firstPoint).TripleProduct(secondPoint - firstPoint, thirdPoint - firstPoint);
	}

	void SwapNormalVectorDirection()
	{
		std::swap(secondPoint, thirdPoint);
	}

	double GetAreaOfTriangle() const
	{
		Vector3d v1 = secondPoint - firstPoint;
		Vector3d v2 = thirdPoint - firstPoint;
		return 0.5 * v1.CrossProduct(v2).GetLength();
	}
};
