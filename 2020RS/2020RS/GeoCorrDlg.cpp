// GeoCorrDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "2020RS.h"
#include "GeoCorrDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include "GeoCorrImg.h"
#include"ControlPT.h"
#include<fstream>


using namespace std;
extern GeoCorrImg dlg11;
extern GeoCorrImg dlg12;
extern GeoCorrImg dlg13;
//
extern GeoCorrImg dlg21;
extern GeoCorrImg dlg22;
extern GeoCorrImg dlg23;

//静态成员变量初始化
Img_kele GeoCorrDlg::BaseImg;
Img_kele GeoCorrDlg::WrapImg;
//GeoCorrImg GeoCorrDlg::dlg11;
//GeoCorrImg GeoCorrDlg::dlg12;
//GeoCorrImg GeoCorrDlg::dlg13;
//GeoCorrImg GeoCorrDlg::dlg21;
//GeoCorrImg GeoCorrDlg::dlg22;
//GeoCorrImg GeoCorrDlg::dlg23;

// GeoCorrDlg 对话框
IMPLEMENT_DYNAMIC(GeoCorrDlg, CDialog)

GeoCorrDlg::GeoCorrDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_GeoCorr_DIALOG, pParent)
{

}

GeoCorrDlg::~GeoCorrDlg()
{
}

void GeoCorrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BaseInfo_LIST, m_BaseInfoList);
	DDX_Control(pDX, IDC_WarpInfo_LIST, m_WrapInfoList);
	DDX_Control(pDX, IDC_LIST3, m_GCPsList);
	DDX_Control(pDX, IDC_COMBO1, m_DegreeCombo);
}


BEGIN_MESSAGE_MAP(GeoCorrDlg, CDialog)
	ON_EN_CHANGE(IDC_Base_MFCEDITBROWSE, &GeoCorrDlg::OnEnChangeBaseMfceditbrowse)
	ON_EN_CHANGE(IDC_Wrap_MFCEDITBROWSE, &GeoCorrDlg::OnEnChangeWrapMfceditbrowse)
	ON_BN_CLICKED(IDC_GeoBegin_BUTTON, &GeoCorrDlg::OnBnClickedGeobeginButton)
	ON_BN_CLICKED(IDC_AddPoint_BUTTON, &GeoCorrDlg::OnBnClickedAddpointButton)
	ON_BN_CLICKED(IDC_DelPoint_BUTTON, &GeoCorrDlg::OnBnClickedDelpointButton)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, &GeoCorrDlg::OnNMClickList3)
	ON_BN_CLICKED(IDC_WrapedOut_BUTTON, &GeoCorrDlg::OnBnClickedWrapedoutButton)
	ON_BN_CLICKED(IDC_DelPoint_BUTTON2, &GeoCorrDlg::OnBnClickedDelpointButton2)
	ON_BN_CLICKED(IDC_DelPoint_BUTTON3, &GeoCorrDlg::OnBnClickedDelpointButton3)
	ON_CBN_SELCHANGE(IDC_COMBO1, &GeoCorrDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_DelPoint_BUTTON4, &GeoCorrDlg::OnBnClickedDelpointButton4)
END_MESSAGE_MAP()


// GeoCorrDlg 消息处理程序

