#include <algorithm>

#include "Tetrahedron.h"

Tetrahedron::Tetrahedron(const Vector3d& p1, const Vector3d& p2, const Vector3d& p3, const Vector3d& p4)
{
	pointInfo.emplace_back(p1);
	pointInfo.emplace_back(p2);
	pointInfo.emplace_back(p3);
	pointInfo.emplace_back(p4);

	planeInfo.emplace_back(Plane3d(p1, p2, p3));
	planeInfo.emplace_back(Plane3d(p1, p2, p4));
	planeInfo.emplace_back(Plane3d(p1, p3, p4));
	planeInfo.emplace_back(Plane3d(p2, p3, p4));
}

std::vector<double> Tetrahedron::GetWeightsForCenterInscribedSphere() const
{
	std::vector<double> facesArea = GetFacesArea();
	double areasSum = 0;
	for (double area : facesArea) areasSum += area;

	std::vector<double> weights{};
	for (double area : facesArea)
		weights.emplace_back(area / areasSum);
	return weights;
}

bool Tetrahedron::CheckPointInsideTetrahedron(const Vector3d& point)
{
	MakeNormalVectorsLookInside();
	return std::all_of(planeInfo.begin(), planeInfo.end(), [point](Plane3d p) {return p.PlaneOrientationRelativeToPoint(point) >= 0; });
}

void Tetrahedron::MakeNormalVectorsLookInside()
{
	for (int i = 0; i < 4; ++i)
		if (planeInfo[i].PlaneOrientationRelativeToPoint(pointInfo[3 - i]) < 0)
			planeInfo[i].SwapNormalVectorDirection();
}

std::vector<double> Tetrahedron::GetFacesArea() const
{
	std::vector<double> answer;
	for (const Plane3d& plane : planeInfo)
		answer.emplace_back(plane.GetAreaOfTriangle());

	return answer;
}

Vector3d Tetrahedron::GetCenterInscribedSphere() const
{
	Vector3d vector{};
	std::vector<double> weights = GetWeightsForCenterInscribedSphere();
	std::reverse(weights.begin(), weights.end());
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
			vector[i] += weights[j] * pointInfo[j][i];
	return vector;
}