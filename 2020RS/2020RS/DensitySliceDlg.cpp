// DensitySliceDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "2020RS.h"
#include "DensitySliceDlg.h"
#include "afxdialogex.h"

extern Img_kele MainImg;
extern ReadTIF m_TIFIMG;
// DensitySliceDlg 对话框

IMPLEMENT_DYNAMIC(DensitySliceDlg, CDialog)

DensitySliceDlg::DensitySliceDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DensitySliceDIALOG, pParent)
{

}

DensitySliceDlg::~DensitySliceDlg()
{
}

void DensitySliceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DensitySliceList, m_DSList);
	DDX_Control(pDX, IDC_ColorLibList, m_ColorLibList);
	DDX_Control(pDX, IDC_Band_COMBO, m_SelectBand_COMBO);
	DDX_Control(pDX, IDC_SLICE_PROGRESS, m_SLICE_PROGRESS);
}


BEGIN_MESSAGE_MAP(DensitySliceDlg, CDialog)
	ON_BN_CLICKED(IDC_Reverse_BUTTON, &DensitySliceDlg::OnBnClickedReverseButton)
	ON_WM_PAINT()
	ON_EN_KILLFOCUS(IDC_Level_EDIT, &DensitySliceDlg::OnEnKillfocusLevelEdit)
	ON_BN_CLICKED(IDC_Output_BUTTON, &DensitySliceDlg::OnBnClickedOutputButton)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_DensitySliceList, &DensitySliceDlg::OnNMCustomdrawDensityslicelist)
	ON_LBN_DBLCLK(IDC_ColorLibList, &DensitySliceDlg::OnLbnDblclkColorliblist)
END_MESSAGE_MAP()


// DensitySliceDlg 消息处理程序


BOOL DensitySliceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  在此添加额外的初始化
	//左侧分级列表初始化
	CRect rect;
	m_DSList.GetClientRect(&rect);
	m_DSList.SetExtendedStyle(m_DSList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_DSList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, rect.Width() / 4, 0);
	m_DSList.InsertColumn(1, _T("颜色"), LVCFMT_CENTER, rect.Width() / 4, 1);
	m_DSList.InsertColumn(2, _T("上限"), LVCFMT_CENTER, rect.Width() / 4, 2);
	m_DSList.InsertColumn(3, _T("下限"), LVCFMT_CENTER, rect.Width() / 4, 3);
	//颜色库列表初始化
	DWORD styles = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES;
	ListView_SetExtendedListViewStyleEx(m_ColorLibList.m_hWnd, styles, styles);
	
	//ReadColorLib("");
	//m_ColorLibList.InsertString(0, "Rainbow");
	
	//遍历色彩库文件夹，在m_colorlist全部显示供用户选择
	//默认显示最后一个色彩
	TraverseFiles(".\\色谱库");

	//文本框初始化
	SetDlgItemText(IDC_Level_EDIT, _T("10"));

	//
	((CComboBox*)GetDlgItem(IDC_Band_COMBO))->AddString("R");
	((CComboBox*)GetDlgItem(IDC_Band_COMBO))->AddString("G");
	((CComboBox*)GetDlgItem(IDC_Band_COMBO))->AddString("B");
	//
	flag = 0;
	


	//	int flag_BMP_TIF = -1;//0为bmp，1为tif
	HWND hWnd_IFBMP;
	hWnd_IFBMP = ::FindWindow(NULL, "主窗口");
	CWnd*cWNd_IFBMP;
	cWNd_IFBMP = FromHandle(hWnd_IFBMP);
	CString str_IFBMP;
	cWNd_IFBMP->GetDlgItem(IDC_EDIT1)->GetWindowText(str_IFBMP);
	if (str_IFBMP == "")
	{

		SetDlgItemInt(IDC_Max_EDIT, NAN);
		SetDlgItemInt(IDC_Min_EDIT, NAN);
		return	false;
	}
	
	if (str_IFBMP.Right(4) == ".BMP" || str_IFBMP.Right(4) == ".bmp")
		flag_BMP_TIF = 0;
	else if (str_IFBMP.Right(4) == ".tif" || str_IFBMP.Right(4) == ".TIF")
		flag_BMP_TIF = 1;

	if (flag_BMP_TIF == 0)
	{
		if (MainImg.ImgParaInCls.RMin != MainImg.ImgParaInCls.RMax)
		{
			SetDlgItemInt(IDC_Max_EDIT, MainImg.ImgParaInCls.RMax);
			SetDlgItemInt(IDC_Min_EDIT, MainImg.ImgParaInCls.RMin);
			//分级显示
			CString str_degree;
			GetDlgItem(IDC_Level_EDIT)->GetWindowText(str_degree);
			int degree = atoi(str_degree);
			show_list(colorlib, degree);
		}
	}
	else
	{
		m_TIFIMG.GetTIFDataInfo();
		if (m_TIFIMG.TifFile.EdRmin != m_TIFIMG.TifFile.EdRmax)
		{
			SetDlgItemInt(IDC_Max_EDIT, m_TIFIMG.TifFile.EdRmax);
			SetDlgItemInt(IDC_Min_EDIT, m_TIFIMG.TifFile.EdRmin);
			//分级显示
			CString str_degree;
			GetDlgItem(IDC_Level_EDIT)->GetWindowText(str_degree);
			int degree = atoi(str_degree);
			show_list(colorlib, degree);
		}

	}
	
	//默认选择波段为R
	m_SelectBand_COMBO.SetCurSel(0);

	//初始化进度条
	if(flag_BMP_TIF==0)
		m_SLICE_PROGRESS.SetRange(0, MainImg.ImgParaInCls.ImgH);
	else
		m_SLICE_PROGRESS.SetRange(0, m_TIFIMG.TifFile.ImgH);

	m_SLICE_PROGRESS.SetStep(1);

	m_SLICE_PROGRESS.SetPos(0);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

