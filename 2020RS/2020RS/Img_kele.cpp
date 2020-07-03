#include "stdafx.h"
#include "Img_kele.h"
using namespace std;

Img_kele::Img_kele()
{
}


Img_kele::~Img_kele()
{
}

//����Ԫ��˹��Ԫ����matrix����ʵ��

//�����ڴ�ռ䣨����Ӱ��ʱʹ�ã�
BOOL Img_kele::CreateBandSpace()
{
	cout << "���������ڴ��ImgH:";
	cout << ImgParaInCls.ImgH << endl;
	ImgParaInCls.ImgRAdr = new UCHAR *[ImgParaInCls.ImgH]; memset(ImgParaInCls.ImgRAdr, 0, ImgParaInCls.ImgH * sizeof(UCHAR*));
	ImgParaInCls.ImgGAdr = new UCHAR *[ImgParaInCls.ImgH]; memset(ImgParaInCls.ImgGAdr, 0, ImgParaInCls.ImgH * sizeof(UCHAR*));
	ImgParaInCls.ImgBAdr = new UCHAR *[ImgParaInCls.ImgH]; memset(ImgParaInCls.ImgBAdr, 0, ImgParaInCls.ImgH * sizeof(UCHAR*));
	ImgParaInCls.ImgMAdr = new UCHAR *[ImgParaInCls.ImgH]; memset(ImgParaInCls.ImgMAdr, 0, ImgParaInCls.ImgH * sizeof(UCHAR*));

	for (int jj = 0; jj < 4; jj++)
	{
		if (jj == 0)
		{
			for (int ii = 0; ii < ImgParaInCls.ImgH; ii++)
			{
				UCHAR *pdata = new UCHAR[ImgParaInCls.ImgW]; memset(pdata, 0, ImgParaInCls.ImgW * sizeof(UCHAR));
				ImgParaInCls.ImgRAdr[ii] = pdata;
			}
		}
		else if (jj == 1)
		{
			for (int ii = 0; ii < ImgParaInCls.ImgH; ii++)
			{
				UCHAR *pdata = new UCHAR[ImgParaInCls.ImgW]; memset(pdata, 0, ImgParaInCls.ImgW * sizeof(UCHAR));
				ImgParaInCls.ImgGAdr[ii] = pdata;
			}
		}
		else if (jj == 2)
		{
			for (int ii = 0; ii < ImgParaInCls.ImgH; ii++)
			{
				UCHAR *pdata = new UCHAR[ImgParaInCls.ImgW]; memset(pdata, 0, ImgParaInCls.ImgW * sizeof(UCHAR));
				ImgParaInCls.ImgBAdr[ii] = pdata;
			}
		}
		else if (jj == 3)
		{
			for (int ii = 0; ii < ImgParaInCls.ImgH; ii++)
			{
				UCHAR *pdata = new UCHAR[ImgParaInCls.ImgW]; memset(pdata, 0, ImgParaInCls.ImgW * sizeof(UCHAR));
				ImgParaInCls.ImgMAdr[ii] = pdata;
			}
		}
	}
	return TRUE;
}

//�ͷ��ڴ�ռ�
BOOL Img_kele::ReleaseBandSpace()
{
	ReleaseEveryBand(ImgParaInCls.ImgRAdr);
	ReleaseEveryBand(ImgParaInCls.ImgGAdr);
	ReleaseEveryBand(ImgParaInCls.ImgBAdr);
	ReleaseEveryBand(ImgParaInCls.ImgMAdr);

	return TRUE;
}

BOOL Img_kele::ReleaseEveryBand(UCHAR **ImgBandAdr)
{
	UCHAR *pdata;
	for (int ii = 0; ii < ImgParaInCls.ImgH; ii++)
	{
		pdata = ImgBandAdr[ii];
		if (pdata)delete[]pdata;
		ImgBandAdr[ii] = NULL;
	}
	delete[]ImgBandAdr;
	ImgBandAdr = NULL;

	return TRUE;
}

//��ʼ��BMPλͼ��Ϣ
BOOL Img_kele::InitBitMapInfo(int nWidth, int nHeight, int colorbit, BITMAPINFO* pinfo)
{
	DWORD n4 = ((DWORD)nWidth * colorbit) / 4;
	if (((DWORD)nWidth * colorbit) % 4) n4++; n4 *= 4;//���Ҫ4�ı���
	ULONG lk = nHeight; lk *= n4;
	pinfo->bmiHeader.biSize = 40;			//sizeof(BITMAPINFOHEADER);
	pinfo->bmiHeader.biWidth = nWidth;		//λͼ��ȣ�������Ϊ��λ
	pinfo->bmiHeader.biHeight = nHeight;	//λͼ�߶ȣ�������Ϊ��λ
	pinfo->bmiHeader.biPlanes = 1;			//Ŀ���豸�ļ��𣬱���Ϊ1
	pinfo->bmiHeader.biBitCount = 8 * colorbit;		//ÿ�����������λ����������1(˫ɫ),4(16ɫ),8��256ɫ),16���߲�ɫ),24(���ɫ)֮һ
	pinfo->bmiHeader.biCompression = BI_RGB;//λͼѹ������,������0(��ѹ��),1(BI_RLE8),2(BI_RLE4)֮һ
	pinfo->bmiHeader.biSizeImage = lk;//λͼ�Ĵ�С(���а���Ϊ�˲���4��������ӵĿ��ֽ�)
	pinfo->bmiHeader.biXPelsPerMeter = 0;	//λͼˮƽ�ֱ��ʣ�ÿ��������
	pinfo->bmiHeader.biYPelsPerMeter = 0;	//λͼ��ֱ�ֱ��ʣ�ÿ��������
	pinfo->bmiHeader.biClrImportant = 0;	//λͼʵ��ʹ�õ���ɫ���е���ɫ��
	pinfo->bmiHeader.biClrUsed = 0;			//λͼ��ʾ��������Ҫ����ɫ��
	return TRUE;
}

