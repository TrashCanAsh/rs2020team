#include "ReadTIF.h"
#include"stdafx.h"


ReadTIF::ReadTIF()
{
}


ReadTIF::~ReadTIF()
{
}

ReadTIF::ReadTIF(const ReadTIF & CopyImg)
{

	TifFile.ImgH = CopyImg.TifFile.ImgH;
	TifFile.ImgW = CopyImg.TifFile.ImgW;
	TifFile.RMax = CopyImg.TifFile.RMax;
	TifFile.RMin = CopyImg.TifFile.RMin;
	TifFile.GMax = CopyImg.TifFile.GMax;
	TifFile.GMin = CopyImg.TifFile.GMin;
	TifFile.BMax = CopyImg.TifFile.BMax;
	TifFile.BMin = CopyImg.TifFile.BMin;
	TifFile.EdRmax = CopyImg.TifFile.EdRmax;
	TifFile.EdRmin = CopyImg.TifFile.EdRmin;
	TifFile.EdGmax = CopyImg.TifFile.EdGmax;
	TifFile.EdGmin = CopyImg.TifFile.EdGmin;
	TifFile.EdBmax= CopyImg.TifFile.EdGmin;
	TifFile.EdBmin = CopyImg.TifFile.EdBmin;

	TifFile.ImgRAdr = new UINT16 *[TifFile.ImgH]; memset(TifFile.ImgRAdr, 0, TifFile.ImgH * sizeof(UCHAR*));
	TifFile.ImgGAdr = new UINT16 *[TifFile.ImgH]; memset(TifFile.ImgGAdr, 0, TifFile.ImgH * sizeof(UCHAR*));
	TifFile.ImgBAdr = new UINT16 *[TifFile.ImgH]; memset(TifFile.ImgBAdr, 0, TifFile.ImgH * sizeof(UCHAR*));
	//TifFile.ImgMAdr = new UINT16 *[TifFile.ImgH]; memset(TifFile.ImgMAdr, 0, TifFile.ImgH * sizeof(UCHAR*));

	for (int jj = 0; jj < 4; jj++)
	{
		if (jj == 0)
		{
			for (int ii = 0; ii < TifFile.ImgH; ii++)
			{
				UINT16 *pdata = new UINT16[TifFile.ImgW]; memset(pdata, 0, TifFile.ImgW * sizeof(UINT16));
				TifFile.ImgRAdr[ii] = pdata;
			}
		}
		else if (jj == 1)
		{
			for (int ii = 0; ii < TifFile.ImgH; ii++)
			{
				UINT16 *pdata = new UINT16[TifFile.ImgW]; memset(pdata, 0, TifFile.ImgW * sizeof(UINT16));
				TifFile.ImgGAdr[ii] = pdata;
			}
		}
		else if (jj == 2)
		{
			for (int ii = 0; ii < TifFile.ImgH; ii++)
			{
				UINT16 *pdata = new UINT16[TifFile.ImgW]; memset(pdata, 0, TifFile.ImgW * sizeof(UINT16));
				TifFile.ImgBAdr[ii] = pdata;
			}
		}
		else if (jj == 3)
		{
			/*for (int ii = 0; ii < TifFile.ImgH; ii++)
			{
				UINT16 *pdata = new UINT16[TifFile.ImgW]; memset(pdata, 0, TifFile.ImgW * sizeof(UINT16));
				TifFile.ImgMAdr[ii] = pdata;
			}*/
		}
	}

	for (int ii = 0; ii < TifFile.ImgH; ii++)
	{
		for (int jj = 0; jj < TifFile.ImgW; jj++)
		{
			UINT16 rr = CopyImg.TifFile.ImgRAdr[ii][jj];
			UINT16 gg = CopyImg.TifFile.ImgGAdr[ii][jj];
			UINT16 bb = CopyImg.TifFile.ImgBAdr[ii][jj];
			//UINT16 mm = CopyImg.TifFile.ImgMAdr[ii][jj];
			TifFile.ImgRAdr[ii][jj] = rr;
			TifFile.ImgGAdr[ii][jj] = gg;
			TifFile.ImgBAdr[ii][jj] = bb;
			//TifFile.ImgMAdr[ii][jj] = mm;
		}

	}
}

BOOL ReadTIF::InitBitMapInfo(int nWidth, int nHeight, int colorbit, BITMAPINFO * pinfo)
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

