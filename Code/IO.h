#ifndef _IO_H_
#define _IO_H_

#include <QString>
#include "PDE.h"

class Mesh;
class Materials;
class Model;

class DataIO
{
public:
	DataIO();
	~DataIO();

	bool read();
	void write(int step, Point p);
	Model* getModel();

private:
	Mesh* _mesh{};
	Materials* _materials{};
	Model* _model{};

};


#endif