//λͼ��Ϣ��ʼ��
BOOL Img_kele::InitBitMapFileInfo(int Width, int Height, int colorbit, BITMAPFILEHEADER* pbmfh, BITMAPINFOHEADER* pbmih)
{
	DWORD n4 = ((DWORD)Width * colorbit) / 4; if (((DWORD)Width * colorbit) % 4) n4++; n4 *= 4;
	ULONG lk = Height; lk *= n4;
	int off = 14 + sizeof(BITMAPINFOHEADER);
	pbmfh->bfType = 0x4D42;
	pbmfh->bfSize = off + lk;
	pbmfh->bfReserved1 = 0;
	pbmfh->bfReserved2 = 0;
	pbmfh->bfOffBits = off;
	//----------------------
	pbmih->biSize = 40;
	pbmih->biWidth = Width;
	pbmih->biHeight = Height;
	pbmih->biPlanes = 1;
	pbmih->biBitCount = 8 * colorbit;
	pbmih->biCompression = BI_RGB;
	pbmih->biSizeImage = lk;
	pbmih->biXPelsPerMeter = 0;
	pbmih->biYPelsPerMeter = 0;
	pbmih->biClrImportant = 0;
	pbmih->biClrUsed = 0;

	return TRUE;
}

//����Ӱ����ʾ�ڴ�
BOOL Img_kele::CreateDisplaySpace(MyImage *img, int Height, int Width)
{
	long len = 3 * Height * Width;
	ImgParaInCls.DisplayData = new char[len]; if (ImgParaInCls.DisplayData == NULL)return FALSE;
	memset(ImgParaInCls.DisplayData, 255, len);
	ImgParaInCls.DisplayLen = len;
	ImgParaInCls.DisplayWidth = Width;
	ImgParaInCls.DisplayHeight = Height;
	InitBitMapInfo(Width, Height, 3, &ImgParaInCls.DisplayInfo);
	return TRUE;
}

BOOL Img_kele::CreateDisplaySpace(int Height, int Width)
{
	long len = 3 * Height * Width;
	ImgParaInCls.DisplayData = new char[len]; if (ImgParaInCls.DisplayData == NULL)return FALSE;
	memset(ImgParaInCls.DisplayData, 255, len);
	ImgParaInCls.DisplayLen = len;
	ImgParaInCls.DisplayWidth = Width;
	ImgParaInCls.DisplayHeight = Height;
	InitBitMapInfo(Width, Height, 3, &ImgParaInCls.DisplayInfo);
	return TRUE;
}

BOOL Img_kele::DisplayImgColor(HDC *hdc, int DisWidth, int DisHeight, int Disoffx, int Disoffy, int srcWidth, int srcHeight, int srcoffx, int srcoffy)
{
	//�������
	if (srcWidth != DisWidth || srcHeight != DisHeight)
	{
		double WidFac = 1.0*srcWidth / DisWidth;
		double HeiFac = 1.0*srcHeight / DisHeight;

		//�˴�LinearFac�ĸ�ֵ���ǵ�����С�������ڱ�Ӱ��С��
		double LinearFac = WidFac;
		if (HeiFac > LinearFac)
			LinearFac = HeiFac;

		DisWidth = 1.0*srcWidth / LinearFac;
		while (DisWidth % 4)
			DisWidth++;
		DisHeight = 1.0*srcHeight / LinearFac;

		UCHAR *pdata = new UCHAR[3 * DisWidth*DisHeight]; if (!pdata) { AfxMessageBox("�����ز�������ʧ�ܣ�"); return FALSE; }
		memset(pdata, 0, sizeof(UCHAR) * 3 * DisWidth*DisHeight);
		
		//�ݶ�Ϊ������ڵ㷨
		int Sel = 0;
		//int Sel = resample_combo.GetCurSel();

		int off = 0;
		//char b, g, r;
		for (int ii = 0; ii < DisHeight; ii++)
		{
			for (int jj = 0; jj < DisWidth; jj++)
			{
				off = 3 * (ii * DisWidth + jj);

				if (Sel == 0)
				{
					pdata[off] = NearestNeighbor(srcoffx + jj*LinearFac, srcoffy + ii*LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgBAdr, 0);
					pdata[off + 1] = NearestNeighbor(srcoffx + jj*LinearFac, srcoffy + ii*LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgGAdr, 0);
					pdata[off + 2] = NearestNeighbor(srcoffx + jj*LinearFac, srcoffy + ii*LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgRAdr, 0);
				}
				else if (Sel == 1)
				{
					pdata[off] = BilinearInterpolation(srcoffx + jj*LinearFac, srcoffy + ii*LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgBAdr, 0);
					pdata[off + 1] = BilinearInterpolation(srcoffx + jj*LinearFac, srcoffy + ii*LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgGAdr, 0);
					pdata[off + 2] = BilinearInterpolation(srcoffx + jj*LinearFac, srcoffy + ii*LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgRAdr, 0);
				}
				else if (Sel == 2)
				{
					pdata[off] = CubicConvolution(srcoffx + jj*LinearFac, srcoffy + ii*LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgBAdr, 0);
					pdata[off + 1] = CubicConvolution(srcoffx + jj*LinearFac, srcoffy + ii*LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgGAdr, 0);
					pdata[off + 2] = CubicConvolution(srcoffx + jj*LinearFac, srcoffy + ii*LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgRAdr, 0);
				}
				else
				{
					AfxMessageBox("�ز�����ʽѡ������");
					return FALSE;
				}
			}
		}

		//��ʼ���ļ�BITMAPINFO����ͼ���С�ı�
		BITMAPINFO mapinfo;
		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);

		int nn = StretchDIBits(*hdc, 0, 0, DisWidth, DisHeight, 0, 0, DisWidth, DisHeight, (void*)pdata, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
		if (nn == 0) { AfxMessageBox("��ʾʧ�ܣ�"); return FALSE; }
		else return TRUE;
		delete[]pdata;
	}
	else
	{
		ImgParaInCls.ImgXoff = Disoffx;
		ImgParaInCls.ImgYoff = Disoffy;
		ImgParaInCls.DisplayWidth = DisWidth;
		ImgParaInCls.DisplayHeight = DisHeight;

		//����ͼ����ʾ�ռ�
		CreateDisplaySpace(ImgParaInCls.ImgH, ImgParaInCls.ImgW);

		//����д��DisplayData
		UCHAR *Rimg;
		UCHAR *Gimg;
		UCHAR *Bimg;
		int r, g, b;
		for (int ii = 0; ii < ImgParaInCls.ImgH; ii++)
		{
			Rimg = ImgParaInCls.ImgRAdr[ii];
			Gimg = ImgParaInCls.ImgGAdr[ii];
			Bimg = ImgParaInCls.ImgBAdr[ii];
			for (int jj = 0; jj < ImgParaInCls.ImgW; jj++)
			{
				r = Rimg[jj];
				g = Gimg[jj];
				b = Bimg[jj];
				int off = 3 * (ii*ImgParaInCls.ImgW + jj);
				ImgParaInCls.DisplayData[off + 0] = b;
				ImgParaInCls.DisplayData[off + 1] = g;
				ImgParaInCls.DisplayData[off + 2] = r;
			}
		}

		//��ʼ���ļ�BITMAPINFO����ͼ���С�ı�
		BITMAPINFO mapinfo;
		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);

		int nn = StretchDIBits(*hdc, 0, 0, DisWidth, DisHeight, 0, 0, srcWidth, srcHeight, (void*)ImgParaInCls.DisplayData, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
		if (nn == 0) { AfxMessageBox("��ʾʧ�ܣ�"); return FALSE; }
		else return TRUE;
	}

}