BOOL GeoCorrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	lock(true);

	CRect rect; CRect vrect; CRect lrect;
	// 获取编程语言列表视图控件的位置和大小   
	m_BaseInfoList.GetClientRect(&rect);
	m_WrapInfoList.GetClientRect(&vrect);
	
	// 为列表视图控件添加全行选中和栅格风格   
	m_BaseInfoList.SetExtendedStyle(m_BaseInfoList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_WrapInfoList.SetExtendedStyle(m_WrapInfoList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	// 为基准影像信息列表视图控件添加三列   
	m_BaseInfoList.InsertColumn(0, _T("项目"), LVCFMT_CENTER, rect.Width() / 3.2, 0);
	m_BaseInfoList.InsertColumn(1, _T("值"), LVCFMT_CENTER, rect.Width() / 1.45, 1);
	m_BaseInfoList.InsertItem(0, _T("文件类型"));
	m_BaseInfoList.InsertItem(1, _T("行列数"));
	/*m_BaseInfoList.InsertItem(1, _T("波段数"));
	m_BaseInfoList.InsertItem(2, _T("像元大小"));*/
	m_BaseInfoList.InsertItem(2, _T("比特数"));
	/*m_BaseInfoList.InsertItem(4, _T("空间参考"));
	m_BaseInfoList.InsertItem(5, _T("横坐标配准系数"));
	m_BaseInfoList.InsertItem(6, _T("纵坐标配准系数"));*/

	// 为待校正影像信息列表视图控件添加三列   
	m_WrapInfoList.InsertColumn(0, _T("项目"), LVCFMT_CENTER, rect.Width() / 3.2, 0);
	m_WrapInfoList.InsertColumn(1, _T("值"), LVCFMT_CENTER, rect.Width() / 1.45, 1);
	m_WrapInfoList.InsertItem(0, _T("文件类型"));
	m_WrapInfoList.InsertItem(1, _T("行列数"));
	/*m_BaseInfoList.InsertItem(1, _T("波段数"));
	m_BaseInfoList.InsertItem(2, _T("像元大小"));*/
	m_WrapInfoList.InsertItem(2, _T("比特数"));
	/*m_BaseInfoList.InsertItem(4, _T("空间参考"));
	m_BaseInfoList.InsertItem(5, _T("横坐标配准系数"));
	m_BaseInfoList.InsertItem(6, _T("纵坐标配准系数"));*/

	//暂时先固定地址，方便测试
	SetDlgItemText(IDC_Base_MFCEDITBROWSE, "C:\\Users\\荔枝男孩\\Desktop\\第3次多光谱相机\\89号样本\\TC200089.BMP");
	SetDlgItemText(IDC_Wrap_MFCEDITBROWSE, "C:\\Users\\荔枝男孩\\Desktop\\第3次多光谱相机\\89号样本\\TC100089.BMP");

	::SetWindowPos(this->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE);

	/*dlg11.iNum = 1; dlg11.iFlag = 1;
	dlg11.Create(IDD_GeoCorrImg_DIALOG);
	dlg12.iNum = 1; dlg12.iFlag = 2;
	dlg12.Create(IDD_GeoCorrImg_DIALOG);
	dlg13.iNum = 1; dlg13.iFlag = 3;
	dlg13.Create(IDD_GeoCorrImg_DIALOG);
	dlg21.iNum = 2; dlg21.iFlag = 1;
	dlg21.Create(IDD_GeoCorrImg_DIALOG);
	dlg22.iNum = 2; dlg22.iFlag = 2;
	dlg22.Create(IDD_GeoCorrImg_DIALOG);
	dlg23.iNum = 2; dlg23.iFlag = 3;
	dlg23.Create(IDD_GeoCorrImg_DIALOG);*/

	//初始化listcontrol
	m_GCPsList.GetClientRect(&rect);
	//
	m_GCPsList.SetExtendedStyle(m_GCPsList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_GCPsList.InsertColumn(0, "序号", LVCFMT_LEFT, 50, 0);
	m_GCPsList.InsertColumn(1, "Base X", LVCFMT_LEFT, rect.Width() / 5, 1);
	m_GCPsList.InsertColumn(2, "Base Y", LVCFMT_LEFT, rect.Width() /5, 2);
	m_GCPsList.InsertColumn(3, "Wrap X", LVCFMT_LEFT, rect.Width() /5, 3);
	m_GCPsList.InsertColumn(4, "Wrap Y", LVCFMT_LEFT, rect.Width() /5, 4);
	m_GCPsList.InsertColumn(5, "Predict X", LVCFMT_LEFT, rect.Width() / 5, 5);
	m_GCPsList.InsertColumn(6, "Predict Y", LVCFMT_LEFT, rect.Width() /5, 6);
	m_GCPsList.InsertColumn(7, "Error X", LVCFMT_LEFT, rect.Width() /5, 7);
	m_GCPsList.InsertColumn(8, "Error Y", LVCFMT_LEFT, rect.Width() /5, 8);
	m_GCPsList.InsertColumn(9, "RMS", LVCFMT_LEFT, rect.Width() /5, 9);
	
	//combo bo初始化，默认选择degree为1
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("1");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("2");
	//默认显示degree = 1;
	m_DegreeCombo.SetCurSel(0);

	//初始化redio button，默认采用最近零点法重采样。
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);

	UpdateData();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void GeoCorrDlg::OnEnChangeBaseMfceditbrowse()
{
	//基准影像文件路径的获取

	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	CString BaseImgPath;
	GetDlgItemText(IDC_Base_MFCEDITBROWSE, BaseImgPath);
	cout << BaseImgPath << endl;

	BOOL flag=BaseImg.ReadBmpInfo(BaseImgPath);
	if (flag == FALSE)
		MessageBox("获取BMP文件信息失败！");
	else
	{
		cout << "类外地址：" << &BaseImg.ImgParaInCls << endl;

		cout << "W=" << BaseImg.ImgParaInCls.ImgW << ",H=" << BaseImg.ImgParaInCls.ImgH << endl;

		m_BaseInfoList.SetItemText(0, 1, _T("BMP"));
		CString str;
		str.Format(_T("%d,%d"), BaseImg.ImgParaInCls.ImgW, BaseImg.ImgParaInCls.ImgH);
		m_BaseInfoList.SetItemText(1, 1, _T(str));
		str.Format(_T("%d"), BaseImg.ImgParaInCls.BmpInfoHeader.biBitCount);
		m_BaseInfoList.SetItemText(2, 1, _T(str));
	}

	
	//str.Format(_T("%d"), rdata.iBandNum);
	//m_RasterInfo.SetItemText(1, 1, _T(str));
	//str.Format(_T("(%f,%f)"), fabs(rdata.arrTransf[1]), fabs(rdata.arrTransf[5]));
}





void GeoCorrDlg::OnEnChangeWrapMfceditbrowse()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString WrapImgPath;
	GetDlgItemText(IDC_Wrap_MFCEDITBROWSE, WrapImgPath);
	cout << WrapImgPath << endl;


	BOOL flag = WrapImg.ReadBmpInfo(WrapImgPath);
	if (flag == FALSE)
		MessageBox("获取BMP文件信息失败！");
	else
	{
		cout << "类外地址：" << &WrapImg.ImgParaInCls << endl;

		cout << "W=" << WrapImg.ImgParaInCls.ImgW << ",H=" << WrapImg.ImgParaInCls.ImgH << endl;

		m_WrapInfoList.SetItemText(0, 1, _T("BMP"));
		CString str;
		str.Format(_T("%d,%d"), WrapImg.ImgParaInCls.ImgW, WrapImg.ImgParaInCls.ImgH);
		m_WrapInfoList.SetItemText(1, 1, _T(str));
		str.Format(_T("%d"), WrapImg.ImgParaInCls.BmpInfoHeader.biBitCount);
		m_WrapInfoList.SetItemText(2, 1, _T(str));
		//cout << WrapImg.ImgParaInCls.BmpInfoHeader.biBitCount << endl;
	}
}


void GeoCorrDlg::OnBnClickedGeobeginButton()
{
	// TODO: 在此添加控件通知处理程序代码
	lock(false);
	BOOL flag = FALSE;
	CString BaseImgPath;
	GetDlgItemText(IDC_Base_MFCEDITBROWSE, BaseImgPath);
	flag=BaseImg.CreateBandSpace();
	if (flag == FALSE)
	{
		MessageBox("基准影像数据空间开辟失败！");
		return;
	}
	flag = FALSE;

	flag=BaseImg.ReadBmpData(BaseImgPath);
	if (flag == FALSE)
	{
		MessageBox("基准影像数据读入失败！");
		return;
	}
	else
	{
		//MessageBox("基准影像数据读入成功！");
		cout << "基准影像数据读入成功!" << endl;
	}
	flag = FALSE;


	CString WrapImgPath;
	GetDlgItemText(IDC_Wrap_MFCEDITBROWSE, WrapImgPath);
	WrapImg.CreateBandSpace();
	flag=WrapImg.ReadBmpData(WrapImgPath);
	if (flag == FALSE)
	{
		MessageBox("待校正影像数据读入失败！");
		return;
	}
	else
	{
		//MessageBox("待校正影像数据读入成功！");
		cout << "待校正影像数据读入成功!" << endl;
	}
		

	////以下为显示图像部分，目前hdc是主窗口的，故在主窗口中显示影像，根据需要获取待显示窗口的HDC，传入函数
	////获取主窗口句柄
	//HWND hWnd;
	//hWnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	//HDC hdc;
	//hdc = ::GetDC(hWnd);
	//CRect rect;
	//::GetClientRect(hWnd, &rect);

	////影像以原始大小在主窗口输出
	////BaseImg.DisplayImgColor(&hdc, BaseImg.ImgParaInCls.ImgW, BaseImg.ImgParaInCls.ImgH, 0, 0, BaseImg.ImgParaInCls.ImgW, BaseImg.ImgParaInCls.ImgH, 0, 0);
	//
	////影像可以根据主窗口大小调整显示图像的大小
	////目前请不要修改偏移量，即int Disoffx, int Disoffy,int srcoffx,int srcoffy四个参数，全部使用0
	//BaseImg.DisplayImgColor(&hdc, rect.Width(), rect.Height(), 0, 0, BaseImg.ImgParaInCls.ImgW, BaseImg.ImgParaInCls.ImgH, 0, 0);


	//初始化选择控制点界面

	dlg12.oldPoint.x = -1;
	dlg12.oldPoint.y = -1;
	dlg22.oldPoint.x = -1;
	dlg22.oldPoint.y = -1;
	//显示选择界面,1为基准，2为校正
	
	dlg11.ShowWindow(SW_SHOW);
	dlg12.ShowWindow(SW_SHOW);
	dlg13.ShowWindow(SW_SHOW);
	dlg21.ShowWindow(SW_SHOW);
	dlg22.ShowWindow(SW_SHOW);
	dlg23.ShowWindow(SW_SHOW);

	HWND hWnd;
	HDC hdc;
	CRect rect;

	//初始化放大系数
	double fac1 = 4; //原影像缩小4倍到dlg2	
	double fac2 = 0.25;//dlg2放大4倍到dlg1
	double fac3 = 0.25;//dlg1放大4倍到dlg3

	//读入影像的宽高
	int ww = BaseImg.ImgParaInCls.ImgW;
	int hh = BaseImg.ImgParaInCls.ImgH;

	//初始化六个选择界面，选择偏移量
	int offx1 = 0; int offy1 = 0;//假设X-2窗口中的选择框最左上角坐标为(0,0)
	int offx2 = 0; int offy2 = 0;//假设X-1窗口中的选择框最左上角坐标为(0,0)

	//基准影像
	//dialog12
	hWnd = ::FindWindow(NULL, "dialog12");
	hdc = ::GetDC(hWnd);
	::GetClientRect(hWnd, &rect);
	BaseImg.DisplayImgColor(&hdc, ww/fac1,hh/fac1, 0, 0, BaseImg.ImgParaInCls.ImgW, BaseImg.ImgParaInCls.ImgH, 0, 0);
	

	
	//dialog11
	hWnd = ::FindWindow(NULL, "dialog11");
	hdc = ::GetDC(hWnd);
	::GetClientRect(hWnd, &rect);
	BaseImg.DisplaySquareImgColor(&hdc, 100 / fac2, 100 / fac2, offx1, offy1,fac1,fac2);


	//dialog13
	hWnd = ::FindWindow(NULL, "dialog13");
	hdc = ::GetDC(hWnd);
	::GetClientRect(hWnd, &rect);
	BaseImg.DisplaySquareImgColor(&hdc, 100 / fac3, 100 / fac3,offx1,offy1,offx2,offy2,fac1,fac2,fac3);


	//校正影像
	//dialog22
	hWnd = ::FindWindow(NULL, "dialog22");
	hdc = ::GetDC(hWnd);
	::GetClientRect(hWnd, &rect);
	WrapImg.DisplayImgColor(&hdc, ww / fac1, hh / fac1, 0, 0, WrapImg.ImgParaInCls.ImgW, WrapImg.ImgParaInCls.ImgH, 0, 0);
	
	//dialog21
	hWnd = ::FindWindow(NULL, "dialog21");
	hdc = ::GetDC(hWnd);
	::GetClientRect(hWnd, &rect);
	WrapImg.DisplaySquareImgColor(&hdc, 100 / fac2, 100 / fac2, offx1, offy1, fac1, fac2);

	//dialog23
	hWnd = ::FindWindow(NULL, "dialog23");
	hdc = ::GetDC(hWnd);
	::GetClientRect(hWnd, &rect);
	BaseImg.DisplaySquareImgColor(&hdc, 100 / fac3, 100 / fac3, offx1, offy1, offx2, offy2, fac1, fac2, fac3);
	
}

void GeoCorrDlg::GoToGcp(int Gcp_Num, double x1, double y1,double x2,double y2, double fac1,double fac2,double fac3)
{
	//BaseImg Goto
	HWND hWnd;
	CWnd *cWnd;
	HDC hdc;
	CRect rect;
	hWnd = ::FindWindow(NULL, "dialog12"); 
	hdc = ::GetDC(hWnd);
	::GetClientRect(hWnd, &rect);
	cWnd = FromHandle(hWnd);

	CPoint point;
	point.x = floor(x1 / fac1 + 0.5);
	point.y = floor(y1 / fac1 + 0.5) ;
	CPoint oldPoint = dlg12.oldPoint;

	CDC* pDC;
	CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
	pDC = cWnd->GetDC();
	cWnd->GetClientRect(rect);
	//设置绘图格式为反色绘图
	int nRopMode = pDC->SetROP2(R2_NOTXORPEN);
	//擦除上次绘制
	if (oldPoint.x >= 0 && oldPoint.y >= 0)
	{
		pDC->MoveTo(oldPoint.x - 50, oldPoint.y + 50);
		pDC->LineTo(oldPoint.x + 50, oldPoint.y + 50);
		pDC->MoveTo(oldPoint.x + 50, oldPoint.y + 50);
		pDC->LineTo(oldPoint.x + 50, oldPoint.y - 50);
		pDC->MoveTo(oldPoint.x + 50, oldPoint.y - 50);
		pDC->LineTo(oldPoint.x - 50, oldPoint.y - 50);
		pDC->MoveTo(oldPoint.x - 50, oldPoint.y - 50);
		pDC->LineTo(oldPoint.x - 50, oldPoint.y + 50);
	}
	//防止方框超出边界
	if (point.x < 50)
		point.x = 50;
	if (point.x + 50 > rect.right)
		point.x = rect.right - 50;
	if (point.y < 50)
		point.y = 50;
	if (point.y + 50 > rect.bottom)
		point.y = rect.bottom - 50;
	//绘制新的选择框
	pDC->MoveTo(point.x - 50, point.y + 50);
	pDC->LineTo(point.x + 50, point.y + 50);
	pDC->MoveTo(point.x + 50, point.y + 50);
	pDC->LineTo(point.x + 50, point.y - 50);
	pDC->MoveTo(point.x + 50, point.y - 50);
	pDC->LineTo(point.x - 50, point.y - 50);
	pDC->MoveTo(point.x - 50, point.y - 50);
	pDC->LineTo(point.x - 50, point.y + 50);
	dlg12.oldPoint = point;

	//在11窗口重新显示影像
	hWnd = ::FindWindow(NULL, "dialog11");
	hdc = ::GetDC(hWnd);
	::GetClientRect(hWnd, &rect);
	cWnd = FromHandle(hWnd);
	GeoCorrDlg::BaseImg.DisplaySquareImgColor(&hdc, 100 / fac2, 100 / fac2, floor(x1 / fac1 + 0.5)-50, floor(y1 / fac1 + 0.5)-50, fac1, fac2);

	//消除上一次的方框
	dlg11.oldPoint.x = -1;
	dlg11.oldPoint.y = -1;

	//在11窗口显示选择框
	//设置绘图格式为反色绘图
	pDC = cWnd->GetDC();
	nRopMode = pDC->SetROP2(R2_NOTXORPEN);
	//擦除上次绘制
	oldPoint = dlg11.oldPoint;
	point.x = 200;
	point.y = 200;
	if (oldPoint.x >= 0 && oldPoint.y >= 0)
	{
		pDC->MoveTo(oldPoint.x - 50, oldPoint.y + 50);
		pDC->LineTo(oldPoint.x + 50, oldPoint.y + 50);
		pDC->MoveTo(oldPoint.x + 50, oldPoint.y + 50);
		pDC->LineTo(oldPoint.x + 50, oldPoint.y - 50);
		pDC->MoveTo(oldPoint.x + 50, oldPoint.y - 50);
		pDC->LineTo(oldPoint.x - 50, oldPoint.y - 50);
		pDC->MoveTo(oldPoint.x - 50, oldPoint.y - 50);
		pDC->LineTo(oldPoint.x - 50, oldPoint.y + 50);
	}
	pDC->MoveTo(point.x - 50, point.y + 50);
	pDC->LineTo(point.x + 50, point.y + 50);
	pDC->MoveTo(point.x + 50, point.y + 50);
	pDC->LineTo(point.x + 50, point.y - 50);
	pDC->MoveTo(point.x + 50, point.y - 50);
	pDC->LineTo(point.x - 50, point.y - 50);
	pDC->MoveTo(point.x - 50, point.y - 50);
	pDC->LineTo(point.x - 50, point.y + 50);
	//
	dlg11.oldPoint = point;
	//在dlg3显示新的区域
	hWnd = ::FindWindow(NULL, "dialog13");
	hdc = ::GetDC(hWnd);
	::GetClientRect(hWnd, &rect);
	cWnd = FromHandle(hWnd);
	GeoCorrDlg::BaseImg.DisplaySquareImgColor(&hdc, 100 / fac3, 100 / fac3, floor(x1 / fac1 + 0.5) - 50, floor(y1 / fac1 + 0.5) - 50, 150, 150, fac1, fac2, fac3);

	//消除上一次的十字线
	dlg13.oldPoint.x = -1;
	dlg13.oldPoint.y = -1;


	//画十字线
	pDC = cWnd->GetDC();
	cWnd->GetClientRect(rect);
	//设置绘图格式为反色绘图
	nRopMode = pDC->SetROP2(R2_NOTXORPEN);
	//擦除上次绘制
	oldPoint = dlg13.oldPoint;
	if (oldPoint.x >= 0 && oldPoint.y >= 0)
	{
		pDC->MoveTo(0, oldPoint.y);
		pDC->LineTo(rect.right, oldPoint.y);
		pDC->MoveTo(oldPoint.x, 0);
		pDC->LineTo(oldPoint.x, rect.bottom);
	}
	//
	pDC->MoveTo(0, point.y);
	pDC->LineTo(rect.right, point.y);
	pDC->MoveTo(point.x, 0);
	pDC->LineTo(point.x, rect.bottom);
	//
	dlg13.oldPoint = point;
		



	//WrapImage

	hWnd = ::FindWindow(NULL, "dialog22");
	hdc = ::GetDC(hWnd);
	::GetClientRect(hWnd, &rect);
	cWnd = FromHandle(hWnd);

	
	point.x = floor(x2 / fac1 + 0.5);
	point.y = floor(y2 / fac1 + 0.5);
	oldPoint = dlg22.oldPoint;

	pDC = cWnd->GetDC();
	cWnd->GetClientRect(rect);
	//设置绘图格式为反色绘图
	nRopMode = pDC->SetROP2(R2_NOTXORPEN);
	//擦除上次绘制
	if (oldPoint.x >= 0 && oldPoint.y >= 0)
	{
		pDC->MoveTo(oldPoint.x - 50, oldPoint.y + 50);
		pDC->LineTo(oldPoint.x + 50, oldPoint.y + 50);
		pDC->MoveTo(oldPoint.x + 50, oldPoint.y + 50);
		pDC->LineTo(oldPoint.x + 50, oldPoint.y - 50);
		pDC->MoveTo(oldPoint.x + 50, oldPoint.y - 50);
		pDC->LineTo(oldPoint.x - 50, oldPoint.y - 50);
		pDC->MoveTo(oldPoint.x - 50, oldPoint.y - 50);
		pDC->LineTo(oldPoint.x - 50, oldPoint.y + 50);
	}
	//防止方框超出边界
	if (point.x < 50)
		point.x = 50;
	if (point.x + 50 > rect.right)
		point.x = rect.right - 50;
	if (point.y < 50)
		point.y = 50;
	if (point.y + 50 > rect.bottom)
		point.y = rect.bottom - 50;
	//绘制新的选择框
	pDC->MoveTo(point.x - 50, point.y + 50);
	pDC->LineTo(point.x + 50, point.y + 50);
	pDC->MoveTo(point.x + 50, point.y + 50);
	pDC->LineTo(point.x + 50, point.y - 50);
	pDC->MoveTo(point.x + 50, point.y - 50);
	pDC->LineTo(point.x - 50, point.y - 50);
	pDC->MoveTo(point.x - 50, point.y - 50);
	pDC->LineTo(point.x - 50, point.y + 50);
	dlg22.oldPoint = point;

	//在21窗口重新显示影像
	hWnd = ::FindWindow(NULL, "dialog21");
	hdc = ::GetDC(hWnd);
	::GetClientRect(hWnd, &rect);
	cWnd = FromHandle(hWnd);
	GeoCorrDlg::WrapImg.DisplaySquareImgColor(&hdc, 100 / fac2, 100 / fac2, floor(x2 / fac1 + 0.5) - 50, floor(y2 / fac1 + 0.5) - 50, fac1, fac2);

	//消除上一次的方框
	dlg21.oldPoint.x = -1;
	dlg21.oldPoint.y = -1;

	//在21窗口显示选择框
	//设置绘图格式为反色绘图
	pDC = cWnd->GetDC();
	nRopMode = pDC->SetROP2(R2_NOTXORPEN);
	//擦除上次绘制
	oldPoint = dlg21.oldPoint;
	point.x = 200;
	point.y = 200;
	if (oldPoint.x >= 0 && oldPoint.y >= 0)
	{
		pDC->MoveTo(oldPoint.x - 50, oldPoint.y + 50);
		pDC->LineTo(oldPoint.x + 50, oldPoint.y + 50);
		pDC->MoveTo(oldPoint.x + 50, oldPoint.y + 50);
		pDC->LineTo(oldPoint.x + 50, oldPoint.y - 50);
		pDC->MoveTo(oldPoint.x + 50, oldPoint.y - 50);
		pDC->LineTo(oldPoint.x - 50, oldPoint.y - 50);
		pDC->MoveTo(oldPoint.x - 50, oldPoint.y - 50);
		pDC->LineTo(oldPoint.x - 50, oldPoint.y + 50);
	}
	pDC->MoveTo(point.x - 50, point.y + 50);
	pDC->LineTo(point.x + 50, point.y + 50);
	pDC->MoveTo(point.x + 50, point.y + 50);
	pDC->LineTo(point.x + 50, point.y - 50);
	pDC->MoveTo(point.x + 50, point.y - 50);
	pDC->LineTo(point.x - 50, point.y - 50);
	pDC->MoveTo(point.x - 50, point.y - 50);
	pDC->LineTo(point.x - 50, point.y + 50);
	//
	dlg21.oldPoint = point;
	//在dlg3显示新的区域
	hWnd = ::FindWindow(NULL, "dialog23");
	hdc = ::GetDC(hWnd);
	::GetClientRect(hWnd, &rect);
	cWnd = FromHandle(hWnd);
	GeoCorrDlg::WrapImg.DisplaySquareImgColor(&hdc, 100 / fac3, 100 / fac3, floor(x2 / fac1 + 0.5) - 50, floor(y2 / fac1 + 0.5) - 50, 150, 150, fac1, fac2, fac3);

	//消除上一次的十字线
	dlg23.oldPoint.x = -1;
	dlg23.oldPoint.y = -1;


	//画十字线
	pDC = cWnd->GetDC();
	cWnd->GetClientRect(rect);
	//设置绘图格式为反色绘图
	nRopMode = pDC->SetROP2(R2_NOTXORPEN);
	//擦除上次绘制
	oldPoint = dlg23.oldPoint;
	if (oldPoint.x >= 0 && oldPoint.y >= 0)
	{
		pDC->MoveTo(0, oldPoint.y);
		pDC->LineTo(rect.right, oldPoint.y);
		pDC->MoveTo(oldPoint.x, 0);
		pDC->LineTo(oldPoint.x, rect.bottom);
	}
	//
	pDC->MoveTo(0, point.y);
	pDC->LineTo(rect.right, point.y);
	pDC->MoveTo(point.x, 0);
	pDC->LineTo(point.x, rect.bottom);
	//
	dlg23.oldPoint = point;
}

	/*By_WYY*/
//添加控制点
void GeoCorrDlg::OnBnClickedAddpointButton()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取编辑框的内容
	CString str_BaseX;
	CString str_BaseY;
	CString str_WrapX;
	CString str_WrapY;
	
	GetDlgItem(IDC_BaseX_EDIT)->GetWindowText(str_BaseX);
	GetDlgItem(IDC_BaseY_EDIT)->GetWindowText(str_BaseY);
	GetDlgItem(IDC_WrapX_EDIT)->GetWindowText(str_WrapX);
	GetDlgItem(IDC_WrapY_EDIT)->GetWindowText(str_WrapY);

	if (str_BaseX == ""||str_BaseY == ""||str_WrapX == ""||str_WrapY=="")
	{
		MessageBox("请在图中选择一对控制点");
	}
	else
	{
		double BaseX = atof(str_BaseX);
		double BaseY = atof(str_BaseY);
		double WrapX = atof(str_WrapX);
		double WrapY = atof(str_WrapY);


		//更新list信息
		int now_items = m_GCPsList.GetItemCount() + 1;
		CString str_now_items;
		str_now_items.Format(_T("%d"), now_items);
		m_GCPsList.InsertItem(now_items, str_now_items); //插入第几行数据
		m_GCPsList.SetItemText(now_items - 1, 1, str_BaseX);
		m_GCPsList.SetItemText(now_items - 1, 2, str_BaseY);
		m_GCPsList.SetItemText(now_items - 1, 3, str_WrapX);
		m_GCPsList.SetItemText(now_items - 1, 4, str_WrapY);

		//insert 进Gcps数据结构
		GcpStruct newdate;
		newdate.baseX = BaseX;
		newdate.baseY = BaseY;
		newdate.wrapX = WrapX;
		newdate.wrapY = WrapY;
		GcpDate.push_back(newdate);

		///多项式拟合次数
		CString str_degree;
		GetDlgItem(IDC_COMBO1)->GetWindowText(str_degree);
		int degree = atoi(str_degree);
		ControlPT ControlPtCls;

		cout << "degree:" << degree << endl;
		if (GcpDate.size() >= 3)
		{
			if (degree == 1)
			{
				matrix Coefficient(3, 2); matrix Res(GcpDate.size(), 5);
				cout << endl << GcpDate.size() << endl;
				//一次多项式拟合系数矩阵(3,2)第一列为x的3个系数，第二列为y的3个系数
				Coefficient = ControlPtCls.GeoCorrection(GcpDate, degree);
				//返回矩阵大小为（num,5），前两列为预测的x，y,后两列为预测x,y的误差，最后一列为RMS
				Res = ControlPtCls.CalError(GcpDate, Coefficient, degree);

				//计算总体误差
				CString totalrms;
				double TotalRMS = ControlPtCls.CalTotalError(Res, GcpDate.size());
				totalrms.Format("%.1lf", TotalRMS);
				GetDlgItem(IDC_RmsError_Edit)->SetWindowText(totalrms);
				//误差输出
				//Res.MatrixPrint();

				//更新list的predict x,y,error x,error y
				for (int ii = 0; ii < now_items; ii++)
				{
					for (int jj = 0; jj < 5; jj++)
					{
						CString str;

						str.Format("%.1lf", Res.mat[ii][jj]);
						m_GCPsList.SetItemText(ii, jj + 5, str);
					}
				}

			}
			else if (degree == 2 && GcpDate.size() >= 6)
			{
				matrix Coefficient(6, 2); matrix Res(GcpDate.size(), 5);
				//一次多项式拟合系数矩阵(6,2)第一列为x的6个系数，第二列为y的6个系数
				Coefficient = ControlPtCls.GeoCorrection(GcpDate, degree);
				//返回矩阵大小为（num,5），前两列为预测的x，y,后两列为预测x,y的误差，最后一列为RMS
				Res = ControlPtCls.CalError(GcpDate, Coefficient, degree);
				//计算总体误差
				CString totalrms;
				double TotalRMS = ControlPtCls.CalTotalError(Res, GcpDate.size());
				totalrms.Format("%.1lf", TotalRMS);
				GetDlgItem(IDC_RmsError_Edit)->SetWindowText(totalrms);

				//更新list的predict x,y,error x,error y
				for (int ii = 0; ii < now_items; ii++)
				{
					for (int jj = 0; jj < 5; jj++)
					{
						CString str;

						str.Format("%.1lf", Res.mat[ii][jj]);
						m_GCPsList.SetItemText(ii, jj + 5, str);
					}
				}
			}
		}
	}
}