BOOL DensitySliceDlg::ReadColorLib(CString FilePath)
{
	FilePath = ".\\色谱库\\" + FilePath;
	cout << FilePath << endl;
	char ReadStr[1024]; memset(ReadStr, 0, 1024);
	FILE *fp = fopen(FilePath, "r"); if (!fp) { MessageBox("打开Lib色带文件失败！"); return FALSE; }
	fgets(ReadStr, 450, fp); if (!strstr(ReadStr, "ZOUCOLORLSTLIB")) { fclose(fp); return FALSE; }
	UCHAR r, g, b; 
	int nn;
	//内存空间初始化
	memset(colorlib, 0, 256 * sizeof(COLORREF));
	//把颜色读入数组
	for (int ii = 0; ii < 256; ii++)
	{
		fgets(ReadStr, 450, fp); nn = SsToStr60(ReadStr, SS_Dat); if (nn < 3) continue;
		r = atoi(SS_Dat[1]);
		g = atoi(SS_Dat[2]);
		b = atoi(SS_Dat[3]);
		colorlib[ii] = (COLORREF)RGB(r, g, b);
	}
	fclose(fp);
	return TRUE;
}

int DensitySliceDlg::SsToStr60(char * str, char * s_dat[])
{
	int  nn;
	char ch, *pstr;
	s_dat[0] = str;
	ch = *str; if (ch == '\0' || ch == '\n') return 0;
	nn = 0; pstr = strtok(str, ", ;\t\r\n");
	while (pstr)
	{
		if (pstr) { s_dat[nn] = pstr; if (nn < MAX_DAT) nn++; }
		pstr = strtok(NULL, ", ;\t\r\n");
	}
	return nn;
}

bool DensitySliceDlg::TraverseFiles(string inPath)
{
	//目标文件夹路径
	inPath += "\\*.lib";
	//用于查找的句柄
	intptr_t handle;
	struct _finddata64i32_t fileinfo ;
	//第一次查找
	handle = _findfirst(inPath.c_str(), &fileinfo);
	if (handle == -1)
		return -1;
	int colorNum = 0;
	CString fileName;
	do
	{
		//找到的文件的文件名
		//ReadColorLib(fileinfo.name);
		//更新list
		fileName.Format("%s", fileinfo.name);
		m_ColorLibList.InsertString(colorNum, fileName);
		colorNum = colorNum + 1;
	} while (_findnext(handle, &fileinfo)!=-1);
	_findclose(handle);

	//默认读取第一个色彩库
	ReadColorLib(fileName);
	return true;
}


