// SpectralViewDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "2020RS.h"
#include "SpectralViewDlg.h"
#include "afxdialogex.h"

//状态栏相关
static UINT indicators[] =
{
	IDS_SpectralStatus,
	IDS_WaveLength,
	IDS_WaveLengthNum,
	IDS_Reflectivity,
	IDS_ReflectivityNum,
	IDS_ProgramVersion,
	IDS_Time
};

// SpectralViewDlg 对话框

IMPLEMENT_DYNAMIC(SpectralViewDlg, CDialog)

SpectralViewDlg::SpectralViewDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SpectralView_DIALOG, pParent)
{

}

SpectralViewDlg::~SpectralViewDlg()
{
}

void SpectralViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_SpecLib_TREE, m_SpecTree);
	DDX_Control(pDX, IDC_SpecLine_LIST, m_specList);
	DDX_Control(pDX, IDC_Property_LIST, m_PropList);
	DDX_Control(pDX, IDC_EDIT1, m_PropEdit);
	DDX_Control(pDX, IDC_Curve_MFCCOLORBUTTON, m_CurveColor);
}


BEGIN_MESSAGE_MAP(SpectralViewDlg, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_Property_LIST, &SpectralViewDlg::OnNMDblclkPropertyList)
	//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_Property_LIST, &SpectralViewDlg::OnLvnItemchangedPropertyList)
//	ON_BN_CLICKED(IDC_BUTTON3, &SpectralViewDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &SpectralViewDlg::OnEnChangeMfceditbrowse1)
	ON_BN_CLICKED(IDC_CloseSpe_BUTTON, &SpectralViewDlg::OnBnClickedClosespeButton)
	//	ON_NOTIFY(HDN_ITEMCHANGED, 0, &SpectralViewDlg::OnHdnItemchangedSpeclineList)
	//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_SpecLine_LIST, &SpectralViewDlg::OnLvnItemchangedSpeclineList)
		//ON_NOTIFY(LVN_ITEMCHANGED, IDC_SpecLine_LIST, &SpectralViewDlg::OnItemChangedListCtrl)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_SpecLine_LIST, &SpectralViewDlg::OnLvnItemchangedSpeclineList)
	ON_EN_KILLFOCUS(IDC_EDIT1, &SpectralViewDlg::OnEnKillfocusEdit1)
	//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_Property_LIST, &SpectralViewDlg::OnNMCustomdrawPropertyList)
	ON_NOTIFY(LVN_INSERTITEM, IDC_SpecLine_LIST, &SpectralViewDlg::OnLvnInsertitemSpeclineList)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SpecLine_LIST, &SpectralViewDlg::OnNMCustomdrawSpeclineList)
	ON_NOTIFY(NM_CLICK, IDC_SpecLine_LIST, &SpectralViewDlg::OnNMClickSpeclineList)

//	ON_BN_KILLFOCUS(IDC_Curve_MFCCOLORBUTTON, &SpectralViewDlg::OnBnKillfocusCurveMfccolorbutton)
//	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_Curve_MFCCOLORBUTTON, &SpectralViewDlg::OnBnHotItemChangeCurveMfccolorbutton)
	ON_BN_CLICKED(IDC_Curve_MFCCOLORBUTTON, &SpectralViewDlg::OnBnClickedCurveMfccolorbutton)
	ON_WM_MOUSEMOVE()
	ON_NOTIFY(LVN_DELETEALLITEMS, IDC_SpecLine_LIST, &SpectralViewDlg::OnLvnDeleteallitemsSpeclineList)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// SpectralViewDlg 消息处理程序


