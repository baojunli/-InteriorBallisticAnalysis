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
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK")); // 关键是这句
	QFile file("model.xml");
	if (!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		std::cout << "参数文件打开失败！" << std::endl;
		return false;
	}
	QDomDocument* doc = new QDomDocument;
	if (!doc->setContent(&file))
	{
		file.close();
		return false;
	}
	std::cout << "参数读取中。。。" << std::endl;

	QDomNodeList  paraNodeList = doc->elementsByTagName("Parameter");

	V0 = getValue(&paraNodeList, QString::fromLocal8Bit("药室容积")); //药室容积 m3	
	m = getValue(&paraNodeList, QString::fromLocal8Bit("弹丸质量")); //弹丸质量 kg
	//装药条件
	f = getValue(&paraNodeList, QString::fromLocal8Bit("火药力"));      //火药力 KJ/Kg
	a = getValue(&paraNodeList, QString::fromLocal8Bit("余容"));    //余容
	w = getValue(&paraNodeList, QString::fromLocal8Bit("装药量"));;       //装药量 g
	Pp = getValue(&paraNodeList, QString::fromLocal8Bit("密度"));    //火药密度 Kg/m3
	c = getValue(&paraNodeList, QString::fromLocal8Bit("热力系数"));     //火药热力系数
	u1 = getValue(&paraNodeList, QString::fromLocal8Bit("燃速系数")); //燃速系数
	n = getValue(&paraNodeList, QString::fromLocal8Bit("压力指数"));     //压力指数
	e1 = getValue(&paraNodeList, QString::fromLocal8Bit("弧厚"));   //弧厚 m
	cai = getValue(&paraNodeList, QString::fromLocal8Bit("cai"));;  //形状特征量
	r = getValue(&paraNodeList, QString::fromLocal8Bit("r"));;
	u = getValue(&paraNodeList, QString::fromLocal8Bit("u"));
	p = getValue(&paraNodeList, QString::fromLocal8Bit("p"));
	//初始条件
	p0 = getValue(&paraNodeList, QString::fromLocal8Bit("初始压强"));      //MPa
	air = getValue(&paraNodeList, QString::fromLocal8Bit("空气压强"));
	//次要功计算参数
	K1 = getValue(&paraNodeList, QString::fromLocal8Bit("K1"));
	b = getValue(&paraNodeList, QString::fromLocal8Bit("b"));
	//计算步长
	h = getValue(&paraNodeList, QString::fromLocal8Bit("时间步长"));
	

	std::cout << "参数读取完毕！" << std::endl;
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
