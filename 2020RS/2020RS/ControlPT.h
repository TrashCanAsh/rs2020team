#pragma once
#include "matrix.h"
#include <vector>
using namespace std;
//控制点结构+求系数的函数
struct GcpStruct {
	double baseX;
	double baseY;
	double wrapX;
	double wrapY;
};
class ControlPT
{
public:
	ControlPT();
	~ControlPT();

	//几何校正
	//控制点vector，校正多项式次数
	//返回矩阵大小为（*，2），第一列为x的系数，后一列为y的系数（matrix.cpp中的不对，以sx2.cpp中的为准）
	matrix GeoCorrection(vector<GcpStruct> ControlPT, int degree);
	//控制点vector，解求出的x,y系数（*，2），次数
	//返回矩阵大小为（num,4），前两列为预测的x，y,后两列为预测x,y的误差
	matrix CalError(vector<GcpStruct> ControlPT, matrix Coe, int degree);
};

