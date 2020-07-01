#pragma once
#include<vector>
#include <fstream>  
#include<iostream>
#include <string> 
using namespace std;

struct PT {
	float xx; //绘画的X轴数据
	float yy;//绘画的Y轴数据
};
struct ASDstruct {
	CString name;
	vector<PT> data;
	float MinRel;//单条光谱最小值
	float MaxRel;//单条光谱最大值
};

class SpectralIO
{
public:
	SpectralIO();
	~SpectralIO();
	static vector<ASDstruct> ASDdata; //光谱shuju
	BOOL readfile(CString FilePath);
	void delete_data(int nItem);//按照顺序删除
	void del_data(CString delName); //按照文件名字删除
};

