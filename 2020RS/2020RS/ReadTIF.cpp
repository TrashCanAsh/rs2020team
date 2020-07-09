#include "ReadTIF.h"
#include"stdafx.h"


ReadTIF::ReadTIF()
{
}


ReadTIF::~ReadTIF()
{
}

BOOL ReadTIF::InitBitMapInfo(int nWidth, int nHeight, int colorbit, BITMAPINFO * pinfo)
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

BOOL ReadTIF::ReadTIFFile(CString FilePath)
{

	char *InImg = (LPSTR)(LPCTSTR)FilePath;
	const char *pszFormat = "GTiff";

	//注册文件格式  
	GDALAllRegister();
	//using namespace std;
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");  //支持中文路径

	GDALDataset *poIn = (GDALDataset*)GDALOpen(InImg, GA_ReadOnly);
	if (poIn == NULL)
	{
		AfxMessageBox("文件打开失败！");
		return false;
	}

	GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);
	if (poDriver == NULL)
	{
		GDALClose((GDALDatasetH)poIn);
		AfxMessageBox("驱动运行失败！");
		return false;
	}

	//图像基本参数的获取
	TifFile.ImgW = poIn->GetRasterXSize();
	TifFile.ImgH = poIn->GetRasterYSize();
	TifFile.BandNum = poIn->GetRasterCount();
	TifFile.strDescription = poIn->GetDriver()->GetDescription();
	TifFile.type = poIn->GetRasterBand(1)->GetRasterDataType();
	TifFile.eDT = poIn->GetRasterBand(1)->GetRasterDataType();
	poIn->GetGeoTransform(TifFile.GeoTrans);
	//一般默认TIF影像背景值为0
	TifFile.Back = 0;

	cout << "X:" << TifFile.ImgW << " Y:" << TifFile.ImgH << " BandNum:" << TifFile.BandNum << endl;
	if (TifFile.type == GDT_UInt16)
	{
		cout << "数据类型：" << "UInt16" << endl;
	}

	if (TifFile.BandNum < 3)
	{
		//只取第一个波段数据，存在ImgRAdr中
		//开辟内存空间
		TifFile.ImgRAdr = new UINT16 *[TifFile.ImgH]; memset(TifFile.ImgRAdr, 0, TifFile.ImgH * sizeof(UINT16*));
		for (int ii = 0; ii < TifFile.ImgH; ii++)
		{
			UINT16 *pdata = new UINT16[TifFile.ImgW]; memset(pdata, 0, TifFile.ImgW * sizeof(UINT16));
			TifFile.ImgRAdr[ii] = pdata;
		}
		//图像数据读入
		GDALRasterBand *poBand;
		poBand = poIn->GetRasterBand(1);
		for (int ii = 0; ii < TifFile.ImgH; ii++)
		{
			poBand->RasterIO(GF_Read, 0, 0, TifFile.ImgW, 1, TifFile.ImgRAdr[ii], TifFile.ImgW, 1, GDT_UInt16, 0, 0);
		}
	}
	else
	{
		//只取前三波段数据，存在ImgRAdr、ImgGAdr、ImgBAdr中
		//开辟内存空间
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
		//图像数据读入
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
	//统计每个波段的最大值最小值
		//当前未考虑排除背景值的影响
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
	//单波段影像显示
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

		//初始化文件BITMAPINFO，因图像大小改变
		BITMAPINFO mapinfo;
		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);

		int nn = StretchDIBits(*hdc, Disoffx, Disoffy, DisWidth, DisHeight, 0, 0, DisWidth, DisHeight, (void*)pdata, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
		if (nn == 0) { AfxMessageBox("显示失败！"); return FALSE; }
		else return TRUE;
		delete[]pdata;
	}

}

BOOL ReadTIF::DisplayTIFImgColor(HDC * hdc, int DisWidth, int DisHeight, int Disoffx, int Disoffy, int srcWidth, int srcHeight, UINT16 * ImgRAdr, UINT16 * ImgGAdr, UINT16 * ImgBAdr)
{
	//三波段影像显示
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

		//初始化文件BITMAPINFO，因图像大小改变
		BITMAPINFO mapinfo;
		InitBitMapInfo(DisWidth, DisHeight, 3, &mapinfo);

		int nn = StretchDIBits(*hdc, Disoffx, Disoffy, DisWidth, DisHeight, 0, 0, DisWidth, DisHeight, (void*)pdata, &mapinfo, DIB_RGB_COLORS, SRCCOPY);
		if (nn == 0) { AfxMessageBox("显示失败！"); return FALSE; }
		else return TRUE;
		delete[]pdata;
	}
}