BOOL ReadTIF::ReadTIFFile(CString FilePath)
{

	char *InImg = (LPSTR)(LPCTSTR)FilePath;
	const char *pszFormat = "GTiff";

	//ע���ļ���ʽ  
	GDALAllRegister();
	//using namespace std;
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");  //֧������·��

	GDALDataset *poIn = (GDALDataset*)GDALOpen(InImg, GA_ReadOnly);
	if (poIn == NULL)
	{
		AfxMessageBox("�ļ���ʧ�ܣ�");
		return false;
	}

	GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);
	if (poDriver == NULL)
	{
		GDALClose((GDALDatasetH)poIn);
		AfxMessageBox("��������ʧ�ܣ�");
		return false;
	}

	//ͼ����������Ļ�ȡ
	TifFile.ImgW = poIn->GetRasterXSize();
	TifFile.ImgH = poIn->GetRasterYSize();
	TifFile.BandNum = poIn->GetRasterCount();
	TifFile.strDescription = poIn->GetDriver()->GetDescription();
	TifFile.type = poIn->GetRasterBand(1)->GetRasterDataType();
	TifFile.eDT = poIn->GetRasterBand(1)->GetRasterDataType();
	poIn->GetGeoTransform(TifFile.GeoTrans);
	//һ��Ĭ��TIFӰ�񱳾�ֵΪ0
	TifFile.Back = 0;

	cout << "X:" << TifFile.ImgW << " Y:" << TifFile.ImgH << " BandNum:" << TifFile.BandNum << endl;
	if (TifFile.type == GDT_UInt16)
	{
		cout << "�������ͣ�" << "UInt16" << endl;
	}

	if (TifFile.BandNum < 3)
	{
		//ֻȡ��һ���������ݣ�����ImgRAdr��
		//�����ڴ�ռ�
		TifFile.ImgRAdr = new UINT16 *[TifFile.ImgH]; memset(TifFile.ImgRAdr, 0, TifFile.ImgH * sizeof(UINT16*));
		for (int ii = 0; ii < TifFile.ImgH; ii++)
		{
			UINT16 *pdata = new UINT16[TifFile.ImgW]; memset(pdata, 0, TifFile.ImgW * sizeof(UINT16));
			TifFile.ImgRAdr[ii] = pdata;
		}
		//ͼ�����ݶ���
		GDALRasterBand *poBand;
		poBand = poIn->GetRasterBand(1);
		for (int ii = 0; ii < TifFile.ImgH; ii++)
		{
			poBand->RasterIO(GF_Read, 0, 0, TifFile.ImgW, 1, TifFile.ImgRAdr[ii], TifFile.ImgW, 1, GDT_UInt16, 0, 0);
		}
	}
	else
	{
		//ֻȡǰ���������ݣ�����ImgRAdr��ImgGAdr��ImgBAdr��
		//�����ڴ�ռ�
		TifFile.ImgRAdr = new UINT16 *[TifFile.ImgH]; memset(TifFile.ImgRAdr, 0, TifFile.ImgH * sizeof(UINT16*));
		for (int ii = 0; ii < TifFile.ImgH; ii++)
		{
			UINT16 *pdata = new UINT16[TifFile.ImgW]; memset(pdata, 0, TifFile.ImgW * sizeof(UINT16));
			TifFile.ImgRAdr[ii] = pdata;
		}
		TifFile.ImgGAdr = new UINT16 *[TifFile.ImgH]; memset(TifFile.ImgGAdr, 0, TifFile.ImgH * sizeof(UINT16*));
		for (int ii = 0; ii < TifFile.ImgH; ii++)
		{
			UINT16 *pdata = new UINT16[TifFile.ImgW]; memset(pdata, 0, TifFile.ImgW * sizeof(UINT16));
			TifFile.ImgGAdr[ii] = pdata;
		}
		TifFile.ImgBAdr = new UINT16 *[TifFile.ImgH]; memset(TifFile.ImgBAdr, 0, TifFile.ImgH * sizeof(UINT16*));
		for (int ii = 0; ii < TifFile.ImgH; ii++)
		{
			UINT16 *pdata = new UINT16[TifFile.ImgW]; memset(pdata, 0, TifFile.ImgW * sizeof(UINT16));
			TifFile.ImgBAdr[ii] = pdata;
		}
		//ͼ�����ݶ���
		GDALRasterBand *poBand;
		poBand = poIn->GetRasterBand(1);
		for (int ii = 0; ii < TifFile.ImgH; ii++)
		{
			poBand->RasterIO(GF_Read, 0, 0, TifFile.ImgW, 1, TifFile.ImgBAdr[ii], TifFile.ImgW, 1, GDT_UInt16, 0, 0);
		}
		poBand = poIn->GetRasterBand(2);
		for (int ii = 0; ii < TifFile.ImgH; ii++)
		{
			poBand->RasterIO(GF_Read, 0, 0, TifFile.ImgW, 1, TifFile.ImgGAdr[ii], TifFile.ImgW, 1, GDT_UInt16, 0, 0);
		}
		poBand = poIn->GetRasterBand(3);
		for (int ii = 0; ii < TifFile.ImgH; ii++)
		{
			poBand->RasterIO(GF_Read, 0, 0, TifFile.ImgW, 1, TifFile.ImgRAdr[ii], TifFile.ImgW, 1, GDT_UInt16, 0, 0);
		}
	}
	return TRUE;
}

