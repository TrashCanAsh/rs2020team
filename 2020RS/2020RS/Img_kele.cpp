#include "stdafx.h"
//#include<vector>
#include "Img_kele.h"
#include<iostream>
using namespace std;

Img_kele::Img_kele()
{
}


Img_kele::~Img_kele()
{
}

Img_kele::Img_kele(const Img_kele & CopyImg)
{
	ImgParaInCls.ImgH = CopyImg.ImgParaInCls.ImgH;
	ImgParaInCls.ImgW = CopyImg.ImgParaInCls.ImgW;
	ImgParaInCls.RMax = CopyImg.ImgParaInCls.RMax;
	ImgParaInCls.RMin = CopyImg.ImgParaInCls.RMin;
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

	for (int ii = 0; ii < ImgParaInCls.ImgH; ii++)
	{
		for (int jj = 0; jj < ImgParaInCls.ImgW; jj++)
		{
			UCHAR rr = CopyImg.ImgParaInCls.ImgRAdr[ii][jj];
			UCHAR gg = CopyImg.ImgParaInCls.ImgGAdr[ii][jj];
			UCHAR bb = CopyImg.ImgParaInCls.ImgBAdr[ii][jj];
			UCHAR mm = CopyImg.ImgParaInCls.ImgMAdr[ii][jj];
			ImgParaInCls.ImgRAdr[ii][jj] = rr;
			ImgParaInCls.ImgGAdr[ii][jj] = gg;
			ImgParaInCls.ImgBAdr[ii][jj] = bb;
			ImgParaInCls.ImgMAdr[ii][jj] = mm;
		}
	
	}
}

//列主元高斯消元法在matrix类中实现

//开辟内存空间（读入影像时使用）
BOOL Img_kele::CreateBandSpace()
{
	cout << "开辟数组内存的ImgH:";
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

//释放内存空间
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

//初始化BMP位图信息
BOOL Img_kele::InitBitMapInfo(int nWidth, int nHeight, int colorbit, BITMAPINFO* pinfo)
{
	DWORD n4 = ((DWORD)nWidth * colorbit) / 4;
	if (((DWORD)nWidth * colorbit) % 4) n4++; n4 *= 4;//宽度要4的倍数
	ULONG lk = nHeight; lk *= n4;
	pinfo->bmiHeader.biSize = 40;			//sizeof(BITMAPINFOHEADER);
	pinfo->bmiHeader.biWidth = nWidth;		//位图宽度，以像素为单位
	pinfo->bmiHeader.biHeight = nHeight;	//位图高度，以像素为单位
	pinfo->bmiHeader.biPlanes = 1;			//目标设备的级别，必须为1
	pinfo->bmiHeader.biBitCount = 8 * colorbit;		//每个像素所需的位数，必须是1(双色),4(16色),8（256色),16（高彩色),24(真彩色)之一
	pinfo->bmiHeader.biCompression = BI_RGB;//位图压缩类型,必须是0(不压缩),1(BI_RLE8),2(BI_RLE4)之一
	pinfo->bmiHeader.biSizeImage = lk;//位图的大小(其中包含为了补齐4倍数而添加的空字节)
	pinfo->bmiHeader.biXPelsPerMeter = 0;	//位图水平分辨率，每米像素数
	pinfo->bmiHeader.biYPelsPerMeter = 0;	//位图垂直分辨率，每米像素数
	pinfo->bmiHeader.biClrImportant = 0;	//位图实际使用的颜色表中的颜色数
	pinfo->bmiHeader.biClrUsed = 0;			//位图显示过程中重要的颜色数
	return TRUE;
}

//位图信息初始化
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

//开辟影像显示内存
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
	//调整宽高
	if (srcWidth != DisWidth || srcHeight != DisHeight)
	{
		double WidFac = 1.0*srcWidth / DisWidth;
		double HeiFac = 1.0*srcHeight / DisHeight;

		//此处LinearFac的赋值考虑的是缩小（即窗口比影像小）
		double LinearFac = WidFac;
		if (HeiFac > LinearFac)
			LinearFac = HeiFac;

		DisWidth = 1.0*srcWidth / LinearFac;
		while (DisWidth % 4)
			DisWidth++;
		DisHeight = 1.0*srcHeight / LinearFac;

		UCHAR *pdata = new UCHAR[3 * DisWidth*DisHeight]; if (!pdata) { AfxMessageBox("创建重采样数组失败！"); return FALSE; }
		memset(pdata, 0, sizeof(UCHAR) * 3 * DisWidth*DisHeight);
		
		//暂定为用最近邻点法
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
					AfxMessageBox("重采样方式选择有误！");
					return FALSE;
				}
				
			}
		}

		//初始化文件BITMAPINFO，因图像大小改变
		BITMAPINFO mapinfo;
		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);

		int nn = StretchDIBits(*hdc, Disoffx, Disoffy, DisWidth, DisHeight, 0, 0, DisWidth, DisHeight, (void*)pdata, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
		if (nn == 0) { AfxMessageBox("显示失败！"); return FALSE; }
		else return TRUE;
		delete[]pdata;
	}
	else
	{
		ImgParaInCls.ImgXoff = Disoffx;
		ImgParaInCls.ImgYoff = Disoffy;
		ImgParaInCls.DisplayWidth = DisWidth;
		ImgParaInCls.DisplayHeight = DisHeight;

		//创建图像显示空间
		CreateDisplaySpace(ImgParaInCls.ImgH, ImgParaInCls.ImgW);

		//数据写入DisplayData
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

		//初始化文件BITMAPINFO，因图像大小改变
		BITMAPINFO mapinfo;
		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);

		int nn = StretchDIBits(*hdc, 0, 0, DisWidth, DisHeight, 0, 0, srcWidth, srcHeight, (void*)ImgParaInCls.DisplayData, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
		if (nn == 0) { AfxMessageBox("显示失败！"); return FALSE; }
		else return TRUE;
	}

}