BOOL ReadTIF::TIFCanopy(CString InFilrPath, CString OutFilrPath, double T1, double T2)
{

	//这里应是获取控件中的Tif文件路径
	//CString strInImg, strOutImg;
	//strInImg = ".\\data\\753Subset.tif";
	//strOutImg = ".\\data\\753Classify.tif";
	char *InImg = (LPSTR)(LPCTSTR)InFilrPath;
	char *OutImg = (LPSTR)(LPCTSTR)OutFilrPath;
	const char *pszFormat = "GTiff";

	//double T1 = 5000, T2 = 4500;

	//注册文件格式  
	GDALAllRegister();
	//using namespace std;
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");  //支持中文路径

	GDALDataset *poIn = (GDALDataset*)GDALOpen(InImg, GA_ReadOnly);
	if (poIn == NULL)
	{
		AfxMessageBox("文件打开失败！");
		return false;
	}

	GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);
	if (poDriver == NULL)
	{
		GDALClose((GDALDatasetH)poIn);
		AfxMessageBox("驱动运行失败！");
		return false;
	}

	//图像基本参数的获取
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
		cout << "数据类型：" << "UInt16" << endl;
	}

	//输出文件的创建以及投影信息的写入
	GDALDataset*poOut = poDriver->Create(OutImg, XSize, YSize, 1, eDT, NULL);
	GDALRasterBand* pOut = poOut->GetRasterBand(1);
	if (poOut == NULL)
	{
		AfxMessageBox("写出文件创建失败！");
	}
	double GeoTrans[6] = { 0 };
	poIn->GetGeoTransform(GeoTrans);
	poOut->SetGeoTransform(GeoTrans);
	poOut->SetProjection(poIn->GetProjectionRef());

	//待分类图像数组
	UINT16*InData = new UINT16[XSize*YSize*BandNum];
	if (InData == NULL) { AfxMessageBox("创建写入数据数组失败！"); return false; }
	memset(InData, 0, XSize*YSize *BandNum * sizeof(UINT16));

	//分类数据数组
	UINT16 *Classify = new UINT16[XSize*YSize]; if (!Classify) { AfxMessageBox("创建分类数据数组失败"); return false; }
	memset(Classify, 0, XSize*YSize * sizeof(UINT16));

	//图像数据读入
	GDALRasterBand *poBand;
	for (int k = 1; k <= BandNum; k++)
	{
		poBand = poIn->GetRasterBand(k);
		poBand->RasterIO(GF_Read, 0, 0, XSize, YSize, InData + (k - 1)*XSize*YSize, XSize, YSize, GDT_UInt16, 0, 0);
	}

	//生成随机数种子
	struct tm *ptr;
	time_t lt;
	lt = time(NULL); srand((unsigned)lt);

	int curr;
	int ClassNum = 0;
	//类中心像元行列坐标
	int centerii, centerjj;
	//当前像元行列坐标
	int currii, currjj;
	UINT16 *CenterVal = new UINT16[BandNum];
	if (CenterVal == NULL) { cout << "类中心数据信息数组开辟失败！" << endl; };
	memset(CenterVal, 0, BandNum * sizeof(UINT16));

	double dis; double val;

	BOOL *isDelted = new BOOL[XSize*YSize]; if (isDelted == NULL) { cout << "isDelted数组控件开辟失败！" << endl; }
	memset(isDelted, 0, XSize*YSize * sizeof(BOOL));
	//int thisClsNum;

	vector<PixelPT>CanopyList;
	PixelPT NewCanopy;

	int OldRemainNum = ImgSize;
	int NewRemainNum = ImgSize;
	int T1Num;//用于指示是否对所有类的距离都>T1

	//开始循环
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
			CanopyList.push_back(NewCanopy);
			//从List中删除该点
			isDelted[curr] = 1;
			//该点被归类
			Classify[centerii*XSize + centerjj] = CanopyList.size();

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
					for (vector<PixelPT>::iterator it = CanopyList.begin(); it != CanopyList.end(); it++)
					{
						//获取当前是第几类的类中心
						ClassNum = distance(CanopyList.begin(), it) + 1;

						//计算到当前所有类中心的距离
						dis = 0;
						centerii = (*it).y;
						centerjj = (*it).x;

						for (int kk = 0; kk < BandNum; kk++)
						{
							dis += abs(InData[kk*ImgSize + currii * XSize + currjj] - InData[kk*ImgSize + centerii * XSize + centerjj]);
						}
						dis = 1.0 * dis / BandNum;

						//到当前类中心距离判断
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
							cout << "距离计算错误！！！" << endl;
							return false;
						}

					}
					if (T1Num == CanopyList.size() && Classify[currii*XSize + currjj] == 0)
					{
						//同时满足到所有类中心的距离大于T1
						//且未被归为任何一类（即不是<T2跳出循环后误进此判别）
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
	cout << "完成Canopy非监督分类！" << endl;

	//==================================================================================================
	////影像显示
	//int DisW, DisH;
	//CRect rect;
	//GetDlgItem(IDC_STATIC)->GetClientRect(&rect);
	//DisW = rect.Width(); DisH = rect.Height();

	////获取主窗口句柄
	//HWND hWnd;
	//hWnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	//HDC hdc;
	//hdc = ::GetDC(hWnd);
	//BOOL flag = DisplayTIFImgColor(&hdc, rect.Width(), rect.Height(), 0, 0, XSize, YSize, Classify);
	//if (flag == NULL)
	//	MessageBox("影像显示失败！");
	//==================================================================================================

	//写影像
	//写出分类图像
	pOut->RasterIO(GF_Write, 0, 0, XSize, YSize, Classify, XSize, YSize, GDT_UInt16, 0, 0);

	GDALClose((GDALDatasetH)poIn);
	GDALClose((GDALDatasetH)poOut);


	delete[]InData; delete[]Classify; delete[]CenterVal;
	AfxMessageBox("输出TIF影像OK");


	return true;
}

