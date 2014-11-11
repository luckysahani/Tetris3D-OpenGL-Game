#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define X_axis 50
#define Y_axis 51
#define Z_axis 52
#define clkwise 1
#define antclkwise -1


float **rotate(float inp[][4], int dir, int axis, int num){
	float Rx[4][4] = {{1,0,0,0},{0,0,-1*dir,0},{0,1*dir,0,0},{0,0,0,1}};
	float Ry[4][4] = {{0,0,1*dir,0},{0,1,0,0},{-1*dir,0,0,0},{0,0,0,1}};
	float Rz[4][4] = {{0,-1*dir,0,0},{1*dir,0,0,0},{0,0,1,0},{0,0,0,1}};

	float R[4][4];
	switch(axis){
		case X_axis:
			memcpy(R, Rx, sizeof(int) * 4 * 4);
			break;
		case Y_axis:
			memcpy(R, Ry, sizeof(int) * 4 * 4);
			break;
		case Z_axis:
			memcpy(R, Rz, sizeof(int) * 4 * 4);
			break;
		defualt:
			return;
	}
	
	float **res;
	int i,j,k;
	res = (float**)calloc(4,sizeof(float*));
	for(i=0;i<4;i++) res[i] = (float*)calloc(num,sizeof(float));

	float mat[4][num];
	for(i=0;i<4;i++) for(j=0;j<num;j++) mat[i][j] = inp[j][i];
	
	float min=INT_MAX,max=INT_MIN;
	float tx,ty,tz;

	for(i=0;i<num;i++){
		if(mat[0][i]>max) max = mat[0][i];
		if(mat[0][i]<min) min = mat[0][i];
	}
	tx = ((float)max+(float)min)/2;
	min=INT_MAX,max=INT_MIN;
	for(i=0;i<num;i++){
		if(mat[1][i]>max) max = mat[1][i];
		if(mat[1][i]<min) min = mat[1][i];
	}
	ty = ((float)max+(float)min)/2;
	min=INT_MAX,max=INT_MIN;
	for(i=0;i<num;i++){
		if(mat[1][i]>max) max = mat[2][i];
		if(mat[1][i]<min) min = mat[2][i];
	}
	tz = ((float)max+(float)min)/2;
	min=INT_MAX,max=INT_MIN;

	float T[4][4] = {1,0,0,-tx,0,1,0,-ty,0,0,1,-tz,0,0,0,1};	
	float Tb[4][4] = {1,0,0,tx,0,1,0,ty,0,0,1,tz,0,0,0,1};	

	float res2[4][4];
	float res1[4][4];
	for(i=0;i<4;i++) for(j=0;j<4;j++) res2[i][j]=0;
	for(i=0;i<4;i++) for(j=0;j<4;j++) res1[i][j]=0;

	for(i=0;i<4;i++) for(j=0;j<4;j++) for(k=0;k<4;k++) res2[i][j]+=Tb[i][k]*R[k][j];
	for(i=0;i<4;i++) for(j=0;j<4;j++) for(k=0;k<4;k++) res1[i][j]+=res2[i][k]*T[k][j];
	for(i=0;i<4;i++) for(j=0;j<num;j++) for(k=0;k<4;k++) res[i][j]+=res1[i][k]*mat[k][j];

	return res;
}

int main(){
	int num=4;
	float mat[][4] = {{0,0,0,1},{-1,0,0,1},{1,0,0,1},{0,1,0,1}};
	// float mat[][4] = {{0,0,0,1},{2,0,0,1},{2,1,0,1},{0,1,0,1},{0,0,-1,1},{2,0,-1,1},{2,1,-1,1},{0,1,-1,1}};
	float **res = rotate(mat,clkwise,Z_axis,num);
	int i,j;
	for(i=0;i<num;i++){
		for(j=0;j<4;j++) printf("%.1f ",mat[i][j]);
		putchar('\n');
	}
	putchar('\n');
	for(i=0;i<4;i++){
		for(j=0;j<num;j++) printf("%.1f ",res[i][j]);
		putchar('\n');
	}

	return 0;
}
