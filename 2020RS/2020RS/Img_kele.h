#pragma once

#include <iostream>

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
	char  RName[MAXPATH];				//R����Ӱ���ļ���
	char  GName[MAXPATH];				//G����Ӱ���ļ���
	char  BName[MAXPATH];				//B����Ӱ���ļ���
	char  MName[MAXPATH];				//M����Ӱ���ļ���
	int         ImgXoff, ImgYoff;		//��Կͻ���ƫ��
	long        DisplayLen;
	int         DisplayWidth, DisplayHeight;//������ʾ��
	char        *DisplayData;            //��ɫ�ã���ң��Ӱ��XOR
	BITMAPINFO  DisplayInfo;             //�ļ���ɫ��
	int Back;


	//�ļ���ʽת��
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
	//��ʼ��BMPλͼ��Ϣ
	BOOL InitBitMapInfo(int nWidth, int nHeight, int colorbit, BITMAPINFO* pinfo);
	BOOL InitBitMapFileInfo(int Width, int Height, int colorbit, BITMAPFILEHEADER* pbmfh, BITMAPINFOHEADER* pbmih);
	//����Ӱ����ʾ�ڴ�
	BOOL CreateDisplaySpace(MyImage *img, int Height, int Width);
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
};