BOOL SpectralViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//控制台
	//if (!OpenConsole()) AfxMessageBox(_T("控制台打开失败"));

	//左侧文件列表的初始化
	HTREEITEM hRoot;     // 树的根节点的句柄   
	HTREEITEM hCataItem; // 可表示任一分类节点的句柄   
	HTREEITEM hSpecItem;  // 可表示任一光谱文件节点的句柄

	////树中节点前可添加图标
	////插入根节点
	//hRoot = m_SpecTree.InsertItem(_T("USGS"), 0, 0);
	////在根节点下插入光谱类M
	//hCataItem = m_SpecTree.InsertItem(_T("M"), NULL, NULL, hRoot, TVI_LAST);
	////在M类下插入光谱文件节点
	//hSpecItem = m_SpecTree.InsertItem(_T("Spec1"), NULL, NULL, hCataItem, TVI_LAST);
	//hSpecItem = m_SpecTree.InsertItem(_T("Spec2"), NULL, NULL, hCataItem, TVI_LAST);

	////在根节点下插入光谱类S
	//hCataItem = m_SpecTree.InsertItem(_T("S"), NULL, NULL, hRoot, TVI_LAST);
	////在S类下插入光谱文件节点
	//hSpecItem = m_SpecTree.InsertItem(_T("Spec3"), NULL, NULL, hCataItem, TVI_LAST);
	//hSpecItem = m_SpecTree.InsertItem(_T("Spec4"), NULL, NULL, hCataItem, TVI_LAST);


	//右侧上方光谱曲线选择的初始化
	CRect lrect;
	m_specList.GetClientRect(&lrect);
	// 为列表视图控件添加全行选中和栅格风格
	m_specList.SetExtendedStyle(m_specList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//checkbox的添加
	ListView_SetExtendedListViewStyle(m_specList.GetSafeHwnd(), m_specList.GetExStyle() | LVS_EX_CHECKBOXES);

	m_specList.InsertColumn(0, _T("光谱名称"), LVCFMT_CENTER, lrect.Width() / 1.5, 0);
	m_specList.InsertColumn(1, _T(" "), LVCFMT_CENTER, lrect.Width() / 4, 1);
	//m_specList.InsertColumn(0, _T("颜色"), LVCFMT_CENTER, lrect.Width() / 3);
	//m_specList.InsertItem(0, _T("光谱曲线1的名称"));
	//m_specList.InsertItem(1, _T("光谱曲线2的名称"));


	//右侧下方绘图属性的初始化
	//隐藏Edit控件
	m_PropEdit.ShowWindow(SW_HIDE);
	CRect prect;
	m_PropList.GetClientRect(&prect);
	// 为列表视图控件添加全行选中和栅格风格
	m_PropList.SetExtendedStyle(m_PropList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加两列   
	m_PropList.InsertColumn(0, _T("项目"), LVCFMT_CENTER, prect.Width() / 2, 0);
	//m_PropList.InsertColumn(1, _T(" 1 "), LVCFMT_CENTER, prect.Width() / 2.5, 1);
	m_PropList.InsertColumn(1, _T("值"), LVCFMT_CENTER, prect.Width() / 2, 1);
	m_PropList.InsertItem(0, _T("图表标题"));
	
	//曲线属性相关
	m_PropList.InsertItem(1, _T("曲线文件名"));
	m_PropList.InsertItem(2, _T("反射率最大值"));
	m_PropList.InsertItem(3, _T("反射率最小值"));
	m_PropList.InsertItem(4, _T("曲线颜色"));
	m_PropList.InsertItem(5, _T("曲线粗细"));
	

	//读入曲线颜色数组数据
	if (ReadColorLib() == FALSE)
	{
		MessageBox("曲线颜色数组读入错误！");
	}

	CRect rc;
	m_PropList.GetSubItemRect(4, 1, LVIR_LABEL, rc);//获得子项的RECT；
	CWnd *Parent= m_CurveColor.GetParent();
	m_CurveColor.SetParent(&m_PropList);//转换坐标为列表框中的坐标
	m_CurveColor.MoveWindow(rc);//移动Edit到RECT坐在的位置;
	//m_CurveColor.SetParent(Parent);

	m_SpectralStatusbar.Create(this);                  //创造状态栏
	m_SpectralStatusbar.SetIndicators(indicators, 7);   //设置状态栏项目栏数
	m_SpectralStatusbar.SetPaneInfo(0, IDS_SpectralStatus, SBPS_STRETCH, 80);
	m_SpectralStatusbar.SetPaneInfo(1, IDS_WaveLength, SBPS_STRETCH, 80);
	m_SpectralStatusbar.SetPaneInfo(2, IDS_WaveLengthNum, SBPS_STRETCH, 80);
	m_SpectralStatusbar.SetPaneInfo(3, IDS_Reflectivity, SBPS_STRETCH, 80);
	m_SpectralStatusbar.SetPaneInfo(4, IDS_ReflectivityNum, SBPS_STRETCH, 80);
	m_SpectralStatusbar.SetPaneInfo(5, IDS_ProgramVersion, SBPS_STRETCH, 220);
	m_SpectralStatusbar.SetPaneInfo(6, IDS_Time, SBPS_STRETCH, 120);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, IDS_Time);
	SetTimer(2, 1000, NULL);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//bool SpectralViewDlg::OpenConsole()
//{
//	if (!AllocConsole()) return FALSE; //控制台调试窗口开启
//
//	freopen("CONOUT$", "w", stdout);//开启中文控制台输出支持
//
//	return TRUE;
//}

void SpectralViewDlg::OnNMDblclkPropertyList(NMHDR *pNMHDR, LRESULT *pResult)
{
	//双击右侧下方属性列表
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CRect rc;

	currRow = pNMListView->iItem;//获得选中的行
	currCol = pNMListView->iSubItem;//获得选中列
	int allRow = m_PropList.GetItemCount();//获取当前一共多少行

	cout << "当前点击第" << currRow << "行，" << "第" << currCol << "列，共" << allRow << "行" << endl;

	if (pNMListView->iSubItem != 0) //如果选择的是子项;
	{
		m_PropList.GetSubItemRect(currRow, currCol, LVIR_LABEL, rc);//获得子项的RECT；
		m_PropEdit.SetParent(&m_PropList);//转换坐标为列表框中的坐标
		m_PropEdit.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		m_PropEdit.SetWindowText(m_PropList.GetItemText(currRow, currCol));//将该子项中的值放在Edit控件中；
		m_PropEdit.ShowWindow(SW_SHOW);//显示Edit控件；
		m_PropEdit.SetFocus();//设置Edit焦点
		m_PropEdit.ShowCaret();//显示光标
		m_PropEdit.SetSel(-1);//将光标移动到最后
		/*if (currRow == allRow - 1)
		{
			m_PropList.InsertItem(currRow + 1, _T(""));
		}*/
		//m_PropList.SetItemText(1, 1, _T("默认"));
		//CString tem;
		//m_PropEdit.GetWindowText(tem); //得到用户输入的新的内容
		////GetDlgItemText(IDC_EDIT1, tem);
		//cout << (LPCTSTR)tem << endl;
		//m_PropList.SetItemText(currRow, currCol, tem); //设置编辑框的新内容
		////m_PropEdit.ShowWindow(SW_HIDE); //隐藏编辑框
	}



	*pResult = 0;


}

void SpectralViewDlg::OnEnKillfocusEdit1()
{
	// TODO: 在此添加控件通知处理程序代码
	//根据PropertyEdit的修改值，即图表的绘制属性被修改
	UpdateData();
	CString tem;
	m_PropEdit.GetWindowText(tem);    //得到用户输入的新的内容  
	m_PropList.SetItemText(currRow, currCol, tem);   //设置编辑框的新内容  
	m_PropEdit.ShowWindow(SW_HIDE);                //隐藏编辑框

	if (currRow == 0 && currCol == 1)
	{
		//标题被修改
		SetDlgItemText(IDC_Title_STATIC, tem);
	}
}

BOOL SpectralViewDlg::ReadColorLib()
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

int SpectralViewDlg::SsToStr60(char * str, char * s_dat[])
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


//void SpectralViewDlg::OnBnClickedButton3()
//{
//	//点击显示按钮
//	// TODO: 在此添加控件通知处理程序代码
//	double stepX, stepY;
//	CRect rect;
//	CDC* pDCH;
//	double max = 0;
//	//设置画笔
//	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
//	CPen* pOldPen = NULL;
//	int iPenWidth;
//	//获取绘图窗口的CDC资源
//	this->GetDlgItem(IDC_STATIC)->GetClientRect(rect);
//	pDCH = this->GetDlgItem(IDC_STATIC)->GetDC();
//	int nRopMode = pDCH->SetROP2(R2_NOTXORPEN);
//	//获取第一条折线
//	ASDstruct temp;
//	temp = SpectralIO::ASDdata.front();
//	//找最大值
//	for (int i = 0; i < temp.data.size(); i++)
//	{
//		double tp = temp.data[i].yy;
//		if (tp > max)
//			max = tp;
//	}
//	//计算XY轴单位距离
//	stepX = double(rect.Width() - 2) / (double)temp.data.size();
//	stepY = double(rect.Height() - 2) / (max * (double)1.2);
//	//设置画笔
//	iPenWidth = 1;
//	pOldPen = pDCH->SelectObject(&pen);
//	//逐点画折线图
//	for (int i = 0, j = i + 10; i < temp.data.size() - 10; i = i + 10, j = i + 10)
//	{
//		pDCH->MoveTo(int(i * stepX + 1), int(rect.Height() - temp.data[i].yy * stepY - 1));
//		pDCH->LineTo(int(j * stepX), int(rect.Height() - temp.data[j].yy * stepY));
//	}
//	//释放CDC资源
//	ReleaseDC(pDCH);
//}


void SpectralViewDlg::OnEnChangeMfceditbrowse1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//MessageBox("!!!");

	//读入文件
	CString FilePath;
	GetDlgItemText(IDC_MFCEDITBROWSE1, FilePath);
	SpectralIO spectrallib;
	spectrallib.readfile(FilePath);
	int maxnum = SpectralIO::ASDdata.size();
	int  now_item = m_specList.GetItemCount();
	m_specList.InsertItem(now_item, SpectralIO::ASDdata[maxnum - 1].name);
	m_specList.SetCheck(now_item);

	//选择新的光谱曲线颜色
	CurColorStruct data;
	data.name = SpectralIO::ASDdata[maxnum - 1].name;
	cout << "光谱名为：" << data.name << endl;
	data.CurColor = colorlib[colorNum * 30 % 256];
	CurrentColor.push_back(data);
	colorNum++;
	std::cout << "当前颜色数量：" << CurrentColor.size() << endl;

	//设置属性栏中的曲线颜色
	COLORREF color;
	color = data.CurColor;
	m_CurveColor.SetColor(color);

	//设置曲线文件名以及最大最小值
	m_PropList.SetItemText(1, 1, SpectralIO::ASDdata[maxnum - 1].name);
	float Min, Max;
	Min = SpectralIO::ASDdata[maxnum - 1].MinRel;
	Max= SpectralIO::ASDdata[maxnum - 1].MaxRel;
	CString tem;
	tem.Format("%.3f", Min);
	m_PropList.SetItemText(2, 1, tem);
	tem.Format("%.3f", Max);
	m_PropList.SetItemText(3, 1, tem);

	//绘制曲线
	cout << "读入曲线时绘制" << endl;
	DrawSpectralPic(IDC_STATIC, data.name, PS_SOLID, 1, color, 5, 0.0);
	int PenWith = 1;
	tem.Format("%d", PenWith);
	m_PropList.SetItemText(5, 1, tem);
}




