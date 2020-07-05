// GeoCorrDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "2020RS.h"
#include "GeoCorrDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include "GeoCorrImg.h"
#include"ControlPT.h"
using namespace std;


//静态成员变量初始化
Img_kele GeoCorrDlg::BaseImg;
Img_kele GeoCorrDlg::WrapImg;
GeoCorrImg GeoCorrDlg::dlg11;
GeoCorrImg GeoCorrDlg::dlg12;
GeoCorrImg GeoCorrDlg::dlg13;
GeoCorrImg GeoCorrDlg::dlg21;
GeoCorrImg GeoCorrDlg::dlg22;
GeoCorrImg GeoCorrDlg::dlg23;

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
}


BEGIN_MESSAGE_MAP(GeoCorrDlg, CDialog)
	ON_EN_CHANGE(IDC_Base_MFCEDITBROWSE, &GeoCorrDlg::OnEnChangeBaseMfceditbrowse)
	ON_EN_CHANGE(IDC_Wrap_MFCEDITBROWSE, &GeoCorrDlg::OnEnChangeWrapMfceditbrowse)
	ON_BN_CLICKED(IDC_GeoBegin_BUTTON, &GeoCorrDlg::OnBnClickedGeobeginButton)
	ON_BN_CLICKED(IDC_AddPoint_BUTTON, &GeoCorrDlg::OnBnClickedAddpointButton)
	ON_BN_CLICKED(IDC_DelPoint_BUTTON, &GeoCorrDlg::OnBnClickedDelpointButton)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, &GeoCorrDlg::OnNMClickList3)
	ON_BN_CLICKED(IDC_WrapedOut_BUTTON, &GeoCorrDlg::OnBnClickedWrapedoutButton)
END_MESSAGE_MAP()


// GeoCorrDlg 消息处理程序

