#include "material.h"
#include <iostream>
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>
#include <QDomNodeList>

bool Materials::read()
{
	QFile file("material.xml");
	if (!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		std::cout << "�����ļ���ʧ�ܣ�" << std::endl;
		return false;
	}
	QDomDocument* doc = new QDomDocument;
	if (!doc->setContent(&file))
	{
		file.close();
		return false;
	}
	std::cout << "�������Զ�ȡ�С�����" << std::endl;

	QDomNodeList materialList = doc->elementsByTagName("Material");
	const int nm = materialList.size();
	for (int i = 0; i < nm; ++i)
	{
		QDomElement maele = materialList.at(i).toElement();
		int id = maele.attribute("ID").toInt();

		QDomNodeList paraList = maele.elementsByTagName("Parameter");
		double v = paraList.at(0).toElement().attribute("Value").toDouble();

		_paras.insert(id, v);
	}

	std::cout << "�������Զ�ȡ��ϣ�" << std::endl;
	delete doc;
	return true;
}

double Materials::getMaterialPara(int id)
{
	if (_paras.contains(id))
		return _paras.value(id);
	return 0;
}

