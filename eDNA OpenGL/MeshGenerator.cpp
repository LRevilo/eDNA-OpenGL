#include "MeshGenerator.h"
#include "MeshComponent.h"

MeshGenerator::MeshGenerator() {}
MeshGenerator::~MeshGenerator() {}

void MeshGenerator::Reset(MeshComponent& MC)
{
	MC.Vertices.clear();
	MC.Indices.clear();
	MC.Material = 0;
	MC.Translation = glm::dvec3(0.0, 0.0, 0.0);
	MC.Rotation = glm::vec3(0.f, 0.f, 0.f);
	MC.Scale = glm::vec3(1.f, 1.f, 1.f);
}

void MeshGenerator::Plane(MeshComponent& MC, int Size)
{
	Vertex vertex;
	//int n = 1;// << Subdivisions; // == 2^n
	//float dn = 1.f / (n);
	vertex.Normal = glm::vec3(0, 0, 1);
	vertex.Tangent = glm::vec3(0, 1, 0);
	vertex.Bitangent = glm::vec3(1, 0, 0);
	
	int n = std::max(Size,2);
	float dn = 1.f / (n-1);
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			vertex.Position = glm::vec3(x, y, 0) * dn;
			vertex.UV = glm::vec2(x, y) * dn;
			MC.Vertices.push_back(vertex);
		}
	}
	for (int y = 0; y < n-1; y++)
	{
		for (int x = 0; x < n-1; x++)
		{
			int i0 = (n)* y + x;
			int i1 = i0 + 1;
			int i2 = i0 + (n);
			int i3 = i0 + (n) + 1;

			MC.Indices.push_back(i0);
			MC.Indices.push_back(i1);
			MC.Indices.push_back(i2);
			MC.Indices.push_back(i2);
			MC.Indices.push_back(i1);
			MC.Indices.push_back(i3);
		}
	}

	MC.Scale = glm::vec3(1.f, 1.f, 1.f);
}

void MeshGenerator::Cylinder(struct MeshComponent& MC, int SizeX, int SizeY)
{
	Vertex vertex;
	//int n = 1;// << Subdivisions; // == 2^n
	//float dn = 1.f / (n);
	
	vertex.Tangent = glm::vec3(0, 0, 1);
	

	int X = std::max(SizeX, 2);
	int Y = std::max(SizeY, 2);

	float dx = 1.f / (X - 1);
	float dy = 1.f / (Y - 1);

	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			float angle = x * dx * glm::two_pi<float>();
			float cos = std::cos(angle);
			float sin = std::sin(angle);
			vertex.Position = glm::vec3(cos, sin, y * dy);
			vertex.Normal = glm::vec3(cos, sin, 0);

			vertex.Bitangent = glm::cross(vertex.Normal, vertex.Tangent);

			vertex.UV = glm::vec2(x*dx, y*dy);
			MC.Vertices.push_back(vertex);
		}
	}

for (int y = 0; y < Y - 1; y++)
{
	for (int x = 0; x < X - 1; x++)
	{
		int i0 = (X)*y + x;
		int i1 = i0 + 1;
		int i2 = i0 + (X);
		int i3 = i0 + (X)+1;

		MC.Indices.push_back(i0);
		MC.Indices.push_back(i1);
		MC.Indices.push_back(i2);
		MC.Indices.push_back(i2);
		MC.Indices.push_back(i1);
		MC.Indices.push_back(i3);
	}
}

	MC.Scale = glm::vec3(1.f, 1.f, 1.f);
}

void MeshGenerator::Cube(struct MeshComponent& MC)
{
	Vertex vertex;

	for (int n = 0; n < cube_vertices.size(); n++)
	{
		vertex.Position = cube_vertices[n];
		vertex.Normal = cube_normals[n];
		vertex.UV = cube_uvs[n];
		MC.Vertices.push_back(vertex);
	}
	for (int i = 0; i < cube_indicies.size(); i++)
	{
		MC.Indices.push_back(cube_indicies[i]);
	}

}