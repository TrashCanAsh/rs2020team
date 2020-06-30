// SpectralViewDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "2020RS.h"
#include "SpectralViewDlg.h"
#include "afxdialogex.h"
#include <iostream>
using namespace std;


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
	DDX_Control(pDX, IDC_SpecLib_TREE, m_SpecTree);
	DDX_Control(pDX, IDC_SpecLine_LIST, m_specList);
	DDX_Control(pDX, IDC_Property_LIST, m_PropList);
	DDX_Control(pDX, IDC_EDIT1, m_PropEdit);
}


BEGIN_MESSAGE_MAP(SpectralViewDlg, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_Property_LIST, &SpectralViewDlg::OnNMDblclkPropertyList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_Property_LIST, &SpectralViewDlg::OnLvnItemchangedPropertyList)
END_MESSAGE_MAP()


// SpectralViewDlg 消息处理程序


BOOL SpectralViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//控制台
	if (!OpenConsole()) AfxMessageBox(_T("控制台打开失败"));

	//左侧文件列表的初始化
	HTREEITEM hRoot;     // 树的根节点的句柄   
	HTREEITEM hCataItem; // 可表示任一分类节点的句柄   
	HTREEITEM hSpecItem;  // 可表示任一光谱文件节点的句柄
	
	//树中节点前可添加图标
	//插入根节点
	hRoot = m_SpecTree.InsertItem(_T("USGS"), 0, 0);
	//在根节点下插入光谱类M
	hCataItem = m_SpecTree.InsertItem(_T("M"), NULL, NULL, hRoot, TVI_LAST);
	//在M类下插入光谱文件节点
	hSpecItem = m_SpecTree.InsertItem(_T("Spec1"), NULL, NULL, hCataItem, TVI_LAST);
	hSpecItem = m_SpecTree.InsertItem(_T("Spec2"), NULL, NULL, hCataItem, TVI_LAST);

	//在根节点下插入光谱类S
	hCataItem = m_SpecTree.InsertItem(_T("S"), NULL, NULL, hRoot, TVI_LAST);
	//在S类下插入光谱文件节点
	hSpecItem = m_SpecTree.InsertItem(_T("Spec3"), NULL, NULL, hCataItem, TVI_LAST);
	hSpecItem = m_SpecTree.InsertItem(_T("Spec4"), NULL, NULL, hCataItem, TVI_LAST);


	//右侧上方光谱曲线选择的初始化
	CRect lrect;
	m_specList.GetClientRect(&lrect);
	// 为列表视图控件添加全行选中和栅格风格
	m_specList.SetExtendedStyle(m_specList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//checkbox的添加
	ListView_SetExtendedListViewStyle(m_specList.GetSafeHwnd(), m_specList.GetExStyle() | LVS_EX_CHECKBOXES);
	//m_specList.InsertColumn(0, _T("波段"), LVCFMT_CENTER, lrect.Width() / 2, 0);
	m_specList.InsertItem(0, _T("光谱曲线1的名称"));
	m_specList.InsertItem(1, _T("光谱曲线2的名称"));


	//右侧下方绘图属性的初始化
	//隐藏Edit控件
	//m_PropEdit.ShowWindow(SW_HIDE);
	CRect prect;
	m_PropList.GetClientRect(&prect);
	// 为列表视图控件添加全行选中和栅格风格
	m_PropList.SetExtendedStyle(m_PropList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加三列   
	m_PropList.InsertColumn(0, _T("项目"), LVCFMT_CENTER, prect.Width() / 3.2, 0);
	m_PropList.InsertColumn(1, _T("值"), LVCFMT_CENTER, prect.Width() / 1.45, 1);
	m_PropList.InsertItem(0, _T("X轴最小值"));
	m_PropList.InsertItem(1, _T("X轴最大值"));
	m_PropList.InsertItem(2, _T("Y轴最小值"));
	m_PropList.InsertItem(3, _T("Y轴最大值"));
	m_PropList.InsertItem(4, _T("标题"));
	//m_PropList.InsertItem(5, _T("横坐标配准系数"));
	//m_PropList.InsertItem(6, _T("纵坐标配准系数"));


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

bool SpectralViewDlg::OpenConsole()
{
	if (!AllocConsole()) return FALSE; //控制台调试窗口开启

	freopen("CONOUT$", "w", stdout);//开启中文控制台输出支持

	return TRUE;
}

void SpectralViewDlg::OnNMDblclkPropertyList(NMHDR *pNMHDR, LRESULT *pResult)
{
	//双击右侧下方属性列表
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CRect rc;

	int currRow = pNMListView->iItem;//获得选中的行
	int currCol = pNMListView->iSubItem;//获得选中列
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
		if (currRow == allRow - 1)
		{
			m_PropList.InsertItem(currRow + 1, _T(""));
		}
		//m_PropList.SetItemText(1, 1, _T("默认"));
		CString tem;
		//m_PropEdit.GetWindowText(tem); //得到用户输入的新的内容
		GetDlgItemText(IDC_EDIT1,tem);
		cout << (LPCTSTR)tem << endl;
		m_PropList.SetItemText(currRow, currCol, _T("默认值")); //设置编辑框的新内容
		//m_PropEdit.ShowWindow(SW_HIDE); //隐藏编辑框
	}

	*pResult = 0;

	
}




void SpectralViewDlg::OnLvnItemchangedPropertyList(NMHDR *pNMHDR, LRESULT *pResult)
{
	//属性列表值被更改
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	//获取更改后的图表标题，并更改Static Text的显示
	CString title = m_PropList.GetItemText(4, 1);
	SetDlgItemText(IDC_Title_STATIC, title);

	*pResult = 0;
}