BOOL ReadTIF::GetTIFDataInfo()
{
	//ͳ��ÿ�����ε����ֵ��Сֵ
		//��ǰδ�����ų�����ֵ��Ӱ��
	if (TifFile.BandNum < 3)
	{
		TifFile.EdRmin = 65535;
		TifFile.EdRmax = 0;
		for (int ii = 0; ii < TifFile.ImgH; ii++)
		{
			for (int jj = 0; jj < TifFile.ImgW; jj++)
			{
				if (TifFile.ImgRAdr[ii][jj] > TifFile.EdRmax)
					TifFile.EdRmax = TifFile.ImgRAdr[ii][jj];
				if (TifFile.ImgRAdr[ii][jj] < TifFile.EdRmin)
					TifFile.EdRmin = TifFile.ImgRAdr[ii][jj];
			}
		}
	}
	else
	{
		TifFile.EdRmin = 65535;
		TifFile.EdRmax = 0;
		for (int ii = 0; ii < TifFile.ImgH; ii++)
		{
			for (int jj = 0; jj < TifFile.ImgW; jj++)
			{
				if (TifFile.ImgRAdr[ii][jj] > TifFile.EdRmax)
					TifFile.EdRmax = TifFile.ImgRAdr[ii][jj];
				if (TifFile.ImgRAdr[ii][jj] < TifFile.EdRmin)
					TifFile.EdRmin = TifFile.ImgRAdr[ii][jj];
			}
		}
		TifFile.EdGmin = 65535;
		TifFile.EdGmax = 0;
		for (int ii = 0; ii < TifFile.ImgH; ii++)
		{
			for (int jj = 0; jj < TifFile.ImgW; jj++)
			{
				if (TifFile.ImgGAdr[ii][jj] > TifFile.EdGmax)
					TifFile.EdGmax = TifFile.ImgGAdr[ii][jj];
				if (TifFile.ImgGAdr[ii][jj] < TifFile.EdGmin)
					TifFile.EdGmin = TifFile.ImgGAdr[ii][jj];
			}
		}
		TifFile.EdBmin = 65535;
		TifFile.EdBmax = 0;
		for (int ii = 0; ii < TifFile.ImgH; ii++)
		{
			for (int jj = 0; jj < TifFile.ImgW; jj++)
			{
				if (TifFile.ImgBAdr[ii][jj] > TifFile.EdBmax)
					TifFile.EdBmax = TifFile.ImgBAdr[ii][jj];
				if (TifFile.ImgBAdr[ii][jj] < TifFile.EdBmin)
					TifFile.EdBmin = TifFile.ImgBAdr[ii][jj];
			}
		}
	}
	TifFile.EdRmax /= 255;
	if (TifFile.EdRmax > 255)
		TifFile.EdRmax = 255;
	TifFile.EdRmin /= 255;

	TifFile.EdGmax /= 255;
	if (TifFile.EdGmax > 255)
		TifFile.EdGmax = 255;
	TifFile.EdGmin /= 255;
	
	TifFile.EdBmax /= 255;
	if (TifFile.EdBmax > 255)
		TifFile.EdBmax = 255;
	TifFile.EdBmin /= 255;
	return TRUE;
}

UINT16 ReadTIF::NearestNeighbor(float x, float y, int Width, int Height, UINT16 * Data, UINT16 B0)
{
	int x0 = (int)(x + 0.5); if (x0 < 0 || x0 >= Width) { return B0; }
	int y0 = (int)(y + 0.5); if (y0 < 0 || y0 >= Height) { return B0; }


	//UINT16 *p = *(Data + y0);

	UINT16 ch = Data[y0*Width + x0];

	return ch;
}

