#pragma once

#include <iostream>
#include <vector>
#include "matrix.h"
using namespace std;
#define MAXPATH 150
#define UCHAR unsigned char
#define EPSILON 0.00000001

typedef struct tagImageStruct MyImage;
struct tagImageStruct
{
	int ImgW;							//Ӱ���
	int ImgH;							//Ӱ���
	UCHAR **ImgRAdr;					//R��������
	UCHAR **ImgGAdr;					//G��������
	UCHAR **ImgBAdr;					//B��������
	UCHAR **ImgMAdr;					//M��������
	UCHAR RMin, RMax;					//R��������Ӱ�������Сֵ
	UCHAR GMin, GMax;					//G��������Ӱ�������Сֵ
	UCHAR BMin, BMax;					//B��������Ӱ�������Сֵ
	UCHAR MMin, MMax;					//M��������Ӱ�������Сֵ
	int   EdRmin, EdRmax;				//R������ʾӰ�������Сֵ
	int   EdGmin, EdGmax;				//G������ʾӰ�������Сֵ
	int   EdBmin, EdBmax;				//B������ʾӰ�������Сֵ
	int   EdMmin, EdMmax;				//M������ʾӰ�������Сֵ
	//char  RName[MAXPATH];				//R����Ӱ���ļ���
	//char  GName[MAXPATH];				//G����Ӱ���ļ���
	//char  BName[MAXPATH];				//B����Ӱ���ļ���
	//char  MName[MAXPATH];				//M����Ӱ���ļ���
	int         ImgXoff, ImgYoff;		//��Կͻ���ƫ��
	long        DisplayLen;
	int         DisplayWidth, DisplayHeight;//������ʾ��
	char        *DisplayData;            //��ɫ�ã���ң��Ӱ��XOR
	BITMAPINFO  DisplayInfo;             //�ļ���ɫ��
	int Back;//����ֵ
	//ֱ��ͼ
	float HistoR[256];//�洢�ûҶ�ֵ��Ԫ����ռ����Ԫ���ı���
	float HistoG[256];
	float HistoB[256];
	float HismaxR;
	float HismaxG;
	float HismaxB;

	//�Ǽල������
	int ClassNum;
	UCHAR **Classify;
	vector<int> ClassInfo;


	//�ļ���ʽת��
	BITMAPFILEHEADER BmpFileHeader;
	BITMAPINFOHEADER BmpInfoHeader;
};


//�Ǽල�����������
typedef struct tagCanopyStruct MyCanopy;
struct tagCanopyStruct {
	int x, y;
	double Sumx, Sumy;
	int Count;
};

class Img_kele
{
public:
	Img_kele();
	~Img_kele();

	Img_kele(const Img_kele &CopyImg);//��������
	MyImage ImgParaInCls;
	

	BOOL CreateBandSpace();
	BOOL ReleaseBandSpace();
	BOOL ReleaseEveryBand(UCHAR **ImgBandAdr);
	//��ʼ��BMPλͼ��Ϣ
	BOOL InitBitMapInfo(int nWidth, int nHeight, int colorbit, BITMAPINFO* pinfo);
	BOOL InitBitMapFileInfo(int Width, int Height, int colorbit, BITMAPFILEHEADER* pbmfh, BITMAPINFOHEADER* pbmih);
	//����Ӱ����ʾ�ڴ�
	BOOL CreateDisplaySpace(MyImage *img, int Height, int Width);
	BOOL CreateDisplaySpace(int Height, int Width);

	//��ɫ��ʾӰ��
	//1-2������ʾ�������½Ǵ��ڣ�
	//����ʾӰ�񴰿ڵ�hdc����ʾ����ʾ�ߣ���ʾ����ƫ��x����ʾ����ƫ��y��ԴӰ�����ݿ�ԴӰ�����ݸߣ�ԴӰ������ƫ��x��ԴӰ������ƫ��y
	BOOL DisplayImgColor(HDC *hdc, int DisWidth, int DisHeight, int Disoffx, int Disoffy,int srcWidth,int srcHeight,int srcoffx,int srcoffy);

