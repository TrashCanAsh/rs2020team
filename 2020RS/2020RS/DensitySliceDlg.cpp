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
	
	//ReadColorLib("");
	//m_ColorLibList.InsertString(0, "Rainbow");
	TraverseFiles(".\\色谱库");
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

BOOL DensitySliceDlg::ReadColorLib(string Path)
{
	CString FilePath = Path.c_str();
	FilePath = ".\\色谱库\\" + FilePath;
	//int xxxxx = 1;
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
	do
	{
		//找到的文件的文件名
		ReadColorLib(fileinfo.name);
		//更新list
		m_ColorLibList.InsertString(colorNum, fileinfo.name);
		colorNum = colorNum + 1;
	} while (_findnext(handle, &fileinfo)!=-1);
	_findclose(handle);
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
	
	//如果用户没有打开主窗口的影像
	if (MainImg.ImgParaInCls.RMax == 0 && MainImg.ImgParaInCls.RMin == 0)
	{
		MessageBox("请在主窗口打开影像");
		return;
	}
	Img_kele copyImg(MainImg);
	//分级显示
	CString str_degree;
	GetDlgItem(IDC_Level_EDIT)->GetWindowText(str_degree);
	int degree = atoi(str_degree);
	int listNum = m_DSList.GetItemCount();
	double fac1 = 256 / (copyImg.ImgParaInCls.RMax - copyImg.ImgParaInCls.RMin);
	UCHAR **ImageDate = copyImg.ImgParaInCls.ImgRAdr;

	CString str_temp;
	int* LevelList = new int[255];//问题：用listnum初始化会报错，表示删除指针是NULL
	for (int ii = 0; ii < listNum; ii++)
	{
		str_temp = m_DSList.GetItemText(ii, 2);
		LevelList[ii*2] =atoi(str_temp);
		str_temp = m_DSList.GetItemText(ii, 3);
		LevelList[ii * 2 + 1] = atoi(str_temp);
	}
	for (int ii = 0; ii < copyImg.ImgParaInCls.ImgH; ii++)
	{
		for (int jj = 0; jj < copyImg.ImgParaInCls.ImgW; jj++)
		{
			COLORREF xiugai = GetColorLevel(ImageDate[ii][jj],listNum,fac1,LevelList);
			copyImg.ImgParaInCls.ImgRAdr[ii][jj] = GetRValue(xiugai);
			copyImg.ImgParaInCls.ImgGAdr[ii][jj] = GetGValue(xiugai);
			copyImg.ImgParaInCls.ImgBAdr[ii][jj] = GetBValue(xiugai);
			/*if (jj % 50 == 0)
				std::cout << "ii = " << ii << "jj=" << jj << std::endl;*/
		}
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
	
	//int xxxx = 1;
	if (flag == FALSE)
		MessageBox("影像显示失败！");
	else
		MessageBox("done");

	delete[] LevelList;

	////保存BMP
	//CString writepath ;
	//writepath = "C:\\Users\\荔枝男孩\\Desktop\\result\\main.BMP";
	//UCHAR *pdata = memset(, );
	//for (int ii = 0; ii < copyImg.ImgParaInCls.ImgH; ii++)
	//{
	//	for (int jj = 0; jj < copyImg.ImgParaInCls.ImgW; jj++)
	//	{
	//		*pdata(3 * ii*MainImg.ImgParaInCls.ImgW+ 3 * jj ) = MainImg.ImgParaInCls.ImgBAdr[]
	//		*pdata(3 * ii*MainImg.ImgParaInCls.ImgW + 3 * jj + 1) =
	//		*pdata(3 * ii*MainImg.ImgParaInCls.ImgW + 3 * jj + 2) =
	//	}
	//}
	//MainImg.OutputDensitySlicingAsBMP(copyImg.ImgParaInCls.ImgRAdr,writepath);

	//释放内存
	/*delete[]copyImg.ImgParaInCls.ImgRAdr;
	delete[]copyImg.ImgParaInCls.ImgGAdr;
	delete[]copyImg.ImgParaInCls.ImgBAdr;
	delete[]copyImg.ImgParaInCls.ImgMAdr;*/
	
	// TODO: 在此添加控件通知处理程序代码
}
