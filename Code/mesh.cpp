#include <vtkUnstructuredGrid.h>
#include <iostream>
#include "mesh.h"
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>
#include <QDomNodeList>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <QStringList>
#include <vtkIdList.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <QDir>
#include <vtkUnstructuredGridWriter.h>

VTKCellType TypeStringToVTKCellType(QString stype)
{
	VTKCellType cellType = VTK_EMPTY_CELL;
	if (stype == "VERTEX1") cellType = VTK_VERTEX;
	else if (stype == "LINE2") cellType = VTK_LINE;
	else if (stype == "TRI3") cellType = VTK_TRIANGLE;
	else if (stype == "QUAD4") cellType = VTK_QUAD;
	else if (stype == "TET4") cellType = VTK_TETRA;
	else if (stype == "HEX8") cellType = VTK_HEXAHEDRON;
	else if (stype == "WED6") cellType = VTK_WEDGE;
	else if (stype == "PYR5") cellType = VTK_PYRAMID;

	return cellType;
}


int Component::getID()
{
	return _id;
}

void Component::setID(int id)
{
	_id = id;
}

QList<int> Component::getmember()
{
	return _member;
}

void Component::appendMember(int m)
{
	_member.append(m);
}

Mesh::Mesh()
{
	_mesh = vtkUnstructuredGrid::New();
	_components.clear();
}

Mesh::~Mesh()
{
	for (auto c : _components)
		delete c;
	_components.clear();

	if (_mesh != nullptr)
		_mesh->Delete();
}

bool Mesh::read()
{
	QFile file("meshdata.xml");
	if (!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		std::cout << "网格文件打开失败！" << std::endl;
		return false;
	}
	QDomDocument* doc = new QDomDocument;
	if (!doc->setContent(&file))
	{
		file.close();
		return false;
	}
	std::cout << "网格文件读取中。。。" << std::endl;

	QDomNodeList meshList =doc->elementsByTagName("MeshKernel");
	const int nMesh = meshList.size();
	if (nMesh != 1)
	{
		std::cout << "网格文件错误！" << std::endl;
		return false;
	}

	QDomElement kernelele = meshList.at(0).toElement();

	//节点
	QDomNodeList nodelist = kernelele.elementsByTagName("Node");
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	const int nNode = nodelist.size();
	double minx = 1e33, maxx = -1e33, miny = 1e33, maxy = -1e33;
	for (int i = 0; i < nNode; ++i)
	{
		QDomElement nodeele = nodelist.at(i).toElement();
		QString text = nodeele.text();
		QStringList scoor = text.split(",");
		points->InsertNextPoint(scoor[1].toDouble(), scoor[2].toDouble(), scoor[3].toDouble());
		double x = scoor[1].toDouble();
		double y = scoor[2].toDouble();

		if (x < minx) minx = x;
		if (x > maxx) maxx = x;

		if (y < miny) miny = y;
		if (y > maxy) maxy = y;
	}
	_location[0] = minx;
	_location[1] = maxx;
	_D = maxy - miny;

	_mesh->SetPoints(points);
	QDomNodeList elementList = kernelele.elementsByTagName("Element");
	const int nele = elementList.size();
	for (int i = 0; i < nele; ++i)
	{
		QDomElement eleele = elementList.at(i).toElement();
		QString text = eleele.text();
		QStringList info = text.split(",");
		VTKCellType celltype = TypeStringToVTKCellType(info.at(1));
		vtkSmartPointer<vtkIdList> idlist = vtkSmartPointer<vtkIdList>::New();
		for (int i = 2; i < info.size(); ++i)
		{
			int id = info.at(i).toInt();
			idlist->InsertNextId(id);
		}
		_mesh->InsertNextCell(celltype, idlist);
	}

	QDomNodeList setList = doc->elementsByTagName("MeshSet");
	const int nSet = setList.size();
	for (int i = 0; i < nSet; ++i)
	{
		QDomElement setEle = setList.at(i).toElement();
		QString sID = setEle.attribute("ID");
		QString stype = setEle.attribute("Type");
		
		if (stype.toLower() != "element")
		{
			std::cout << "组件类型必须为单元类型！" << std::endl;
			return false;
		}
		
		Component * com = new Component;
		com->setID(sID.toInt());
		QDomNodeList memList = setEle.elementsByTagName("Member");
		for (int j = 0; j < memList.size(); ++j)
		{
			bool ok = false;
			QDomElement memele = memList.at(j).toElement();
			QString text = memele.text();
			QStringList sids = text.split(",");
			for (QString s : sids)
			{
				int mid = s.toInt(&ok);
				if (!ok) continue;
				com->appendMember(mid);
			}
		}

		_components.append(com);
	}

	std::cout << "网格文件读取完毕！" << std::endl;
	delete doc;
	return true;
}

void Mesh::write(int step, Point p0)
{
	QString filename = QDir::currentPath() + QString("/Result/res_%1.vtk").arg(step);
	double press = p0.p;
	double l = p0.l * 1000;
	const double split = _location[0] + l;
	double  t = p0.t;

	vtkUnstructuredGrid* ug = vtkUnstructuredGrid::New();
	ug->DeepCopy(_mesh);

	int np = _mesh->GetNumberOfPoints();
	vtkPointData* pd = ug->GetPointData();
	vtkDoubleArray* da = vtkDoubleArray::New();
	da->SetName("P(MPa)");
	pd->AddArray(da);

	for (int i = 0; i < np; ++i)
	{
		double* coor = _mesh->GetPoint(i);
		double va = (coor[0] < split ? press : 0.1);
		da->InsertNextValue(va);
	}
	vtkUnstructuredGridWriter  * writer = vtkUnstructuredGridWriter::New();
	writer->SetFileName(filename.toLatin1().data());
	writer->SetInputData(ug);
	writer->Write();

	writer->Delete();
	ug->Delete();

	std::cout << "t = " << t * 1000 << "ms     l = " << l << "mm" << std::endl;
}

Component* Mesh::getComponent(int id)
{
	for (Component* c : _components)
	{
		if (c->getID() == id)
			return c;
	}
	return nullptr;
}

double Mesh::getButtomArea()
{
	return _D*_D* 3.1415926 / 4;
}

void Mesh::getLength(double &min, double &max)
{
	min = _location[0];
	max = _location[1];
}
