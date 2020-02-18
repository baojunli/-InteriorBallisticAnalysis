#ifndef _MESH_H_
#define _MESH_H_

#include <QList>
#include <vtkCellType.h>
#include <QString>
#include "PDE.h"

class vtkUnstructuredGrid;

class Component
{
public:
	Component() = default;
	~Component() = default;

	int getID();
	void setID(int id);
	QList<int> getmember();
	void appendMember(int m);

private:
	int _id{ -1 };
	QList<int> _member{};
};

class Mesh
{
public:
	Mesh();
	~Mesh();
	bool read();
	void write(int step, Point p);
	Component* getComponent(int id);
	void getLength(double &min, double &max);
	double getButtomArea();

private:
	QList<Component*> _components{};
	vtkUnstructuredGrid* _mesh{};
	double _location[2];
	double _D{ 0.0 };
};


#endif