//BOOL Img_kele::DisplayImgColor(HDC *hdc, int DisWidth, int DisHeight, int Disoffx, int Disoffy, int srcWidth, int srcHeight, int srcoffx, int srcoffy)
//{
//	//�������
//	if (ImgParaInCls.ImgW != DisWidth || ImgParaInCls.ImgH != DisHeight)
//	{
//		double WidFac = 1.0*ImgParaInCls.ImgW / DisWidth;
//		double HeiFac = 1.0*ImgParaInCls.ImgH / DisHeight;
//
//		//�˴�LinearFac�ĸ�ֵ���ǵ�����С�������ڱ�Ӱ��С��
//		double LinearFac = WidFac;
//		if (HeiFac > LinearFac)
//			LinearFac = HeiFac;
//
//		DisWidth = 1.0*ImgParaInCls.ImgW / LinearFac;
//		while (DisWidth % 4)
//			DisWidth++;
//		DisHeight = 1.0*ImgParaInCls.ImgH / LinearFac;
//
//		UCHAR *pdata = new UCHAR[3 * DisWidth*DisHeight]; if (!pdata) { AfxMessageBox("�����ز�������ʧ�ܣ�"); return FALSE; }
//		memset(pdata, 0, sizeof(UCHAR) * 3 * DisWidth*DisHeight);
//
//
//		//int Sel = resample_combo.GetCurSel();
//		int Sel = 0;
//		int off = 0;
//		//char b, g, r;
//		for (int ii = 0; ii < DisHeight; ii++)
//		{
//			for (int jj = 0; jj < DisWidth; jj++)
//			{
//				off = 3 * (ii * DisWidth + jj);
//
//				if (Sel == 0)
//				{
//					pdata[off] = NearestNeighbor(jj*LinearFac, ii*LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgBAdr, 255);
//					pdata[off + 1] = NearestNeighbor(jj*LinearFac, ii*LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgGAdr, 255);
//					pdata[off + 2] = NearestNeighbor(jj*LinearFac, ii*LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgRAdr, 255);
//				}
//				else if (Sel == 1)
//				{
//					pdata[off] = BilinearInterpolation(jj*LinearFac, ii*LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgBAdr, 255);
//					pdata[off + 1] = BilinearInterpolation(jj*LinearFac, ii*LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgGAdr, 255);
//					pdata[off + 2] = BilinearInterpolation(jj*LinearFac, ii*LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgRAdr, 255);
//				}
//				else if (Sel == 2)
//				{
//					pdata[off] = CubicConvolution(jj*LinearFac, ii*LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgBAdr, 255);
//					pdata[off + 1] = CubicConvolution(jj*LinearFac, ii*LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgGAdr, 255);
//					pdata[off + 2] = CubicConvolution(jj*LinearFac, ii*LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgRAdr, 255);
//				}
//				else
//				{
//					AfxMessageBox("�ز�����ʽѡ������");
//					return FALSE;
//				}
//			}
//		}
//
//		//��ʼ���ļ�BITMAPINFO����ͼ���С�ı�
//		BITMAPINFO mapinfo;
//		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);
//
//		int nn = StretchDIBits(*hdc, 0, 0, DisWidth, DisHeight, 0, 0, DisWidth, DisHeight, (void*)pdata, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
//		if (nn == 0) { AfxMessageBox("��ʾʧ�ܣ�"); return FALSE; }
//		else return TRUE;
//		delete[]pdata;
//	}
//	else
//	{
//		ImgParaInCls.ImgXoff = Disoffx;
//		ImgParaInCls.ImgYoff = Disoffy;
//		ImgParaInCls.DisplayWidth = DisWidth;
//		ImgParaInCls.DisplayHeight = DisHeight;
//
//		//����ͼ����ʾ�ռ�
//		CreateDisplaySpace(ImgParaInCls.ImgH, ImgParaInCls.ImgW);
//
//		//����д��DisplayData
//		UCHAR *Rimg;
//		UCHAR *Gimg;
//		UCHAR *Bimg;
//		int r, g, b;
//		for (int ii = 0; ii < ImgParaInCls.ImgH; ii++)
//		{
//			Rimg = ImgParaInCls.ImgRAdr[ii];
//			Gimg = ImgParaInCls.ImgGAdr[ii];
//			Bimg = ImgParaInCls.ImgBAdr[ii];
//			for (int jj = 0; jj < ImgParaInCls.ImgW; jj++)
//			{
//				r = Rimg[jj];
//				g = Gimg[jj];
//				b = Bimg[jj];
//				int off = 3 * (ii*ImgParaInCls.ImgW + jj);
//				ImgParaInCls.DisplayData[off + 0] = b;
//				ImgParaInCls.DisplayData[off + 1] = g;
//				ImgParaInCls.DisplayData[off + 2] = r;
//			}
//		}
//
//		//��ʼ���ļ�BITMAPINFO����ͼ���С�ı�
//		BITMAPINFO mapinfo;
//		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);
//
//		int nn = StretchDIBits(*hdc, 0, 0, DisWidth, DisHeight, 0, 0, srcWidth, srcHeight, (void*)ImgParaInCls.DisplayData, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
//		if (nn == 0) { AfxMessageBox("��ʾʧ�ܣ�"); return FALSE; }
//		else return TRUE;
//	}
//
//	
//	ImgParaInCls.ImgXoff = Disoffx;
//	ImgParaInCls.ImgYoff = Disoffy;
//	ImgParaInCls.DisplayWidth = DisWidth;
//	ImgParaInCls.DisplayHeight = DisHeight;
//
//	//����ͼ����ʾ�ռ�
//	CreateDisplaySpace(ImgParaInCls.ImgH, ImgParaInCls.ImgW);
//
//	//����д��DisplayData
//	UCHAR *Rimg;
//	UCHAR *Gimg;
//	UCHAR *Bimg;
//	int r, g, b;
//	for (int ii = 0; ii < ImgParaInCls.ImgH; ii++)
//	{
//		Rimg = ImgParaInCls.ImgRAdr[ii];
//		Gimg = ImgParaInCls.ImgGAdr[ii];
//		Bimg = ImgParaInCls.ImgBAdr[ii];
//		for (int jj = 0; jj < ImgParaInCls.ImgW; jj++)
//		{
//			r = Rimg[jj];
//			g = Gimg[jj];
//			b = Bimg[jj];
//			int off = 3 * (ii*ImgParaInCls.ImgW + jj);
//			ImgParaInCls.DisplayData[off + 0] = b;
//			ImgParaInCls.DisplayData[off + 1] = g;
//			ImgParaInCls.DisplayData[off + 2] = r;
//		}
//	}
//
//	////����д��DisplayData
//	//UCHAR *Rimg;
//	//UCHAR *Gimg;
//	//UCHAR *Bimg;
//	//int r, g, b;
//	//for (int ii = 0; ii < ImgParaInCls.ImgH; ii++)
//	//{
//	//	Rimg = ImgParaInCls.ImgRAdr[ii];
//	//	Gimg = ImgParaInCls.ImgGAdr[ii];
//	//	Bimg = ImgParaInCls.ImgBAdr[ii];
//	//	for (int jj = 0; jj < ImgParaInCls.ImgW; jj++)
//	//	{
//	//		r = Rimg[jj];
//	//		g = Gimg[jj];
//	//		b = Bimg[jj];
//	//		int off = 3 * (ii*ImgParaInCls.ImgW + jj);
//	//		ImgParaInCls.DisplayData[off + 0] = b;
//	//		ImgParaInCls.DisplayData[off + 1] = g;
//	//		ImgParaInCls.DisplayData[off + 2] = r;
//	//	}
//	//}
//
//	//��ʼ���ļ�BITMAPINFO����ͼ���С�ı�
//	BITMAPINFO mapinfo;
//	InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);
//
//	int nn = StretchDIBits(*hdc, 0, 0, DisWidth, DisHeight, 0, 0, srcWidth, srcHeight, (void*)ImgParaInCls.DisplayData, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
//	if (nn == 0) { AfxMessageBox("��ʾʧ�ܣ�"); return FALSE; }
//	else return TRUE;
//}



