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
	//计算得到多项式拟合的系数
	//控制点vector，校正多项式次数
	//返回矩阵大小为（*，2），第一列为x的系数，后一列为y的系数
	matrix GeoCorrection(vector<GcpStruct> ControlPT, int degree);
	//计算每个控制点
	//控制点vector，解求出的x,y系数（*，2），次数
	//返回矩阵大小为（num,5），前两列为预测的x，y,后两列为预测x,y的误差，第五列为单个点的RMS即sqrt(x预测误差平方+y预测误差平方)
	matrix CalError(vector<GcpStruct> ControlPT, matrix Coe, int degree);
	//计算当前所有控制点的整体RMS
	//CalError函数计算得到的结果，控制点数量
	//返回总体RMS
	double CalTotalError(matrix CalError, int num);
};