	//1-1������ʾӰ�񣨼��Ϸ����ڣ�
	//����ʾӰ�񴰿ڵ�hdc����ʾ����ʾ�ߣ�offx1=(1-2)�е�ѡ������Ͻ����꣬offy1=(1-2)�е�ѡ������Ͻ�����y��fac1=max(srcW/DisW,srcH/DisH),fac2=1.0/��ǰ����(1-1)�߳�*��һ������(1-2)��ѡ���߳�
	BOOL DisplaySquareImgColor(HDC *hdc, int DisWidth, int DisHeight, int offx, int offy,double fac1,double fac2);
	//1-3������ʾ�������½Ǵ��ڣ�
	//����ʾӰ�񴰿ڵ�hdc����ʾ����ʾ�ߣ�offx1=(1-2)�е�ѡ������Ͻ����꣬offy1=(1-2)�е�ѡ������Ͻ�����y��offx2=(1-1)��ѡ������Ͻ�����x��offy2=(1-1)��ѡ������Ͻ�����y,fac1=max(srcW/DisW,srcH/DisH),fac2=1.0/1-1���ڱ߳�*1-2������ѡ���߳�,fac3=1.0/��ǰ����(1-3)�߳�*��һ������(1-1)��ѡ���߳�
	BOOL DisplaySquareImgColor(HDC *hdc, int DisWidth, int DisHeight, int offx1, int offy1, int offx2, int offy2, double fac1, double fac2, double fac3);

	//���¶��߿ɺ���
	//��ɫ��ʾӰ������ΪUCHAR���ͣ�
	BOOL DisplayImgColor(UCHAR **ImgRBand, UCHAR **ImgGBand, UCHAR **ImgBBand);
	//��ɫ��ʾӰ������Ϊfloat���ͣ�
	BOOL DisplayImgColor(float *ImgRBand, float *ImgGBand, float *ImgBBand);

	BOOL DisplayImg(CClientDC *dc, MyImage *img);

	//�ͷ�Ӱ����ʾ�����ڴ�
	BOOL DeleteDisplaySpace();

	//�����������
	BOOL LinearStretch(int Rmin, int Rmax, int Gmin, int Gmax, int Bmin, int Bmax);

	//�������ΪBMP�ļ�·����������ļ���Ϣ�����ݴ洢λ��
	BOOL ReadBmpInfo(CString BmpFilePath);
	BOOL ReadBmpData(CString BmpFilePath);
	//ԭʼ����ΪBMPд��000�����ļ�������ʵ���Խ��Ϊ���BMP�ļ�ͷ������ȡBMPӰ������
	BOOL WriteBmpToControlFile(CString BmpFilePath, FILE *fBmp, CString BmpFileName);
	//��ȡBMP���ݵĴ���
	BOOL WriteBmpToRGBImg(CString BmpFilePath, FILE *fBmp, int Width, int Height, long offBits);

	//JPG�ļ�תΪBMP�ļ�
	BOOL WarpJpgToBmp(CString InFilePath);

	//��Ԫ�ز���
	//����ڵ㷨
	UCHAR NearestNeighbor(float x, float y, int Width, int Height, UCHAR **Data, UCHAR B0);
	//˫�����ڲ�
	UCHAR BilinearInterpolation(float x, float y, int Width, int Height, UCHAR ** Data, UCHAR B0);
	//˫���ξ��
	UCHAR CubicConvolution(float x, float y, int Width, int Height, UCHAR ** Data, UCHAR B0);

	//����У�����Ӱ��
	//X��ϵ������Y��ϵ�����󣬴�У��Ӱ�����У��Ӱ��ߣ��ز���ʱʹ�ã�����У��Ӱ��R���ε�ַ����У��Ӱ��G���ε�ַ����У��Ӱ��B���ε�ַ���ز�����ʽ���ļ�·��
	BOOL OutputCorrRes(matrix CoeX, matrix CoeY, int Width, int Height, UCHAR**ImgRAdr, UCHAR**ImgGAdr, UCHAR**ImgBAdr, int flag,int degree, CString FilePath);
	//ͳ��Ӱ��������Ϣ//����Ӱ��������Сֵ�Լ�ֱ��ͼ����ͳ��
	//����ͳ����Ϣ�������ڵ�ImgParaInCls���ݽṹ�У�����ֱ��ͼ�д�ŵĲ��Ǿ������������ռ����Ԫ�İٷֱȣ�
	BOOL ReadImgDataImfo();
	//����ܶȷָ��ļ�
	//BMP�ļ����ݵ�ַ������ļ�·��
	BOOL OutputDensitySlicingAsBMP(UCHAR *ImgAdr, CString FilePath);

	//�Ǽල����
	//ĿǰCanopy�㷨������ֱ��ִ��KMeans�㷨
	//T1��T2��T1>T2��MaxIterateTimeΪ����������
	BOOL Canopy(double T1, double T2, int MaxIterateTime);
	BOOL DisplayImgGray(HDC *hdc, int DisWidth, int DisHeight, int Disoffx, int Disoffy, int srcWidth, int srcHeight, int srcoffx, int srcoffy, UCHAR **ImgAdr);
	BOOL CreateClassifySpace();

};