void DensitySliceDlg::show_list(COLORREF * colorlibhead, int degree)
{
	//已经获得波段的最大值
	CString str_Max, str_Min;
	GetDlgItem(IDC_Max_EDIT)->GetWindowText(str_Max);
	GetDlgItem(IDC_Min_EDIT)->GetWindowText(str_Min);
	double DN_Max, DN_Min;
	DN_Max = atof(str_Max); DN_Min = atof(str_Min);

	//
	double level = (DN_Max - DN_Min) / degree;
	CString str;
	for (int ii = 0; ii < degree; ii++)
	{
		
		str.Format("%d", ii + 1);
		m_DSList.InsertItem(ii, str);

		//
		//m_DSList.SetItemText(ii,1) color

		int level_max, level_min;
		level_min = floor(ii*level + DN_Min+0.5);
		level_max = floor(ii*level + DN_Min + level+0.5);
		
		if (level_max > 255 &&level_max <300)
			level_max = 255;
		else if(level_max >65535&& level_max <65550)
			level_max = 65535;
		str.Format("%d", level_max);
		m_DSList.SetItemText(ii, 2,str);
		str.Format("%d", level_min);
		m_DSList.SetItemText(ii, 3, str);
	}
}

COLORREF DensitySliceDlg::GetColorLevel2(UINT16 DN_Date,int listNum,double fac1, int *LevelList)
{
	//DN_Date = DN_Date * 255;
	int levelMax,levelMin;
	int flag11 = 0;
	int colorlevel;
	for (int ii = 0; ii < listNum; ii++)
	{
		levelMax = LevelList[ii * 2];
		levelMin = LevelList[ii * 2 + 1];
		if (DN_Date <= levelMax && DN_Date >= levelMin)
		{
			colorlevel = (levelMax + levelMin) / 2 * fac1/255;
			flag11 = 1;
			break;
		}
		
	}
	if (flag11 == 0)
		colorlevel = 0;

	return colorlib[colorlevel];
	
}

COLORREF DensitySliceDlg::GetColorLevel(UCHAR DN_Date, int listNum, double fac1, int *LevelList)
{
	//DN_Date = DN_Date * 255;
	int levelMax, levelMin;
	int flag11 = 0;
	int colorlevel;
	for (int ii = 0; ii < listNum; ii++)
	{
		levelMax = LevelList[ii * 2];
		levelMin = LevelList[ii * 2 + 1];
		if (DN_Date <= levelMax && DN_Date >= levelMin)
		{
			colorlevel = (levelMax + levelMin) / 2 * fac1;
			flag11 = 1;
			break;
		}
	}
	if (flag11 == 0)
		colorlevel = 0;

	return colorlib[colorlevel];

}
BOOL DensitySliceDlg::DrawColorLib(int PicID, COLORREF * colorlibhead, int flag)
{
	double step = 1.0;
	CRect rect;
	CDC* pDC;
	//设置画笔
	
	//获取绘图窗口的CDC资源
	this->GetDlgItem(PicID)->GetClientRect(rect);
	pDC = this->GetDlgItem(PicID)->GetDC();
	//x轴步长
	step = double(rect.Width() - 2) / (double)256;
	//记录画笔
	int i;
	//逐点画折线图
	if (flag == 0)
	{
		for ( i = 0; i < 256; i++)
		{
			CPen pen(PS_SOLID, 2, colorlibhead[i]);
			pDC->SelectObject(&pen);
			pDC->MoveTo(int(i * step + 1), int(rect.Height() - 1));
			pDC->LineTo(int(i * step + 1), int(1));
			pen.DeleteObject();
		}
	}
	else if(flag == 1)
	{
		for (i = 0; i < 256; i++)
		{
			CPen pen(PS_SOLID, 2, colorlibhead[255 - i]);
			pDC->SelectObject(&pen);
			pDC->MoveTo(int(i * step + 1), int(rect.Height() - 1));
			pDC->LineTo(int(i * step + 1), int(1));
			pen.DeleteObject();
		}
	}
	
	//释放CDC资源
	ReleaseDC(pDC);
	return TRUE;
}

void DensitySliceDlg::OnBnClickedReverseButton()
{
	// TODO: 在此添加控件通知处理程序代码
	flag = !flag;
	COLORREF temp[256];
	for (int i = 0; i < 256; i++)
	{
		temp[i] = colorlib[i];
	}
	for (int i = 0; i < 256; i++)
	{
		colorlib[i] = temp[255 - i];
	}
	DrawColorLib(IDC_ColorSlice, colorlib, 0);
	m_DSList.DeleteAllItems();
	//分级显示
	CString str_degree;
	GetDlgItem(IDC_Level_EDIT)->GetWindowText(str_degree);
	int degree = atoi(str_degree);
	show_list(colorlib, degree);

	//
	if (flag_BMP_TIF == 0)
		copyImg1 = Read(MainImg);
	else
		copyImg2 = Read2(m_TIFIMG);
}


void DensitySliceDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialog::OnPaint()

	DrawColorLib(IDC_ColorSlice, colorlib, 0);
}

//重新改变分级，改变list
void DensitySliceDlg::OnEnKillfocusLevelEdit()
{
	
	if (MainImg.ImgParaInCls.RMin != MainImg.ImgParaInCls.RMax)
	{
		UpdateData();
		int degree;
		CString str_degree;
		GetDlgItem(IDC_Level_EDIT)->GetWindowText(str_degree);
		degree = atoi(str_degree);
		if (degree < 0 || degree >255)
		{
			MessageBox("选择参数有误，请重新选择参数");
			return;
		}
		m_DSList.DeleteAllItems();
		show_list(colorlib, degree);
	}
	else
		return;
	//有个问题，回车会直接关闭窗口
	// TODO: 在此添加控件通知处理程序代码
}


void DensitySliceDlg::OnBnClickedOutputButton()
{
	HWND hWnd_IFBMP;
	hWnd_IFBMP = ::FindWindow(NULL, "主窗口");
	CWnd*cWNd_IFBMP;
	cWNd_IFBMP = FromHandle(hWnd_IFBMP);
	CString str_IFBMP;
	cWNd_IFBMP->GetDlgItem(IDC_EDIT1)->GetWindowText(str_IFBMP);
	int flag_BMP_TIF = -1;//0为bmp，1为tif
	if (str_IFBMP.Right(4) == ".BMP" || str_IFBMP.Right(4) == ".bmp")
		flag_BMP_TIF = 0;
	else if (str_IFBMP.Right(4) == ".tif" || str_IFBMP.Right(4) == ".TIF")
		flag_BMP_TIF = 1;
	else
	{
		MessageBox("请打开一幅影像");
		return;
	}
	m_SLICE_PROGRESS.SetPos(0);
	
	if (flag_BMP_TIF == 0)
		Save(copyImg1);
	else
		Save2(copyImg2);
}


void DensitySliceDlg::OnNMCustomdrawDensityslicelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		//cout << "1--";
		COLORREF crText, crBkgnd;
		int nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec);
		//cout << "nItem:" << nItem;
		//cout << "pLVCD->iSubItem:" << pLVCD->iSubItem << endl;
		if (pLVCD->iSubItem == 1)
		{
			if (nItem == 0)
			{
				//cout << "绘制绘制"<<pLVCD->iSubItem << "," << nItem << endl;
				CString str_temp;
				int levelmax, levelmin;
				str_temp = m_DSList.GetItemText(nItem, 2);
				levelmin = atoi(str_temp);
				str_temp = m_DSList.GetItemText(nItem, 3);
				levelmax = atoi(str_temp);
				int index = (levelmin + levelmax) / 2;

				if (flag_BMP_TIF == 1)
					index /= 255;

				crText = RGB(0, 0, 0);
				crBkgnd = colorlib[index];
				//*pResult = CDRF_DODEFAULT;
			}
			else
			{
				crText = RGB(0, 0, 0);
				crBkgnd = RGB(255, 255, 255);
				//*pResult = CDRF_DODEFAULT;
			}
			//pLVCD->clrTextBk = crBkgnd;
		}
		else
		{
			//cout << pLVCD->iSubItem << endl;
			crText = RGB(0, 0, 0);
			crBkgnd = RGB(255, 255, 255);
			//*pResult = CDRF_DODEFAULT;
		}

		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crBkgnd;
		//*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		// This is the notification message for an item. We'll request
		// notifications before each subitem's prepaint stage.
		//cout << "2--";
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		int nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec);
		COLORREF crText, crBkgnd;
		if (pLVCD->iSubItem == 1)
		{
			if (nItem >= 0)
			{
				CString str_temp;
				int levelmax, levelmin;
				str_temp = m_DSList.GetItemText(nItem, 2);
				levelmin = atoi(str_temp);
				str_temp = m_DSList.GetItemText(nItem, 3);
				levelmax = atoi(str_temp);
				int index = (levelmin + levelmax) / 2;

				if (flag_BMP_TIF == 1)
					index /= 255;

				crText = RGB(0, 0, 0);
				crBkgnd = colorlib[index];
			}
			else
			{
				crText = RGB(0, 0, 0);
				crBkgnd = RGB(255, 255, 255);
				//*pResult = CDRF_DODEFAULT;
			}
			//pLVCD->clrTextBk = crBkgnd;
		}
		else
		{
			//cout << pLVCD->iSubItem << endl;
			crText = RGB(0, 0, 0);
			crBkgnd = RGB(255, 255, 255);
			//*pResult = CDRF_DODEFAULT;
		}

		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crBkgnd;
	}
	else if ((CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage)
	{
		//cout << "3--";
		int nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec);
		COLORREF crText, crBkgnd;
		if (pLVCD->iSubItem == 1)
		{
			if (nItem >= 0)
			{
				CString str_temp;
				int levelmax, levelmin;
				str_temp = m_DSList.GetItemText(nItem, 2);
				levelmin = atoi(str_temp);
				str_temp = m_DSList.GetItemText(nItem, 3);
				levelmax = atoi(str_temp);
				int index = (levelmin + levelmax) / 2;

				if (flag_BMP_TIF == 1)
					index /= 255;

				crText = RGB(0, 0, 0);
				crBkgnd = colorlib[index];
			}
			else
			{
				crText = RGB(0, 0, 0);
				crBkgnd = RGB(255, 255, 255);
				//*pResult = CDRF_DODEFAULT;
			}
			//pLVCD->clrTextBk = crBkgnd;
		}
		else
		{
			//cout << pLVCD->iSubItem << endl;
			crText = RGB(0, 0, 0);
			crBkgnd = RGB(255, 255, 255);
			//*pResult = CDRF_DODEFAULT;
		}

		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crBkgnd;
	}
	*pResult = 0;
	*pResult |= CDRF_NOTIFYPOSTPAINT;		//必须有，不然就没有效果
	*pResult |= CDRF_NOTIFYITEMDRAW;		//必须有，不然就没有效果
}