BOOL GeoCorrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

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


	dlg11.iNum = 1; dlg11.iFlag = 1;
	dlg11.Create(IDD_GeoCorrImg_DIALOG, this);
	dlg12.iNum = 1; dlg12.iFlag = 2;
	dlg12.Create(IDD_GeoCorrImg_DIALOG, this);
	dlg13.iNum = 1; dlg13.iFlag = 3;
	dlg13.Create(IDD_GeoCorrImg_DIALOG, this);
	dlg21.iNum = 2; dlg21.iFlag = 1;
	dlg21.Create(IDD_GeoCorrImg_DIALOG, this);
	dlg22.iNum = 2; dlg22.iFlag = 2;
	dlg22.Create(IDD_GeoCorrImg_DIALOG, this);
	dlg23.iNum = 2; dlg23.iFlag = 3;
	dlg23.Create(IDD_GeoCorrImg_DIALOG, this);

	//初始化listcontrol
	m_GCPsList.GetClientRect(&rect);
	//
	m_GCPsList.SetExtendedStyle(m_GCPsList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_GCPsList.InsertColumn(0, "序号", LVCFMT_LEFT, rect.Width() /10, 0);
	m_GCPsList.InsertColumn(1, "Base X", LVCFMT_LEFT, rect.Width() /5, 1);
	m_GCPsList.InsertColumn(2, "Base Y", LVCFMT_LEFT, rect.Width() /5, 2);
	m_GCPsList.InsertColumn(3, "Wrap X", LVCFMT_LEFT, rect.Width() /5, 3);
	m_GCPsList.InsertColumn(4, "Wrap Y", LVCFMT_LEFT, rect.Width() /5, 4);
	m_GCPsList.InsertColumn(5, "Predict X", LVCFMT_LEFT, rect.Width() /5, 5);
	m_GCPsList.InsertColumn(6, "Predict Y", LVCFMT_LEFT, rect.Width() /5, 6);
	m_GCPsList.InsertColumn(7, "Error X", LVCFMT_LEFT, rect.Width() /5, 7);
	m_GCPsList.InsertColumn(8, "Error Y", LVCFMT_LEFT, rect.Width() /5, 8);
	m_GCPsList.InsertColumn(9, "RMS", LVCFMT_LEFT, rect.Width() /5, 9);
	
	//
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("1");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("2");

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

	//显示基准影像
	dlg11.ShowWindow(SW_SHOW);
	dlg12.ShowWindow(SW_SHOW);
	dlg13.ShowWindow(SW_SHOW);
	//
	HWND hWnd;
	HDC hdc;
	CRect rect;
	//
	hWnd = ::FindWindow(NULL, "dialog12");
	hdc = ::GetDC(hWnd);
	::GetClientRect(hWnd, &rect);
	double fac1 = max(1.0*BaseImg.ImgParaInCls.ImgW / rect.Width(), 1.0*BaseImg.ImgParaInCls.ImgH / rect.Height());
	BaseImg.DisplayImgColor(&hdc, rect.Width(), rect.Height(), 0, 0, BaseImg.ImgParaInCls.ImgW, BaseImg.ImgParaInCls.ImgH, 0, 0);
	
	//
	int offx1 = 0; int offy1 = 0;//假设1-2中的选择框最左下角坐标为(0,100)
	//double fac2 = 1.0 / 400 * 100;
	double fac2 = 1.0 / 400 * 100;
	hWnd = ::FindWindow(NULL, "dialog11");
	hdc = ::GetDC(hWnd);
	::GetClientRect(hWnd, &rect);
	BaseImg.DisplaySquareImgColor(&hdc, rect.Width(), rect.Height(), offx1, offy1,fac1,fac2);
	
	//
	int offx2 = 50; int offy2 = 0;//假设1-1中的选择框最左下角坐标为(50,0)
	double fac3 = 1.0 / 400 * 100;
	hWnd = ::FindWindow(NULL, "dialog13");
	hdc = ::GetDC(hWnd);
	::GetClientRect(hWnd, &rect);
	BaseImg.DisplaySquareImgColor(&hdc, rect.Width(), rect.Height(),offx1,offy1,offx2,offy2,fac1,fac2,fac3);
	//显示校正影像
	dlg21.ShowWindow(SW_SHOW);
	dlg22.ShowWindow(SW_SHOW);
	dlg23.ShowWindow(SW_SHOW);
	//
	hWnd = ::FindWindow(NULL, "dialog21");
	hdc = ::GetDC(hWnd);
	::GetClientRect(hWnd, &rect);
	WrapImg.DisplayImgColor(&hdc, rect.Width(), rect.Height(), 0, 0, WrapImg.ImgParaInCls.ImgW, WrapImg.ImgParaInCls.ImgH, 0, 0);
	//
	hWnd = ::FindWindow(NULL, "dialog22");
	hdc = ::GetDC(hWnd);
	::GetClientRect(hWnd, &rect);
	WrapImg.DisplayImgColor(&hdc, rect.Width(), rect.Height(), 0, 0, WrapImg.ImgParaInCls.ImgW, WrapImg.ImgParaInCls.ImgH, 0, 0);
	//
	hWnd = ::FindWindow(NULL, "dialog23");
	hdc = ::GetDC(hWnd);
	::GetClientRect(hWnd, &rect);
	WrapImg.DisplayImgColor(&hdc, rect.Width(), rect.Height(), 0, 0, WrapImg.ImgParaInCls.ImgW, WrapImg.ImgParaInCls.ImgH, 0, 0);

	
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
	GetDlgItem(IDC_BaseX_EDIT)->GetWindowText(str_BaseY);
	GetDlgItem(IDC_BaseX_EDIT)->GetWindowText(str_WrapX);
	GetDlgItem(IDC_BaseX_EDIT)->GetWindowText(str_WrapY);

	int BaseX = atof(str_BaseX);
	int BaseY = atof(str_BaseY);
	int WrapX = atof(str_WrapX);
	int WrapY = atof(str_WrapY);


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
	if (GcpDate.size() >= 3)
	{
		if (degree == 1)
		{
			matrix Coefficient(3, 2); matrix Res(GcpDate.size(), 5);
			cout << endl << GcpDate.size() << endl;
			//一次多项式拟合系数矩阵(3,2)第一列为x的3个系数，第二列为y的3个系数
			Coefficient= ControlPtCls.GeoCorrection(GcpDate, degree);
			//返回矩阵大小为（num,5），前两列为预测的x，y,后两列为预测x,y的误差，最后一列为RMS
			Res = ControlPtCls.CalError(GcpDate,Coefficient,degree);

			//计算总体误差RMS
			double TotalRMS = ControlPtCls.CalTotalError(Res, GcpDate.size());

			//误差输出
			cout << "误差信息：" << endl;
			Res.MatrixPrint();

			//更新list的predict x,y,error x,error y
			for (int ii = 0; ii < now_items; ii++)
			{
				for (int jj=0; jj < 5; jj++)
				{
					CString str;
					
					str.Format("%.3lf", Res.mat[ii][jj]);
					m_GCPsList.SetItemText(ii,jj+5,str);
				}
			}
		}
		else if (degree == 2 && GcpDate.size()>= 6)
		{
			matrix Coefficient(6, 2); matrix Res(GcpDate.size(), 5);
			//一次多项式拟合系数矩阵(6,2)第一列为x的6个系数，第二列为y的6个系数
			Coefficient= ControlPtCls.GeoCorrection(GcpDate, degree);
			//返回矩阵大小为（num,5），前两列为预测的x，y,后两列为预测x,y的误差，最后一列为RMS
			Res = ControlPtCls.CalError(GcpDate, Coefficient, degree);

			//更新list的predict x,y,error x,error y
			for (int ii = 0; ii < now_items; ii++)
			{
				for (int jj = 0; jj < 5; jj++)
				{
					CString str;

					str.Format("%.3lf", Res.mat[ii][jj]);
					m_GCPsList.SetItemText(ii, jj + 5, str);
				}
			}
		}
	}

}

