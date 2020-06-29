// SpectralViewDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "2020RS.h"
#include "SpectralViewDlg.h"
#include "afxdialogex.h"


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
}


BEGIN_MESSAGE_MAP(SpectralViewDlg, CDialog)
END_MESSAGE_MAP()


// SpectralViewDlg 消息处理程序


BOOL SpectralViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
