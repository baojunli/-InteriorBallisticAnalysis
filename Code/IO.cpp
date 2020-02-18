#include "IO.h"
#include "mesh.h"
#include "material.h"
#include "model.h"

DataIO::DataIO()
{
	_mesh = new Mesh;
	_materials = new Materials;
	_model = new Model(_mesh, _materials);
}

DataIO::~DataIO()
{
	delete _mesh;
	delete _materials;
	delete _model;
}

bool DataIO::read()
{
	if (!_mesh->read()) return false;
	if (!_materials->read()) return false;
	if (!_model->read()) return false;
	return true;
}

void DataIO::write(int step, Point p)
{
	_mesh->write(step, p);
}

Model* DataIO::getModel()
{
	return _model;
}