void DensitySliceDlg::OnLbnDblclkColorliblist()
{
	//MessageBox("hhhhh");
	// TODO: 在此添加控件通知处理程序代码
	int nSel;
	nSel = m_ColorLibList.GetCurSel();
	CString s;
	m_ColorLibList.GetText(nSel, s);
	cout << s.GetBuffer() << endl;
	ReadColorLib(s.GetBuffer());
	DrawColorLib(IDC_ColorSlice, colorlib, 0);
	m_DSList.DeleteAllItems();
	//分级显示
	CString str_degree;
	GetDlgItem(IDC_Level_EDIT)->GetWindowText(str_degree);
	int degree = atoi(str_degree);
	show_list(colorlib, degree);


	//双击显示影像
	HWND hWnd_IFBMP;
	hWnd_IFBMP = ::FindWindow(NULL, "主窗口");
	CWnd*cWNd_IFBMP;
	cWNd_IFBMP = FromHandle(hWnd_IFBMP);
	CString str_IFBMP;
	cWNd_IFBMP->GetDlgItem(IDC_EDIT1)->GetWindowText(str_IFBMP);
	int flag_BMP_TIF = -1;//0为bmp，1为tif
	if (str_IFBMP.Right(4) == ".BMP" || str_IFBMP.Right(4) == ".bmp")
		flag_BMP_TIF = 0;
	else if (str_IFBMP.Right(4) == ".tif" || str_IFBMP.Right(4) == ".TIF")
		flag_BMP_TIF = 1;
	else
	{
		MessageBox("请打开一幅影像");
		return;
	}
	m_SLICE_PROGRESS.SetPos(0);
	if (flag_BMP_TIF == 0)
		copyImg1 =  Read(MainImg);
	else
		copyImg2 = Read2(m_TIFIMG);
}