//删除控制点
void GeoCorrDlg::OnBnClickedDelpointButton()
{
	
	if (now_click_GCP == -1)
	{
		MessageBox("请选择一条控制点数据进行删除");
	}
	else
	{
		m_GCPsList.DeleteItem(now_click_GCP);
		//从Gcpdate删除
		auto erasenum = GcpDate.begin() + now_click_GCP;
		GcpDate.erase(erasenum);

		//编辑框清空
		GetDlgItem(IDC_BaseX_EDIT)->SetWindowText("");
		GetDlgItem(IDC_BaseY_EDIT)->SetWindowText("");
		GetDlgItem(IDC_WrapX_EDIT)->SetWindowText("");
		GetDlgItem(IDC_WrapY_EDIT)->SetWindowText("");

		///多项式拟合次数
		CString str_degree;
		GetDlgItem(IDC_COMBO1)->GetWindowText(str_degree);
		int degree = atoi(str_degree);
		ControlPT ControlPtCls;

		//更新list
		for (int ii = 0; ii < m_GCPsList.GetItemCount(); ii++)
		{
			CString str;
			str.Format("%d", ii + 1);
			m_GCPsList.SetItemText(ii, 0, str);
		}

		int now_items = m_GCPsList.GetItemCount();

		//更新计算结果
		if (GcpDate.size() >= 3)
		{
			if (degree == 1)
			{
				matrix Coefficient(3, 2); matrix Res(GcpDate.size(), 5);
				cout << endl << GcpDate.size() << endl;
				//一次多项式拟合系数矩阵(3,2)第一列为x的3个系数，第二列为y的3个系数
				Coefficient = ControlPtCls.GeoCorrection(GcpDate, degree);
				//返回矩阵大小为（num,5），前两列为预测的x，y,后两列为预测x,y的误差，最后一列为RMS
				Res = ControlPtCls.CalError(GcpDate, Coefficient, degree);

				//计算总体误差
				CString totalrms;
				double TotalRMS = ControlPtCls.CalTotalError(Res, GcpDate.size());
				totalrms.Format("%.1lf", TotalRMS);
				GetDlgItem(IDC_RmsError_Edit)->SetWindowText(totalrms);
				//误差输出
				Res.MatrixPrint();

				//更新list的predict x,y,error x,error y
				for (int ii = 0; ii < now_items; ii++)
				{
					for (int jj = 0; jj < 5; jj++)
					{
						CString str;

						str.Format("%.1lf", Res.mat[ii][jj]);
						m_GCPsList.SetItemText(ii, jj + 5, str);
					}
				}
			}
			else if (degree == 2 && GcpDate.size() >= 6)
			{
				matrix Coefficient(6, 2); matrix Res(GcpDate.size(), 5);
				//一次多项式拟合系数矩阵(6,2)第一列为x的6个系数，第二列为y的6个系数
				Coefficient = ControlPtCls.GeoCorrection(GcpDate, degree);
				//返回矩阵大小为（num,5），前两列为预测的x，y,后两列为预测x,y的误差，最后一列为RMS
				Res = ControlPtCls.CalError(GcpDate, Coefficient, degree);
				//计算总体误差
				CString totalrms;
				double TotalRMS = ControlPtCls.CalTotalError(Res, GcpDate.size());
				totalrms.Format("%.1lf", TotalRMS);
				GetDlgItem(IDC_RmsError_Edit)->SetWindowText(totalrms);
				//更新list的predict x,y,error x,error y
				for (int ii = 0; ii < now_items; ii++)
				{
					for (int jj = 0; jj < 5; jj++)
					{
						CString str;

						str.Format("%.1lf", Res.mat[ii][jj]);
						m_GCPsList.SetItemText(ii, jj + 5, str);
					}
				}
			}
			else
			{
				for (int ii = 5; ii < 10; ii++)
				{
					m_GCPsList.DeleteColumn(ii);
				}
			}
		}
		else
		{
			for (int ii = 5; ii < 10; ii++)
			{
				m_GCPsList.DeleteColumn(ii);
			}
		}

	}
	//还原当前未点击
	now_click_GCP = -1;
}

