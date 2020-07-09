#pragma once
#include"stdafx.h"
#include <iostream>
#include<cstring>
#include <vector>
#include "gdal/include/gdal_priv.h"
#include "gdal/include/cpl_conv.h"	
#pragma comment(lib,"gdal/gdal_i.lib")
using namespace std;


//��ʹ��int,������WORD
struct PixelPT {
	int x;
	int y;
};

typedef struct tagTIFStruct MyTIFImage;
struct tagTIFStruct
{
	int ImgW;							//Ӱ���
	int ImgH;							//Ӱ���
	int BandNum;						//��������
	UINT16 Back;						//����ֵ
	UINT16 **ImgRAdr;					//R��������
	UINT16 **ImgGAdr;					//G��������
	UINT16 **ImgBAdr;					//B��������
	UINT16 RMin, RMax;					//R��������Ӱ�������Сֵ
	UINT16 GMin, GMax;					//G��������Ӱ�������Сֵ
	UINT16 BMin, BMax;					//B��������Ӱ�������Сֵ
	int   EdRmin, EdRmax;				//R������ʾӰ�������Сֵ
	int   EdGmin, EdGmax;				//G������ʾӰ�������Сֵ
	int   EdBmin, EdBmax;				//B������ʾӰ�������Сֵ
	int   EdMmin, EdMmax;				//M������ʾӰ�������Сֵ
	CString strDescription;
	GDALDataType type;
	GDALDataType eDT;
	double GeoTrans[6];
};

class ReadTIF
{
public:
	ReadTIF();
	~ReadTIF();

	MyTIFImage TifFile;
	

	//��ʼ��BMPλͼ��Ϣ
	BOOL InitBitMapInfo(int nWidth, int nHeight, int colorbit, BITMAPINFO* pinfo);

	//TIFӰ����루�洢�ڽṹ�е�ImgAdr�У�
	BOOL ReadTIFFile(CString FilePath);

	//TIFӰ����루�洢�ں����е�UINT16*InData��,���·�ע��ȥ����ֱ��������������ʾ��һ���εĻҶ�Ӱ�񣬵��Ǵ��ڽ����ƫ����Ҫ������
	//BOOL ReadTIFFile(CString strInImg);

	//ͳ��ÿ�����ε����ֵ��Сֵ
	BOOL GetTIFDataInfo();

	//ע�������ڵ㷨����Ĳ����ڴ���UINT16 *Data������**ImgAdr�洢������ɸ����е�Img_kele�е�����ڵ㷨�����Ĳ������ͼ��ɣ�
	UINT16 NearestNeighbor(float x, float y, int Width, int Height, UINT16 *Data, UINT16 B0);

	//�����λҶ���ʾ
	BOOL DisplayTIFImgColor(HDC *hdc, int DisWidth, int DisHeight, int Disoffx, int Disoffy, int srcWidth, int srcHeight, UINT16 *ImgAdr);

	//��ɫӰ����ʾ
	BOOL DisplayTIFImgColor(HDC *hdc, int DisWidth, int DisHeight, int Disoffx, int Disoffy, int srcWidth, int srcHeight, UINT16 *ImgRAdr, UINT16*ImgGAdr, UINT16 *ImgBAdr);


	//Canopy�Ǽල����
	//�˴���ֱ�ӻὫ�����Ӱ��д�����ļ�
	//�·�ע�ʹ������ֱ��ʹ������Ӱ��������������ʾ������Ҫ����ƫ�Ʋ���������ʾ������ȫ�ڵģ�������ENVI�в鿴���������Ч��������ʱ���T1,T2�кܴ��ϵ��
	BOOL TIFCanopy(CString InFilrPath, CString OutFilrPath, double T1, double T2);

	BOOL ReadTIFOneStar(CString strInImg);
	BOOL CreateBandSpace();
	//����ڵ㷨
	UINT16 NearestNeighbor(float x, float y, int Width, int Height, UINT16 **Data, UINT16 B0);
	BOOL DisplayImgColor(HDC *hdc, int DisWidth, int DisHeight, int Disoffx, int Disoffy, int srcWidth, int srcHeight, int srcoffx, int srcoffy);

	BOOL ReadTIFWH(CString strInImg);
};