//��ɫ��ʾӰ������ΪUCHAR���ͣ�


BOOL Img_kele::DisplayImgColor(UCHAR **ImgRBand, UCHAR **ImgGBand, UCHAR **ImgBBand)
{
	UCHAR *Rimg;
	UCHAR *Gimg;
	UCHAR *Bimg;
	int r, g, b;
	for (int ii = 0; ii < ImgParaInCls.ImgH; ii++)
	{
		Rimg = ImgRBand[ii];
		Gimg = ImgGBand[ii];
		Bimg = ImgBBand[ii];
		for (int jj = 0; jj < ImgParaInCls.ImgW; jj++)
		{
			r = Rimg[jj];
			g = Gimg[jj];
			b = Bimg[jj];
			int off = 3 * (ii*ImgParaInCls.ImgW + jj);
			ImgParaInCls.DisplayData[off + 0] = b;
			ImgParaInCls.DisplayData[off + 1] = g;
			ImgParaInCls.DisplayData[off + 2] = r;
		}
	}

	//GImgPara = ImgParaInCls;

	//��ȡ�����ھ��
	HWND hWnd;
	hWnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	HDC hdc;
	hdc = ::GetDC(hWnd);

	int nn = StretchDIBits(hdc, ImgParaInCls.ImgXoff, ImgParaInCls.ImgYoff, ImgParaInCls.DisplayWidth, ImgParaInCls.DisplayHeight, 0, 0, ImgParaInCls.ImgW, ImgParaInCls.ImgH, (void*)ImgParaInCls.DisplayData, &ImgParaInCls.DisplayInfo, DIB_RGB_COLORS, SRCCOPY);
	if (nn == 0) { AfxMessageBox("��ʾʧ�ܣ�"); return FALSE; }

	return TRUE;
}