//点击实现Goto功能
void GeoCorrDlg::OnNMClickList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	//点击获取item序号
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	now_click_GCP = pNMListView->iItem ;
	if (now_click_GCP < 0 )
	{
		cout << "ddddd";
		return;
	}
	int Gcp_Num = atoi(m_GCPsList.GetItemText(now_click_GCP, 0));
	double x1 = atof(m_GCPsList.GetItemText(now_click_GCP, 1));
	double y1 = atof(m_GCPsList.GetItemText(now_click_GCP, 2));
	double x2 = atof(m_GCPsList.GetItemText(now_click_GCP, 3));
	double y2 = atof(m_GCPsList.GetItemText(now_click_GCP, 4));

	//假设fac1 = 4;fac2 = fac3 = 0.25
	GoToGcp(Gcp_Num, x1, y1,x2,y2,4.0,0.25,0.25);

	//更新Edit
	GetDlgItem(IDC_BaseX_EDIT)->SetWindowText(m_GCPsList.GetItemText(now_click_GCP, 1));
	GetDlgItem(IDC_BaseY_EDIT)->SetWindowText(m_GCPsList.GetItemText(now_click_GCP, 2));
	GetDlgItem(IDC_WrapX_EDIT)->SetWindowText(m_GCPsList.GetItemText(now_click_GCP, 3));
	GetDlgItem(IDC_WrapY_EDIT)->SetWindowText(m_GCPsList.GetItemText(now_click_GCP, 4));





}
/*By_WYY*/

