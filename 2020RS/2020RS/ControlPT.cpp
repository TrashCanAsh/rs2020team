#include "stdafx.h"
#include "ControlPT.h"
#include <vector>
#include <iostream>
using namespace std;


ControlPT::ControlPT()
{
}


ControlPT::~ControlPT()
{
}

matrix ControlPT::GeoCorrection(vector<GcpStruct> ControlPT, int degree)
{
	//用最小二乘法解求系数
	if (degree == 1)
	{
		//一次多项式
		//AX=B
		matrix Coefficient(3, 3);
		matrix Xx(3, 1);
		matrix Xy(3, 1);
		matrix Bx(3, 1);
		matrix By(3, 1);
		for (std::vector<GcpStruct>::iterator it = ControlPT.begin(); it != ControlPT.end(); ++it)
		{
			double u = (*it).baseX; double u2 = (*it).baseX*(*it).baseX;
			double v = (*it).baseY; double v2 = (*it).baseY*(*it).baseY;

			//A的计算
			Coefficient.mat[0][0]++; Coefficient.mat[0][1] += u; Coefficient.mat[0][2] += v;
			Coefficient.mat[1][0] += u; Coefficient.mat[1][1] += u2; Coefficient.mat[1][2] += u * v;
			Coefficient.mat[2][0] += v; Coefficient.mat[2][1] += u * v; Coefficient.mat[2][2] += v2;

			//B的计算
			Bx.mat[0][0] += (*it).wrapX; Bx.mat[1][0] += (*it).wrapX*u; Bx.mat[2][0] += (*it).wrapX*v;
			By.mat[0][0] += (*it).wrapY; By.mat[1][0] += (*it).wrapY*u; By.mat[2][0] += (*it).wrapY*v;
		}
		//解求系数
		Xx = Coefficient.inv()*Bx;
		Xy = Coefficient.inv()*By;

		//前三个为x的系数，后三个为y的系数
		matrix X(3, 2);
		for (int ii = 0; ii < 3; ii++)
		{
			X.mat[ii][0] = Xx.mat[ii][0];
			X.mat[ii][1] = Xy.mat[ii][0];
		}

		return X;
	}
	else if (degree == 2)
	{
		//二次多项式
		//AX=B
		matrix Coefficient(6, 6);
		matrix Xx(6, 1);
		matrix Xy(6, 1);
		matrix Bx(6, 1);
		matrix By(6, 1);
		for (std::vector<GcpStruct>::iterator it = ControlPT.begin(); it != ControlPT.end(); ++it)
		{
			double u = (*it).baseX; double u2 = (*it).baseX*(*it).baseX; double u3 = (*it).baseX*(*it).baseX*(*it).baseX; double u4 = (*it).baseX*(*it).baseX*(*it).baseX*(*it).baseX;
			double v = (*it).baseY; double v2 = (*it).baseY*(*it).baseY; double v3 = (*it).baseY*(*it).baseY*(*it).baseY; double v4 = (*it).baseY*(*it).baseY*(*it).baseY*(*it).baseY;

			//A的计算
			Coefficient.mat[0][0]++; Coefficient.mat[0][1] += u; Coefficient.mat[0][2] += v; Coefficient.mat[0][3] += u2; Coefficient.mat[0][4] += u * v; Coefficient.mat[0][5] += v2;
			Coefficient.mat[1][0] += u; Coefficient.mat[1][1] += u2; Coefficient.mat[1][2] += u * v; Coefficient.mat[1][3] += u3; Coefficient.mat[1][4] += u2 * v; Coefficient.mat[1][5] += u * v2;
			Coefficient.mat[2][0] += v; Coefficient.mat[2][1] += u * v; Coefficient.mat[2][2] += v2; Coefficient.mat[2][3] += u2 * v; Coefficient.mat[2][4] += u * v2; Coefficient.mat[2][5] += v3;
			Coefficient.mat[3][0] += u2; Coefficient.mat[3][1] += u3; Coefficient.mat[3][2] += u2 * v; Coefficient.mat[3][3] += u4; Coefficient.mat[3][4] += u3 * v; Coefficient.mat[3][5] += u2 * v2;
			Coefficient.mat[4][0] += u * v; Coefficient.mat[4][1] += u2 * v; Coefficient.mat[4][2] += u * v2; Coefficient.mat[4][3] += u3 * v; Coefficient.mat[4][4] += u2 * v2; Coefficient.mat[4][5] += u * v3;
			Coefficient.mat[5][0] += v2; Coefficient.mat[5][1] += u * v2; Coefficient.mat[5][2] += v3; Coefficient.mat[5][3] += u2 * v2; Coefficient.mat[5][4] += u * v3; Coefficient.mat[5][5] += v4;

			//B的计算
			Bx.mat[0][0] += (*it).wrapX; Bx.mat[1][0] += (*it).wrapX*u; Bx.mat[2][0] += (*it).wrapX*v; Bx.mat[3][0] += (*it).wrapX*u2; Bx.mat[4][0] += (*it).wrapX*u*v; Bx.mat[5][0] += (*it).wrapX*v2;
			By.mat[0][0] += (*it).wrapY; By.mat[1][0] += (*it).wrapY*u; By.mat[2][0] += (*it).wrapY*v; By.mat[3][0] += (*it).wrapY*u2; By.mat[4][0] += (*it).wrapY*u*v; By.mat[5][0] += (*it).wrapY*v2;
		}
		//解求系数
		Xx = Coefficient.inv()*Bx;
		Xy = Coefficient.inv()*By;

		//前六个为x的系数，后六个为y的系数
		matrix X(6, 2);
		for (int ii = 0; ii < 6; ii++)
		{
			X.mat[ii][0] = Xx.mat[ii][0];
			X.mat[ii][1] = Xy.mat[ii][0];
		}

		return X;
	}
	else
	{
		cout << "多项式次数超过2次！！！";
		return matrix(1, 1);
	}

	return matrix();
}
matrix ControlPT::CalError(vector<GcpStruct> ControlPT, matrix Coe, int degree)
{
	int num = ControlPT.size();
	matrix PredAndError(num, 5);
	matrix pred(1, 2);
	int count = 0;

	if (degree == 1)
	{
		double u, v;
		//u,v组成的矩阵
		matrix A(1, 3);
		for (std::vector<GcpStruct>::iterator it = ControlPT.begin(); it != ControlPT.end(); ++it)
		{
			u = (*it).baseX;
			v = (*it).baseY;

			A.mat[0][0] = 1; A.mat[0][1] = u; A.mat[0][2] = v;
			pred = A * Coe;
			PredAndError.mat[count][0] = pred.mat[0][0];
			PredAndError.mat[count][1] = pred.mat[0][1];
			PredAndError.mat[count][2] = (*it).wrapX - pred.mat[0][0];
			PredAndError.mat[count][3] = (*it).wrapY - pred.mat[0][1];
			PredAndError.mat[count][4] = sqrt(PredAndError.mat[count][2] * PredAndError.mat[count][2] + PredAndError.mat[count][3] * PredAndError.mat[count][3]);

			count++;

		}

		return PredAndError;
	}
	else if (degree == 2)
	{
		double u, v, u2, v2;
		//u,v组成的矩阵
		matrix A(1, 6);
		for (std::vector<GcpStruct>::iterator it = ControlPT.begin(); it != ControlPT.end(); ++it)
		{
			u = (*it).baseX; u2 = (*it).baseX*(*it).baseX;
			v = (*it).baseY; v2 = (*it).baseY*(*it).baseY;

			A.mat[0][0] = 1; A.mat[0][1] = u; A.mat[0][2] = v; A.mat[0][3] = u2; A.mat[0][4] = u * v; A.mat[0][5] = v2;
			pred = A * Coe;

			PredAndError.mat[count][0] = pred.mat[0][0];
			PredAndError.mat[count][1] = pred.mat[0][1];
			PredAndError.mat[count][2] = (*it).wrapX - pred.mat[0][0];
			PredAndError.mat[count][3] = (*it).wrapY - pred.mat[0][1];
			PredAndError.mat[count][4] = sqrt(PredAndError.mat[count][2] * PredAndError.mat[count][2] + PredAndError.mat[count][3] * PredAndError.mat[count][3]);

			count++;
		}
		return PredAndError;
	}
	else
	{
		cout << "多项式系数选择错误！" << endl;
	}

	return matrix();
}

double ControlPT::CalTotalError(matrix CalError, int num)
{
	double TotalError = 0;
	for (int ii = 0; ii < num; ii++)
	{
		TotalError += CalError.mat[ii][2] * CalError.mat[ii][2] + CalError.mat[ii][3] * CalError.mat[ii][3];
	}
	TotalError = sqrt(TotalError / double(num));
	return TotalError;
}
