#ifndef ONEDIM_H
#define ONEDIM_H

#include "data.h"
#include "schema.h"

void R_(double *w, double p, double u, double zl, double zr) {
	if (!w) return ;
	w[0]=(-(p)+(zr)*(u))/((zl)+(zr));
	w[1]=((p)+(zl)*(u))/((zl)+(zr));
	//return w;
}

void R(double *w, double w1, double w2, double zl, double zr) {
	if (!w) return ;
	w[0]=(-(w1)*(zl)+(w2)*(zr));
	w[1]=(w1)+(w2);
	//return w;
}


void step1d(cell1d *d, double *z, const int x, const double dt, const double la, const double h, reconstruct r) {
	int i;
	cell1d temp;
	double *w0, *dw0, *w1,*dw1, *w_1,*dw_1;
	
	w0=(double*)malloc(2*sizeof(double));
	dw0=(double*)malloc(2*sizeof(double));
	w1=(double*)malloc(2*sizeof(double));
	dw1=(double*)malloc(2*sizeof(double));
	w_1=(double*)malloc(2*sizeof(double));
	dw_1=(double*)malloc(2*sizeof(double));

	double zl, zr;
	temp=d[0]; //здесь хранится ячейка слева от обсчитываемой в данный момент
	for (i=1;i<x-1;i++) {
		zl=z[i];
		zr=z[i-1];
		R_(w0, d[i].u, d[i].vx, zl, zr);
		R_(w_1, temp.u, temp.vx, zl, zr);
		R_(w1, d[i+1].u, d[i+1].vx, zl, zr);
		R_(dw0, d[i].dux, d[i].dvx, zl, zr);
		R_(dw_1, temp.dux, temp.dvx, zl, zr);
		R_(dw1, d[i+1].dux, d[i+1].dvx, zl, zr);
		
		r(la, h, dt, w1[0], w0[0], dw1[0], dw0[0], &w0[0], &dw0[0]);
		r(la, h, dt, w_1[1], w0[1], dw_1[1], dw0[1], &w0[1], &dw0[1]);		
        
        temp=d[i];
        R(w1, w0[0], w0[1], zl, zr);	//w1=[u, vx]
        R(dw1, dw0[0], dw0[1], zl, zr); //dw1=[dux, dvx]  
        d[i].u=w1[0];
        d[i].vx=w1[1];
        d[i].dux=dw1[0];
        d[i].dvx=dw1[1];      
	}
	free(w0);
	free(dw0);
	free(w1);
	free(dw1);
	free(w_1);
	free(dw_1);
} 

void steps1d(int N, const double dt, const double la, const double h, data1d *d, double *z, reconstruct r) {
	int i;
	for (i=0;i<N;i++) {
		step1d(d->data, z, d->x, dt, la, h, r);
	}
}

#endif //ONEDIM_H