void GeoCorrDlg::OnBnClickedWrapedoutButton()
{
	// TODO: 在此添加控件通知处理程序代码
	//单击输出
	ControlPT ControlPtCls;

	///多项式拟合次数
	CString str_degree;
	GetDlgItem(IDC_COMBO1)->GetWindowText(str_degree);
	int degree = atoi(str_degree);

	int flag = 1;//重采样方式,默认使用最近零点法
	if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck())
		flag = 1;

	else if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck())
		flag = 2;
	else if (((CButton *)GetDlgItem(IDC_RADIO3))->GetCheck())
		flag = 3;
	else
		MessageBox("请选择重采样");
	CString FilePath;//输出文件路径
	GetDlgItemText(IDC_OutWraped_MFCEDITBROWSE, FilePath);
	BOOL outFlag;
	if (degree == 1)
	{

		matrix Coefficient(3, 2); matrix Res(GcpDate.size(), 5);
		//一次多项式拟合系数矩阵(3,2)第一列为x的3个系数，第二列为y的3个系数
		Coefficient = ControlPtCls.GeoCorrection(GcpDate, degree);
		//返回矩阵大小为（num,4），前两列为预测的x，y,后两列为预测x,y的误差
		Res = ControlPtCls.GeoCorrection(GcpDate, degree);

		matrix Coeffx(1, 3); matrix Coeffy(1, 3);
		for (int ii = 0; ii < 3; ii++)
		{
			Coeffx.mat[0][ii] = Coefficient.mat[ii][0];
			Coeffy.mat[0][ii] = Coefficient.mat[ii][1];
		}
		Coeffy.mat[0][0] = -Coeffy.mat[0][0];
		outFlag = BaseImg.OutputCorrRes(Coeffx, Coeffy, BaseImg.ImgParaInCls.ImgW, BaseImg.ImgParaInCls.ImgH, WrapImg.ImgParaInCls.ImgRAdr, WrapImg.ImgParaInCls.ImgGAdr, WrapImg.ImgParaInCls.ImgGAdr, flag, degree, FilePath);
	}
	else if (degree == 2)
	{
		matrix Coefficient(6, 2); matrix Res(GcpDate.size(), 5);
		//一次多项式拟合系数矩阵(6,2)第一列为x的6个系数，第二列为y的6个系数
		Coefficient = ControlPtCls.GeoCorrection(GcpDate, degree);
		//返回矩阵大小为（num,4），前两列为预测的x，y,后两列为预测x,y的误差
		Res = ControlPtCls.GeoCorrection(GcpDate, degree);

		matrix Coeffx(1, 6); matrix Coeffy(1, 6);
		for (int ii = 0; ii < 6; ii++)
		{
			Coeffx.mat[ii][0] = Coefficient.mat[ii][0];
			Coeffy.mat[ii][0] = Coefficient.mat[ii][1];
		}
		Coeffy.mat[0][0] = -Coeffy.mat[0][0];
		outFlag = BaseImg.OutputCorrRes(Coeffx, Coeffy, BaseImg.ImgParaInCls.ImgW, BaseImg.ImgParaInCls.ImgH, WrapImg.ImgParaInCls.ImgRAdr, WrapImg.ImgParaInCls.ImgGAdr, WrapImg.ImgParaInCls.ImgGAdr, flag, degree, FilePath);
	}
	else
	{
		cout << "系数选择错误！";
	}

	if (outFlag == FALSE)
	{
		MessageBox("校正影像输出失败");
	}
	else
	{
		MessageBox("校正影像输出成功！！！");
	}


}
//字符串分隔  ", :;\t\r\n\\"  点号 逗号 空格 分号
//读取数据
int __fastcall  SsToStr_ReadPtsDate(char *str, char *s_dat[])
{
	int  nn;
	char ch, *pstr;
	s_dat[0] = str;
	ch = *str;
	if (ch == '\0' || ch == '\n') return 0;
	nn = 0; pstr = strtok(str, ", :;\t\r\n\\");
	while (pstr)
	{
		/*if (pstr)
		{
			s_dat[nn] = pstr; if (nn < MAX_DAT) nn++;
		}*/
		if (pstr)
		{
			s_dat[nn] = pstr; if (nn < 100) nn++;
		}
		pstr = strtok(NULL, ", :;\t\r\n\\");
	}
	return nn;
}