BOOL ReadTIF::DisplayTIFImgColor(HDC * hdc, int DisWidth, int DisHeight, int Disoffx, int Disoffy, int srcWidth, int srcHeight, UINT16 * ImgAdr)
{
	//������Ӱ����ʾ
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
		//int Sel = 0;
		//int Sel = resample_combo.GetCurSel();

		int off = 0;
		//char b, g, r;
		for (int ii = 0; ii < DisHeight; ii++)
		{
			for (int jj = 0; jj < DisWidth; jj++)
			{
				off = 3 * ((DisHeight - 1 - ii) * DisWidth + jj);

				pdata[off] = (int)1.0*NearestNeighbor(jj * LinearFac, ii * LinearFac, srcWidth, srcHeight, ImgAdr, 0) / 256.0;
				pdata[off + 1] = (int)1.0*NearestNeighbor(jj * LinearFac, ii * LinearFac, srcWidth, srcHeight, ImgAdr, 0) / 256.0;
				pdata[off + 2] = (int)1.0*NearestNeighbor(jj * LinearFac, ii * LinearFac, srcWidth, srcHeight, ImgAdr, 0) / 256.0;

			}
		}

		//��ʼ���ļ�BITMAPINFO����ͼ���С�ı�
		BITMAPINFO mapinfo;
		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);

		int nn = StretchDIBits(*hdc, Disoffx, Disoffy, DisWidth, DisHeight, 0, 0, DisWidth, DisHeight, (void*)pdata, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
		if (nn == 0) { AfxMessageBox("��ʾʧ�ܣ�"); return FALSE; }
		else return TRUE;
		delete[]pdata;
	}

}

BOOL ReadTIF::DisplayTIFImgColor(HDC * hdc, int DisWidth, int DisHeight, int Disoffx, int Disoffy, int srcWidth, int srcHeight, UINT16 * ImgRAdr, UINT16 * ImgGAdr, UINT16 * ImgBAdr)
{
	//������Ӱ����ʾ
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
		//int Sel = 0;
		//int Sel = resample_combo.GetCurSel();

		int off = 0;
		//char b, g, r;
		for (int ii = 0; ii < DisHeight; ii++)
		{
			for (int jj = 0; jj < DisWidth; jj++)
			{
				off = 3 * ((DisHeight - 1 - ii) * DisWidth + jj);

				pdata[off] = (int)1.0*NearestNeighbor(jj * LinearFac, ii * LinearFac, srcWidth, srcHeight, ImgBAdr, 0) / 256.0;
				pdata[off + 1] = (int)1.0*NearestNeighbor(jj * LinearFac, ii * LinearFac, srcWidth, srcHeight, ImgGAdr, 0) / 256.0;
				pdata[off + 2] = (int)1.0*NearestNeighbor(jj * LinearFac, ii * LinearFac, srcWidth, srcHeight, ImgRAdr, 0) / 256.0;

			}
		}

		//��ʼ���ļ�BITMAPINFO����ͼ���С�ı�
		BITMAPINFO mapinfo;
		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);

		int nn = StretchDIBits(*hdc, Disoffx, Disoffy, DisWidth, DisHeight, 0, 0, DisWidth, DisHeight, (void*)pdata, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
		if (nn == 0) { AfxMessageBox("��ʾʧ�ܣ�"); return FALSE; }
		else return TRUE;
		delete[]pdata;
	}
}

