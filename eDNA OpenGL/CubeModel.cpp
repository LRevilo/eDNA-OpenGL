#include "CubeModel.h"

CubeModel::CubeModel()
	: Model()
{
	Meshes.push_back(Mesh(cube_vertices, cube_normals, cube_uvs));
}