#include "PDE.h"
#include <math.h>

double FZt(double Z, double Zk, double c, double B, double p, double n)
{
	if (Z < Zk)
		return (sqrt(c / (2 * B))*pow(p, n));
	if (Z >= Zk)
		return 0;
}


double FLt(double v)
{
	return v;
}

double FVt(double c, double p)
{
	return (c*p / 2);
}

double FK(double Z, double Zk, double cai, double r, double u, double cais, double rs)
{
	if (Z < 1)
		return cai*Z*(1 + r*Z + u*Z*Z);
	if (Z >= 1 && Z < Zk)
		return cais*Z*(1 + rs*Z);
	if (Z >= Zk)
		return 1;
}

double FP(double lk, double l, double K, double v)
{
	return (K - v*v) / (lk + l);
}

double Flk(double de, double Pp, double a, double K)
{
	return 1 - de / Pp - (a - 1 / Pp)*de*K;
}


//四阶龙格库塔方程
Point Runge_Kutta(Point pt, double h, double Zk, double c, double B, double n, double cai, double r, double u, double cais, double rs, double de, double Pp, double a)
{
	double kz1 = h*FZt(pt.Z, Zk, c, B, pt.p, n);
	double kl1 = h*FLt(pt.v);
	double kv1 = h*FVt(c, pt.p);
	double K2 = FK(pt.Z + kz1 / 2, Zk, cai, r, u, cais, rs);
	double lk2 = Flk(de, Pp, a, K2);
	double p2 = FP(lk2, pt.l + kl1 / 2, K2, pt.v + kv1 / 2);
	double kz2 = h*FZt(pt.Z + kz1 / 2, Zk, c, B, p2, n);
	double kl2 = h*FLt(pt.v + kv1 / 2);
	double kv2 = h*FVt(c, p2);
	double K3 = FK(pt.Z + kz2 / 2, Zk, cai, r, u, cais, rs);
	double lk3 = Flk(de, Pp, a, K3);
	double p3 = FP(lk3, pt.l + kl2 / 2, K3, pt.v + kv2 / 2);
	double kz3 = h*FZt(pt.Z + kz2 / 2, Zk, c, B, p3, n);
	double kl3 = h*FLt(pt.v + kv2 / 2);
	double kv3 = h*FVt(c, p3);
	double K4 = FK(pt.Z + K3, Zk, cai, r, u, cais, rs);
	double lk4 = Flk(de, Pp, a, K4);
	double p4 = FP(lk4, pt.l + kl3, K4, pt.v + kv3);
	double kz4 = h*FZt(pt.Z + kz3, Zk, c, B, p4, n);
	double kl4 = h*FLt(pt.v + kv3);
	double kv4 = h*FVt(c, p4);
	Point next;
	next.Z = pt.Z + (kz1 + 2 * kz2 + 2 * kz3 + kz4) / 6;
	next.l = pt.l + (kl1 + 2 * kl2 + 2 * kl3 + kl4) / 6;
	next.v = pt.v + (kv1 + 2 * kv2 + 2 * kv3 + kv4) / 6;
	next.K = FK(next.Z, Zk, cai, r, u, cais, rs);
	double lk0 = Flk(de, Pp, a, next.K);
	next.p = FP(lk0, next.l, next.K, next.v);
	next.t = pt.t + h;
	return next;
}

Point Return(Point pt, double l0, double Vj, double f, double de)
{
	Point red;
	red.l = pt.l*l0;
	red.t = pt.t*l0 / Vj;
	red.p = pt.p*f*de;
	red.v = pt.v*Vj;
	red.K = pt.K;
	red.Z = pt.Z;
	return red;
}