BOOL ReadTIF::ReadTIFOneStar(CString strInImg)
{
	//读入TIF影像
	//CString strInImg;
	//此处应改为获取控件中的tif路径
	//strInImg = ".\\data\\LC08_L1TP_119039_20200519_20200527_01_T1_B10.tif";
	char *InImg = (LPSTR)(LPCTSTR)strInImg;
	const char *pszFormat = "GTiff";

	//注册文件格式  
	GDALAllRegister();
	//using namespace std;
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");  //支持中文路径

	GDALDataset *poIn = (GDALDataset*)GDALOpen(InImg, GA_ReadOnly);
	if (poIn == NULL)
	{
		AfxMessageBox("文件打开失败！");
		return FALSE;
	}

	GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);
	if (poDriver == NULL)
	{
		GDALClose((GDALDatasetH)poIn);
		AfxMessageBox("驱动运行失败！");
		return FALSE;
	}

	//图像基本参数的获取

	//图像基本参数的获取
	TifFile.ImgW = poIn->GetRasterXSize();
	TifFile.ImgH = poIn->GetRasterYSize();
	TifFile.BandNum = poIn->GetRasterCount();
	TifFile.strDescription = poIn->GetDriver()->GetDescription();
	TifFile.type = poIn->GetRasterBand(1)->GetRasterDataType();
	TifFile.eDT = poIn->GetRasterBand(1)->GetRasterDataType();
	poIn->GetGeoTransform(TifFile.GeoTrans);
	//一般默认TIF影像背景值为0
	TifFile.Back = 0;
	int XSize = TifFile.ImgW;
	int YSize = TifFile.ImgH;
	int ImgSize = XSize * YSize;
	int BandNum = TifFile.BandNum;
	cout << "X:" << XSize << " Y:" << YSize << " BandNum:" << BandNum << endl;
	if (TifFile.type == GDT_UInt16)
	{
		cout << "数据类型：" << "UInt16" << endl;
	}

	//待分类图像数组
	UINT16 *InData = new UINT16[XSize*YSize];
	if (InData == NULL) { AfxMessageBox("创建写入数据数组失败！"); return FALSE; }
	memset(InData, 0, XSize*YSize * sizeof(UINT16));

	//图像数据读入
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


	////影像统计最大最小值
	//UINT16 Max, Min;

	//int DisW, DisH;
	//CRect rect;
	//GetDlgItem(IDC_STATIC)->GetClientRect(&rect);
	//DisW = rect.Width(); DisH = rect.Height();

	////获取主窗口句柄
	//HWND hWnd;
	//hWnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	//HDC hdc;
	//hdc = ::GetDC(hWnd);

	//BOOL flag = DisplayTIFImgColor(&hdc, rect.Width(), rect.Height(), 0, 0, XSize, YSize, InData);
	//if (flag == NULL)
	//	AfxMessageBox("影像显示失败！");

	/*GDALClose((GDALDatasetH)poIn);
	GDALClose((GDALDatasetH)poOut);*/

	delete[]InData;
	return TRUE;
}

