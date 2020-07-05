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
	//����õ�����ʽ��ϵ�ϵ��
	//���Ƶ�vector��У������ʽ����
	//���ؾ����СΪ��*��2������һ��Ϊx��ϵ������һ��Ϊy��ϵ��
	matrix GeoCorrection(vector<GcpStruct> ControlPT, int degree);
	//����ÿ�����Ƶ�
	//���Ƶ�vector���������x,yϵ����*��2��������
	//���ؾ����СΪ��num,5����ǰ����ΪԤ���x��y,������ΪԤ��x,y����������Ϊ�������RMS��sqrt(xԤ�����ƽ��+yԤ�����ƽ��)
	matrix CalError(vector<GcpStruct> ControlPT, matrix Coe, int degree);
	//���㵱ǰ���п��Ƶ������RMS
	//CalError��������õ��Ľ�������Ƶ�����
	//��������RMS
	double CalTotalError(matrix CalError, int num);
};