BOOL Img_kele::DisplaySquareImgColor(HDC *hdc, int DisWidth, int DisHeight, int offx, int offy,double fac1, double fac2)
{
	if (fac1*fac2!=1||DisWidth!=ImgParaInCls.ImgW||DisHeight!=ImgParaInCls.ImgH)
	{
		//double WidFac = 1.0*srcWidth / DisWidth;
		//double HeiFac = 1.0*srcHeight / DisHeight;

		////此处LinearFac的赋值考虑的是缩小（即窗口比影像小）
		//double LinearFac = WidFac;
		//if (HeiFac > LinearFac)
		//	LinearFac = HeiFac;

		//DisWidth = 1.0*srcWidth / LinearFac;
		//while (DisWidth % 4)
		//	DisWidth++;
		//正方形
		while (DisHeight % 4)
			DisHeight++;
		DisWidth = DisHeight;

		UCHAR *pdata = new UCHAR[3 * DisWidth*DisHeight]; if (!pdata) { AfxMessageBox("创建重采样数组失败！"); return FALSE; }
		memset(pdata, 0, sizeof(UCHAR) * 3 * DisWidth*DisHeight);

		//暂定为用最近邻点法
		int Sel = 0;
		//int Sel = resample_combo.GetCurSel();

		int off = 0;
		//char b, g, r;

		//double LinearFac = 1280.0 / 400;

		double srcoffx = offx * fac1;
		double srcoffy = offy * fac1 ;

		//因为BMP是关于轴对称的存储

		srcoffy = 1024 - srcoffy - 100 * fac1;

		for (int ii = 0; ii < DisHeight; ii++)
		{
			for (int jj = 0; jj < DisWidth; jj++)
			{
				off = 3 * (ii * DisWidth + jj);

				if (Sel == 0)
				{
					pdata[off] = NearestNeighbor(srcoffx + jj * fac2*fac1, srcoffy + ii * fac2*fac1, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgBAdr, 0);
					pdata[off + 1] = NearestNeighbor(srcoffx + jj * fac2*fac1, srcoffy + ii * fac2*fac1, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgGAdr, 0);
					pdata[off + 2] = NearestNeighbor(srcoffx + jj * fac2*fac1, srcoffy + ii * fac2*fac1, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgRAdr, 0);
				}
				else if (Sel == 1)
				{
					pdata[off] = BilinearInterpolation(srcoffx + jj * fac2*fac1, srcoffy + ii * fac2*fac1, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgBAdr, 0);
					pdata[off + 1] = BilinearInterpolation(srcoffx + jj * fac2*fac1, srcoffy + ii * fac2*fac1, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgGAdr, 0);
					pdata[off + 2] = BilinearInterpolation(srcoffx + jj * fac2*fac1, srcoffy + ii * fac2*fac1, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgRAdr, 0);
				}
				else if (Sel == 2)
				{
					pdata[off] = CubicConvolution(srcoffx + jj * fac2*fac1, srcoffy + ii * fac2*fac1, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgBAdr, 0);
					pdata[off + 1] = CubicConvolution(srcoffx + jj * fac2*fac1, srcoffy + ii * fac2*fac1, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgGAdr, 0);
					pdata[off + 2] = CubicConvolution(srcoffx + jj * fac2*fac1, srcoffy + ii * fac2*fac1, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgRAdr, 0);
				}
				else
				{
					AfxMessageBox("重采样方式选择有误！");
					return FALSE;
				}
			}
		}

		//初始化文件BITMAPINFO，因图像大小改变
		BITMAPINFO mapinfo;
		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);

		int nn = StretchDIBits(*hdc, 0, 0, DisWidth, DisHeight, 0, 0, DisWidth, DisHeight, (void*)pdata, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
		if (nn == 0) { AfxMessageBox("显示失败！"); return FALSE; }
		else return TRUE;
		delete[]pdata;
	}
	else
	{
		AfxMessageBox("请确认是否确实满足以下条件：（DisWidth=ImgParaInCls.ImgW&&DisHeight=ImgParaInCls.ImgH）&&（fac1*fac2=1）");
		return FALSE;
		ImgParaInCls.ImgXoff = 0;
		ImgParaInCls.ImgYoff = 0;
		ImgParaInCls.DisplayWidth = DisWidth;
		ImgParaInCls.DisplayHeight = DisHeight;

		//创建图像显示空间
		CreateDisplaySpace(ImgParaInCls.ImgH, ImgParaInCls.ImgW);

		//数据写入DisplayData
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

		//初始化文件BITMAPINFO，因图像大小改变
		BITMAPINFO mapinfo;
		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);

		int nn = StretchDIBits(*hdc, 0, 0, DisWidth, DisHeight, 0, 0, ImgParaInCls.ImgW, ImgParaInCls.ImgH, (void*)ImgParaInCls.DisplayData, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
		if (nn == 0) { AfxMessageBox("显示失败！"); return FALSE; }
		else return TRUE;
	}

	return TRUE;
}

BOOL Img_kele::DisplaySquareImgColor(HDC *hdc, int DisWidth, int DisHeight, int offx1, int offy1, int offx2, int offy2, double fac1, double fac2, double fac3)
{

	//调整宽高
	if (fac1*fac2*fac3 != 1|| DisWidth != ImgParaInCls.ImgW || DisHeight != ImgParaInCls.ImgH)
	{
		//double WidFac = 1.0*srcWidth / DisWidth;
		//double HeiFac = 1.0*srcHeight / DisHeight;

		////此处LinearFac的赋值考虑的是缩小（即窗口比影像小）
		//double LinearFac = WidFac;
		//if (HeiFac > LinearFac)
		//	LinearFac = HeiFac;

		//DisWidth = 1.0*srcWidth / LinearFac;
		//while (DisWidth % 4)
		//	DisWidth++;
		//正方形
		while (DisHeight % 4)
			DisHeight++;
		DisWidth = DisHeight;

		UCHAR *pdata = new UCHAR[3 * DisWidth*DisHeight]; if (!pdata) { AfxMessageBox("创建重采样数组失败！"); return FALSE; }
		memset(pdata, 0, sizeof(UCHAR) * 3 * DisWidth*DisHeight);

		//暂定为用最近邻点法
		int Sel = 0;

		int off = 0;
		//char b, g, r;
		cout << "offy1:" << offy1 << " " << "offy2:" << offy2 << endl;
		double srcoffx = offx1 * fac1 + offx2 * fac2 * fac1;
		double srcoffy = offy1 * fac1 + offy2 * fac2 * fac1;
		//
		srcoffy = 1024 - srcoffy -100*fac1*fac2;
		
		
		//for (int ii = 0; ii < DisHeight; ii++)

		for (int ii = 0; ii < DisHeight; ii++)
		{
			for (int jj = 0; jj < DisWidth; jj++)
			{
				off = 3 * (ii * DisWidth + jj);

				if (Sel == 0)
				{
					pdata[off] = NearestNeighbor(srcoffx + jj * fac3*fac2*fac1, srcoffy + ii * fac3*fac2*fac1, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgBAdr, 0);
					pdata[off + 1] = NearestNeighbor(srcoffx + jj * fac3*fac2*fac1, srcoffy + ii * fac3*fac2*fac1, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgGAdr, 0);
					pdata[off + 2] = NearestNeighbor(srcoffx + jj * fac3*fac2*fac1, srcoffy + ii * fac3*fac2*fac1, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgRAdr, 0);
				}
				else if (Sel == 1)
				{
					pdata[off] = BilinearInterpolation(srcoffx + jj * fac3*fac2*fac1, srcoffy + ii * fac3*fac2*fac1, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgBAdr, 0);
					pdata[off + 1] = BilinearInterpolation(srcoffx + jj * fac3*fac2*fac1, srcoffy + ii * fac3*fac2*fac1, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgGAdr, 0);
					pdata[off + 2] = BilinearInterpolation(srcoffx + jj * fac3*fac2*fac1, srcoffy + ii * fac3*fac2*fac1, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgRAdr, 0);
				}
				else if (Sel == 2)
				{
					pdata[off] = CubicConvolution(srcoffx + jj * fac3*fac2*fac1, srcoffy + ii * fac3*fac2*fac1, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgBAdr, 0);
					pdata[off + 1] = CubicConvolution(srcoffx + jj * fac3*fac2*fac1, srcoffy + ii * fac3*fac2*fac1, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgGAdr, 0);
					pdata[off + 2] = CubicConvolution(srcoffx + jj * fac3*fac2*fac1, srcoffy + ii * fac3*fac2*fac1, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgParaInCls.ImgRAdr, 0);
				}
				else
				{
					AfxMessageBox("重采样方式选择有误！");
					return FALSE;
				}
			}
		}

		//初始化文件BITMAPINFO，因图像大小改变
		BITMAPINFO mapinfo;
		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);

		int nn = StretchDIBits(*hdc, 0, 0, DisWidth, DisHeight, 0, 0, DisWidth, DisHeight, (void*)pdata, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
		if (nn == 0) { AfxMessageBox("显示失败！"); return FALSE; }
		else return TRUE;
		delete[]pdata;
	}
	else
	{
		AfxMessageBox("请确认是否确实满足以下条件：（DisWidth=ImgParaInCls.ImgW&&DisHeight=ImgParaInCls.ImgH）&&（fac1*fac2*fac3=1）");
		return FALSE;
		ImgParaInCls.ImgXoff = 0;
		ImgParaInCls.ImgYoff = 0;
		ImgParaInCls.DisplayWidth = DisWidth;\
		ImgParaInCls.DisplayHeight = DisHeight;

		//创建图像显示空间
		CreateDisplaySpace(ImgParaInCls.ImgH, ImgParaInCls.ImgW);

		//数据写入DisplayData
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

		//初始化文件BITMAPINFO，因图像大小改变
		BITMAPINFO mapinfo;
		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);

		int nn = StretchDIBits(*hdc, 0, 0, DisWidth, DisHeight, 0, 0, ImgParaInCls.ImgW, ImgParaInCls.ImgH, (void*)ImgParaInCls.DisplayData, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
		if (nn == 0) { AfxMessageBox("显示失败！"); return FALSE; }
		else return TRUE;
	}

	return TRUE;
}