BOOL ReadTIF::TIFCanopy(CString InFilrPath, CString OutFilrPath, double T1, double T2)
{

	//����Ӧ�ǻ�ȡ�ؼ��е�Tif�ļ�·��
	//CString strInImg, strOutImg;
	//strInImg = ".\\data\\753Subset.tif";
	//strOutImg = ".\\data\\753Classify.tif";
	char *InImg = (LPSTR)(LPCTSTR)InFilrPath;
	char *OutImg = (LPSTR)(LPCTSTR)OutFilrPath;
	const char *pszFormat = "GTiff";

	//double T1 = 5000, T2 = 4500;

	//ע���ļ���ʽ  
	GDALAllRegister();
	//using namespace std;
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");  //֧������·��

	GDALDataset *poIn = (GDALDataset*)GDALOpen(InImg, GA_ReadOnly);
	if (poIn == NULL)
	{
		AfxMessageBox("�ļ���ʧ�ܣ�");
		return false;
	}

	GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);
	if (poDriver == NULL)
	{
		GDALClose((GDALDatasetH)poIn);
		AfxMessageBox("��������ʧ�ܣ�");
		return false;
	}

	//ͼ����������Ļ�ȡ
	int XSize = poIn->GetRasterXSize();
	int YSize = poIn->GetRasterYSize();
	int BandNum = poIn->GetRasterCount();
	CString strDescription = poIn->GetDriver()->GetDescription();
	GDALDataType type = poIn->GetRasterBand(1)->GetRasterDataType();
	GDALDataType eDT = poIn->GetRasterBand(1)->GetRasterDataType();
	int ImgSize = XSize * YSize;
	cout << "X:" << XSize << " Y:" << YSize << " BandNum:" << BandNum << endl;
	if (type == GDT_UInt16)
	{
		cout << "�������ͣ�" << "UInt16" << endl;
	}

	//����ļ��Ĵ����Լ�ͶӰ��Ϣ��д��
	GDALDataset*poOut = poDriver->Create(OutImg, XSize, YSize, 1, eDT, NULL);
	GDALRasterBand* pOut = poOut->GetRasterBand(1);
	if (poOut == NULL)
	{
		AfxMessageBox("д���ļ�����ʧ�ܣ�");
	}
	double GeoTrans[6] = { 0 };
	poIn->GetGeoTransform(GeoTrans);
	poOut->SetGeoTransform(GeoTrans);
	poOut->SetProjection(poIn->GetProjectionRef());

	//������ͼ������
	UINT16*InData = new UINT16[XSize*YSize*BandNum];
	if (InData == NULL) { AfxMessageBox("����д����������ʧ�ܣ�"); return false; }
	memset(InData, 0, XSize*YSize *BandNum * sizeof(UINT16));

	//������������
	UINT16 *Classify = new UINT16[XSize*YSize]; if (!Classify) { AfxMessageBox("����������������ʧ��"); return false; }
	memset(Classify, 0, XSize*YSize * sizeof(UINT16));

	//ͼ�����ݶ���
	GDALRasterBand *poBand;
	for (int k = 1; k <= BandNum; k++)
	{
		poBand = poIn->GetRasterBand(k);
		poBand->RasterIO(GF_Read, 0, 0, XSize, YSize, InData + (k - 1)*XSize*YSize, XSize, YSize, GDT_UInt16, 0, 0);
	}

	//�������������
	struct tm *ptr;
	time_t lt;
	lt = time(NULL); srand((unsigned)lt);

	int curr;
	int ClassNum = 0;
	//��������Ԫ��������
	int centerii, centerjj;
	//��ǰ��Ԫ��������
	int currii, currjj;
	UINT16 *CenterVal = new UINT16[BandNum];
	if (CenterVal == NULL) { cout << "������������Ϣ���鿪��ʧ�ܣ�" << endl; };
	memset(CenterVal, 0, BandNum * sizeof(UINT16));

	double dis; double val;

	BOOL *isDelted = new BOOL[XSize*YSize]; if (isDelted == NULL) { cout << "isDelted����ؼ�����ʧ�ܣ�" << endl; }
	memset(isDelted, 0, XSize*YSize * sizeof(BOOL));
	//int thisClsNum;

	vector<PixelPT>CanopyList;
	PixelPT NewCanopy;

	int OldRemainNum = ImgSize;
	int NewRemainNum = ImgSize;
	int T1Num;//����ָʾ�Ƿ��������ľ��붼>T1

	//��ʼѭ��
	while (NewRemainNum != 0)
	{
		if (OldRemainNum == NewRemainNum)
		{
			//���ѡȡ��һ�������ĵ�
			//�Լ�����˴�ѭ��������û���µĵ��Ϊ�����Ļ򱻹�Ϊ�µ��࣬Ϊ������������ѭ�����������ѡȡ������
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
			//���õ����Canopy�б���
			NewCanopy.x = centerjj;
			NewCanopy.y = centerii;
			CanopyList.push_back(NewCanopy);
			//��List��ɾ���õ�
			isDelted[curr] = 1;
			//�õ㱻����
			Classify[centerii*XSize + centerjj] = CanopyList.size();

			OldRemainNum--;
			NewRemainNum--;
		}
		else
		{
			OldRemainNum = NewRemainNum;
		}

		//���������б��еĵ���б���������
		for (int currii = 0; currii < YSize; currii++)
		{
			for (int currjj = 0; currjj < XSize; currjj++)
			{
				if (isDelted[currii * XSize + currjj] == 0)
				{
					//û�дӴ�ѡList��ɾ���ĵ�
					T1Num = 0;
					for (vector<PixelPT>::iterator it = CanopyList.begin(); it != CanopyList.end(); it++)
					{
						//��ȡ��ǰ�ǵڼ����������
						ClassNum = distance(CanopyList.begin(), it) + 1;

						//���㵽��ǰ���������ĵľ���
						dis = 0;
						centerii = (*it).y;
						centerjj = (*it).x;

						for (int kk = 0; kk < BandNum; kk++)
						{
							dis += abs(InData[kk*ImgSize + currii * XSize + currjj] - InData[kk*ImgSize + centerii * XSize + centerjj]);
						}
						dis = 1.0 * dis / BandNum;

						//����ǰ�����ľ����ж�
						if (dis >= 0 && dis <= T2)
						{
							//inside T2,member of cluster
							Classify[currii*XSize + currjj] = ClassNum;
							//can not be a cluster center
							isDelted[currii*XSize + currjj] = 1;
							NewRemainNum--;
							break;
							//thisClsNum++;
						}
						else if (dis > T2 && dis <= T1)
						{
							//outside T2 inside T1,member of cluster
							Classify[currii*XSize + currjj] = ClassNum;
							//could also be a center itself
							//thisClsNum++;
						}
						else if (dis > T1)
						{
							//outside T1 boundary,not a member of this cluster
							T1Num++;
						}
						else
						{
							cout << "���������󣡣���" << endl;
							return false;
						}

					}
					if (T1Num == CanopyList.size() && Classify[currii*XSize + currjj] == 0)
					{
						//ͬʱ���㵽���������ĵľ������T1
						//��δ����Ϊ�κ�һ�ࣨ������<T2����ѭ����������б�
						NewCanopy.x = currjj;
						NewCanopy.y = currii;
						CanopyList.push_back(NewCanopy);
						isDelted[currii*XSize + currjj] = 1;
						Classify[currii*XSize + currjj] = CanopyList.size();
						NewRemainNum--;
					}
				}
			}
		}

	}

	cout << "RemainNum=" << NewRemainNum << endl;
	cout << "���Canopy�Ǽල���࣡" << endl;

	//==================================================================================================
	////Ӱ����ʾ
	//int DisW, DisH;
	//CRect rect;
	//GetDlgItem(IDC_STATIC)->GetClientRect(&rect);
	//DisW = rect.Width(); DisH = rect.Height();

	////��ȡ�����ھ��
	//HWND hWnd;
	//hWnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	//HDC hdc;
	//hdc = ::GetDC(hWnd);
	//BOOL flag = DisplayTIFImgColor(&hdc, rect.Width(), rect.Height(), 0, 0, XSize, YSize, Classify);
	//if (flag == NULL)
	//	MessageBox("Ӱ����ʾʧ�ܣ�");
	//==================================================================================================

	//дӰ��
	//д������ͼ��
	pOut->RasterIO(GF_Write, 0, 0, XSize, YSize, Classify, XSize, YSize, GDT_UInt16, 0, 0);

	GDALClose((GDALDatasetH)poIn);
	GDALClose((GDALDatasetH)poOut);


	delete[]InData; delete[]Classify; delete[]CenterVal;
	AfxMessageBox("���TIFӰ��OK");


	return true;
}