//删除控制点
void GeoCorrDlg::OnBnClickedDelpointButton()
{
	// TODO: 在此添加控件通知处理程序代码
	m_GCPsList.DeleteItem(now_click_GCP);
	//从Gcpdate删除
	auto erasenum = GcpDate.begin() + now_click_GCP;
	GcpDate.erase(erasenum);

	///多项式拟合次数
	CString str_degree;
	GetDlgItem(IDC_EDIT4)->GetWindowText(str_degree);
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

			//计算总体误差RMS
			double TotalRMS = ControlPtCls.CalTotalError(Res, GcpDate.size());

			//误差输出
			Res.MatrixPrint();

			//更新list的predict x,y,error x,error y
			for (int ii = 0; ii < now_items; ii++)
			{
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

			//更新list的predict x,y,error x,error y
			for (int ii = 0; ii < now_items; ii++)
			{
				for (int jj = 0; jj < 5; jj++)
				{
					CString str;

					str.Format("%.3lf", Res.mat[ii][jj]);
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


void GeoCorrDlg::OnNMClickList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	//点击获取item序号
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	now_click_GCP = pNMListView->iItem ;
}
/*By_WYY*/

void GeoCorrDlg::OnBnClickedWrapedoutButton()
{
	// TODO: 在此添加控件通知处理程序代码
	//单击输出
	ControlPT ControlPtCls;

	int degree = 1;//多项式拟合系数
	int flag = 1;//重采样方式
	CString FilePath;//输出文件路径
	if (degree == 1)
	{

		matrix Coefficient(3, 2); matrix Res(GcpDate.size(), 4);
		//一次多项式拟合系数矩阵(3,2)第一列为x的3个系数，第二列为y的3个系数
		Coefficient = ControlPtCls.GeoCorrection(GcpDate, degree);
		//返回矩阵大小为（num,4），前两列为预测的x，y,后两列为预测x,y的误差
		Res = ControlPtCls.GeoCorrection(GcpDate, degree);

		matrix Coeffx(3, 1); matrix Coeffy(3, 1);
		for (int ii = 0; ii < 3; ii++)
		{
			Coeffx.mat[ii][0] = Coefficient.mat[ii][0];
			Coeffy.mat[ii][0] = Coefficient.mat[ii][1];
		}
		CString FilePath;
		WrapImg.OutputCorrRes(Coeffx, Coeffy, BaseImg.ImgParaInCls.ImgW, BaseImg.ImgParaInCls.ImgH, WrapImg.ImgParaInCls.ImgRAdr, WrapImg.ImgParaInCls.ImgGAdr, WrapImg.ImgParaInCls.ImgGAdr, flag, FilePath);
	}
	else if (degree == 2)
	{
		matrix Coefficient(6, 2); matrix Res(GcpDate.size(), 4);
		//一次多项式拟合系数矩阵(6,2)第一列为x的6个系数，第二列为y的6个系数
		Coefficient = ControlPtCls.GeoCorrection(GcpDate, degree);
		//返回矩阵大小为（num,4），前两列为预测的x，y,后两列为预测x,y的误差
		Res = ControlPtCls.GeoCorrection(GcpDate, degree);

		matrix Coeffx(3, 1); matrix Coeffy(3, 1);
		for (int ii = 0; ii < 3; ii++)
		{
			Coeffx.mat[ii][0] = Coefficient.mat[ii][0];
			Coeffy.mat[ii][0] = Coefficient.mat[ii][1];
		}
		WrapImg.OutputCorrRes(Coeffx, Coeffy, BaseImg.ImgParaInCls.ImgW, BaseImg.ImgParaInCls.ImgH, WrapImg.ImgParaInCls.ImgRAdr, WrapImg.ImgParaInCls.ImgGAdr, WrapImg.ImgParaInCls.ImgGAdr, flag, FilePath);
	}
	else
	{
		cout << "系数选择错误！";
	}

}
