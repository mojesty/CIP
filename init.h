#ifndef INIT_H
#define INIT_H

#include "data.h"
#include <math.h>

//TODO: config-файл

cell2d nulls2d() {
	cell2d res;
	res.u=0;
	res.vx=0;
	res.vy=0;
	res.dux=0;
	res.duy=0;
	res.dvx=0;
	res.dvxy=0;
	res.dvy=0;
	res.dvyx=0;
	return res;
}

cell1d nulls1d() {
	cell1d res;
	res.u=0;
	res.vx=0;
	res.dux=0;
	res.dvx=0;
	return res;
}

cell2d rectangle(int x, int y) {
	cell2d res;	
	double xf=(double)(x)/(double)(XMAX);
	double yf = (double)(y)/(double)(YMAX);
	res=nulls2d();
	if ((xf>=0.45) && (xf<=0.55) && (yf>=0.45) && (yf<=0.55))
		res.u=1;
	return res;
}

cell1d rectangle (int x) {
	cell1d res;	
	double xf=(double)(x)/(double)(XMAX);
	res=nulls1d();
	if ((xf>=0.45) && (xf<=0.55))
		res.u=1;
	return res;
}

cell2d circle(int x, int y) { 
	cell2d res;	
	double xf=(double)(x)/(double)(XMAX);
	double yf = (double)(y)/(double)(YMAX);
	res=nulls2d();
	if (xf*xf+yf*yf<=0.01)
		res.u=1;
	return res;
}


#endif //INIT_H
