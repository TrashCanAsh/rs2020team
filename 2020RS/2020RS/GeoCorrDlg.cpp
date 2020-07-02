// GeoCorrDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "2020RS.h"
#include "GeoCorrDlg.h"
#include "afxdialogex.h"
#include <iostream>
using namespace std;

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
}


BEGIN_MESSAGE_MAP(GeoCorrDlg, CDialog)
	ON_EN_CHANGE(IDC_Base_MFCEDITBROWSE, &GeoCorrDlg::OnEnChangeBaseMfceditbrowse)
	ON_EN_CHANGE(IDC_Wrap_MFCEDITBROWSE, &GeoCorrDlg::OnEnChangeWrapMfceditbrowse)
	ON_BN_CLICKED(IDC_GeoBegin_BUTTON, &GeoCorrDlg::OnBnClickedGeobeginButton)
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
	GetDlgItemText(IDC_Wrap_MFCEDITBROWSE, BaseImgPath);
	flag=BaseImg.CreateBandSpace();
	if (flag == FALSE)
		MessageBox("基准影像数据空间开辟失败！");
	flag = FALSE;

	flag=BaseImg.ReadBmpData(BaseImgPath);
	if (flag == FALSE)
		MessageBox("基准影像数据读入失败！");
	else
		MessageBox("基准影像数据读入成功！");
	flag = FALSE;


	CString WrapImgPath;
	GetDlgItemText(IDC_Wrap_MFCEDITBROWSE, WrapImgPath);
	WrapImg.CreateBandSpace();
	flag=WrapImg.ReadBmpData(WrapImgPath);
	if (flag == FALSE)
		MessageBox("待校正影像数据读入失败！");
	else
		MessageBox("待校正影像数据读入成功！");
}