//BOOL Img_kele::DisplayImgColor(HDC *hdc, int DisWidth, int DisHeight, int Disoffx, int Disoffy, int srcWidth, int srcHeight, int srcoffx, int srcoffy)
//{
//	//调整宽高
//	if (ImgParaInCls.ImgW != DisWidth || ImgParaInCls.ImgH != DisHeight)
//	{
//		double WidFac = 1.0*ImgParaInCls.ImgW / DisWidth;
//		double HeiFac = 1.0*ImgParaInCls.ImgH / DisHeight;
//
//		//此处LinearFac的赋值考虑的是缩小（即窗口比影像小）
//		double LinearFac = WidFac;
//		if (HeiFac > LinearFac)
//			LinearFac = HeiFac;
//
//		DisWidth = 1.0*ImgParaInCls.ImgW / LinearFac;
//		while (DisWidth % 4)
//			DisWidth++;
//		DisHeight = 1.0*ImgParaInCls.ImgH / LinearFac;
//
//		UCHAR *pdata = new UCHAR[3 * DisWidth*DisHeight]; if (!pdata) { AfxMessageBox("创建重采样数组失败！"); return FALSE; }
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
//					AfxMessageBox("重采样方式选择有误！");
//					return FALSE;
//				}
//			}
//		}
//
//		//初始化文件BITMAPINFO，因图像大小改变
//		BITMAPINFO mapinfo;
//		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);
//
//		int nn = StretchDIBits(*hdc, 0, 0, DisWidth, DisHeight, 0, 0, DisWidth, DisHeight, (void*)pdata, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
//		if (nn == 0) { AfxMessageBox("显示失败！"); return FALSE; }
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
//		//创建图像显示空间
//		CreateDisplaySpace(ImgParaInCls.ImgH, ImgParaInCls.ImgW);
//
//		//数据写入DisplayData
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
//		//初始化文件BITMAPINFO，因图像大小改变
//		BITMAPINFO mapinfo;
//		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);
//
//		int nn = StretchDIBits(*hdc, 0, 0, DisWidth, DisHeight, 0, 0, srcWidth, srcHeight, (void*)ImgParaInCls.DisplayData, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
//		if (nn == 0) { AfxMessageBox("显示失败！"); return FALSE; }
//		else return TRUE;
//	}
//
//	
//	ImgParaInCls.ImgXoff = Disoffx;
//	ImgParaInCls.ImgYoff = Disoffy;
//	ImgParaInCls.DisplayWidth = DisWidth;
//	ImgParaInCls.DisplayHeight = DisHeight;
//
//	//创建图像显示空间
//	CreateDisplaySpace(ImgParaInCls.ImgH, ImgParaInCls.ImgW);
//
//	//数据写入DisplayData
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
//	////数据写入DisplayData
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
//	//初始化文件BITMAPINFO，因图像大小改变
//	BITMAPINFO mapinfo;
//	InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);
//
//	int nn = StretchDIBits(*hdc, 0, 0, DisWidth, DisHeight, 0, 0, srcWidth, srcHeight, (void*)ImgParaInCls.DisplayData, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
//	if (nn == 0) { AfxMessageBox("显示失败！"); return FALSE; }
//	else return TRUE;
//}



//彩色显示影像（数据为UCHAR类型）


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

	//获取主窗口句柄
	HWND hWnd;
	hWnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	HDC hdc;
	hdc = ::GetDC(hWnd);

	int nn = StretchDIBits(hdc, ImgParaInCls.ImgXoff, ImgParaInCls.ImgYoff, ImgParaInCls.DisplayWidth, ImgParaInCls.DisplayHeight, 0, 0, ImgParaInCls.ImgW, ImgParaInCls.ImgH, (void*)ImgParaInCls.DisplayData, &ImgParaInCls.DisplayInfo, DIB_RGB_COLORS, SRCCOPY);
	if (nn == 0) { AfxMessageBox("显示失败！"); return FALSE; }

	return TRUE;
}

//彩色显示影像（数据为float类型）
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
	if (nn == 0) { AfxMessageBox("显示失败！"); return FALSE; }

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
	if (nn == 0) { AfxMessageBox("显示失败！"); return FALSE; }
	else AfxMessageBox("显示成功！");
	return TRUE;
}

//释放影像显示所用内存
BOOL Img_kele::DeleteDisplaySpace()
{
	if (ImgParaInCls.DisplayData)delete[]ImgParaInCls.DisplayData;
	ImgParaInCls.DisplayData = NULL;
	ImgParaInCls.DisplayLen = 0;
	ImgParaInCls.DisplayWidth = 0;
	ImgParaInCls.DisplayHeight = 0;
	return TRUE;
}

