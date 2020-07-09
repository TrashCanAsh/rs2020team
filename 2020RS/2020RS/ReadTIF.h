#pragma once
#include"stdafx.h"
#include <iostream>
#include<cstring>
#include <vector>
#include "gdal/include/gdal_priv.h"
#include "gdal/include/cpl_conv.h"	
#pragma comment(lib,"gdal/gdal_i.lib")
using namespace std;


//先使用int,再试试WORD
struct PixelPT {
	int x;
	int y;
};

typedef struct tagTIFStruct MyTIFImage;
struct tagTIFStruct
{
	int ImgW;							//影像宽
	int ImgH;							//影像高
	int BandNum;						//波段数量
	UINT16 Back;						//背景值
	UINT16 **ImgRAdr;					//R波段数据
	UINT16 **ImgGAdr;					//G波段数据
	UINT16 **ImgBAdr;					//B波段数据
	UINT16 RMin, RMax;					//R波段输入影像最大最小值
	UINT16 GMin, GMax;					//G波段输入影像最大最小值
	UINT16 BMin, BMax;					//B波段输入影像最大最小值
	int   EdRmin, EdRmax;				//R波段显示影像最大最小值
	int   EdGmin, EdGmax;				//G波段显示影像最大最小值
	int   EdBmin, EdBmax;				//B波段显示影像最大最小值
	int   EdMmin, EdMmax;				//M波段显示影像最大最小值
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
	

	//初始化BMP位图信息
	BOOL InitBitMapInfo(int nWidth, int nHeight, int colorbit, BITMAPINFO* pinfo);

	//TIF影像读入（存储在结构中的ImgAdr中）
	BOOL ReadTIFFile(CString FilePath);

	//TIF影像读入（存储在函数中的UINT16*InData中,将下方注释去除可直接在主界面中显示第一波段的灰度影像，但是窗口界面的偏移需要调整）
	//BOOL ReadTIFFile(CString strInImg);

	//统计每个波段的最大值最小值
	BOOL GetTIFDataInfo();

	//注意此最近邻点法传入的采样内存是UINT16 *Data（若按**ImgAdr存储数据则可改现有的Img_kele中的最近邻点法函数的参数类型即可）
	UINT16 NearestNeighbor(float x, float y, int Width, int Height, UINT16 *Data, UINT16 B0);

	//单波段灰度显示
	BOOL DisplayTIFImgColor(HDC *hdc, int DisWidth, int DisHeight, int Disoffx, int Disoffy, int srcWidth, int srcHeight, UINT16 *ImgAdr);

	//彩色影像显示
	BOOL DisplayTIFImgColor(HDC *hdc, int DisWidth, int DisHeight, int Disoffx, int Disoffy, int srcWidth, int srcHeight, UINT16 *ImgRAdr, UINT16*ImgGAdr, UINT16 *ImgBAdr);


	//Canopy非监督分类
	//此代码直接会将分类后影像写出至文件
	//下方注释代码可以直接使分类后的影像在主界面中显示（但需要调整偏移参数）（显示可能是全黑的，可以在ENVI中查看，具体分类效果和运行时间跟T1,T2有很大关系）
	BOOL TIFCanopy(CString InFilrPath, CString OutFilrPath, double T1, double T2);

	BOOL ReadTIFOneStar(CString strInImg);
	BOOL CreateBandSpace();
	//最近邻点法
	UINT16 NearestNeighbor(float x, float y, int Width, int Height, UINT16 **Data, UINT16 B0);
	BOOL DisplayImgColor(HDC *hdc, int DisWidth, int DisHeight, int Disoffx, int Disoffy, int srcWidth, int srcHeight, int srcoffx, int srcoffy);

	BOOL ReadTIFWH(CString strInImg);
};

