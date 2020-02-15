#ifndef _Model_H_
#define _Model_H_

class Materials;
class Mesh;

class Model
{
public:
	Model(Mesh* mesh, Materials* ma);
	~Model() = default;

	bool read();

private:
	Mesh* _mesh{};
	Materials* _material{};

public:
	double S = 1.3E-4;   //枪膛截面积 m2
	double V0 = 20.7E-6; //药室容积 m3
	double lg = 0.654;  //弹丸行程
	double m = 48.2E-3; //弹丸质量 kg
	//装药条件
	double f = 980;       //火药力 KJ/Kg
	double a = 9.2E-4;    //余容
	double w = 17;       //装药量 g
	double Pp = 1600;    //火药密度 Kg/m3
	double c = 0.22;     //火药热力系数
	double u1 = 6.85E-8; //燃速系数
	double n = 0.85;     //压力指数
	double e1 = 2E-4;    //弧厚 m
	double cai = 0.8235;  //形状特征量
	double r = 0.13207;
	double u = -0.05160;
	double p = 1.1518E-4;
	//初始条件
	double p0 = 40;     //MPa
	//次要功计算参数
	double K1 = 1.10;
	double b = 0.2520;
	//计算步长
	double h = 0.01;
};

#endif