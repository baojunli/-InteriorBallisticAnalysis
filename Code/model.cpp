#include "model.h"
#include "mesh.h"
#include <iostream>
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>
#include <QDomNodeList>
#include <QTextCodec>
#include <QString>
#include <QDebug>

Model::Model(Mesh* mesh, Materials* ma)
{
	_mesh = mesh;
	_material = ma;
}

bool Model::read()
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK")); // �ؼ������
	QFile file("model.xml");
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
	std::cout << "������ȡ�С�����" << std::endl;

	QDomNodeList  paraNodeList = doc->elementsByTagName("Parameter");

	V0 = getValue(&paraNodeList, QString::fromLocal8Bit("ҩ���ݻ�")); //ҩ���ݻ� m3	
	m = getValue(&paraNodeList, QString::fromLocal8Bit("��������")); //�������� kg
	//װҩ����
	f = getValue(&paraNodeList, QString::fromLocal8Bit("��ҩ��"));      //��ҩ�� KJ/Kg
	a = getValue(&paraNodeList, QString::fromLocal8Bit("����"));    //����
	w = getValue(&paraNodeList, QString::fromLocal8Bit("װҩ��"));;       //װҩ�� g
	Pp = getValue(&paraNodeList, QString::fromLocal8Bit("�ܶ�"));    //��ҩ�ܶ� Kg/m3
	c = getValue(&paraNodeList, QString::fromLocal8Bit("����ϵ��"));     //��ҩ����ϵ��
	u1 = getValue(&paraNodeList, QString::fromLocal8Bit("ȼ��ϵ��")); //ȼ��ϵ��
	n = getValue(&paraNodeList, QString::fromLocal8Bit("ѹ��ָ��"));     //ѹ��ָ��
	e1 = getValue(&paraNodeList, QString::fromLocal8Bit("����"));   //���� m
	cai = getValue(&paraNodeList, QString::fromLocal8Bit("cai"));;  //��״������
	r = getValue(&paraNodeList, QString::fromLocal8Bit("r"));;
	u = getValue(&paraNodeList, QString::fromLocal8Bit("u"));
	p = getValue(&paraNodeList, QString::fromLocal8Bit("p"));
	//��ʼ����
	p0 = getValue(&paraNodeList, QString::fromLocal8Bit("��ʼѹǿ"));      //MPa
	air = getValue(&paraNodeList, QString::fromLocal8Bit("����ѹǿ"));
	//��Ҫ���������
	K1 = getValue(&paraNodeList, QString::fromLocal8Bit("K1"));
	b = getValue(&paraNodeList, QString::fromLocal8Bit("b"));
	//���㲽��
	h = getValue(&paraNodeList, QString::fromLocal8Bit("ʱ�䲽��"));
	

	std::cout << "������ȡ��ϣ�" << std::endl;
	delete doc;
	return true;
}

double Model::getArea()
{
	return _mesh->getButtomArea();
}

void Model::getLength(double &min, double &max)
{
	_mesh->getLength(min, max);
}

double Model::getValue(QDomNodeList* nodeList, QString des)
{
	const int n = nodeList->size();
	for (int i = 0; i < n; ++i)
	{
		QDomElement ele = nodeList->at(i).toElement();
		QString sname = ele.attribute("Describe");
	
		if (sname  != des) continue;
		QString sv = ele.attribute("Value");
		return sv.toDouble();
	}
	return 0;
}