void SpectralViewDlg::OnBnClickedClosespeButton()
{
	//点击关闭按钮
	int nItem = -1;
	SpectralIO spectrallib;
	POSITION pos = m_specList.GetFirstSelectedItemPosition();
	nItem = m_specList.GetNextSelectedItem(pos);
	if (nItem < 0)
	{
		return;
	}
	HWND hwndLV;
	hwndLV = GetDlgItem(IDC_SpecLine_LIST)->GetSafeHwnd();
	if (ListView_GetCheckState(hwndLV, nItem)) 
	{
		DrawSpectralPic(IDC_STATIC, nItem, PS_SOLID, 1, CurrentColor[nItem].CurColor, 5, 0.0);
	}
	//消除折线
	
	spectrallib.delete_data(nItem);
	
	//更新list

	// 全部清空list
	m_specList.DeleteItem(nItem);
	pos = m_specList.GetFirstSelectedItemPosition();
	//重新显示
	/*for (int ii = 0; ii < SpectralIO::ASDdata.size(); ii++)
	{
		m_specList.InsertItem(ii, SpectralIO::ASDdata[ii].name);
	}*/

	// TODO: 在此添加控件通知处理程序代码
	//关闭时需要查看checkbox的状态，选择是否擦除曲线
	//MessageBox("记得码上根据checkbox的状态，选择是否擦除曲线的代码");

	//还要删去CurrentColor vector中的颜色
	CurrentColor.erase(begin(CurrentColor) + nItem);


}



