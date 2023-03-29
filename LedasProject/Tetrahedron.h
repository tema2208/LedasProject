#pragma once
#include <vector>

#include "Plane3d.h"
#include "Vector3d.h"

class Tetrahedron
{
	std::vector<Vector3d> pointInfo{};
	std::vector<Plane3d> planeInfo{};

	//this Barycentric coordinate system is built on the vertices of the tetrahedron
	std::vector<double> GetWeightsForCenterInscribedSphere() const;
public:
	Tetrahedron(const Vector3d& p1, const Vector3d& p2, const Vector3d& p3, const Vector3d& p4);
	Tetrahedron() = delete;

	bool CheckPointInsideTetrahedron(const Vector3d& point);

	void MakeNormalVectorsLookInside();

	std::vector<double> GetFacesArea() const;

	Vector3d GetCenterInscribedSphere() const;
};