//读取文件名
int __fastcall  SsToStr_ReadPtsName(char *str, char *s_dat[])
{
	int  nn;
	char ch, *pstr;
	s_dat[0] = str;
	ch = *str;
	if (ch == '\0' || ch == '\n') return 0;
	nn = 0; pstr = strtok(str, "., :;\t\r\n\\");
	while (pstr)
	{
		/*if (pstr)
		{
			s_dat[nn] = pstr; if (nn < MAX_DAT) nn++;
		}*/
		if (pstr)
		{
			s_dat[nn] = pstr; if (nn < 100) nn++;
		}
		pstr = strtok(NULL, "., :;\t\r\n\\");
	}
	return nn;
}
//仅保留0.0和0.5
double PrecisionConversion(double date)
{
	date = floor(date * 10 + 0.5) / 10;//四舍五入，保留一位
	//仅保留0.0和0.5
	if (date - floor(date) > 0.5)
		date = floor(date) + 0.5;
	else
		date = floor(date);
	return date;
}
//读取控制点
void GeoCorrDlg::OnBnClickedDelpointButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//清空数据
	GcpDate.erase(GcpDate.begin(),GcpDate.end());
	//清空list
	m_GCPsList.DeleteAllItems();
	CFileDialog Dlg(TRUE);
	CString FilePath;	
	if (Dlg.DoModal() == IDOK)
	{
		FilePath = Dlg.GetPathName();
	}
	//读取文件名
	CString datename;//数据名
	int file_nn = 0;
	char *SS[10];
	CString s1 = FilePath.Right(3);
	if (s1!="pts")
	{
		MessageBox("数据打开错误");
		return;
	}
	else
	{
		//读取数据
		GcpStruct one_gcpdate;
		char ReadStr[500];
		int nn = 0;
		char *SS_Dat[20];
		FILE *fp = fopen(FilePath, "r");

		//跳过5行
		int iii = 5;
		while (iii)
		{

			if (feof(fp))break;
			fgets(ReadStr, 800, fp);
			iii = iii - 1;
		
		}
	
		while (1)
		{
			if (feof(fp))break;
			fgets(ReadStr, 800, fp);
			nn = SsToStr_ReadPtsDate(ReadStr, SS_Dat);
			double BaseXX = atof(SS_Dat[0]);
			double BaseYY = atof(SS_Dat[1]);
			double WrapXX = atof(SS_Dat[2]);
			double WrapYY = atof(SS_Dat[3]);

			one_gcpdate.baseX = PrecisionConversion(BaseXX);
			one_gcpdate.baseY = PrecisionConversion(BaseYY);
			one_gcpdate.wrapX = PrecisionConversion(WrapXX);
			one_gcpdate.wrapY = PrecisionConversion(WrapYY);

			GcpDate.push_back(one_gcpdate);

			
		}
		fclose(fp);

	}


	//show list control
	
	//多项式拟合次数
	CString str_degree;
	GetDlgItem(IDC_COMBO1)->GetWindowText(str_degree);
	int degree = atoi(str_degree);
	//控制点类实例
	ControlPT ControlPtCls;

	if (GcpDate.size() >= 3)
	{
		if (degree == 1)
		{
			matrix Coefficient(3, 2); matrix Res(GcpDate.size(), 5);
			//一次多项式拟合系数矩阵(3,2)第一列为x的3个系数，第二列为y的3个系数
			Coefficient = ControlPtCls.GeoCorrection(GcpDate, degree);
			cout << "系数：" << endl;
			Coefficient.MatrixPrint();

			//返回矩阵大小为（num,5），前两列为预测的x，y,后两列为预测x,y的误差，最后一列为RMS
			Res = ControlPtCls.CalError(GcpDate, Coefficient, degree);

			//计算总体误差
			CString totalrms;
			double TotalRMS = ControlPtCls.CalTotalError(Res, GcpDate.size());
			totalrms.Format("%.3lf", TotalRMS);
			GetDlgItem(IDC_RmsError_Edit)->SetWindowText(totalrms);
			//误差输出

			CString listnum;
			CString BaseX, BaseY, WrapX, WrapY;
			//更新list的predict x,y,error x,error y
			for (int ii = 0; ii < GcpDate.size(); ii++)
			{

				listnum.Format("%d", ii+1);
				m_GCPsList.InsertItem(ii, listnum);

				BaseX.Format("%.1f", GcpDate[ii].baseX);
				m_GCPsList.SetItemText(ii, 1, BaseX);
				BaseY.Format("%.1f", GcpDate[ii].baseY);
				m_GCPsList.SetItemText(ii, 2, BaseY);
				WrapX.Format("%.1f", GcpDate[ii].wrapX);
				m_GCPsList.SetItemText(ii, 3, WrapX);
				WrapY.Format("%.1f", GcpDate[ii].wrapY);
				m_GCPsList.SetItemText(ii, 4, WrapY);
				cout << "hello";

				for (int jj = 0; jj < 5; jj++)
				{
					CString str;
					str.Format("%.3lf", Res.mat[ii][jj]);
					m_GCPsList.SetItemText(ii, jj + 5, str);
				}
			}

		}
		else if (degree == 2 && GcpDate.size() >= 6)
		{
			matrix Coefficient(6, 2); matrix Res(GcpDate.size(), 5);
			//一次多项式拟合系数矩阵(6,2)第一列为x的6个系数，第二列为y的6个系数
			Coefficient = ControlPtCls.GeoCorrection(GcpDate, degree);
			//返回矩阵大小为（num,5），前两列为预测的x，y,后两列为预测x,y的误差，最后一列为RMS
			Res = ControlPtCls.CalError(GcpDate, Coefficient, degree);
			cout << "系数：" << endl;
			Coefficient.MatrixPrint();
			//计算总体误差
			CString totalrms;
			double TotalRMS = ControlPtCls.CalTotalError(Res, GcpDate.size());
			totalrms.Format("%.3lf", TotalRMS);
			GetDlgItem(IDC_RmsError_Edit)->SetWindowText(totalrms);

			CString listnum;
			CString BaseX, BaseY, WrapX, WrapY;
			//更新list的predict x,y,error x,error y
			for (int ii = 0; ii < GcpDate.size(); ii++)
			{

				listnum.Format("%d", ii+1);
				m_GCPsList.InsertItem(ii, listnum);

				BaseX.Format("%.1f", GcpDate[ii].baseX);
				m_GCPsList.SetItemText(ii, 1, BaseX);
				BaseY.Format("%.1f", GcpDate[ii].baseY);
				m_GCPsList.SetItemText(ii, 2, BaseY);
				WrapX.Format("%.1f", GcpDate[ii].wrapX);
				m_GCPsList.SetItemText(ii, 3, WrapX);
				WrapY.Format("%.1f", GcpDate[ii].wrapY);
				m_GCPsList.SetItemText(ii, 4, WrapY);
				cout << "hello";

				for (int jj = 0; jj < 5; jj++)
				{
					CString str;
					str.Format("%.3lf", Res.mat[ii][jj]);
					m_GCPsList.SetItemText(ii, jj + 5, str);
				}
			}
		}
	}
	MessageBox("done");
}


