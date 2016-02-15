#ifndef ONEDIM_H
#define ONEDIM_H

#include "data.h"
#include "schema.h"

double * R_(double *p, double *u, double *zl, double *zr) {
	double * w=(double*)malloc(2*sizeof(double));
	if (!w) return NULL;
	w[0]=(-(*p)+(*zr)*(*u))/((*zl)+(*zr));
	w[1]=((*p)+(*zl)*(*u))/((*zl)+(*zr));
	return w;
}

double * R(double *w1, double *w2, double *zl, double *zr) {
	double * w=(double*)malloc(2*sizeof(double));
	if (!w) return NULL;
	w[0]=(-(*w1)*(*zl)+(*w2)*(*zr));
	w[1]=(*w1)+(*w2);
	return w;
}

void step(data1d *in, data1d *out, double *z, int dt, reconstruct r) {
	int i;
	for (i=0;i<	in->x;i++) {
		
	}

} 

#endif //ONEDIM_H
