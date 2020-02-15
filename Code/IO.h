#ifndef _IO_H_
#define _IO_H_

#include <QString>

class Mesh;
class Materials;
class Model;

class DataIO
{
public:
	DataIO();
	~DataIO();

	bool read();
	void write();

private:
	Mesh* _mesh{};
	Materials* _materials{};
	Model* _model{};

};


#endif