Img_kele DensitySliceDlg::Read(Img_kele MainImg)
{
	Img_kele copyImg(MainImg);
	//分级显示
	CString str_degree;
	GetDlgItem(IDC_Level_EDIT)->GetWindowText(str_degree);
	int degree = atoi(str_degree);
	int listNum = m_DSList.GetItemCount();
	double fac1 = 256 / (copyImg.ImgParaInCls.RMax - copyImg.ImgParaInCls.RMin);
	CString select_Band;
	GetDlgItem(IDC_Band_COMBO)->GetWindowText(select_Band);
	UCHAR **ImageDate = {};
	if (select_Band == "R")
		ImageDate = copyImg.ImgParaInCls.ImgRAdr;
	else if (select_Band == "G")
		ImageDate = copyImg.ImgParaInCls.ImgGAdr;
	else if (select_Band == "B")
		ImageDate = copyImg.ImgParaInCls.ImgBAdr;
	else
		MessageBox("波段选择错误");

	CString str_temp;
	int* LevelList = new int[255];//问题：用listnum初始化会报错，表示删除指针是NULL
	for (int ii = 0; ii < listNum; ii++)
	{
		str_temp = m_DSList.GetItemText(ii, 2);
		LevelList[ii * 2] = atoi(str_temp);
		str_temp = m_DSList.GetItemText(ii, 3);
		LevelList[ii * 2 + 1] = atoi(str_temp);
	}
	for (int ii = 0; ii < copyImg.ImgParaInCls.ImgH; ii++)
	{
		for (int jj = 0; jj < copyImg.ImgParaInCls.ImgW; jj++)
		{
			COLORREF xiugai = GetColorLevel(ImageDate[ii][jj], listNum, fac1, LevelList);
			copyImg.ImgParaInCls.ImgRAdr[ii][jj] = GetRValue(xiugai);
			copyImg.ImgParaInCls.ImgGAdr[ii][jj] = GetGValue(xiugai);
			copyImg.ImgParaInCls.ImgBAdr[ii][jj] = GetBValue(xiugai);
			/*if (jj % 50 == 0)
				std::cout << "ii = " << ii << "jj=" << jj << std::endl;*/
		}
		m_SLICE_PROGRESS.SetPos(ii + 1);
	}
	HWND hWnd;
	hWnd = ::FindWindow(NULL, "主窗口");
	CWnd* m_parentDLG;
	m_parentDLG = FromHandle(hWnd);
	HDC hdc;
	hdc = ::GetDC(hWnd);
	CRect rect;
	::GetClientRect(hWnd, &rect);

	CRect rectCtrl;
	m_parentDLG->GetDlgItem(IDC_EDIT1)->GetWindowRect(&rectCtrl); //获取被选中的控件大小
	std::cout << "EDIT_1坐标：";
	std::cout << rectCtrl.left << "," << rectCtrl.top << "," << rectCtrl.right << "," << rectCtrl.bottom << std::endl;
	//转化为客户区坐标
	m_parentDLG->ScreenToClient(&rectCtrl);

	//
		//创建实线，宽度为1，灰色的笔
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(240, 240, 240));
	//将笔选入DC
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	//创建一个灰色的刷子
	HBRUSH hBrush = CreateSolidBrush(RGB(240, 240, 240));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	//绘制矩形，灰色边框，灰色区域的
	Rectangle(hdc, rectCtrl.right + 10, rectCtrl.top, rect.Width(), rect.Height());
	//恢复绘图对象
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);
	//删除绘图对象
	DeleteObject(hPen);
	DeleteObject(hBrush);

	//
	Rectangle(hdc, rectCtrl.right + 10, rectCtrl.top, rect.Width(), rect.Height());
	flag = copyImg.DisplayImgColor(&hdc, rect.Width() - rectCtrl.right - 25, rect.Height() - rectCtrl.top - 10, rectCtrl.right + 10, rectCtrl.top, MainImg.ImgParaInCls.ImgW, MainImg.ImgParaInCls.ImgH, 0, 0);


	if (flag == FALSE)
		MessageBox("影像显示失败！");

	delete[] LevelList;

	return copyImg;
	
}