void SpectralViewDlg::OnLvnItemchangedSpeclineList(NMHDR *pNMHDR, LRESULT *pResult)
{

	//LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	//CheckBox控制是否显示该光谱曲线
	//int nItem;
	//nItem = m_specList.GetItemCount();
	//if (m_specList.GetCheck(0))
	//{
	//	//绘制第一条曲线
	//	double stepX, stepY;
	//	CRect rect;
	//	CDC* pDCH;
	//	double max = 0;
	//	//设置画笔
	//	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
	//	CPen* pOldPen = NULL;
	//	int iPenWidth;
	//	//获取绘图窗口的CDC资源
	//	this->GetDlgItem(IDC_STATIC)->GetClientRect(rect);
	//	pDCH = this->GetDlgItem(IDC_STATIC)->GetDC();
	//	int nRopMode = pDCH->SetROP2(R2_NOTXORPEN);
	//	//获取第一条折线
	//	ASDstruct temp;
	//	temp = SpectralIO::ASDdata.front();
	//	//找最大值
	//	for (int i = 0; i < temp.data.size(); i++)
	//	{
	//		double tp = temp.data[i].yy;
	//		if (tp > max)
	//			max = tp;
	//	}
	//	//计算XY轴单位距离
	//	stepX = double(rect.Width() - 2) / (double)temp.data.size();
	//	stepY = double(rect.Height() - 2) / (max * (double)1.2);
	//	//设置画笔
	//	iPenWidth = 1;
	//	pOldPen = pDCH->SelectObject(&pen);
	//	//逐点画折线图
	//	for (int i = 0, j = i + 10; i < temp.data.size() - 10; i = i + 10, j = i + 10)
	//	{
	//		pDCH->MoveTo(int(i * stepX + 1), int(rect.Height() - temp.data[i].yy * stepY - 1));
	//		pDCH->LineTo(int(j * stepX), int(rect.Height() - temp.data[j].yy * stepY));
	//	}
	//	//释放CDC资源
	//	ReleaseDC(pDCH);
	//}
	//else
	//{
	//	//擦除第一条曲线
	//	double stepX, stepY;
	//	CRect rect;
	//	CDC* pDCH;
	//	double max = 0;
	//	//设置画笔
	//	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
	//	CPen* pOldPen = NULL;
	//	int iPenWidth;
	//	//获取绘图窗口的CDC资源
	//	this->GetDlgItem(IDC_STATIC)->GetClientRect(rect);
	//	pDCH = this->GetDlgItem(IDC_STATIC)->GetDC();
	//	int nRopMode = pDCH->SetROP2(R2_NOTXORPEN);
	//	//获取第一条折线
	//	ASDstruct temp;
	//	temp = SpectralIO::ASDdata.front();
	//	//找最大值
	//	for (int i = 0; i < temp.data.size(); i++)
	//	{
	//		double tp = temp.data[i].yy;
	//		if (tp > max)
	//			max = tp;
	//	}
	//	//计算XY轴单位距离
	//	stepX = double(rect.Width() - 2) / (double)temp.data.size();
	//	stepY = double(rect.Height() - 2) / (max * (double)1.2);
	//	//设置画笔
	//	iPenWidth = 1;
	//	pOldPen = pDCH->SelectObject(&pen);
	//	//逐点画折线图
	//	for (int i = 0, j = i + 10; i < temp.data.size() - 10; i = i + 10, j = i + 10)
	//	{
	//		pDCH->MoveTo(int(i * stepX + 1), int(rect.Height() - temp.data[i].yy * stepY - 1));
	//		pDCH->LineTo(int(j * stepX), int(rect.Height() - temp.data[j].yy * stepY));
	//	}
	//	//释放CDC资源
	//	ReleaseDC(pDCH);
	//}

	//SpectralList实现checkbox的选中或取消选中以重画光谱
	LPNMITEMACTIVATE pNMLV = (LPNMITEMACTIVATE)pNMHDR;
	if ((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(1)) /* old state : unchecked */
		&& (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(2)) /* new state : checked */
		)
	{
		cout << "Item " << pNMLV->iItem << " is checked" << endl;
		CString SpecName = m_specList.GetItemText(pNMLV->iItem, 0);
		cout << "文件名为" << SpecName << endl;
		//绘制第一条曲线
		//if (pNMLV->iItem == 0)
		//{
		//	//哪个checkbox被选中就重画哪条曲线
		//	double stepX, stepY;
		//	CRect rect;
		//	CDC* pDCH;
		//	double max = 0;
		//	//设置画笔
		//	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
		//	CPen* pOldPen = NULL;
		//	int iPenWidth;
		//	//获取绘图窗口的CDC资源
		//	this->GetDlgItem(IDC_STATIC)->GetClientRect(rect);
		//	pDCH = this->GetDlgItem(IDC_STATIC)->GetDC();
		//	int nRopMode = pDCH->SetROP2(R2_NOTXORPEN);
		//	//获取第一条折线
		//	ASDstruct temp;
		//	temp = SpectralIO::ASDdata.front();
		//	//找最大值
		//	for (int i = 0; i < temp.data.size(); i++)
		//	{
		//		double tp = temp.data[i].yy;
		//		if (tp > max)
		//			max = tp;
		//	}
		//	//计算XY轴单位距离
		//	stepX = double(rect.Width() - 2) / (double)temp.data.size();
		//	stepY = double(rect.Height() - 2) / (max * (double)1.2);
		//	//设置画笔
		//	iPenWidth = 1;
		//	pOldPen = pDCH->SelectObject(&pen);
		//	//逐点画折线图
		//	for (int i = 0, j = i + 10; i < temp.data.size() - 10; i = i + 10, j = i + 10)
		//	{
		//		pDCH->MoveTo(int(i * stepX + 1), int(rect.Height() - temp.data[i].yy * stepY - 1));
		//		pDCH->LineTo(int(j * stepX), int(rect.Height() - temp.data[j].yy * stepY));
		//	}
		//	//释放CDC资源
		//	ReleaseDC(pDCH);
		//}
		
		int nPosition;
		for (vector<CurColorStruct>::iterator it = CurrentColor.begin(); it != CurrentColor.end(); it++)
		{
			//根据波谱文件名查找曲线颜色
			if ((*it).name == SpecName)
			{
				nPosition = distance(CurrentColor.begin(), it);
				cout << "光谱文件名为：" << SpecName;
				cout << "距离为:";
				cout << nPosition << endl;
				//设置曲线属性颜色
				COLORREF color;
				if (!CurrentColor.empty())
				{
					cout << "设置曲线属性颜色" << endl;
					color = CurrentColor[nPosition].CurColor;
				}
				else
					color = RGB(0, 0, 255);//有点点问题，因颜色被固定
				//SpectralViewDlg::m_CurveColor.SetColor(color);

				cout << "绘制曲线" << endl;
				DrawSpectralPic(IDC_STATIC, SpecName, PS_SOLID, 1, color, 5, 0.0);

				break;
			}
			else
			{
				cout << "未找到该光谱" << endl;
			}
		}

		////设置曲线属性颜色
		//COLORREF color;
		//if (!CurrentColor.empty())
		//{
		//	cout << "设置曲线属性颜色" << endl;
		//	color = CurrentColor[nPosition].CurColor;
		//}	
		//else
		//	color = RGB(0, 0, 255);//有点点问题，因颜色被固定
		////SpectralViewDlg::m_CurveColor.SetColor(color);

		//DrawSpectralPic(IDC_STATIC, SpecName,PS_SOLID,1, color,5,0.0);
	}
	else if ((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(2)) /* old state : checked */
		&& (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(1)) /* new state : unchecked */
		)
	{
		//cout << "Item " << pNMLV->iItem << " is unchecked" << endl;
		//CString SpecName = m_specList.GetItemText(pNMLV->iItem, 0);
		//cout << "文件名为" << SpecName << endl;
		////绘制第一条曲线
		//if (pNMLV->iItem == 0)
		//{
		//	//哪个checkbox被选中就重画哪条曲线
		//	double stepX, stepY;
		//	CRect rect;
		//	CDC* pDCH;
		//	double max = 0;
		//	//设置画笔
		//	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
		//	CPen* pOldPen = NULL;
		//	int iPenWidth;
		//	//获取绘图窗口的CDC资源
		//	this->GetDlgItem(IDC_STATIC)->GetClientRect(rect);
		//	pDCH = this->GetDlgItem(IDC_STATIC)->GetDC();
		//	int nRopMode = pDCH->SetROP2(R2_NOTXORPEN);
		//	//获取第一条折线
		//	ASDstruct temp;
		//	temp = SpectralIO::ASDdata.front();
		//	//找最大值
		//	for (int i = 0; i < temp.data.size(); i++)
		//	{
		//		double tp = temp.data[i].yy;
		//		if (tp > max)
		//			max = tp;
		//	}
		//	//计算XY轴单位距离
		//	stepX = double(rect.Width() - 2) / (double)temp.data.size();
		//	stepY = double(rect.Height() - 2) / (max * (double)1.2);
		//	//设置画笔
		//	iPenWidth = 1;
		//	pOldPen = pDCH->SelectObject(&pen);
		//	//逐点画折线图
		//	for (int i = 0, j = i + 10; i < temp.data.size() - 10; i = i + 10, j = i + 10)
		//	{
		//		pDCH->MoveTo(int(i * stepX + 1), int(rect.Height() - temp.data[i].yy * stepY - 1));
		//		pDCH->LineTo(int(j * stepX), int(rect.Height() - temp.data[j].yy * stepY));
		//	}
		//	//释放CDC资源
		//	ReleaseDC(pDCH);
		//}
		
		cout << "Item " << pNMLV->iItem << " is checked" << endl;
		CString SpecName = m_specList.GetItemText(pNMLV->iItem, 0);
		cout << "文件名为" << SpecName << endl;
		int nPosition;
		for (vector<CurColorStruct>::iterator it = CurrentColor.begin(); it != CurrentColor.end(); it++)
		{
			//根据波谱文件名查找曲线颜色
			if ((*it).name == SpecName)
			{
				nPosition = distance(CurrentColor.begin(), it);
				cout << "光谱文件名为：" << SpecName;
				cout << "距离为:";
				cout << nPosition << endl;
				//设置曲线属性颜色
				COLORREF color;
				if (!CurrentColor.empty())
				{
					cout << "设置曲线属性颜色" << endl;
					color = CurrentColor[nPosition].CurColor;
				}
				else
					color = RGB(0, 0, 255);//有点点问题，因颜色被固定
				//SpectralViewDlg::m_CurveColor.SetColor(color);

				cout << "绘制曲线" << endl;
				DrawSpectralPic(IDC_STATIC, SpecName, PS_SOLID, 1, color, 5, 0.0);

				break;
			}
			else
			{
				cout << "未找到该光谱" << endl;
			}
		}

		////设置曲线属性颜色
		//COLORREF color;
		//if (!CurrentColor.empty())
		//	color = CurrentColor[nPosition].CurColor;
		//else
		//	color = RGB(0, 0, 255);//有点点问题，因颜色被固定
		////SpectralViewDlg::m_CurveColor.SetColor(color);

		//DrawSpectralPic(IDC_STATIC, SpecName, PS_SOLID, 1, color, 5, 0.0);
	}
	else
	{
		cout << "Item " << pNMLV->iItem << " does't change the check-status" << endl;
	}

	*pResult = 0;
}




