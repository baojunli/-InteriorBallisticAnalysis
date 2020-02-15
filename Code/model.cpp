#include "model.h"

Model::Model(Mesh* mesh, Materials* ma)
{
	_mesh = mesh;
	_material = ma;
}

bool Model::read()
{
	return false;
}
