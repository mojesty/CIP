#ifndef SCHEMA_H
#define SCHEMA_H

#define MIN(a, b) (((a)<(b))?(a):(b))
#define MAX(a, b) (((a)>(b))?(a):(b))
#define ABS(a) ((a) > 0 ? (a) : (-(a)))

typedef void (*reconstruct)(const double, const double, const double, const double, const double, const double, const double, double *, double *);

void none(const double la, const double h, const double dt, const double u1, const double u0, const double v1, const double v0, double *u, double *v)
{
}

void cir(const double la, const double h, const double dt, const double u1, const double u0, const double v1, const double v0, double *u, double *v)
{
	double c = la * dt / h;
	*u = u0 - c * (u0 - u1);
	*v = (u0 - u1) / h;
}

void cip(const double la, const double h, const double dt, const double u1, const double u0, const double v1, const double v0, double *u, double *v)
{
	const double delta0 = u0 - u1;
	const double a = (v0 + v1) / h / h - 2.0 * delta0 / h / h / h;
	const double b = (2.0 * v0 + v1) / h - 3.0 * delta0 / h / h;
	const double c = v0;
	const double d = u0;
	const double x = -la * dt;
	*u = a * x * x * x + b * x * x + c * x + d;
	*v = 3.0 * a * x * x + 2.0 * b * x + c;
}


void cip2l(const double la, const double h, const double dt, const double u1, const double u0, const double v1, const double v0, double *u, double *v)
{
	const double k = la * dt / h;
	const double delta0 = u1 - u0;
	const double d1 = delta0 + h * v1;
	*u = u0 + 2.0 * k * delta0 + h * k * v1 - k * k * d1;
	*v = -v1 - 2.0 / h * delta0 + 2.0 * k / h * d1;
}

void cip2r(const double la, const double h, const double dt, const double u1, const double u0, const double v1, const double v0, double *u, double *v)
{
	const double k = la * dt / h;
	const double delta0 = u1 - u0;
	const double d1 = delta0 + h * v0;
	*u = u0 - h * k * v0 + k * k * d1;
	*v = v0 - 2.0 * k / h * d1;
}

void bis1(const double la, const double h, const double dt, const double u1, const double u0, const double v1, const double v0, double *u, double *v)
{
	cip(la, h, dt, u1, u0, v1, v0, u, v);
	
	if ((*u) < MIN(u0, u1) || (*u) > MAX(u0, u1)) {
		cip2l(la, h, dt, u1, u0, v1, v0, u, v);
	}
	if ((*u) < MIN(u0, u1) || (*u) > MAX(u0, u1)) {
		cip2r(la, h, dt, u1, u0, v1, v0, u, v);
	}
	if ((*u) < MIN(u0, u1) || (*u) > MAX(u0, u1)) {
		cir(la, h, dt, u1, u0, v1, v0, u, v);
	}
}

void bis2(const double la, const double h, const double dt, const double u1, const double u0, const double v1, const double v0, double *u, double *v)
{
	const double nu = (u0 - u1) / h;
	const double d0 = ABS(nu - v0);
	const double d_1 = ABS(nu - v1);
		
	const double a = (v0 + v1) / h / h - 2.0 * (u0 - u1) / h / h / h;
	const double b = (2.0 * v0 + v1) / h - 3.0 * (u0 - u1) / h / h;
	const double c = v0;
	const double d = u0;
		
	const double x0 = - b / 2 / (a + 1e-6);
	const double f0 = 3.0 * a * x0 * x0 + 2.0 * b * x0 + c;

	if (v0 * v1 >= 0 && nu * v0 >= 0) {
		if (x0 > -h && x0 < 0 && f0 * nu < 0) {
			if (MIN(v0, v1) < nu < MAX(v0, v1)) {
				cir(la, h, dt, u1, u0, v1, v0, u, v);
			} else {
				if (d0 > d_1) {
					cip2l(la, h, dt, u1, u0, v1, v0, u, v);
				} else {
					cip2r(la, h, dt, u1, u0, v1, v0, u, v);
				}
			}
		} else {
			cip(la, h, dt, u1, u0, v1, v0, u, v);
		}
	} else if (v0 * v1 >= 0 && nu * v0 < 0) {
		cir(la, h, dt, u1, u0, v1, v0, u, v);
	} else {
		if (d0 > d_1) {
			cip2l(la, h, dt, u1, u0, v1, v0, u, v);
		} else {
			cip2r(la, h, dt, u1, u0, v1, v0, u, v);
		}
	}
}

#endif // SCHEMA_H

