#include "PDE.h"
#include<iostream>
#include<fstream>
#include<math.h>
#include<vector>
using namespace std;

int main()
{
	//������֪����
	//ǹ�Ź��켰������Ԫ
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
	//��������
	double Zk = (p + e1) / e1;
	double fai = K1 + b*w / (m * 1000);   //��Ҫ��ϵ��
	double de = w / (V0*1E6);        //װ���ܶ�
	double l0 = V0 / S;             //�����ݻ������� m
	double Vj = sqrt((2 * f*w) / (c*fai*m));  //��������ٶ� m/s
	double B = ((S*S*e1*e1) / (f*w*fai*m*u1*u1))*pow(f*de, 2 * (1 - n));
	double Ks = cai*(1 + r + u);
	double cais = (1 - Ks*Zk*Zk) / (Zk - Zk*Zk);
	double rs = Ks / cais - 1;

	//��ֵ����
	Point temp;
	vector<Point> pt;
	double tb = 0;
	double lb = 0;
	double vb = 0;
	double pb = p0 / (f*de);
	double K = (1 / de - 1 / Pp) / (f / p0 + a - 1 / Pp);
	double c0 = sqrt(1 + 4 * r*K / cai);
	double Z = (c0 - 1) / (2 * r);
	temp.t = tb;
	temp.l = lb;
	temp.v = vb;
	temp.p = pb;
	temp.Z = Z;
	temp.K = K;
	pt.push_back(temp);
	double end = lg / l0;
	vector<Point>::iterator iter;
	iter = pt.end() - 1;
	while ((*iter).l <= end)
	{
		temp = Runge_Kutta(*iter, h, Zk, c, B, n, cai, r, u, cais, rs, de, Pp, a);
		pt.push_back(temp);
		iter = pt.end() - 1;
	}
	for (iter = pt.begin(); iter != pt.end(); iter++)
	{
		*iter = Return(*iter, l0, Vj, f, de);
	}
	ofstream outfile("solution.csv", ios::out);
	outfile << "t(s)" << "," << "l(m)" << "," << "v(m/s)" << "," << "p(MPa)" << "," << "K" << "," << "Z" << endl;
	for (iter = pt.begin(); iter != pt.end(); iter++)
	{
		outfile << (*iter).t << "," << (*iter).l << "," << (*iter).v << "," << (*iter).p << "," << (*iter).K << "," << (*iter).Z << endl;
	}
	cout << "�ڵ��������ϣ�" << endl;
}
