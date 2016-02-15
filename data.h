#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>

int XMAX=100;
int YMAX=100;

typedef struct  {
	double u, dux, duy;		//pressure and its spatial derivatives
	double vx, dvx, dvxy;	//X axis velocity and its x and z derivatives
	double vy, dvy, dvyx; 	//Z axis velocity and its z and x derivatives
} cell2d;

typedef struct {
	cell2d ** data;				//Data 2darray
	int x,y; 					//Dimensions
} data2d;

typedef struct  {
	double u, dux;		//pressure and its spatial derivatives
	double vx, dvx;	//X axis velocity and its x and z derivatives
} cell1d;

typedef struct {
	cell1d * data;				//Data 2darray
	int x; 					//Dimensions
} data1d;

/*
typedef struct  {
	double **u, **dux, **duz;		//pressure and its spatial derivatives
	double **vx, **dvx, **dvxz;	//X axis velocity and its x and z derivatives
	double **vz, **dvz, **dvzx; 	//Z axis velocity and its z and x derivatives
	int x,z; 					//Dimensions
} data2d;*/

void save_data(char * path, data2d * d) {
	FILE *f;
	f=fopen (path, "w");
	int i,j;
	for (i=0;i<d->x;i++) {		
		for (j=0;j<d->y;j++) {
			//fprintf(f, "%f\t%f\t%f\n", d->u[i][j], d->vx[i][j], d->vy[i][j]);
			fprintf(f, "%f\t%f\t%f\n", d->data[i][j].u, d->data[i][j].vx, d->data[i][j].vy);
		}
	}
	fclose(f);
}
/*
void free_data(data2d *d) {
	int i;
	for (i=0;i<d->x;i++) {
		free(d->u[i]);
		free(d->dux[i]);
		free(d->duz[i]);
		free(d->vx[i]);
		free(d->dvx[i]);
		free(d->dvxz[i]);
		free(d->vz[i]);
		free(d->dvz[i]);
		free(d->dvzx[i]);
	}
	free(d->u);
	free(d->dux);
	free(d->duz);
	free(d->vx);
	free(d->dvx);
	free(d->dvxz);
	free(d->vz);
	free(d->dvz);
	free(d->dvzx);
}
*/

void free_data(data2d *d) {
	int i;
	for (i=0;i<d->x;i++)
		free(d->data[i]);
	free(d->data);
}

void init_data(data2d *d, int xmax, int ymax,  cell2d(*init)(int x, int y)) {
	d->x=xmax;
	d->y=ymax;
	int i,j;
	d->data=(cell2d**)malloc(xmax*sizeof(cell2d*));
	for (i=0;i<xmax;i++) {
		d->data[i]=(cell2d*)malloc(ymax*sizeof(cell2d));
		for (j=0;j<ymax;j++) {
			d->data[i][j]=(*init)(i,j);
		}
	}
}
		

#endif //DATA_H
