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
	double S = 1.3E-4;   //ǹ�Ž���� m2
	double V0 = 20.7E-6; //ҩ���ݻ� m3
	double lg = 0.654;  //�����г�
	double m = 48.2E-3; //�������� kg
	//װҩ����
	double f = 980;       //��ҩ�� KJ/Kg
	double a = 9.2E-4;    //����
	double w = 17;       //װҩ�� g
	double Pp = 1600;    //��ҩ�ܶ� Kg/m3
	double c = 0.22;     //��ҩ����ϵ��
	double u1 = 6.85E-8; //ȼ��ϵ��
	double n = 0.85;     //ѹ��ָ��
	double e1 = 2E-4;    //���� m
	double cai = 0.8235;  //��״������
	double r = 0.13207;
	double u = -0.05160;
	double p = 1.1518E-4;
	//��ʼ����
	double p0 = 40;     //MPa
	//��Ҫ���������
	double K1 = 1.10;
	double b = 0.2520;
	//���㲽��
	double h = 0.01;
};

#endif