#ifndef _PDE_H_
#define _PDE_H_


struct Point
{
	double t;        //ʱ��
	double p;        //ѹ��
	double l;        //�г�
	double v;        //�ٶ�
	double Z;        //��ȼ��Ժ��
	double K;        //ȼȥ�ٷֱ�
};


double FZt(double Z, double Zk, double c, double B, double p, double n);


double FLt(double v);


double FVt(double c, double p);


double FK(double Z, double Zk, double cai, double r, double u, double cais, double rs);


double FP(double lk, double l, double K, double v);
 

double Flk(double de, double Pp, double a, double K);
 

//�Ľ������������
Point Runge_Kutta(Point pt, double h, double Zk, double c, double B, double n, double cai, double r, double u, double cais, double rs, double de, double Pp, double a);


Point Return(Point pt, double l0, double Vj, double f, double de);

#endif