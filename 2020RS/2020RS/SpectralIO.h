#pragma once
#include<vector>
#include <fstream>  
#include<iostream>
#include <string> 
using namespace std;

struct PT {
	float xx; //�滭��X������
	float yy;//�滭��Y������
};
struct ASDstruct {
	CString name;
	vector<PT> data;
	float MinRel;//����������Сֵ
	float MaxRel;//�����������ֵ
};

class SpectralIO
{
public:
	SpectralIO();
	~SpectralIO();
	static vector<ASDstruct> ASDdata; //����shuju
	BOOL readfile(CString FilePath);
	void delete_data(int nItem);//����˳��ɾ��
	void del_data(CString delName); //�����ļ�����ɾ��
};

