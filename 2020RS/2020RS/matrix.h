#pragma once
//#include"ControlPT.h"
//================================================================
//更新时间：2020.5.21
//================================================================

class matrix
{
public:
	int row;
	int col;
	double **mat=NULL;
	
	//函数部分
	matrix();
	~matrix();
	matrix(int r, int c, double val = 0.0);
	matrix(const  matrix& b);
	void MatrixPrint();
	matrix operator*(matrix b);
	matrix operator-(matrix b);
	matrix operator+(matrix b);
	matrix& operator+=(matrix b);
	matrix& operator=(const matrix& b);
	matrix trans();//矩阵转置
	matrix inv();//矩阵求逆(列主元消元法)
	matrix identity(int n);//单位矩阵
	matrix RowConcat(matrix b);//矩阵行连接
	matrix ColConcat(matrix b);//矩阵列连接
	double MaxAbsElement();//找出矩阵中绝对值最大的元素

};