ReadTIF DensitySliceDlg::Read2(ReadTIF m_TIFIMG)
{
	ReadTIF copyImg(m_TIFIMG);
	//分级显示
	CString str_degree;
	GetDlgItem(IDC_Level_EDIT)->GetWindowText(str_degree);
	int degree = atoi(str_degree);
	int listNum = m_DSList.GetItemCount();
	;
	CString select_Band;
	GetDlgItem(IDC_Band_COMBO)->GetWindowText(select_Band);
	UINT16 **ImageDate = {};
	double fac1;
	if (select_Band == "R")
	{
		ImageDate = m_TIFIMG.TifFile.ImgRAdr;
		fac1 = 65535 / (copyImg.TifFile.EdRmax - copyImg.TifFile.EdRmin);
	}
	else if (select_Band == "G")
	{
		ImageDate = m_TIFIMG.TifFile.ImgGAdr;
		fac1 = 65535 / (copyImg.TifFile.EdGmax - copyImg.TifFile.EdRmin);
	}
	else if (select_Band == "B")
	{
		ImageDate = m_TIFIMG.TifFile.ImgBAdr;
		fac1 = 65535 / (copyImg.TifFile.EdBmax - copyImg.TifFile.EdBmin);
	}
	else
		MessageBox("波段选择错误");

	CString str_temp;
	int* LevelList = new int[255];//问题：用listnum初始化会报错，表示删除指针是NULL
	for (int ii = 0; ii < listNum; ii++)
	{
		str_temp = m_DSList.GetItemText(ii, 2);
		LevelList[ii * 2] = atoi(str_temp);
		str_temp = m_DSList.GetItemText(ii, 3);
		LevelList[ii * 2 + 1] = atoi(str_temp);
	}
	for (int ii = 0; ii < copyImg.TifFile.ImgH; ii++)
	{
		for (int jj = 0; jj < copyImg.TifFile.ImgW; jj++)
		{
			
			UINT16 www = ImageDate[ii][jj] ;
			COLORREF xiugai = GetColorLevel2(www, listNum, fac1, LevelList);
			copyImg.TifFile.ImgRAdr[ii][jj] = GetRValue(xiugai)*255;
			copyImg.TifFile.ImgGAdr[ii][jj] = GetGValue(xiugai)*255;
			copyImg.TifFile.ImgBAdr[ii][jj] = GetBValue(xiugai)*255;
		}
		m_SLICE_PROGRESS.SetPos(ii + 1);
	}
	HWND hWnd;
	hWnd = ::FindWindow(NULL, "主窗口");
	CWnd* m_parentDLG;
	m_parentDLG = FromHandle(hWnd);
	HDC hdc;
	hdc = ::GetDC(hWnd);
	CRect rect;
	::GetClientRect(hWnd, &rect);

	CRect rectCtrl;
	m_parentDLG->GetDlgItem(IDC_EDIT1)->GetWindowRect(&rectCtrl); //获取被选中的控件大小
	std::cout << "EDIT_1坐标：";
	std::cout << rectCtrl.left << "," << rectCtrl.top << "," << rectCtrl.right << "," << rectCtrl.bottom << std::endl;
	//转化为客户区坐标
	m_parentDLG->ScreenToClient(&rectCtrl);

	//
		//创建实线，宽度为1，灰色的笔
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(240, 240, 240));
	//将笔选入DC
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	//创建一个灰色的刷子
	HBRUSH hBrush = CreateSolidBrush(RGB(240, 240, 240));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	//绘制矩形，灰色边框，灰色区域的
	Rectangle(hdc, rectCtrl.right + 10, rectCtrl.top, rect.Width(), rect.Height());
	//恢复绘图对象
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);
	//删除绘图对象
	DeleteObject(hPen);
	DeleteObject(hBrush);

	//
	Rectangle(hdc, rectCtrl.right + 10, rectCtrl.top, rect.Width(), rect.Height());
	flag = copyImg.DisplayImgColor(&hdc, rect.Width() - rectCtrl.right - 25, rect.Height() - rectCtrl.top - 10, rectCtrl.right + 10, rectCtrl.top, m_TIFIMG.TifFile.ImgW, m_TIFIMG.TifFile.ImgH, 0, 0);


	if (flag == FALSE)
		MessageBox("影像显示失败！");

	delete[] LevelList;

	return copyImg;

}

void DensitySliceDlg::Save(Img_kele copyImg)
{
	//保存BMP

	CFileDialog Dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Bitmap Files (*.BMP)||");
	CString WrirtePath;
	CString FileClass;
	if (Dlg.DoModal() == IDOK)
	{

		WrirtePath = Dlg.GetPathName();
	}
	if (WrirtePath == "")
	{
		MessageBox("请选择输出路径");
		return;
	}
	// TODO: 在此添加控件通知处理程序代码
	if (Dlg.m_ofn.nFilterIndex == 1)
	{
		//用户选择了BMP格式
		CString strClass = ".BMP";
		WrirtePath = WrirtePath + strClass;
	}
	else
	{
		MessageBox("只能保存为bmp文件呦");
		return;
	}


	UCHAR *pdata = new UCHAR[3 * copyImg.ImgParaInCls.ImgW*copyImg.ImgParaInCls.ImgH]; if (!pdata) { AfxMessageBox("保存BMP失败"); }
	memset(pdata, 0, sizeof(UCHAR) * 3 * copyImg.ImgParaInCls.ImgW*copyImg.ImgParaInCls.ImgH);
	for (int ii = 0; ii < copyImg.ImgParaInCls.ImgH; ii++)
	{
		for (int jj = 0; jj < copyImg.ImgParaInCls.ImgW; jj++)
		{
			pdata[3 * ii*MainImg.ImgParaInCls.ImgW + 3 * jj] = copyImg.ImgParaInCls.ImgBAdr[ii][jj];
			pdata[3 * ii*MainImg.ImgParaInCls.ImgW + 3 * jj + 1] = copyImg.ImgParaInCls.ImgGAdr[ii][jj];
			pdata[3 * ii*MainImg.ImgParaInCls.ImgW + 3 * jj + 2] = copyImg.ImgParaInCls.ImgRAdr[ii][jj];
		}
		m_SLICE_PROGRESS.SetPos(ii+1);
	}
	MainImg.OutputDensitySlicingAsBMP(pdata, WrirtePath);
}

