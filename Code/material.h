#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <QHash>

class Materials
{
public:
	Materials() = default;
	~Materials() = default;

	bool read();
	double getMaterialPara(int id);

private:
	QHash<int, double> _paras{};
};



#endif