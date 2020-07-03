#pragma once

#include <iostream>

#define MAXPATH 150
#define UCHAR unsigned char
#define EPSILON 0.00000001

typedef struct tagImageStruct MyImage;
struct tagImageStruct
{
	int ImgW;							//影像宽
	int ImgH;							//影像高
	UCHAR **ImgRAdr;					//R波段数据
	UCHAR **ImgGAdr;					//G波段数据
	UCHAR **ImgBAdr;					//B波段数据
	UCHAR **ImgMAdr;					//M波段数据
	UCHAR RMin, RMax;					//R波段输入影像最大最小值
	UCHAR GMin, GMax;					//G波段输入影像最大最小值
	UCHAR BMin, BMax;					//B波段输入影像最大最小值
	UCHAR MMin, MMax;					//M波段输入影像最大最小值
	int   EdRmin, EdRmax;				//R波段显示影像最大最小值
	int   EdGmin, EdGmax;				//G波段显示影像最大最小值
	int   EdBmin, EdBmax;				//B波段显示影像最大最小值
	int   EdMmin, EdMmax;				//M波段显示影像最大最小值
	char  RName[MAXPATH];				//R波段影像文件名
	char  GName[MAXPATH];				//G波段影像文件名
	char  BName[MAXPATH];				//B波段影像文件名
	char  MName[MAXPATH];				//M波段影像文件名
	int         ImgXoff, ImgYoff;		//相对客户区偏移
	long        DisplayLen;
	int         DisplayWidth, DisplayHeight;//快速显示用
	char        *DisplayData;            //填色用，与遥感影像XOR
	BITMAPINFO  DisplayInfo;             //文件填色用
	int Back;


	//文件格式转换
	BITMAPFILEHEADER BmpFileHeader;
	BITMAPINFOHEADER BmpInfoHeader;
};

class Img_kele
{
public:
	Img_kele();
	~Img_kele();

	MyImage ImgParaInCls;

	BOOL CreateBandSpace();
	BOOL ReleaseBandSpace();
	BOOL ReleaseEveryBand(UCHAR **ImgBandAdr);
	//初始化BMP位图信息
	BOOL InitBitMapInfo(int nWidth, int nHeight, int colorbit, BITMAPINFO* pinfo);
	BOOL InitBitMapFileInfo(int Width, int Height, int colorbit, BITMAPFILEHEADER* pbmfh, BITMAPINFOHEADER* pbmih);
	//开辟影像显示内存
	BOOL CreateDisplaySpace(MyImage *img, int Height, int Width);
	BOOL CreateDisplaySpace(int Height, int Width);

	//彩色显示影像
	//1-2窗口显示（即左下角窗口）
	//待显示影像窗口的hdc，显示宽，显示高，显示窗口偏移x，显示窗口偏移y，源影像数据宽，源影像数据高，源影像数据偏移x，源影像数据偏移y
	BOOL DisplayImgColor(HDC *hdc, int DisWidth, int DisHeight, int Disoffx, int Disoffy,int srcWidth,int srcHeight,int srcoffx,int srcoffy);

	//1-1窗口显示影像（即上方窗口）
	//待显示影像窗口的hdc，显示宽，显示高，offx1=(1-2)中的选择框左下角顶点偏移x，offy1=(1-2)中的选择框左下角顶点偏移y，fac1=max(srcW/DisW,srcH/DisH),fac2=1.0/当前窗口(1-1)边长*上一级窗口(1-2)的选择框边长
	BOOL DisplaySquareImgColor(HDC *hdc, int DisWidth, int DisHeight, int offx, int offy,double fac1,double fac2);
	//1-3窗口显示（即右下角窗口）
	//待显示影像窗口的hdc，显示宽，显示高，offx1=(1-2)中的选择框左下角顶点偏移x，offy1=(1-2)中的选择框左下角顶点偏移y，offx2=(1-1)中选择框左下角顶点偏移x，offy2=(1-1)中选择框左下角顶点偏移y,fac1=max(srcW/DisW,srcH/DisH),fac2=1.0/1-1窗口边长*1-2窗口中选择框边长,fac3=1.0/当前窗口(1-3)边长*上一级窗口(1-1)的选择框边长
	BOOL DisplaySquareImgColor(HDC *hdc, int DisWidth, int DisHeight, int offx1, int offy1, int offx2, int offy2, double fac1, double fac2, double fac3);

	//以下二者可忽略
	//彩色显示影像（数据为UCHAR类型）
	BOOL DisplayImgColor(UCHAR **ImgRBand, UCHAR **ImgGBand, UCHAR **ImgBBand);
	//彩色显示影像（数据为float类型）
	BOOL DisplayImgColor(float *ImgRBand, float *ImgGBand, float *ImgBBand);

	BOOL DisplayImg(CClientDC *dc, MyImage *img);

	//释放影像显示所用内存
	BOOL DeleteDisplaySpace();

	//线性拉伸代码
	BOOL LinearStretch(int Rmin, int Rmax, int Gmin, int Gmax, int Bmin, int Bmax);

	//输入参数为BMP文件路径，及存放文件信息的数据存储位置
	BOOL ReadBmpInfo(CString BmpFilePath);
	BOOL ReadBmpData(CString BmpFilePath);
	//原始功能为BMP写入000控制文件，但其实可以借鉴为检查BMP文件头，并获取BMP影像数据
	BOOL WriteBmpToControlFile(CString BmpFilePath, FILE *fBmp, CString BmpFileName);
	//获取BMP数据的代码
	BOOL WriteBmpToRGBImg(CString BmpFilePath, FILE *fBmp, int Width, int Height, long offBits);

	//JPG文件转为BMP文件
	BOOL WarpJpgToBmp(CString InFilePath);

	//像元重采样
	//最近邻点法
	UCHAR NearestNeighbor(float x, float y, int Width, int Height, UCHAR **Data, UCHAR B0);
	//双线性内插
	UCHAR BilinearInterpolation(float x, float y, int Width, int Height, UCHAR ** Data, UCHAR B0);
	//双三次卷积
	UCHAR CubicConvolution(float x, float y, int Width, int Height, UCHAR ** Data, UCHAR B0);
};

