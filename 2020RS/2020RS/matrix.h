#pragma once
//#include"ControlPT.h"
//================================================================
//����ʱ�䣺2020.5.21
//================================================================

class matrix
{
public:
	int row;
	int col;
	double **mat=NULL;
	
	//��������
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
	matrix trans();//����ת��
	matrix inv();//��������(����Ԫ��Ԫ��)
	matrix identity(int n);//��λ����
	matrix RowConcat(matrix b);//����������
	matrix ColConcat(matrix b);//����������
	double MaxAbsElement();//�ҳ������о���ֵ����Ԫ��

};

