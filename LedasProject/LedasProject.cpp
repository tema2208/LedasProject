#include <fstream>
#include <iostream>

#include "Tetrahedron.h"

void PrintMatrix(double matrix[][3])
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 3; j++)
			std::cout << matrix[i][j] << " ";
		std::cout << "\n";
	}
}

void ReadMatrix(double matrix[][3], std::ifstream& f)
{
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 3; j++)
			f >> matrix[i][j];
}

void ReadPoint(double point[], std::ifstream& f )
{
	for (size_t i = 0; i < 3; i++)
	{
		f >> point[i];
	}
}

//answer to task 1)
bool IsPointLieInTetrahedron(double matrix[][3], double point[])
{
	Tetrahedron tetrahedron = { Vector3d(matrix[0]), Vector3d(matrix[1]), Vector3d(matrix[2]), Vector3d(matrix[3]) };
	return tetrahedron.CheckPointInsideTetrahedron(point);
}

//answer to task 2)
Vector3d GetPointAtTheMaximumDistanceFromSurface(double matrix[][3])
{
	Tetrahedron tetrahedron = { Vector3d(matrix[0]), Vector3d(matrix[1]), Vector3d(matrix[2]), Vector3d(matrix[3]) };
	return tetrahedron.GetCenterInscribedSphere();
}

void StartTest()
{
	std::ifstream in;
	in.open("input.txt");
	if(in.is_open())
	{
		int count;
		in >> count;
		for(int i = 0; i < count; i++)
		{
			double matrix[4][3];
			double point[3];
			char symbol;
			ReadMatrix(matrix, in);
			ReadPoint(point, in);

			std::cout << "center : " << GetPointAtTheMaximumDistanceFromSurface(matrix);
			std::cout << "is lie in tetrahedron : " << IsPointLieInTetrahedron(matrix, point) << std::endl;
			in >> symbol;
		}
	}
}

int main()
{
	StartTest();
}