//线性拉伸代码
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
	//读入BMP数据
	FILE*fBmp = fopen(BmpFilePath, "rb"); if (!fBmp)return FALSE;

	//检查BMP文件格式
	fread(&ImgParaInCls.BmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fBmp);
	fread(&ImgParaInCls.BmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fBmp);
	if (ImgParaInCls.BmpFileHeader.bfType != 0x4D42) { AfxMessageBox("图像格式BM错误!"); return FALSE; }
	if (ImgParaInCls.BmpInfoHeader.biCompression != BI_RGB) { AfxMessageBox("图像压缩格式错误！"); return FALSE; }
	if (ImgParaInCls.BmpInfoHeader.biBitCount != 24) { AfxMessageBox("错误，非24bit"); return FALSE; }

	//图像数据位置，图像宽、高参数获取
	long   offBits = ImgParaInCls.BmpFileHeader.bfOffBits;
	int    nWidt = ImgParaInCls.BmpInfoHeader.biWidth;
	int    nHeig = ImgParaInCls.BmpInfoHeader.biHeight;

	//附加
	ImgParaInCls.ImgW = ImgParaInCls.BmpInfoHeader.biWidth;
	ImgParaInCls.ImgH = ImgParaInCls.BmpInfoHeader.biHeight;

	cout << "函数内地址：";
	cout << &ImgParaInCls << endl;

	return TRUE;
}

BOOL Img_kele::ReadBmpData(CString BmpFilePath)
{

	//读入BMP数据
	FILE*fBmp = fopen(BmpFilePath, "rb"); if (!fBmp)return FALSE;

	//分配数据空间（行为单位）
	char *pdata = new char[3 * ImgParaInCls.ImgW + 1]; if (!pdata)return FALSE; memset(pdata, 0, (3 * ImgParaInCls.ImgW) * sizeof(char));
	//char *rdata = new char[ImgParaInCls.ImgW + 1]; if (!rdata) { delete[]pdata; return FALSE; } memset(rdata, 0, (Width) * sizeof(char));
	//char *gdata = new char[ImgParaInCls.ImgW + 1]; if (!gdata) { delete[]pdata; delete[]rdata; return FALSE; } memset(gdata, 0, (Width) * sizeof(char));
	//char *bdata = new char[ImgParaInCls.ImgW + 1]; if (!bdata) { delete[]pdata; delete[]rdata; delete[]gdata; return FALSE; }; memset(bdata, 0, (Width) * sizeof(char));


	ImgParaInCls.RMax = -1; ImgParaInCls.RMin = 256;
	ImgParaInCls.GMax = -1; ImgParaInCls.GMin = 256;
	ImgParaInCls.BMax = -1; ImgParaInCls.BMin = 256;
	fseek(fBmp, ImgParaInCls.BmpFileHeader.bfOffBits, SEEK_SET);
	for (int ii = 0; ii < ImgParaInCls.ImgH; ii++)
	{
		fread(pdata, 3 * ImgParaInCls.ImgW, 1, fBmp);
		for (int jj = 0; jj < ImgParaInCls.ImgW; jj++)
		{
			*(ImgParaInCls.ImgBAdr[ii] + jj) = *(pdata + 3 * jj + 0);
			*(ImgParaInCls.ImgGAdr[ii] + jj) = *(pdata + 3 * jj + 1);
			*(ImgParaInCls.ImgRAdr[ii] + jj) = *(pdata + 3 * jj + 2);

			//统计最大值，最小值
			if (*(ImgParaInCls.ImgBAdr[ii] + jj) < ImgParaInCls.BMin)
				ImgParaInCls.BMin = *(ImgParaInCls.ImgBAdr[ii] + jj);
			if (*(ImgParaInCls.ImgBAdr[ii] + jj) > ImgParaInCls.BMax)
				ImgParaInCls.BMax = *(ImgParaInCls.ImgBAdr[ii] + jj);

			if (*(ImgParaInCls.ImgGAdr[ii] + jj) < ImgParaInCls.GMin)
				ImgParaInCls.GMin = *(ImgParaInCls.ImgGAdr[ii] + jj);
			if (*(ImgParaInCls.ImgGAdr[ii] + jj) > ImgParaInCls.GMax)
				ImgParaInCls.GMax = *(ImgParaInCls.ImgGAdr[ii] + jj);

			if (*(ImgParaInCls.ImgRAdr[ii] + jj) < ImgParaInCls.RMin)
				ImgParaInCls.RMin = *(ImgParaInCls.ImgRAdr[ii] + jj);
			if (*(ImgParaInCls.ImgRAdr[ii] + jj) > ImgParaInCls.RMax)
				ImgParaInCls.RMax = *(ImgParaInCls.ImgRAdr[ii] + jj);

		}
	}
	return TRUE;
}

//原始功能为BMP写入000控制文件，但其实可以借鉴为检查BMP文件头，并获取BMP影像数据
BOOL Img_kele::WriteBmpToControlFile(CString BmpFilePath, FILE *fBmp, CString BmpFileName)
{
	//检查BMP文件格式
	fread(&ImgParaInCls.BmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fBmp);
	fread(&ImgParaInCls.BmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fBmp);
	if (ImgParaInCls.BmpFileHeader.bfType != 0x4D42) { AfxMessageBox("图像格式BM错误!"); return FALSE; }
	if (ImgParaInCls.BmpInfoHeader.biCompression != BI_RGB) { AfxMessageBox("图像压缩格式错误！"); return FALSE; }
	if (ImgParaInCls.BmpInfoHeader.biBitCount != 24) { AfxMessageBox("错误，非24bit"); return FALSE; }

	//图像数据位置，图像宽、高参数获取
	long   offBits = ImgParaInCls.BmpFileHeader.bfOffBits;
	int    nWidt = ImgParaInCls.BmpInfoHeader.biWidth;
	int    nHeig = ImgParaInCls.BmpInfoHeader.biHeight;

	//用.bmp文件初始化控制文件路径，再用.000替换.bmp
	CString ControlFilePath(BmpFilePath);
	ControlFilePath.Replace(".bmp", ".000");
	FILE*f000 = fopen(ControlFilePath, "w"); if (!f000) { fclose(fBmp); return FALSE; }

	//写入参数
	if (f000)
	{
		fprintf(f000, "ImageWH     %5d %5d\n", nWidt, nHeig);
		USES_CONVERSION;
		//红波段
		CString RBandPath(BmpFileName); RBandPath.Replace(".bmp", "R.img");
		char*pr = T2A(RBandPath.GetBuffer(0));
		RBandPath.ReleaseBuffer();
		fprintf(f000, "ETM_BAND   3    0    0    255  %-s \n", pr);

		//蓝波段
		CString GBandPath(BmpFileName); GBandPath.Replace(".bmp", "G.img");
		char*pg = T2A(GBandPath.GetBuffer(0));
		GBandPath.ReleaseBuffer();
		fprintf(f000, "ETM_BAND   2    0    0    255  %-s \n", pg);

		//绿波段
		CString BBandPath(BmpFileName); BBandPath.Replace(".bmp", "B.img");
		char*pb = T2A(BBandPath.GetBuffer(0));
		BBandPath.ReleaseBuffer();
		fprintf(f000, "ETM_BAND   1    0    0    255  %-s \n", pb);

	}

	WriteBmpToRGBImg(BmpFilePath, fBmp, nWidt, nHeig, offBits);

	fclose(f000);
	return TRUE;
}

