#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#define X_axis 50
#define Y_axis 51
#define Z_axis 52
#define clkwise 1
#define antclkwise -1


int **rotate(int inp[][4], int dir, int axis, int num){
	int Rx[4][4] = {{1,0,0,0},{0,0,-1*dir,0},{0,1*dir,0,0},{0,0,0,1}};
	int Ry[4][4] = {{0,0,1*dir,0},{0,1,0,0},{-1*dir,0,0,0},{0,0,0,1}};
	int Rz[4][4] = {{0,-1*dir,0,0},{1*dir,0,0,0},{0,0,1,0},{0,0,0,1}};

	int R[4][4];
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
	
	int **res;
	int i,j,k;
	res = (int**)calloc(4,sizeof(int*));
	for(i=0;i<4;i++) res[i] = (int*)calloc(num,sizeof(int));

	int mat[4][num];
	for(i=0;i<4;i++) for(j=0;j<num;j++) mat[i][j] = inp[j][i];
	for(i=0;i<4;i++){
		for(j=0;j<num;j++) printf("%d ",mat[i][j]);
		putchar('\n');
	}
	putchar('\n');
	
	int min=INT_MAX,max=INT_MIN;
	int tx,ty,tz;

	for(i=0;i<num;i++){
		if(mat[0][i]>max) max = mat[0][i];
		if(mat[0][i]<min) min = mat[0][i];
	}
	tx = (max+min)/2;
	min=INT_MAX,max=INT_MIN;
	for(i=0;i<num;i++){
		if(mat[1][i]>max) max = mat[1][i];
		if(mat[1][i]<min) min = mat[1][i];
	}
	ty = (max+min)/2;
	min=INT_MAX,max=INT_MIN;
	for(i=0;i<num;i++){
		if(mat[1][i]>max) max = mat[2][i];
		if(mat[1][i]<min) min = mat[2][i];
	}
	tz = (max+min)/2;
	min=INT_MAX,max=INT_MIN;
	//printf("%d %d %d\n",tx,ty,tz);

	int T[4][4] = {1,0,0,-tx,0,1,0,-ty,0,0,1,-tz,0,0,0,1};	
	int Tb[4][4] = {1,0,0,tx,0,1,0,ty,0,0,1,tz,0,0,0,1};	

	int res2[4][4];
	int res1[4][4];
	for(i=0;i<4;i++) for(j=0;j<4;j++) res2[i][j]=0;
	for(i=0;i<4;i++) for(j=0;j<4;j++) res1[i][j]=0;

	for(i=0;i<4;i++) for(j=0;j<4;j++) for(k=0;k<4;k++) res2[i][j]+=Tb[i][k]*R[k][j];
	for(i=0;i<4;i++) for(j=0;j<4;j++) for(k=0;k<4;k++) res1[i][j]+=res2[i][k]*T[k][j];
	for(i=0;i<4;i++) for(j=0;j<num;j++) for(k=0;k<4;k++) res[i][j]+=res1[i][k]*mat[k][j];
	//for(i=0;i<4;i++){
	//	for(j=0;j<4;j++) printf("%d ",R[i][j]);
	//	putchar('\n');
	//}
	//putchar('\n');

	return res;
}

int main(){
	int num=4;
	int mat[][4] = {{6,1,6,1},{7,1,6,1},{6,2,6,1},{7,2,6,1}};
	int **res = rotate(mat,antclkwise,Z_axis,num);
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<num;j++) printf("%d ",res[i][j]);
		putchar('\n');
	}

	return 0;
}