void GeoCorrDlg::OnBnClickedDelpointButton3()
{
	CFileDialog Dlg(TRUE);
	CString WrirtePath;
	if (Dlg.DoModal() == IDOK)
	{
		WrirtePath = Dlg.GetPathName();
	}
	// TODO: 在此添加控件通知处理程序代码
	if (WrirtePath.Find('.') == -1)
	{
		CString strClass = ".pts";
		WrirtePath = WrirtePath + strClass;
	}

	ofstream outfile(WrirtePath, ofstream::app);
	CString BaseFile;
	CString WrapFile;
	GetDlgItem(IDC_Base_MFCEDITBROWSE)->GetWindowText(BaseFile);
	GetDlgItem(IDC_Base_MFCEDITBROWSE)->GetWindowText(WrapFile);

	if (GcpDate.size() == 0)
	{
		MessageBox("请先选择或者打开控制点");
	}
	int position = BaseFile.ReverseFind('\\');
	BaseFile = BaseFile.Mid(position+1, BaseFile.GetLength() - 4 - position-1);
	position = WrapFile.ReverseFind('\\');
	WrapFile = WrapFile.Mid(position+1, WrapFile.GetLength() - 4 - position-1);
	outfile << "; 2020RS Image to Image GCP File" << endl
		<< "; base file :" << BaseFile << endl
		<< "; warp file :" << WrapFile << endl
		<< "; Base Image(x, y), Warp Image(x, y)" << endl
		<< ";" << endl;
	CString x1, y1, x2, y2;

	for (int ii = 0; ii < GcpDate.size(); ii++)
	{
		x1.Format("%.1f", GcpDate[ii].baseX);
		y1.Format("%.1f", GcpDate[ii].baseY);
		x2.Format("%.1f", GcpDate[ii].wrapX);
		y2.Format("%.1f", GcpDate[ii].wrapY);
		outfile << x1 <<"    "<< y1<<"    " << x2<<"    " << y2<< endl;
	}
	MessageBox("done");
}