BOOL ReadTIF::ReadTIFOneStar(CString strInImg)
{
	//����TIFӰ��
	//CString strInImg;
	//�˴�Ӧ��Ϊ��ȡ�ؼ��е�tif·��
	//strInImg = ".\\data\\LC08_L1TP_119039_20200519_20200527_01_T1_B10.tif";
	char *InImg = (LPSTR)(LPCTSTR)strInImg;
	const char *pszFormat = "GTiff";

	//ע���ļ���ʽ  
	GDALAllRegister();
	//using namespace std;
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");  //֧������·��

	GDALDataset *poIn = (GDALDataset*)GDALOpen(InImg, GA_ReadOnly);
	if (poIn == NULL)
	{
		AfxMessageBox("�ļ���ʧ�ܣ�");
		return FALSE;
	}

	GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);
	if (poDriver == NULL)
	{
		GDALClose((GDALDatasetH)poIn);
		AfxMessageBox("��������ʧ�ܣ�");
		return FALSE;
	}

	//ͼ����������Ļ�ȡ

	//ͼ����������Ļ�ȡ
	TifFile.ImgW = poIn->GetRasterXSize();
	TifFile.ImgH = poIn->GetRasterYSize();
	TifFile.BandNum = poIn->GetRasterCount();
	TifFile.strDescription = poIn->GetDriver()->GetDescription();
	TifFile.type = poIn->GetRasterBand(1)->GetRasterDataType();
	TifFile.eDT = poIn->GetRasterBand(1)->GetRasterDataType();
	poIn->GetGeoTransform(TifFile.GeoTrans);
	//һ��Ĭ��TIFӰ�񱳾�ֵΪ0
	TifFile.Back = 0;
	int XSize = TifFile.ImgW;
	int YSize = TifFile.ImgH;
	int ImgSize = XSize * YSize;
	int BandNum = TifFile.BandNum;
	cout << "X:" << XSize << " Y:" << YSize << " BandNum:" << BandNum << endl;
	if (TifFile.type == GDT_UInt16)
	{
		cout << "�������ͣ�" << "UInt16" << endl;
	}

	//������ͼ������
	UINT16 *InData = new UINT16[XSize*YSize];
	if (InData == NULL) { AfxMessageBox("����д����������ʧ�ܣ�"); return FALSE; }
	memset(InData, 0, XSize*YSize * sizeof(UINT16));

	//ͼ�����ݶ���
	GDALRasterBand *poBand;
	poBand = poIn->GetRasterBand(3);
	poBand->RasterIO(GF_Read, 0, 0, XSize, YSize, InData, XSize, YSize, GDT_UInt16, 0, 0);

	for (int ii = 0; ii < TifFile.ImgH; ii++)
	{
		for (int jj = 0; jj < TifFile.ImgW; jj++)
		{
			TifFile.ImgRAdr[ii][jj] = InData[ii*TifFile.ImgW + jj];
		}
	}

	poBand = poIn->GetRasterBand(2);
	poBand->RasterIO(GF_Read, 0, 0, XSize, YSize, InData, XSize, YSize, GDT_UInt16, 0, 0);

	for (int ii = 0; ii < TifFile.ImgH; ii++)
	{
		for (int jj = 0; jj < TifFile.ImgW; jj++)
		{
			TifFile.ImgGAdr[ii][jj] = InData[ii*TifFile.ImgW + jj];
		}
	}

	poBand = poIn->GetRasterBand(1);
	poBand->RasterIO(GF_Read, 0, 0, XSize, YSize, InData, XSize, YSize, GDT_UInt16, 0, 0);

	for (int ii = 0; ii < TifFile.ImgH; ii++)
	{
		for (int jj = 0; jj < TifFile.ImgW; jj++)
		{
			TifFile.ImgBAdr[ii][jj] = InData[ii*TifFile.ImgW + jj];
		}
	}


	////Ӱ��ͳ�������Сֵ
	//UINT16 Max, Min;

	//int DisW, DisH;
	//CRect rect;
	//GetDlgItem(IDC_STATIC)->GetClientRect(&rect);
	//DisW = rect.Width(); DisH = rect.Height();

	////��ȡ�����ھ��
	//HWND hWnd;
	//hWnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	//HDC hdc;
	//hdc = ::GetDC(hWnd);

	//BOOL flag = DisplayTIFImgColor(&hdc, rect.Width(), rect.Height(), 0, 0, XSize, YSize, InData);
	//if (flag == NULL)
	//	AfxMessageBox("Ӱ����ʾʧ�ܣ�");

	/*GDALClose((GDALDatasetH)poIn);
	GDALClose((GDALDatasetH)poOut);*/

	delete[]InData;
	return TRUE;
}

