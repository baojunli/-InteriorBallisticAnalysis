#ifndef _PDE_H_
#define _PDE_H_


struct Point
{
	double t;        //时间
	double p;        //压力
	double l;        //行程
	double v;        //速度
	double Z;        //已燃相对厚度
	double K;        //燃去百分比
};


double FZt(double Z, double Zk, double c, double B, double p, double n);


double FLt(double v);


double FVt(double c, double p);


double FK(double Z, double Zk, double cai, double r, double u, double cais, double rs);


double FP(double lk, double l, double K, double v);
 

double Flk(double de, double Pp, double a, double K);
 

//四阶龙格库塔方程
Point Runge_Kutta(Point pt, double h, double Zk, double c, double B, double n, double cai, double r, double u, double cais, double rs, double de, double Pp, double a);


Point Return(Point pt, double l0, double Vj, double f, double de);

#endif