//void SpectralViewDlg::OnNMCustomdrawPropertyList(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	//测试是否能改变单个单元格背景颜色
//	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
//
//	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
//	{
//		*pResult = CDRF_NOTIFYITEMDRAW;
//	}
//	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
//	{
//		// This is the notification message for an item. We'll request
//		// notifications before each subitem's prepaint stage.
//
//		*pResult = CDRF_NOTIFYSUBITEMDRAW;
//	}
//	else if ((CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage)
//	{
//		int nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec);
//		COLORREF crText, crBkgnd;
//		if (0 == pLVCD->iSubItem)
//		{
//			//第一列
//			if (nItem == 1)
//			{
//				//第二行
//				crText = RGB(0, 255, 0);
//				crBkgnd = RGB(255, 0, 0);
//				*pResult = CDRF_DODEFAULT;
//			}
//			else
//			{
//				//其他行
//				crText = RGB(0, 0, 0);
//				crBkgnd = RGB(255, 255, 255);
//				*pResult = CDRF_DODEFAULT;
//			}
//			
//		}
//		else
//		{
//			if (nItem == 0)
//			{
//				crText = RGB(0, 0, 0);
//				crBkgnd = RGB(0, 0, 255);
//				*pResult = CDRF_DODEFAULT;
//			}
//			else
//			{
//				crText = RGB(0, 0, 0);
//				crBkgnd = RGB(255, 255, 255);
//				*pResult = CDRF_DODEFAULT;
//			}
//		}
//
//		pLVCD->clrText = crText;
//		pLVCD->clrTextBk = crBkgnd;
//	}
//	*pResult = 0;
//	*pResult |= CDRF_NOTIFYPOSTPAINT;		//必须有，不然就没有效果
//	*pResult |= CDRF_NOTIFYITEMDRAW;		//必须有，不然就没有效果
//}