BOOL ReadTIF::CreateBandSpace()
{
	cout << "���������ڴ��ImgH:";
	cout << TifFile.ImgH << endl;
	TifFile.ImgRAdr = new UINT16 *[TifFile.ImgH]; memset(TifFile.ImgRAdr, 0, TifFile.ImgH * sizeof(UINT16*));
	TifFile.ImgGAdr = new UINT16 *[TifFile.ImgH]; memset(TifFile.ImgGAdr, 0, TifFile.ImgH * sizeof(UINT16*));
	TifFile.ImgBAdr = new UINT16 *[TifFile.ImgH]; memset(TifFile.ImgBAdr, 0, TifFile.ImgH * sizeof(UINT16*));
	//TifFile.ImgMAdr = new UCHAR *[TifFile.ImgH]; memset(TifFile.ImgMAdr, 0, TifFile.ImgH * sizeof(UCHAR*));

	for (int jj = 0; jj < 4; jj++)
	{
		if (jj == 0)
		{
			for (int ii = 0; ii < TifFile.ImgH; ii++)
			{
				UINT16 *pdata = new UINT16[TifFile.ImgW]; memset(pdata, 0, TifFile.ImgW * sizeof(UINT16));
				TifFile.ImgRAdr[ii] = pdata;
			}
		}
		else if (jj == 1)
		{
			for (int ii = 0; ii < TifFile.ImgH; ii++)
			{
				UINT16 *pdata = new UINT16[TifFile.ImgW]; memset(pdata, 0, TifFile.ImgW * sizeof(UINT16));
				TifFile.ImgGAdr[ii] = pdata;
			}
		}
		else if (jj == 2)
		{
			for (int ii = 0; ii < TifFile.ImgH; ii++)
			{
				UINT16 *pdata = new UINT16[TifFile.ImgW]; memset(pdata, 0, TifFile.ImgW * sizeof(UINT16));
				TifFile.ImgBAdr[ii] = pdata;
			}
		}
	}
	return TRUE;
}

