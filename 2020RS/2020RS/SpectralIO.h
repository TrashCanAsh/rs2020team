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
};

class SpectralIO
{
public:
	SpectralIO();
	~SpectralIO();
	static vector<ASDstruct> ASDdata; //����shuju
	BOOL readfile(CString FilePath);
	void delete_data(int nItem);
};