//��ɫ��ʾӰ������Ϊfloat���ͣ�
BOOL Img_kele::DisplayImgColor(float *ImgRBand, float *ImgGBand, float *ImgBBand)
{
	for (int ii = 0; ii < ImgParaInCls.ImgH; ii++)
	{
		for (int jj = 0; jj < ImgParaInCls.ImgW; jj++)
		{
			int off = ii * ImgParaInCls.ImgW + jj;
			ImgParaInCls.DisplayData[3 * off + 0] = ImgBBand[off];
			ImgParaInCls.DisplayData[3 * off + 1] = ImgGBand[off];
			ImgParaInCls.DisplayData[3 * off + 2] = ImgRBand[off];
		}
	}

	HWND hWnd;
	hWnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	HDC hdc;
	hdc = ::GetDC(hWnd);

	int nn = StretchDIBits(hdc, ImgParaInCls.ImgXoff, ImgParaInCls.ImgYoff, ImgParaInCls.DisplayWidth, ImgParaInCls.DisplayHeight, 0, 0, ImgParaInCls.ImgW, ImgParaInCls.ImgH, (void*)ImgParaInCls.DisplayData, &ImgParaInCls.DisplayInfo, DIB_RGB_COLORS, SRCCOPY);
	if (nn == 0) { AfxMessageBox("��ʾʧ�ܣ�"); return FALSE; }

	return TRUE;
}

BOOL Img_kele::DisplayImg(CClientDC *dc, MyImage *img)
{
	if (!img)return FALSE; if (!img->DisplayData)return FALSE;
	int offX = img->ImgXoff;
	int offY = img->ImgYoff;
	int Wide = img->DisplayWidth;
	int Height = img->DisplayHeight;


	HDC hdc = dc->GetSafeHdc();

	int nn = StretchDIBits(hdc, 0, 0, Wide, Height, 0, 0, Wide, Height, (void*)img->ImgRAdr, &img->DisplayInfo, DIB_RGB_COLORS, SRCCOPY);
	if (nn == 0) { AfxMessageBox("��ʾʧ�ܣ�"); return FALSE; }
	else AfxMessageBox("��ʾ�ɹ���");
	return TRUE;
}

//�ͷ�Ӱ����ʾ�����ڴ�
BOOL Img_kele::DeleteDisplaySpace()
{
	if (ImgParaInCls.DisplayData)delete[]ImgParaInCls.DisplayData;
	ImgParaInCls.DisplayData = NULL;
	ImgParaInCls.DisplayLen = 0;
	ImgParaInCls.DisplayWidth = 0;
	ImgParaInCls.DisplayHeight = 0;
	return TRUE;
}

//�����������
BOOL Img_kele::LinearStretch(int Rmin, int Rmax, int Gmin, int Gmax, int Bmin, int Bmax)
{
	//double RLinFac, GLinFac, BLinFac;
	//RLinFac = 255.0 / (Rmax - Rmin);
	//GLinFac = 255.0 / (Gmax - Gmin);
	//BLinFac = 255.0 / (Bmax - Bmin);
	//int off = 0;
	//UCHAR *Rimg;
	//UCHAR *Gimg;
	//UCHAR *Bimg;
	//int r, g, b;
	//for (int ii = 0; ii < GImgPara.ImgH; ii++)
	//{
	//	Rimg = GImgPara.ImgRAdr[ii];
	//	Gimg = GImgPara.ImgGAdr[ii];
	//	Bimg = GImgPara.ImgBAdr[ii];
	//	for (int jj = 0; jj < GImgPara.ImgW; jj++)
	//	{
	//		r = Rimg[jj]; r = RLinFac * (r - Rmin); if (r < 0) { r = 0; }if (r > 255) { r = 255; }
	//		g = Gimg[jj]; g = GLinFac * (g - Gmin); if (g < 0) { g = 0; }if (g > 255) { g = 255; }
	//		b = Bimg[jj]; b = BLinFac * (b - Rmin); if (b < 0) { b = 0; }if (b > 255) { b = 255; }
	//		off = 3 * (ii*GImgPara.ImgW + jj);

	//		//GImgPara.DisplayData[off + 0] = LinFac * (Rimg[jj] - 0) + min;
	//		//GImgPara.DisplayData[off + 1] = LinFac * (Rimg[jj] - 0) + min;
	//		GImgPara.DisplayData[off + 0] = b;
	//		GImgPara.DisplayData[off + 1] = g;
	//		GImgPara.DisplayData[off + 2] = r;
	//	}
	//}
	return TRUE;
}

BOOL Img_kele::ReadBmpInfo(CString BmpFilePath)
{
	//����BMP����
	FILE*fBmp = fopen(BmpFilePath, "rb"); if (!fBmp)return FALSE;

	//���BMP�ļ���ʽ
	fread(&ImgParaInCls.BmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fBmp);
	fread(&ImgParaInCls.BmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fBmp);
	if (ImgParaInCls.BmpFileHeader.bfType != 0x4D42) { AfxMessageBox("ͼ���ʽBM����!"); return FALSE; }
	if (ImgParaInCls.BmpInfoHeader.biCompression != BI_RGB) { AfxMessageBox("ͼ��ѹ����ʽ����"); return FALSE; }
	if (ImgParaInCls.BmpInfoHeader.biBitCount != 24) { AfxMessageBox("���󣬷�24bit"); return FALSE; }

	//ͼ������λ�ã�ͼ����߲�����ȡ
	long   offBits = ImgParaInCls.BmpFileHeader.bfOffBits;
	int    nWidt = ImgParaInCls.BmpInfoHeader.biWidth;
	int    nHeig = ImgParaInCls.BmpInfoHeader.biHeight;

	//����
	ImgParaInCls.ImgW = ImgParaInCls.BmpInfoHeader.biWidth;
	ImgParaInCls.ImgH = ImgParaInCls.BmpInfoHeader.biHeight;

	cout << "�����ڵ�ַ��";
	cout << &ImgParaInCls << endl;

	return TRUE;
}