//TIFӰ����루�洢�ں����е�UINT16*InData��,���·�ע��ȥ����ֱ��������������ʾ��һ���εĻҶ�Ӱ�񣬵��Ǵ��ڽ����ƫ����Ҫ������

BOOL ReadTIF::DisplayImgColor(HDC *hdc, int DisWidth, int DisHeight, int Disoffx, int Disoffy, int srcWidth, int srcHeight, int srcoffx, int srcoffy)
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

				pdata[off] = 1.0*NearestNeighbor(srcoffx + jj * LinearFac, srcoffy + ii * LinearFac, TifFile.ImgW, TifFile.ImgH, TifFile.ImgBAdr, 0) / 256.0;
				pdata[off + 1] = 1.0*NearestNeighbor(srcoffx + jj * LinearFac, srcoffy + ii * LinearFac, TifFile.ImgW, TifFile.ImgH, TifFile.ImgGAdr, 0) / 256.0;
				pdata[off + 2] = 1.0*NearestNeighbor(srcoffx + jj * LinearFac, srcoffy + ii * LinearFac, TifFile.ImgW, TifFile.ImgH, TifFile.ImgRAdr, 0) / 256.0;

			}
		}

		//��ʼ���ļ�BITMAPINFO����ͼ���С�ı�
		BITMAPINFO mapinfo;
		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);

		int nn = StretchDIBits(*hdc, Disoffx, Disoffy, DisWidth, DisHeight, 0, 0, DisWidth, DisHeight, (void*)pdata, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
		if (nn == 0) { AfxMessageBox("��ʾʧ�ܣ�"); return FALSE; }
		else return TRUE;
		delete[]pdata;
	}
	else
	{
		AfxMessageBox("???");
		return FALSE;
		
	}

}

BOOL ReadTIF::ReadTIFWH(CString strInImg)
{
	char *InImg = (LPSTR)(LPCTSTR)strInImg;
	const char *pszFormat = "GTiff";

	//ע���ļ���ʽ  
	GDALAllRegister();
	//using namespace std;
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");  //֧������·��

	GDALDataset *poIn = (GDALDataset*)GDALOpen(InImg, GA_ReadOnly);
	if (poIn == NULL)
	{
		AfxMessageBox("�ļ���ʧ�ܣ�");
		return FALSE;
	}

	GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);
	if (poDriver == NULL)
	{
		GDALClose((GDALDatasetH)poIn);
		AfxMessageBox("��������ʧ�ܣ�");
		return FALSE;
	}

	//ͼ����������Ļ�ȡ

	//ͼ����������Ļ�ȡ
	TifFile.ImgW = poIn->GetRasterXSize();
	TifFile.ImgH = poIn->GetRasterYSize();
	TifFile.BandNum = poIn->GetRasterCount();
	TifFile.strDescription = poIn->GetDriver()->GetDescription();
	TifFile.type = poIn->GetRasterBand(1)->GetRasterDataType();
	TifFile.eDT = poIn->GetRasterBand(1)->GetRasterDataType();
	poIn->GetGeoTransform(TifFile.GeoTrans);
	//һ��Ĭ��TIFӰ�񱳾�ֵΪ0
	TifFile.Back = 0;


	return TRUE;
}

BOOL ReadTIF::SaveTIF(CString OutPath)
{
	/*pOut->RasterIO(GF_Write, 0, 0, XSize, YSize, Classify, XSize, YSize, GDT_UInt16, 0, 0);

	GDALClose((GDALDatasetH)poIn);
	GDALClose((GDALDatasetH)poOut);*/

	return true;
}

UINT16 ReadTIF::NearestNeighbor(float x, float y, int Width, int Height, UINT16 **Data, UINT16 B0)
{
	int x0 = (int)(x + 0.5); if (x0 < 0 || x0 >= Width) { return B0; }
	int y0 = (int)(y + 0.5); if (y0 < 0 || y0 >= Height) { return B0; }


	UINT16 *p = *(Data + y0);

	UINT16 ch = *(p + x0);

	return ch;
}