//获取BMP数据的代码
BOOL Img_kele::WriteBmpToRGBImg(CString BmpFilePath, FILE *fBmp, int Width, int Height, long offBits)
{
	//生成RGB三个波段Img路径(替换.bmp为.img)
	CString RBandPath(BmpFilePath); RBandPath.Replace(".bmp", "R.img");
	CString GBandPath(BmpFilePath); GBandPath.Replace(".bmp", "G.img");
	CString BBandPath(BmpFilePath); BBandPath.Replace(".bmp", "B.img");

	//创建RGB三个波段的Img路径
	FILE*fRband = fopen(RBandPath, "wb"); if (!fRband) { fclose(fBmp); return FALSE; }
	FILE*fGband = fopen(GBandPath, "wb"); if (!fGband) { fclose(fBmp); fclose(fRband); return FALSE; }
	FILE*fBband = fopen(BBandPath, "wb"); if (!fBband) { fclose(fBmp);  fclose(fRband); fclose(fGband); return FALSE; }

	//分配数据空间（行为单位）
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

//JPG文件转为BMP文件
BOOL Img_kele::WarpJpgToBmp(CString InFilePath)
{
	//为输出的bmp图片创建路径
	CString BmpFilePath(InFilePath);
	BmpFilePath.Replace(".jpg", ".bmp");

	//读取jpg图片数据至内存
	FILE * fp = NULL;
	char * pFileData; pFileData = NULL;
	int file_size = 0;
	fp = fopen(InFilePath, "rb");
	if (fp != NULL)
	{
		//定位至文件末尾，用ftell得到数据长度
		fseek(fp, 0, SEEK_END);
		file_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		pFileData = new char[file_size]; memset(pFileData, 0, file_size);
		fread(pFileData, 1, file_size, fp);
		fclose(fp);
	}

	//由内存数据保存Bmp文件
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

//最近邻点法
UCHAR Img_kele::NearestNeighbor(float x, float y, int Width, int Height, UCHAR **Data, UCHAR B0)
{
	int x0 = (int)(x + 0.5); if (x0 < 0 || x0 >= Width) { return B0; }
	int y0 = (int)(y + 0.5); if (y0 < 0 || y0 >= Height) { return B0; }

	
	UCHAR *p = *(Data + y0);

	UCHAR ch = *(p + x0);
	
	return ch;
}

//双线性内插
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
		//第一列
		if (y < EPSILON)
		{
			//第一列第一行
			pdata = *Data;
			v = *pdata;
		}
		else if (y > Height - 1 - EPSILON)
		{
			//第一列最后一行
			pdata = *(Data + Height - 1);
			v = *pdata;
		}
		else
		{
			//第一列其他
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
		//第一行
		//已考虑x<EPSILON的情况，故在此不考虑
		if (x > Width - 1 - EPSILON)
		{
			//第一行最后一个
			pdata = *Data;
			v = *pdata + Width - 1;
		}
		else
		{
			//第一行其他
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
		//最后一行
		if (y > Height - 1 + EPSILON)
		{
			//最后一行最后一列
			pdata = *(Data + Height - 1);
			v = *(pdata + Width - 1);
		}
		else
		{
			//最后一行其他
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
		//最后一列其他
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

		//讨论m的取值
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

		//讨论n的取值
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

		//讨论v的取值
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

//双三次卷积
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
BOOL Img_kele::OutputCorrRes(matrix CoeX, matrix CoeY, int Width, int Height, UCHAR**ImgRAdr, UCHAR**ImgGAdr, UCHAR**ImgBAdr, int flag, int degree, CString FilePath)
{

	//打开BMP文件
	FILE *BmpFile = fopen(FilePath, "wb"); if (!BmpFile) { cout << "BMP打开出错" << endl; return FALSE; }
	fwrite(&ImgParaInCls.BmpFileHeader, sizeof(BITMAPFILEHEADER), 1, BmpFile);
	fwrite(&ImgParaInCls.BmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, BmpFile);

	//初始化BMP文件头
	BITMAPFILEHEADER BmpFileHeader;
	BITMAPINFOHEADER BmpInfoHeader;
	InitBitMapFileInfo(ImgParaInCls.ImgW, ImgParaInCls.ImgH, 3, &BmpFileHeader, &BmpInfoHeader);
	fwrite(&BmpFileHeader, sizeof(BITMAPFILEHEADER), 1, BmpFile);
	fwrite(&BmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, BmpFile);
	fseek(BmpFile, BmpFileHeader.bfOffBits, SEEK_SET);

	//开辟内存空间
	BYTE *pdata = new BYTE[3 * ImgParaInCls.ImgW*ImgParaInCls.ImgH];
	memset(pdata, 0, 3 * ImgParaInCls.ImgW*ImgParaInCls.ImgH * sizeof(BYTE));

	double x, y;
	int off;
	for (int ii = 0; ii < ImgParaInCls.ImgH; ii++)
	{
		for (int jj = 0; jj < ImgParaInCls.ImgW; jj++)
		{
			off = 3 * (ii*ImgParaInCls.ImgW + jj);

			if (degree == 1)
			{
				//计算预测坐标
				x = CoeX.mat[0][0] + CoeX.mat[0][1] * jj + CoeX.mat[0][2] * ii;
				y = CoeY.mat[0][0] + CoeY.mat[0][1] * jj + CoeY.mat[0][2] * ii;
			}
			else if (degree == 2)
			{
				//计算预测坐标
				x = CoeX.mat[0][0] + CoeX.mat[0][1] * jj + CoeX.mat[0][2] * ii + CoeX.mat[0][3] * jj*jj + CoeX.mat[0][4] * ii*jj + CoeX.mat[0][5] * ii*ii;
				y = CoeY.mat[0][0] + CoeY.mat[0][1] * jj + CoeY.mat[0][2] * ii + CoeY.mat[0][3] * jj*jj + CoeY.mat[0][4] * ii*jj + CoeY.mat[0][5] * ii*ii;
			}
			else
			{
				AfxMessageBox("拟合系数选择错误！");
			}

			if (flag == 1)
			{
				//最近邻点法
				pdata[off] = NearestNeighbor(x, y, Width, Height, ImgBAdr, 0);
				pdata[off + 1] = NearestNeighbor(x, y, Width, Height, ImgGAdr, 0);
				pdata[off + 2] = NearestNeighbor(x, y, Width, Height, ImgRAdr, 0);
			}
			else if (flag == 2)
			{
				//双线性内插
				pdata[off] = BilinearInterpolation(x, y, Width, Height, ImgBAdr, 0);
				pdata[off + 1] = BilinearInterpolation(x, y, Width, Height, ImgGAdr, 0);
				pdata[off + 2] = BilinearInterpolation(x, y, Width, Height, ImgRAdr, 0);
			}
			else if (flag == 3)
			{
				//三次卷积
				pdata[off] = CubicConvolution(x, y, Width, Height, ImgBAdr, 0);
				pdata[off + 1] = CubicConvolution(x, y, Width, Height, ImgGAdr, 0);
				pdata[off + 2] = CubicConvolution(x, y, Width, Height, ImgRAdr, 0);
			}
			else
			{
				AfxMessageBox("重采样方式选择方式错误");
			}
		}
	}

	//输出BMP文件
	fwrite(pdata, 1, 3 * ImgParaInCls.ImgW*ImgParaInCls.ImgH, BmpFile);
	fclose(BmpFile);
	delete[]pdata;

	return TRUE;
}
BOOL Img_kele::ReadImgDataImfo()
{
	//long HistoR[256]; 
	memset(ImgParaInCls.HistoR, 0, 256);
	memset(ImgParaInCls.HistoG, 0, 256);
	memset(ImgParaInCls.HistoB, 0, 256);

	//UCHAR Rmax; Rmax = 0;
	UCHAR *Rimg;
	UCHAR *Gimg;
	UCHAR *Bimg;

	for (int ii = 0; ii < ImgParaInCls.ImgH; ii++)
	{
		Rimg = ImgParaInCls.ImgRAdr[ii];
		Gimg = ImgParaInCls.ImgGAdr[ii];
		Bimg = ImgParaInCls.ImgBAdr[ii];
		for (int jj = 0; jj < ImgParaInCls.ImgW; jj++)
		{
			if (Rimg[jj] != ImgParaInCls.Back)
			{
				ImgParaInCls.HistoR[Rimg[jj]]++;
			}
			if (Gimg[jj] != ImgParaInCls.Back)
			{
				ImgParaInCls.HistoG[Gimg[jj]]++;
			}
			if (Gimg[jj] != ImgParaInCls.Back)
			{
				ImgParaInCls.HistoB[Bimg[jj]]++;
			}
		}
	}

	int ImgSize = ImgParaInCls.ImgH*ImgParaInCls.ImgW;
	//计算各个像素的数量占总像元数的比例
	for (int ii = 0; ii < 256; ii++)
	{
		ImgParaInCls.HistoR[ii] = 1.0*ImgParaInCls.HistoR[ii] / (float)ImgSize;
		ImgParaInCls.HistoG[ii] = 1.0*ImgParaInCls.HistoG[ii] / (float)ImgSize;
		ImgParaInCls.HistoB[ii] = 1.0*ImgParaInCls.HistoB[ii] / (float)ImgSize;
		if (ii == 0)
		{
			ImgParaInCls.HismaxR = ImgParaInCls.HistoR[ii];
			ImgParaInCls.HismaxG = ImgParaInCls.HistoG[ii];
			ImgParaInCls.HismaxB = ImgParaInCls.HistoB[ii];
		}
		else
		{
			if (ImgParaInCls.HistoR[ii] > ImgParaInCls.HismaxR)
				ImgParaInCls.HismaxR = ImgParaInCls.HistoR[ii];
			if (ImgParaInCls.HistoG[ii] > ImgParaInCls.HismaxG)
				ImgParaInCls.HismaxG = ImgParaInCls.HistoG[ii];
			if (ImgParaInCls.HistoB[ii] > ImgParaInCls.HismaxB)
				ImgParaInCls.HismaxB = ImgParaInCls.HistoB[ii];
		}
	}

	return TRUE;
}

BOOL Img_kele::OutputDensitySlicingAsBMP(UCHAR * ImgAdr, CString FilePath)
{
	//打开BMP文件
	FILE *BmpFile = fopen(FilePath, "wb"); if (!BmpFile) { cout << "BMP打开出错" << endl; return FALSE; }
	//fwrite(&ImgParaInCls.BmpFileHeader, sizeof(BITMAPFILEHEADER), 1, BmpFile);
	//fwrite(&ImgParaInCls.BmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, BmpFile);

	//初始化BMP文件头
	BITMAPFILEHEADER BmpFileHeader;
	BITMAPINFOHEADER BmpInfoHeader;
	InitBitMapFileInfo(ImgParaInCls.ImgW, ImgParaInCls.ImgH, 3, &BmpFileHeader, &BmpInfoHeader);
	fwrite(&BmpFileHeader, sizeof(BITMAPFILEHEADER), 1, BmpFile);
	fwrite(&BmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, BmpFile);
	fseek(BmpFile, BmpFileHeader.bfOffBits, SEEK_SET);

	//输出BMP文件
	fwrite(ImgAdr, 1, 3 * ImgParaInCls.ImgW*ImgParaInCls.ImgH, BmpFile);
	fclose(BmpFile);

	return TRUE;
}

//针对BMP的




BOOL Img_kele::Canopy(double T1, double T2, int MaxIterateTime)
{
	vector<MyCanopy>CanopyList;
	MyCanopy NewCanopy;

	struct tm *ptr;
	time_t lt;
	lt = time(NULL); srand((unsigned)lt);

	/*srand(1);*/

	int centerii, centerjj;
	int currii, currjj;

	//标识是否已被删除
	BOOL *isDelted = new BOOL[ImgParaInCls.ImgW*ImgParaInCls.ImgH]; if (isDelted == NULL) { AfxMessageBox("isDelted数组控件开辟失败！"); }
	memset(isDelted, 0, ImgParaInCls.ImgW*ImgParaInCls.ImgH * sizeof(BOOL));

	int curr;
	int XSize = ImgParaInCls.ImgW;
	int YSize = ImgParaInCls.ImgH;
	int ImgSize = XSize * YSize;

	int OldRemainNum = ImgParaInCls.ImgW*ImgParaInCls.ImgH;
	int NewRemainNum = ImgParaInCls.ImgW*ImgParaInCls.ImgH;

	int T1Num;
	int ClassNum;
	double dis;

	while (NewRemainNum != 0)
	{
		if (OldRemainNum == NewRemainNum)
		{
			//随机选取第一个类中心点
			//以及如果此次循环结束并没有新的点成为类中心或被归为新的类，为避免程序进入死循环，重新随机选取类中心
			centerii = rand() % YSize;
			centerjj = rand() % XSize;
			curr = centerii * XSize + centerjj;
			while (isDelted[curr] == 1)
			{
				if (curr < ImgSize - 1)
					curr++;
				else
					curr = 0;
			}
			//将该点存入Canopy列表中
			NewCanopy.x = centerjj;
			NewCanopy.y = centerii;
			NewCanopy.Sumx = centerjj;
			NewCanopy.Sumy = centerii;
			NewCanopy.Count = 1;
			CanopyList.push_back(NewCanopy);
			//从List中删除该点
			isDelted[curr] = 1;

			OldRemainNum--;
			NewRemainNum--;
		}
		else
		{
			OldRemainNum = NewRemainNum;
		}

		//对仍留在列表中的点进行遍历并归类
		for (int currii = 0; currii < YSize; currii++)
		{
			for (int currjj = 0; currjj < XSize; currjj++)
			{
				if (isDelted[currii * XSize + currjj] == 0)
				{
					//没有从待选List中删除的点
					T1Num = 0;
					for (vector<MyCanopy>::iterator it = CanopyList.begin(); it != CanopyList.end(); it++)
					{
						//获取当前是第几类的类中心
						//ClassNum = distance(CanopyList.begin(), it) + 1;
						ClassNum = distance(CanopyList.begin(), it);

						//计算到当前所有类中心的距离
						dis = 0;
						centerii = (*it).y;
						centerjj = (*it).x;

						dis += abs(ImgParaInCls.ImgRAdr[currii][currjj] - ImgParaInCls.ImgRAdr[centerii][centerjj]);
						dis += abs(ImgParaInCls.ImgGAdr[currii][currjj] - ImgParaInCls.ImgGAdr[centerii][centerjj]);
						dis += abs(ImgParaInCls.ImgBAdr[currii][currjj] - ImgParaInCls.ImgBAdr[centerii][centerjj]);
						dis = 1.0 * dis / 3;

						//到当前类中心距离判断
						if (dis >= 0 && dis <= T2)
						{
							//inside T2,member of cluster
							CanopyList[ClassNum].Sumx += currjj;
							CanopyList[ClassNum].Sumy += currii;
							CanopyList[ClassNum].Count++;
							//can not be a cluster center
							isDelted[currii*XSize + currjj] = 1;
							NewRemainNum--;
							break;
							//thisClsNum++;
						}
						else if (dis > T2 && dis <= T1)
						{
							//outside T2 inside T1,member of cluster
							CanopyList[ClassNum].Sumx += currjj;
							CanopyList[ClassNum].Sumy += currii;
							CanopyList[ClassNum].Count++;
							//could also be a center itself
						}
						else if (dis > T1)
						{
							//outside T1 boundary,not a member of this cluster
							T1Num++;
						}
						else
						{
							AfxMessageBox("距离计算错误！！！");
							return FALSE;
						}

					}
					if (T1Num == CanopyList.size())
					{
						//同时满足到所有类中心的距离大于T1
						//且未被归为任何一类（即不是<T2跳出循环后误进此判别）
						NewCanopy.x = currjj;
						NewCanopy.y = currii;
						NewCanopy.Sumx = centerjj;
						NewCanopy.Sumy = centerii;
						NewCanopy.Count = 1;
						CanopyList.push_back(NewCanopy);
						isDelted[currii*XSize + currjj] = 1;
						NewRemainNum--;
					}
				}
			}
		}

	}

	for (vector<MyCanopy>::iterator it = CanopyList.begin(); it != CanopyList.end(); it++)
	{
		//cout << "距离=" << distance(CanopyList.begin(), it) << endl;
		(*it).Sumx /= 1.0*(*it).Count;
		(*it).Sumy /= 1.0*(*it).Count;
		//cout << "原Center=(" << (*it).x << "," << (*it).y << ")" << endl;
		//cout << "现Center=(" << (*it).Sumx << "," << (*it).Sumy << ")" << endl;
		//cout << "类内像元数=" << (*it).Count << endl;
	}

	//KMeans部分
	//需要输入参数：MaxIterateTime,ThresholdValue
	
	double ThresholdValue = 0.0005;

	ImgParaInCls.ClassNum = CanopyList.size();

	ClassNum = CanopyList.size();
	//类中心数组
	double *Center = new double[3 * ClassNum]; if (!Center) { AfxMessageBox("创建类中心数组失败！"); return FALSE; }
	memset(Center, 0, 3 * ClassNum * sizeof(double));
	//下一次分类计算类中心
	double *NextCenter = new double[3 * ClassNum]; if (!NextCenter) { AfxMessageBox("创建统计类中心数组失败！"); return FALSE; }
	memset(NextCenter, 0, 3 * ClassNum * sizeof(double));
	//统计每个类的像元数
	int *PixelNum = new int[ClassNum]; if (!PixelNum) { AfxMessageBox("创建统计像元数数组失败！"); return FALSE; }
	memset(PixelNum, 0, ClassNum * sizeof(int));

	int off;
	int intx, inty;
	for (vector<MyCanopy>::iterator it = CanopyList.begin(); it != CanopyList.end(); it++)
	{
		//初始化类中心
		off = 3 * distance(CanopyList.begin(), it);
		intx = (int)(floor((*it).Sumx + 0.5));
		inty = (int)(floor((*it).Sumy + 0.5));
		Center[off + 0] = ImgParaInCls.ImgRAdr[intx][inty];
		Center[off + 0] = ImgParaInCls.ImgGAdr[intx][inty];
		Center[off + 0] = ImgParaInCls.ImgBAdr[intx][inty];
	}

	int flag; double mindis, curdis;
	UCHAR x1, x2, x3;
	double y1, y2, y3;
	double m1, m2, m3, m4;
	double n1, n2, n3, n4;
	double distance = -1;
	int count;
	for (int mm = 0; mm < MaxIterateTime; mm++)
	{
		//清空上一次数据，为此次做准备
		memset(NextCenter, 0, 3 * ClassNum * sizeof(double));
		memset(PixelNum, 0, ClassNum * sizeof(int));
		count = 0;
		for (int ii = 0; ii < YSize; ii++)
		{
			for (int jj = 0; jj < XSize; jj++)
			{
				//此像元点在空间中的坐标
				x1 = ImgParaInCls.ImgRAdr[ii][jj];
				x2 = ImgParaInCls.ImgGAdr[ii][jj];
				x3 = ImgParaInCls.ImgBAdr[ii][jj];

				for (int kk = 0; kk < ClassNum; kk++)
				{
					//类中心的位置
					y1 = Center[3 * kk + 0];
					y2 = Center[3 * kk + 1];
					y3 = Center[3 * kk + 2];

					//计算相对于中心的距离，并归类
					if (kk == 0)
					{
						flag = 0;
						mindis = sqrt((y1 - x1)*(y1 - x1) + (y2 - x2)*(y2 - x2) + (y3 - x3)*(y3 - x3));
					}
					else
					{
						curdis = sqrt((y1 - x1)*(y1 - x1) + (y2 - x2)*(y2 - x2) + (y3 - x3)*(y3 - x3));
						if (curdis < mindis)
						{
							mindis = curdis;
							flag = kk;
						}
					}
				}
				//分类图像并
				ImgParaInCls.Classify[ii][jj] = flag;

				//为计算下一个类中心准备
				NextCenter[3 * flag] += x1;
				NextCenter[3 * flag + 1] += x2;
				NextCenter[3 * flag + 2] += x3;
				PixelNum[flag]++;
			}
		}

		//cout << mm << ":" << endl;
		for (int ii = 0; ii < ClassNum; ii++)
		{
			//cout << PixelNum[ii] << " ";
		}
		//cout << endl;

		//类中心计算
		for (int nn = 0; nn < ClassNum; nn++)
		{
			//计算下一个类中心
			NextCenter[3 * nn] /= PixelNum[nn];
			NextCenter[3 * nn + 1] /= PixelNum[nn];
			NextCenter[3 * nn + 2] /= PixelNum[nn];

			if (mm > 0)
			{
				//除第一次循环外，计算类中心与上一次类中心的距离是否小于阈值
				m1 = Center[3 * nn];
				m2 = Center[3 * nn + 1];
				m3 = Center[3 * nn + 2];
				n1 = NextCenter[3 * nn];
				n2 = NextCenter[3 * nn + 1];
				n3 = NextCenter[3 * nn + 2];

				distance = sqrt((m1 - n1)*(m1 - n1) + (m2 - n2)*(m2 - n2) + (m3 - n3)*(m3 - n3));

				if (distance < ThresholdValue)
				{
					count++;
				}
			}
			//更换类中心
			Center[3 * nn] = NextCenter[3 * nn];
			Center[3 * nn + 1] = NextCenter[3 * nn + 1];
			Center[3 * nn + 2] = NextCenter[3 * nn + 2];
		}
		//当且仅当K个类的类中心变化的距离都小于阈值时，退出循环
		if (count == ClassNum - 1)
			break;
	}

	for (int ii = 0; ii < ClassNum; ii++)
	{
		ImgParaInCls.ClassInfo.push_back(PixelNum[ii]);
	}

	//cout << "vector数据：" << endl;
	//for (vector<int>::iterator it = ImgParaInCls.ClassInfo.begin(); it != ImgParaInCls.ClassInfo.end(); it++)
	//{
	//	cout << (*it) << " ";
	//}

	delete[]Center; delete[]NextCenter; delete[]PixelNum;
	cout << "K-Means分类成功！" << endl;

	return TRUE;
}

BOOL Img_kele::DisplayImgGray(HDC *hdc, int DisWidth, int DisHeight, int Disoffx, int Disoffy, int srcWidth, int srcHeight, int srcoffx, int srcoffy, UCHAR **ImgAdr)
{
	//调整宽高
	if (srcWidth != DisWidth || srcHeight != DisHeight)
	{
		double WidFac = 1.0*srcWidth / DisWidth;
		double HeiFac = 1.0*srcHeight / DisHeight;

		//此处LinearFac的赋值考虑的是缩小（即窗口比影像小）
		double LinearFac = WidFac;
		if (HeiFac > LinearFac)
			LinearFac = HeiFac;

		DisWidth = 1.0*srcWidth / LinearFac;
		while (DisWidth % 4)
			DisWidth++;
		DisHeight = 1.0*srcHeight / LinearFac;

		UCHAR *pdata = new UCHAR[3 * DisWidth*DisHeight]; if (!pdata) { AfxMessageBox("创建重采样数组失败！"); return FALSE; }
		memset(pdata, 0, sizeof(UCHAR) * 3 * DisWidth*DisHeight);

		//暂定为用最近邻点法
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
					pdata[off] = NearestNeighbor(srcoffx + jj * LinearFac, srcoffy + ii * LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgAdr, 0);
					pdata[off + 1] = NearestNeighbor(srcoffx + jj * LinearFac, srcoffy + ii * LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgAdr, 0);
					pdata[off + 2] = NearestNeighbor(srcoffx + jj * LinearFac, srcoffy + ii * LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgAdr, 0);
				}
				else if (Sel == 1)
				{
					pdata[off] = BilinearInterpolation(srcoffx + jj * LinearFac, srcoffy + ii * LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgAdr, 0);
					pdata[off + 1] = BilinearInterpolation(srcoffx + jj * LinearFac, srcoffy + ii * LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgAdr, 0);
					pdata[off + 2] = BilinearInterpolation(srcoffx + jj * LinearFac, srcoffy + ii * LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgAdr, 0);
				}
				else if (Sel == 2)
				{
					pdata[off] = CubicConvolution(srcoffx + jj * LinearFac, srcoffy + ii * LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgAdr, 0);
					pdata[off + 1] = CubicConvolution(srcoffx + jj * LinearFac, srcoffy + ii * LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgAdr, 0);
					pdata[off + 2] = CubicConvolution(srcoffx + jj * LinearFac, srcoffy + ii * LinearFac, ImgParaInCls.ImgW, ImgParaInCls.ImgH, ImgAdr, 0);
				}
				else
				{
					AfxMessageBox("重采样方式选择有误！");
					return FALSE;
				}
			}
		}

		//初始化文件BITMAPINFO，因图像大小改变
		BITMAPINFO mapinfo;
		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);

		int nn = StretchDIBits(*hdc, Disoffx, Disoffy, DisWidth, DisHeight, 0, 0, DisWidth, DisHeight, (void*)pdata, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
		if (nn == 0) { AfxMessageBox("显示失败！"); return FALSE; }
		else return TRUE;
		delete[]pdata;
	}
	else
	{
		ImgParaInCls.ImgXoff = Disoffx;
		ImgParaInCls.ImgYoff = Disoffy;
		ImgParaInCls.DisplayWidth = DisWidth;
		ImgParaInCls.DisplayHeight = DisHeight;

		//创建图像显示空间
		CreateDisplaySpace(ImgParaInCls.ImgH, ImgParaInCls.ImgW);

		//数据写入DisplayData
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

		//初始化文件BITMAPINFO，因图像大小改变
		BITMAPINFO mapinfo;
		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);

		int nn = StretchDIBits(*hdc, 0, 0, DisWidth, DisHeight, 0, 0, srcWidth, srcHeight, (void*)ImgParaInCls.DisplayData, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
		if (nn == 0) { AfxMessageBox("显示失败！"); return FALSE; }
		else return TRUE;
	}

}
BOOL Img_kele::CreateClassifySpace()
{
	cout << "给Classify数组开辟内存！！！" << endl;

	ImgParaInCls.Classify = new UCHAR*[ImgParaInCls.ImgH]; if (!ImgParaInCls.Classify) { AfxMessageBox("创建分类数组空间失败！"); return FALSE; }
	memset(ImgParaInCls.Classify, 0, ImgParaInCls.ImgH);
	for (int ii = 0; ii < ImgParaInCls.ImgH; ii++)
	{
		UCHAR *pdata = new UCHAR[ImgParaInCls.ImgW]; if (!pdata) { AfxMessageBox("创建分类数组空间失败！"); return FALSE; }
		memset(pdata, 0, ImgParaInCls.ImgW);
		ImgParaInCls.Classify[ii] = pdata;
	}
	return TRUE;
}