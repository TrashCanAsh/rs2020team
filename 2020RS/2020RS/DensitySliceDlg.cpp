// DensitySliceDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "2020RS.h"
#include "DensitySliceDlg.h"
#include "afxdialogex.h"

extern Img_kele MainImg;
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
}


BEGIN_MESSAGE_MAP(DensitySliceDlg, CDialog)
	ON_BN_CLICKED(IDC_Reverse_BUTTON, &DensitySliceDlg::OnBnClickedReverseButton)
	ON_WM_PAINT()
	ON_EN_KILLFOCUS(IDC_Level_EDIT, &DensitySliceDlg::OnEnKillfocusLevelEdit)
	ON_BN_CLICKED(IDC_Output_BUTTON, &DensitySliceDlg::OnBnClickedOutputButton)
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
	ReadColorLib("");
	m_ColorLibList.InsertString(0, "Rainbow");
	//文本框初始化
	SetDlgItemText(IDC_Level_EDIT, _T("10"));
	SetDlgItemInt(IDC_Max_EDIT, MainImg.ImgParaInCls.RMax);
	SetDlgItemInt(IDC_Min_EDIT, MainImg.ImgParaInCls.RMin);
	//
	((CComboBox*)GetDlgItem(IDC_Band_COMBO))->AddString("R");
	((CComboBox*)GetDlgItem(IDC_Band_COMBO))->AddString("G");
	((CComboBox*)GetDlgItem(IDC_Band_COMBO))->AddString("B");
	//
	flag = 0;
	
	if (MainImg.ImgParaInCls.RMin!= MainImg.ImgParaInCls.RMax)
	{
		//分级显示
		CString str_degree;
		GetDlgItem(IDC_Level_EDIT)-> GetWindowText(str_degree);
		int degree = atoi(str_degree);
		show_list(colorlib, degree);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

BOOL DensitySliceDlg::ReadColorLib(CString path)
{
	CString FilePath;
	char ReadStr[1024]; memset(ReadStr, 0, 1024);
	FilePath = ".\\data\\Rainbow.lib";
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
		if (level_max > 255)
			level_max = 255;
		str.Format("%d", level_max);
		m_DSList.SetItemText(ii, 2,str);
		str.Format("%d", level_min);
		m_DSList.SetItemText(ii, 3, str);
	}
}

COLORREF DensitySliceDlg::GetColorLevel(UCHAR DN_Date,int listNum,double fac1, int *LevelList)
{
	
	int levelMax,levelMin;
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
		MessageBox("提取色带失败");
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
	DrawColorLib(IDC_ColorSlice, colorlib, flag);
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

	//进度条
	CProgressCtrl *MySliceProgress = (CProgressCtrl *)GetDlgItem(IDC_SLICE_PROGRESS);
	MySliceProgress->SetRange(0, 10);
	//分级显示
	CString str_degree;
	GetDlgItem(IDC_Level_EDIT)->GetWindowText(str_degree);
	int degree = atoi(str_degree);
	int listNum = m_DSList.GetItemCount();
	double fac1 = 256 / (MainImg.ImgParaInCls.RMax - MainImg.ImgParaInCls.RMin);
	UCHAR **ImageDate = MainImg.ImgParaInCls.ImgRAdr;

	CString str_temp;
	int* LevelList = new int[255];
	for (int ii = 0; ii < listNum; ii++)
	{
		str_temp = m_DSList.GetItemText(ii, 2);
		LevelList[ii*2] =atoi(str_temp);
		str_temp = m_DSList.GetItemText(ii, 3);
		LevelList[ii * 2 + 1] = atoi(str_temp);
	}
	for (int ii = 0; ii < MainImg.ImgParaInCls.ImgH; ii++)
	{
		for (int jj = 0; jj < MainImg.ImgParaInCls.ImgW; jj++)
		{
			COLORREF xiugai = GetColorLevel(ImageDate[ii][jj],listNum,fac1,LevelList);
			MainImg.ImgParaInCls.ImgRAdr[ii][jj] = GetRValue(xiugai);
			MainImg.ImgParaInCls.ImgGAdr[ii][jj] = GetGValue(xiugai);
			MainImg.ImgParaInCls.ImgBAdr[ii][jj] = GetBValue(xiugai);
			if (jj % 50 == 0)
				std::cout << "ii = " << ii << "jj=" << jj << std::endl;
		}
		
		MySliceProgress->OffsetPos(ii/MainImg.ImgParaInCls.ImgH*10);
		//MySliceProgress->OffsetPos(1);
	}
	MessageBox("dong1111");
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
	ScreenToClient(&rectCtrl);  //转化为客户区坐标

	Rectangle(hdc, rectCtrl.right + 10, rectCtrl.top, rect.Width(), rect.Height());

	flag = MainImg.DisplayImgColor(&hdc, rect.Width() - rectCtrl.right - 25, rect.Height() - rectCtrl.top - 10, rectCtrl.right + 10, rectCtrl.top, MainImg.ImgParaInCls.ImgW, MainImg.ImgParaInCls.ImgH, 0, 0);
	flag = MainImg.DisplayImgColor(&hdc, rect.Width() - rectCtrl.right - 25, rect.Height() - rectCtrl.top - 10, rectCtrl.right + 10, rectCtrl.top, MainImg.ImgParaInCls.ImgW, MainImg.ImgParaInCls.ImgH, 0, 0);

	if (flag == FALSE)
		MessageBox("影像显示失败！");
	else
		MessageBox("done");

	delete[] LevelList;

	//问题：用listnum初始化会报错，表示删除指针是NULL
	// TODO: 在此添加控件通知处理程序代码
}