void SpectralViewDlg::OnLvnInsertitemSpeclineList(NMHDR *pNMHDR, LRESULT *pResult)
{
	////SpectralList中插入新的一条光谱
	//LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	//// TODO: 在此添加控件通知处理程序代码
	//int  now_item = m_specList.GetItemCount();
	//CurrentColor.push_back

	//*pResult = 0;
}


void SpectralViewDlg::OnNMCustomdrawSpeclineList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//重绘SpecList以实现item背景色的设置
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		cout << "1--";
		COLORREF crText, crBkgnd;
		int nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec);
		cout << "nItem:" << nItem;
		cout << "pLVCD->iSubItem:" << pLVCD->iSubItem << endl;
		if (pLVCD->iSubItem == 1)
		{
			if (nItem == 0)
			{
				//cout << "绘制绘制"<<pLVCD->iSubItem << "," << nItem << endl;
				crText = RGB(0, 0, 0);
				if (!CurrentColor.empty())
				{
					if (nItem > CurrentColor.size()-1)
					{
						crBkgnd = CurrentColor[CurrentColor.size() - 1].CurColor;
					}
					else
					{
						crBkgnd = CurrentColor[nItem].CurColor;
					}
				}	
				else
					crBkgnd = RGB(255, 255, 255);
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
			cout << pLVCD->iSubItem << endl;
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
		cout << "2--";
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		int nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec);
		COLORREF crText, crBkgnd;
		if (pLVCD->iSubItem == 1)
		{
			if (nItem >= 0)
			{
				cout << "绘制绘制" << pLVCD->iSubItem << "," << nItem << endl;
				crText = RGB(0, 0, 0);
				if (!CurrentColor.empty())
					crBkgnd = CurrentColor[nItem].CurColor;
				else
					crBkgnd = RGB(255, 255, 255);
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
			cout << pLVCD->iSubItem << endl;
			crText = RGB(0, 0, 0);
			crBkgnd = RGB(255, 255, 255);
			//*pResult = CDRF_DODEFAULT;
		}

		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crBkgnd;
	}
	else if ((CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage)
	{
		cout << "3--";
		int nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec);
		COLORREF crText, crBkgnd;
		if (pLVCD->iSubItem == 1)
		{
			if (nItem >= 0)
			{
				cout << "绘制绘制" << pLVCD->iSubItem << "," << nItem << endl;
				crText = RGB(0, 0, 0);
				if (!CurrentColor.empty())
				{
					cout << "!!!" << endl;
					//crBkgnd = CurrentColor[nItem].CurColor;
					if (nItem > CurrentColor.size() - 1)
					{
						crBkgnd = CurrentColor[CurrentColor.size() - 1].CurColor;
					}
					else
					{
						crBkgnd = CurrentColor[nItem].CurColor;
					}
				}
				else
					crBkgnd = RGB(255, 255, 255);
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
			cout << pLVCD->iSubItem << endl;
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
	cout << "OnNMCustomdrawSpeclineList 列表框重绘完毕"<<endl;
}


void SpectralViewDlg::OnNMClickSpeclineList(NMHDR *pNMHDR, LRESULT *pResult)
{
	//单击SpecList列表中的曲线，切换下方曲线属性的颜色
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	CString strSpecName;    // 选择语言的名称字符串   
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;

	int nPosition;

	if (-1 != pNMListView->iItem)        // 如果iItem不是-1，就说明有列表项被选择   
	{
		// 获取被选择列表项第一个子项的文本   
		strSpecName = m_specList.GetItemText(pNMListView->iItem, 0);
		
		//设置属性列表中曲线名称
		m_PropList.SetItemText(1, 1, strSpecName);

		for (vector<CurColorStruct>::iterator it = CurrentColor.begin(); it != CurrentColor.end(); it++)
		{
			//根据波谱文件名查找曲线颜色
			if ((*it).name == strSpecName)
			{
				nPosition = distance(CurrentColor.begin(), it);
			}
		}

		//设置曲线属性颜色
		COLORREF color;
		color = CurrentColor[nPosition].CurColor;
		SpectralViewDlg::m_CurveColor.SetColor(color);

		float Min, Max;
		//设置属性列表最大值最小值
		for (vector<ASDstruct>::iterator it = SpectralIO::ASDdata.begin(); it != SpectralIO::ASDdata.end(); it++)
		{
			//根据波谱文件名查找曲线最大最小值
			if ((*it).name == strSpecName)
			{
				nPosition = distance(SpectralIO::ASDdata.begin(), it);
				Min = (*it).MinRel;
				Max = (*it).MaxRel;
			}
		}

		//最大最小值赋值给曲线属性列
		CString tem;
		tem.Format("%.3f", Min);
		m_PropList.SetItemText(2, 1, tem);
		tem.Format("%.3f", Max);
		m_PropList.SetItemText(3, 1, tem);
	}




	*pResult = 0;
}

bool SpectralViewDlg::DrawSpectralPic(int PicID, int index, int penStyle, int penWidth, COLORREF color, int gap, double esp)
{
	double stepX, stepY;
	double max = 0;
	CRect rect;
	CDC* pDC;
	//设置画笔
	CPen pen(penStyle, penWidth, color);
	CPen* pOldPen = NULL;
	int iPenWidth;
	//获取绘图窗口的CDC资源
	this->GetDlgItem(PicID)->GetClientRect(rect);
	pDC = this->GetDlgItem(PicID)->GetDC();
	//设置绘图格式为反色绘图
	int nRopMode = pDC->SetROP2(R2_NOTXORPEN);
	//获取SpectralIO类的静态成员变量
	ASDstruct temp;
	temp = SpectralIO::ASDdata[index];
	//找反射率的最大值
	for (int i = 0; i < temp.data.size(); i++)
	{
		double tp = temp.data[i].yy;
		if (tp > max)
			max = tp;
	}
	//计算XY轴单位距离
	stepX = double(rect.Width() - 2) / (double)temp.data.size();
	stepY = double(rect.Height() - 2) / (max * (double)1.2);
	//记录画笔
	pOldPen = pDC->SelectObject(&pen);
	//逐点画折线图
	for (int i = 0, j; i < temp.data.size() - gap; i = j)
	{
		j = i + gap;
		while (abs(temp.data[j].yy - temp.data[i].yy) < esp)
		{
			j += gap;
		}
		pDC->MoveTo(int(i * stepX + 1), int(rect.Height() - temp.data[i].yy * stepY - 1));
		pDC->LineTo(int(j * stepX), int(rect.Height() - temp.data[j].yy * stepY));
	}
	//释放CDC资源
	ReleaseDC(pDC);
	return true;
}

bool SpectralViewDlg::DrawSpectralPic(int PicID, CString name, int penStyle, int penWidth, COLORREF color, int gap, double esp)
{
	double stepX, stepY;
	double max = 0;
	CRect rect;
	CDC* pDC;
	//设置画笔
	CPen pen(penStyle, penWidth, color);
	CPen* pOldPen = NULL;
	int iPenWidth;
	//获取绘图窗口的CDC资源
	this->GetDlgItem(PicID)->GetClientRect(rect);
	pDC = this->GetDlgItem(PicID)->GetDC();
	//设置绘图格式为反色绘图
	int nRopMode = pDC->SetROP2(R2_NOTXORPEN);
	//获取SpectralIO类的静态成员变量
	int index = -1;
	ASDstruct temp;
	for (int i = 0; i < SpectralIO::ASDdata.size(); i++)
	{
		if (SpectralIO::ASDdata[i].name == name)
		{
			index = i;
			break;
		}
	}
	if (index < 0)
	{
		return false;
	}
	temp = SpectralIO::ASDdata[index];
	//找反射率的最大值
	for (int i = 0; i < temp.data.size(); i++)
	{
		double tp = temp.data[i].yy;
		if (tp > max)
			max = tp;
	}
	//计算XY轴单位距离
	stepX = double(rect.Width() - 2) / (double)temp.data.size();
	stepY = double(rect.Height() - 2) / (max * (double)1.2);
	//记录画笔
	pOldPen = pDC->SelectObject(&pen);
	//逐点画折线图
	for (int i = 0, j; i < temp.data.size() - gap; i = j)
	{
		j = i + gap;
		while (abs(temp.data[j].yy - temp.data[i].yy) < esp)
		{
			j += gap;
		}
		pDC->MoveTo(int(i * stepX + 1), int(rect.Height() - temp.data[i].yy * stepY - 1));
		pDC->LineTo(int(j * stepX), int(rect.Height() - temp.data[j].yy * stepY));
	}
	//释放CDC资源
	ReleaseDC(pDC);
	return true;
}

//void SpectralViewDlg::OnBnKillfocusCurveMfccolorbutton()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	MessageBox("颜色改变！！！");
//}


//void SpectralViewDlg::OnBnHotItemChangeCurveMfccolorbutton(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// 此功能要求 Internet Explorer 6 或更高版本。
//	// 符号 _WIN32_IE 必须是 >= 0x0600。
//	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//
//	MessageBox("ItemChange!!!");
//
//	*pResult = 0;
//}


void SpectralViewDlg::OnBnClickedCurveMfccolorbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox("dianji!!!");
}

bool SpectralViewDlg::ReadSpectralPoint(int PicID, CPoint point, double & waveLength, double & reflectivity, double ileft, double iright, double itop, double ibottom)
{
	CRect rect;
	CDC* pDC;
	//获取绘图窗口的CDC资源
	this->GetDlgItem(PicID)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	//判断点是否在绘图窗口中
	if (point.x > rect.left && point.x < rect.right && point.y < rect.bottom && point.y > rect.top)
	{
		waveLength = ileft + 1.0 * (point.x - rect.left) / rect.Width() * (iright - ileft);
		reflectivity = ibottom + 1.0 * (rect.bottom - point.y) / rect.Height() * (itop - ibottom);
	}
	else
	{
		waveLength = -128;
		reflectivity = -128;
		return false;
	}
	return true;
}

void SpectralViewDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	double wl = 0, ref = 0;
	ReadSpectralPoint(IDC_STATIC, point, wl, ref, 350.0, 2500.0, 1.0, 0.0);
	//cout << "wl:" << wl << "|||ref:" << ref << endl;
	CString wal, refl;
	if (wl >= 0 && ref >= 0)
	{
		wal.Format(_T("%.3lf"), wl);
		refl.Format(_T("%.3lf"), ref);
	}
	else
	{
		wal.Format(_T("Nan"));
		refl.Format(_T("Nan"));
	}
	//SetDlgItemText(IDC_WaveLength, wal);
	//SetDlgItemText(IDC_reflectivity, refl);
	m_SpectralStatusbar.SetPaneText(2, wal);
	m_SpectralStatusbar.SetPaneText(4, refl);
	CDialog::OnMouseMove(nFlags, point);
}


void SpectralViewDlg::OnLvnDeleteallitemsSpeclineList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	//似乎不会相应此删除
	//MessageBox("Delete!!!");

	*pResult = 0;
}


void SpectralViewDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
		case 2:   //定时器2位为状态栏时间信息
		{
			CTime t1;
			t1 = CTime::GetCurrentTime();//获取当前系统时间
			m_SpectralStatusbar.SetPaneText(6, t1.Format("%Y-%m-%d  %H:%M:%S")); //状态栏显示时间   
			break;
		}
	}
	CDialog::OnTimer(nIDEvent);
}