BOOL Img_kele::ReadBmpData(CString BmpFilePath)
{
	//����BMP����
	FILE*fBmp = fopen(BmpFilePath, "rb"); if (!fBmp)return FALSE;

	//�������ݿռ䣨��Ϊ��λ��
	char *pdata = new char[3 * ImgParaInCls.ImgW + 1]; if (!pdata)return FALSE; memset(pdata, 0, (3 * ImgParaInCls.ImgW) * sizeof(char));
	//char *rdata = new char[ImgParaInCls.ImgW + 1]; if (!rdata) { delete[]pdata; return FALSE; } memset(rdata, 0, (Width) * sizeof(char));
	//char *gdata = new char[ImgParaInCls.ImgW + 1]; if (!gdata) { delete[]pdata; delete[]rdata; return FALSE; } memset(gdata, 0, (Width) * sizeof(char));
	//char *bdata = new char[ImgParaInCls.ImgW + 1]; if (!bdata) { delete[]pdata; delete[]rdata; delete[]gdata; return FALSE; }; memset(bdata, 0, (Width) * sizeof(char));

	fseek(fBmp, ImgParaInCls.BmpFileHeader.bfOffBits, SEEK_SET);
	for (int ii = 0; ii < ImgParaInCls.ImgH; ii++)
	{
		fread(pdata, 3 * ImgParaInCls.ImgW, 1, fBmp);
		for (int jj = 0; jj < ImgParaInCls.ImgW; jj++)
		{
			*(ImgParaInCls.ImgBAdr[ii] + jj) = *(pdata + 3 * jj + 0);
			*(ImgParaInCls.ImgGAdr[ii] + jj) = *(pdata + 3 * jj + 1);
			*(ImgParaInCls.ImgRAdr[ii] + jj) = *(pdata + 3 * jj + 2);
		}
	}
	return TRUE;
}

//ԭʼ����ΪBMPд��000�����ļ�������ʵ���Խ��Ϊ���BMP�ļ�ͷ������ȡBMPӰ������
BOOL Img_kele::WriteBmpToControlFile(CString BmpFilePath, FILE *fBmp, CString BmpFileName)
{
	//���BMP�ļ���ʽ
	fread(&ImgParaInCls.BmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fBmp);
	fread(&ImgParaInCls.BmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fBmp);
	if (ImgParaInCls.BmpFileHeader.bfType != 0x4D42) { AfxMessageBox("ͼ���ʽBM����!"); return FALSE; }
	if (ImgParaInCls.BmpInfoHeader.biCompression != BI_RGB) { AfxMessageBox("ͼ��ѹ����ʽ����"); return FALSE; }
	if (ImgParaInCls.BmpInfoHeader.biBitCount != 24) { AfxMessageBox("���󣬷�24bit"); return FALSE; }

	//ͼ������λ�ã�ͼ����߲�����ȡ
	long   offBits = ImgParaInCls.BmpFileHeader.bfOffBits;
	int    nWidt = ImgParaInCls.BmpInfoHeader.biWidth;
	int    nHeig = ImgParaInCls.BmpInfoHeader.biHeight;

	//��.bmp�ļ���ʼ�������ļ�·��������.000�滻.bmp
	CString ControlFilePath(BmpFilePath);
	ControlFilePath.Replace(".bmp", ".000");
	FILE*f000 = fopen(ControlFilePath, "w"); if (!f000) { fclose(fBmp); return FALSE; }

	//д�����
	if (f000)
	{
		fprintf(f000, "ImageWH     %5d %5d\n", nWidt, nHeig);
		USES_CONVERSION;
		//�첨��
		CString RBandPath(BmpFileName); RBandPath.Replace(".bmp", "R.img");
		char*pr = T2A(RBandPath.GetBuffer(0));
		RBandPath.ReleaseBuffer();
		fprintf(f000, "ETM_BAND   3    0    0    255  %-s \n", pr);

		//������
		CString GBandPath(BmpFileName); GBandPath.Replace(".bmp", "G.img");
		char*pg = T2A(GBandPath.GetBuffer(0));
		GBandPath.ReleaseBuffer();
		fprintf(f000, "ETM_BAND   2    0    0    255  %-s \n", pg);

		//�̲���
		CString BBandPath(BmpFileName); BBandPath.Replace(".bmp", "B.img");
		char*pb = T2A(BBandPath.GetBuffer(0));
		BBandPath.ReleaseBuffer();
		fprintf(f000, "ETM_BAND   1    0    0    255  %-s \n", pb);

	}

	WriteBmpToRGBImg(BmpFilePath, fBmp, nWidt, nHeig, offBits);

	fclose(f000);
	return TRUE;
}