void DensitySliceDlg::Save2(ReadTIF copyImg)
{
	//保存TIF
	CFileDialog Dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Tag Image Files (*.TIF)||");
	CString WrirtePath;
	CString FileClass;
	if (Dlg.DoModal() == IDOK)
	{

		WrirtePath = Dlg.GetPathName();
	}

	if (WrirtePath == "")
	{
		MessageBox("请选择输出路径");
		return;
	}
	// TODO: 在此添加控件通知处理程序代码
	if (Dlg.m_ofn.nFilterIndex == 1)
	{
		//用户选择了BMP格式
		CString strClass = ".TIF";
		WrirtePath = WrirtePath + strClass;
	}
	else
	{
		MessageBox("只能保存为TIF文件呦");
		return;
	}

	////RGB分别存储为*
	//UINT16 *pdataR = new UINT16[ copyImg.TifFile.ImgW*copyImg.TifFile.ImgH]; if (!pdataR) { AfxMessageBox("保存TIF失败"); }
	//memset(pdataR, 0, sizeof(UINT16)  * copyImg.TifFile.ImgW*copyImg.TifFile.ImgH);
	//UINT16 *pdataG = new UINT16[copyImg.TifFile.ImgW*copyImg.TifFile.ImgH]; if (!pdataG) { AfxMessageBox("保存TIF失败"); }
	//memset(pdataG, 0, sizeof(UINT16)  * copyImg.TifFile.ImgW*copyImg.TifFile.ImgH);
	//UINT16 *pdataB = new UINT16[copyImg.TifFile.ImgW*copyImg.TifFile.ImgH]; if (!pdataB) { AfxMessageBox("保存TIF失败"); }
	//memset(pdataB, 0, sizeof(UINT16)  * copyImg.TifFile.ImgW*copyImg.TifFile.ImgH);
	//for (int ii = 0; ii < copyImg.TifFile.ImgH; ii++)
	//{
	//	for (int jj = 0; jj < copyImg.TifFile.ImgW; jj++)
	//	{
	//		pdataR[ii*copyImg.TifFile.ImgW * jj] = copyImg.TifFile.ImgRAdr[ii][jj];
	//		pdataG[ii*copyImg.TifFile.ImgW + jj] = copyImg.TifFile.ImgGAdr[ii][jj];
	//		pdataB[ii*copyImg.TifFile.ImgW + jj] = copyImg.TifFile.ImgBAdr[ii][jj];
	//	}
	//}
	//
	//gdal 保存为文件

	//CImage 保存文件，有点慢
	int r, g, b = 0;
	CImage tempImg;
	HWND hWnd_IFBMP;
	hWnd_IFBMP = ::FindWindow(NULL, "主窗口");
	CWnd*cWNd_IFBMP;
	cWNd_IFBMP = FromHandle(hWnd_IFBMP);
	CString str_IFBMP;
	cWNd_IFBMP->GetDlgItem(IDC_EDIT1)->GetWindowText(str_IFBMP);
	HRESULT hr = tempImg.Load(str_IFBMP);
	m_SLICE_PROGRESS.SetPos(0);
	for (int ii = 0; ii < tempImg.GetWidth(); ii++)
	{
		for (int jj = 0; jj < tempImg.GetHeight(); jj++)
		{
			r = copyImg.TifFile.ImgRAdr[jj][ii]/255;
			g = copyImg.TifFile.ImgGAdr[jj][ii] / 255;
			b = copyImg.TifFile.ImgBAdr[jj][ii] / 255;
			tempImg.SetPixel(ii, jj, RGB(r, g, b));
		
		}
		m_SLICE_PROGRESS.SetPos(ii+1);
	}
	HRESULT hr2 = tempImg.Save(WrirtePath);
	MessageBox("done");

	//copyImg.OutputDensitySlicingAsBMP(pdata, WrirtePath);


   //释内存
   //delete[]copyImg.TifFile.ImgRAdr;
   //delete[]copyImg.TifFile.ImgGAdr;
   //delete[]copyImg.TifFile.ImgBAdr;
}