BOOL ReadTIF::CreateBandSpace()
{
	cout << "开辟数组内存的ImgH:";
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

//TIF影像读入（存储在函数中的UINT16*InData中,将下方注释去除可直接在主界面中显示第一波段的灰度影像，但是窗口界面的偏移需要调整）

BOOL ReadTIF::DisplayImgColor(HDC *hdc, int DisWidth, int DisHeight, int Disoffx, int Disoffy, int srcWidth, int srcHeight, int srcoffx, int srcoffy)
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

				pdata[off] = 1.0*NearestNeighbor(srcoffx + jj * LinearFac, srcoffy + ii * LinearFac, TifFile.ImgW, TifFile.ImgH, TifFile.ImgBAdr, 0) / 256.0;
				pdata[off + 1] = 1.0*NearestNeighbor(srcoffx + jj * LinearFac, srcoffy + ii * LinearFac, TifFile.ImgW, TifFile.ImgH, TifFile.ImgGAdr, 0) / 256.0;
				pdata[off + 2] = 1.0*NearestNeighbor(srcoffx + jj * LinearFac, srcoffy + ii * LinearFac, TifFile.ImgW, TifFile.ImgH, TifFile.ImgRAdr, 0) / 256.0;

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
		AfxMessageBox("???");
		return FALSE;
		
	}

}

BOOL ReadTIF::ReadTIFWH(CString strInImg)
{
	char *InImg = (LPSTR)(LPCTSTR)strInImg;
	const char *pszFormat = "GTiff";

	//注册文件格式  
	GDALAllRegister();
	//using namespace std;
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");  //支持中文路径

	GDALDataset *poIn = (GDALDataset*)GDALOpen(InImg, GA_ReadOnly);
	if (poIn == NULL)
	{
		AfxMessageBox("文件打开失败！");
		return FALSE;
	}

	GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);
	if (poDriver == NULL)
	{
		GDALClose((GDALDatasetH)poIn);
		AfxMessageBox("驱动运行失败！");
		return FALSE;
	}

	//图像基本参数的获取

	//图像基本参数的获取
	TifFile.ImgW = poIn->GetRasterXSize();
	TifFile.ImgH = poIn->GetRasterYSize();
	TifFile.BandNum = poIn->GetRasterCount();
	TifFile.strDescription = poIn->GetDriver()->GetDescription();
	TifFile.type = poIn->GetRasterBand(1)->GetRasterDataType();
	TifFile.eDT = poIn->GetRasterBand(1)->GetRasterDataType();
	poIn->GetGeoTransform(TifFile.GeoTrans);
	//一般默认TIF影像背景值为0
	TifFile.Back = 0;


	return TRUE;
}

UINT16 ReadTIF::NearestNeighbor(float x, float y, int Width, int Height, UINT16 **Data, UINT16 B0)
{
	int x0 = (int)(x + 0.5); if (x0 < 0 || x0 >= Width) { return B0; }
	int y0 = (int)(y + 0.5); if (y0 < 0 || y0 >= Height) { return B0; }


	UINT16 *p = *(Data + y0);

	UINT16 ch = *(p + x0);

	return ch;
}