//��ȡBMP���ݵĴ���
BOOL Img_kele::WriteBmpToRGBImg(CString BmpFilePath, FILE *fBmp, int Width, int Height, long offBits)
{
	//����RGB��������Img·��(�滻.bmpΪ.img)
	CString RBandPath(BmpFilePath); RBandPath.Replace(".bmp", "R.img");
	CString GBandPath(BmpFilePath); GBandPath.Replace(".bmp", "G.img");
	CString BBandPath(BmpFilePath); BBandPath.Replace(".bmp", "B.img");

	//����RGB�������ε�Img·��
	FILE*fRband = fopen(RBandPath, "wb"); if (!fRband) { fclose(fBmp); return FALSE; }
	FILE*fGband = fopen(GBandPath, "wb"); if (!fGband) { fclose(fBmp); fclose(fRband); return FALSE; }
	FILE*fBband = fopen(BBandPath, "wb"); if (!fBband) { fclose(fBmp);  fclose(fRband); fclose(fGband); return FALSE; }

	//�������ݿռ䣨��Ϊ��λ��
	char *pdata = new char[3 * Width + 1]; if (!pdata)return FALSE; memset(pdata, 0, (3 * Width) * sizeof(char));
	char *rdata = new char[Width + 1]; if (!rdata) { delete[]pdata; return FALSE; } memset(rdata, 0, (Width) * sizeof(char));
	char *gdata = new char[Width + 1]; if (!gdata) { delete[]pdata; delete[]rdata; return FALSE; } memset(gdata, 0, (Width) * sizeof(char));
	char *bdata = new char[Width + 1]; if (!bdata) { delete[]pdata; delete[]rdata; delete[]gdata; return FALSE; }; memset(bdata, 0, (Width) * sizeof(char));

	fseek(fBmp, offBits, SEEK_SET);
	for (int ii = 0; ii < Height; ii++)
	{
		fread(pdata, 3 * Width, 1, fBmp);
		for (int jj = 0; jj < Width; jj++)
		{
			*(bdata + jj) = *(pdata + 3 * jj + 0);
			*(gdata + jj) = *(pdata + 3 * jj + 1);
			*(rdata + jj) = *(pdata + 3 * jj + 2);
		}
		fwrite(rdata, 1, Width, fRband);
		fwrite(gdata, 1, Width, fGband);
		fwrite(bdata, 1, Width, fBband);
	}
	delete[]pdata; delete[]rdata; delete[]gdata; delete[]bdata;

	fclose(fRband); fclose(fGband); fclose(fBband);
	return TRUE;
}

//JPG�ļ�תΪBMP�ļ�
BOOL Img_kele::WarpJpgToBmp(CString InFilePath)
{
	//Ϊ�����bmpͼƬ����·��
	CString BmpFilePath(InFilePath);
	BmpFilePath.Replace(".jpg", ".bmp");

	//��ȡjpgͼƬ�������ڴ�
	FILE * fp = NULL;
	char * pFileData; pFileData = NULL;
	int file_size = 0;
	fp = fopen(InFilePath, "rb");
	if (fp != NULL)
	{
		//��λ���ļ�ĩβ����ftell�õ����ݳ���
		fseek(fp, 0, SEEK_END);
		file_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		pFileData = new char[file_size]; memset(pFileData, 0, file_size);
		fread(pFileData, 1, file_size, fp);
		fclose(fp);
	}

	//���ڴ����ݱ���Bmp�ļ�
	if (pFileData != NULL)
	{
		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, file_size);
		void* pData = GlobalLock(hGlobal);
		memcpy(pData, pFileData, file_size);
		GlobalUnlock(hGlobal);


		IStream* pStream = NULL;
		if (CreateStreamOnHGlobal(hGlobal, TRUE, &pStream) == S_OK)
		{
			CImage image;
			if (SUCCEEDED(image.Load(pStream)))

			{
				image.Save(BmpFilePath);
				//image.Draw(lDC->m_hDC, m_xStart, m_yStart, imageWidth, imageHeight);

			}
			pStream->Release();
		}
		GlobalFree(hGlobal);
	}

	delete[]pFileData;


	return TRUE;
}

//����ڵ㷨
UCHAR Img_kele::NearestNeighbor(float x, float y, int Width, int Height, UCHAR **Data, UCHAR B0)
{
	int x0 = (int)(x + 0.5); if (x0 < 0 || x0 >= Width) { return B0; }
	int y0 = (int)(y + 0.5); if (y0 < 0 || y0 >= Height) { return B0; }

	UCHAR *p = *(Data + y0);
	UCHAR ch = *(p + x0);

	return ch;
}

//˫�����ڲ�
UCHAR Img_kele::BilinearInterpolation(float x, float y, int Width, int Height, UCHAR ** Data, UCHAR B0)
{
	float dx, dy, m, n, v;
	UCHAR *pdata;
	UCHAR v1, v2, v3, v4;

	int x0 = x + EPSILON; if (x0<0 || x0>Width) { return B0; }
	int y0 = y + EPSILON; if (y0<0 || y0>Height) { return B0; }

	x0 = x; y0 = y;
	dx = x - x0; dy = y - y0;

	if (x < EPSILON)
	{
		//��һ��
		if (y < EPSILON)
		{
			//��һ�е�һ��
			pdata = *Data;
			v = *pdata;
		}
		else if (y > Height - 1 - EPSILON)
		{
			//��һ�����һ��
			pdata = *(Data + Height - 1);
			v = *pdata;
		}
		else
		{
			//��һ������
			pdata = *(Data + y0);
			v1 = *pdata;
			pdata = *(Data + y0 + 1);
			v3 = *pdata;
			if (v1 == B0)
			{
				v = v3;
			}
			else if (v3 == B0)
			{
				v = v1;
			}
			else
			{
				v = v1 + dy * (v3 - v1);
			}
		}
	}
	else if (y < EPSILON)
	{
		//��һ��
		//�ѿ���x<EPSILON����������ڴ˲�����
		if (x > Width - 1 - EPSILON)
		{
			//��һ�����һ��
			pdata = *Data;
			v = *pdata + Width - 1;
		}
		else
		{
			//��һ������
			pdata = *Data;
			v1 = *(pdata + x0);
			v2 = *(pdata + x0 + 1);
			if (v1 == B0)
			{
				v = v2;
			}
			else if (v2 == B0)
			{
				v = v1;
			}
			else
			{
				v = v1 + dx * (v2 - v1);
			}
		}
	}
	else if (x > Width - 1 + EPSILON)
	{
		//���һ��
		if (y > Height - 1 + EPSILON)
		{
			//���һ�����һ��
			pdata = *(Data + Height - 1);
			v = *(pdata + Width - 1);
		}
		else
		{
			//���һ������
			pdata = *(Data + y0);
			v2 = *(pdata + Width - 1);
			pdata = *(Data + y0 + 1);
			v4 = *(pdata + Width - 1);
			if (v2 == B0)
			{
				v = v4;
			}
			else if (v4 == B0)
			{
				v = v2;
			}
			else
			{
				v = v2 + dy * (v4 - v2);
			}
		}
	}
	else if (y > Height - 1 + EPSILON)
	{
		//���һ������
		pdata = *(Data + Height - 1);
		v3 = *(pdata + x0);
		v4 = *(pdata + x0 + 1);
		if (v3 == B0)
		{
			v = v4;
		}
		else if (v4 == B0)
		{
			v = v3;
		}
		else
		{
			v = v3 + dx * (v4 - v3);
		}
	}
	else
	{
		pdata = *(Data + y0);
		v1 = *(pdata + x0);
		v2 = *(pdata + x0 + 1);

		pdata = *(Data + y0 + 1);
		v3 = *(pdata + x0);
		v4 = *(pdata + x0 + 1);

		//����m��ȡֵ
		if (v3 == B0)
		{
			m = v1;
		}
		else if (v1 == B0)
		{
			m = v3;
		}
		else
		{
			m = v1 + dy * (v3 - v1);
		}

		//����n��ȡֵ
		if (v2 == B0)
		{
			n = v4;
		}
		else if (v4 == B0)
		{
			n = v2;
		}
		else
		{
			n = v2 + dy * (v4 - v2);
		}

		//����v��ȡֵ
		if (m + 0.5 == B0)
		{
			v = n;
		}
		else if (n + 0.5 == B0)
		{
			v = m;
		}
		else
		{
			v = m + dx * (n - m);
		}

	}

	return UCHAR(v + 0.5);

}