void GeoCorrDlg::OnCbnSelchangeCombo1()
{
	//多项式拟合次数
	CString str_degree;
	GetDlgItem(IDC_COMBO1)->GetWindowText(str_degree);
	int degree = atoi(str_degree);
	//控制点类实例
	ControlPT ControlPtCls;

	if (GcpDate.size() >= 3)
	{
		if (degree == 1)
		{
			matrix Coefficient(3, 2); matrix Res(GcpDate.size(), 5);
			//一次多项式拟合系数矩阵(3,2)第一列为x的3个系数，第二列为y的3个系数
			Coefficient = ControlPtCls.GeoCorrection(GcpDate, degree);
			cout << "系数：" << endl;
			Coefficient.MatrixPrint();

			//返回矩阵大小为（num,5），前两列为预测的x，y,后两列为预测x,y的误差，最后一列为RMS
			Res = ControlPtCls.CalError(GcpDate, Coefficient, degree);

			//计算总体误差
			CString totalrms;
			double TotalRMS = ControlPtCls.CalTotalError(Res, GcpDate.size());
			totalrms.Format("%.3lf", TotalRMS);
			GetDlgItem(IDC_RmsError_Edit)->SetWindowText(totalrms);
			//误差输出

			CString listnum;
			CString BaseX, BaseY, WrapX, WrapY;
			//更新list的predict x,y,error x,error y
			for (int ii = 0; ii < GcpDate.size(); ii++)
			{

				listnum.Format("%d", ii);
				m_GCPsList.InsertItem(ii, listnum);

				BaseX.Format("%.1f", GcpDate[ii].baseX);
				m_GCPsList.SetItemText(ii, 1, BaseX);
				BaseY.Format("%.1f", GcpDate[ii].baseY);
				m_GCPsList.SetItemText(ii, 2, BaseY);
				WrapX.Format("%.1f", GcpDate[ii].wrapX);
				m_GCPsList.SetItemText(ii, 3, WrapX);
				WrapY.Format("%.1f", GcpDate[ii].wrapY);
				m_GCPsList.SetItemText(ii, 4, WrapY);
				cout << "hello";

				for (int jj = 0; jj < 5; jj++)
				{
					CString str;
					str.Format("%.3lf", Res.mat[ii][jj]);
					m_GCPsList.SetItemText(ii, jj + 5, str);
				}
			}

		}
		else if (degree == 2 && GcpDate.size() >= 6)
		{
			matrix Coefficient(6, 2); matrix Res(GcpDate.size(), 5);
			//一次多项式拟合系数矩阵(6,2)第一列为x的6个系数，第二列为y的6个系数
			Coefficient = ControlPtCls.GeoCorrection(GcpDate, degree);
			//返回矩阵大小为（num,5），前两列为预测的x，y,后两列为预测x,y的误差，最后一列为RMS
			Res = ControlPtCls.CalError(GcpDate, Coefficient, degree);
			cout << "系数：" << endl;
			Coefficient.MatrixPrint();
			//计算总体误差
			CString totalrms;
			double TotalRMS = ControlPtCls.CalTotalError(Res, GcpDate.size());
			totalrms.Format("%.3lf", TotalRMS);
			GetDlgItem(IDC_RmsError_Edit)->SetWindowText(totalrms);

			CString listnum;
			CString BaseX, BaseY, WrapX, WrapY;
			//更新list的predict x,y,error x,error y
			for (int ii = 0; ii < GcpDate.size(); ii++)
			{

				listnum.Format("%d", ii);
				m_GCPsList.InsertItem(ii, listnum);

				BaseX.Format("%.1f", GcpDate[ii].baseX);
				m_GCPsList.SetItemText(ii, 1, BaseX);
				BaseY.Format("%.1f", GcpDate[ii].baseY);
				m_GCPsList.SetItemText(ii, 2, BaseY);
				WrapX.Format("%.1f", GcpDate[ii].wrapX);
				m_GCPsList.SetItemText(ii, 3, WrapX);
				WrapY.Format("%.1f", GcpDate[ii].wrapY);
				m_GCPsList.SetItemText(ii, 4, WrapY);
				cout << "hello";

				for (int jj = 0; jj < 5; jj++)
				{
					CString str;
					str.Format("%.3lf", Res.mat[ii][jj]);
					m_GCPsList.SetItemText(ii, jj + 5, str);
				}
			}
		}
	}
	MessageBox("RMS更新");
	// TODO: 在此添加控件通知处理程序代码
}

void GeoCorrDlg::lock(bool flag)
{
	if (flag)
	{
		GetDlgItem(IDC_LIST3)->EnableWindow(false);
		GetDlgItem(IDC_AddPoint_BUTTON)->EnableWindow(false);
		GetDlgItem(IDC_DelPoint_BUTTON)->EnableWindow(false);
		GetDlgItem(IDC_DelPoint_BUTTON2)->EnableWindow(false);
		GetDlgItem(IDC_DelPoint_BUTTON3)->EnableWindow(false);
		GetDlgItem(IDC_DelPoint_BUTTON4)->EnableWindow(false);
	}
	else
	{
		GetDlgItem(IDC_LIST3)->EnableWindow(true);
		GetDlgItem(IDC_AddPoint_BUTTON)->EnableWindow(true);
		GetDlgItem(IDC_DelPoint_BUTTON)->EnableWindow(true);
		GetDlgItem(IDC_DelPoint_BUTTON2)->EnableWindow(true);
		GetDlgItem(IDC_DelPoint_BUTTON3)->EnableWindow(true);
		GetDlgItem(IDC_DelPoint_BUTTON4)->EnableWindow(true);

	}
}


void GeoCorrDlg::OnBnClickedDelpointButton4()
{
	//清空数据
	GcpDate.erase(GcpDate.begin(), GcpDate.end());
	//清空list
	m_GCPsList.DeleteAllItems();

	//清空编辑框的内容
	GetDlgItem(IDC_BaseX_EDIT)->SetWindowText("");
	GetDlgItem(IDC_BaseY_EDIT)->SetWindowText("");
	GetDlgItem(IDC_WrapX_EDIT)->SetWindowText("");
	GetDlgItem(IDC_WrapY_EDIT)->SetWindowText("");
	GetDlgItem(IDC_RmsError_Edit)->SetWindowText("");
	// TODO: 在此添加控件通知处理程序代码
}
