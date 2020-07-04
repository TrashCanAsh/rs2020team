#pragma once
#include "matrix.h"
#include <vector>
using namespace std;
//���Ƶ�ṹ+��ϵ���ĺ���
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

	//����У��
	//���Ƶ�vector��У������ʽ����
	//���ؾ����СΪ��*��2������һ��Ϊx��ϵ������һ��Ϊy��ϵ����matrix.cpp�еĲ��ԣ���sx2.cpp�е�Ϊ׼��
	matrix GeoCorrection(vector<GcpStruct> ControlPT, int degree);
	//���Ƶ�vector���������x,yϵ����*��2��������
	//���ؾ����СΪ��num,4����ǰ����ΪԤ���x��y,������ΪԤ��x,y�����
	matrix CalError(vector<GcpStruct> ControlPT, matrix Coe, int degree);
};