//˫���ξ��
UCHAR Img_kele::CubicConvolution(float x, float y, int Width, int Height, UCHAR ** Data, UCHAR B0)
{
	int x0 = x; if (x0 < 0 || x0 >= Width)return B0;
	int y0 = y; if (y0 < 0 || y0 >= Height)return B0;
	int i1 = x0 - 1; if (i1 < 0) { i1 = x0; }
	int i3 = x0 + 1; if (i3 >= Width) { i3 = x0; }
	int i4 = x0 + 2; if (i4 >= Width) { i4 = x0; }
	int j1 = y0 - 1; if (j1 < 0) { j1 = y0; }
	int j3 = y0 + 1; if (j3 >= Height) { j3 = y0; }
	int j4 = y0 + 2; if (j4 >= Height) { j4 = y0; }

	UCHAR* pdata1 = *(Data + j1);
	UCHAR* pdata2 = *(Data + y0);
	UCHAR* pdata3 = *(Data + j3);
	UCHAR* pdata4 = *(Data + j4);

	float dx = x - x0; float dy = y - y0;
	float dx2 = dx * dx; float dy2 = dy * dy;
	float dx3 = dx2 * dx; float dy3 = dy2 * dy;
	float wx1 = -dx + 2 * dx2 - dx3;
	float wx2 = 1 - 2 * dx2 + dx3;
	float wx3 = dx + dx2 - dx3;
	float wx4 = -dx2 + dx3;
	float wy1 = -dy + 2 * dy2 - dy3;
	float wy2 = 1 - 2 * dy2 + dy3;
	float wy3 = dy + dy2 - dy3;
	float wy4 = -dy2 + dy3;

	UCHAR v22 = *(pdata2 + x0); if (v22 == B0)return v22;
	UCHAR  v11 = *(pdata1 + i1); if (v11 == B0) return BilinearInterpolation(x, y, Width, Height, Data, B0);
	UCHAR  v12 = *(pdata1 + x0); if (v12 == B0) return BilinearInterpolation(x, y, Width, Height, Data, B0);
	UCHAR  v13 = *(pdata1 + i3); if (v13 == B0) return BilinearInterpolation(x, y, Width, Height, Data, B0);
	UCHAR  v14 = *(pdata1 + i4); if (v14 == B0) return BilinearInterpolation(x, y, Width, Height, Data, B0);
	UCHAR  v21 = *(pdata2 + i1); if (v21 == B0) return BilinearInterpolation(x, y, Width, Height, Data, B0);
	UCHAR  v23 = *(pdata2 + i3); if (v23 == B0) return v22;
	UCHAR  v24 = *(pdata2 + i4); if (v24 == B0) return BilinearInterpolation(x, y, Width, Height, Data, B0);
	UCHAR  v31 = *(pdata3 + i1); if (v31 == B0) return BilinearInterpolation(x, y, Width, Height, Data, B0);
	UCHAR  v32 = *(pdata3 + x0); if (v32 == B0) return v22;
	UCHAR  v33 = *(pdata3 + i3); if (v33 == B0) return v22;
	UCHAR  v34 = *(pdata3 + i4); if (v34 == B0) return BilinearInterpolation(x, y, Width, Height, Data, B0);
	UCHAR  v41 = *(pdata4 + i1); if (v41 == B0) return BilinearInterpolation(x, y, Width, Height, Data, B0);
	UCHAR  v42 = *(pdata4 + x0); if (v42 == B0) return BilinearInterpolation(x, y, Width, Height, Data, B0);
	UCHAR  v43 = *(pdata4 + i3); if (v43 == B0) return BilinearInterpolation(x, y, Width, Height, Data, B0);
	UCHAR  v44 = *(pdata4 + i4); if (v44 == B0) return BilinearInterpolation(x, y, Width, Height, Data, B0);


	float v = v11 * wx1*wy1 + v21 * wx1*wy2 + v31 * wx1*wy3 + v41 * wx1*wy4 + v12 * wx2*wy1 + v22 * wx2*wy2 + v32 * wx2*wy3 + v42 * wx2*wy4 + v13 * wx3*wy1 + v23 * wx3*wy2 + v33 * wx3*wy3 + v43 * wx3*wy4 + v14 * wx4*wy1 + v24 * wx4*wy2 + v34 * wx4*wy3 + v44 * wx4*wy4;

	return UCHAR(v);
}