// CanopyDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "2020RS.h"
#include "CanopyDlg.h"
#include "afxdialogex.h"
#include"ReadTIF.h"

extern Img_kele MainImg;
// CanopyDlg 对话框

IMPLEMENT_DYNAMIC(CanopyDlg, CDialog)

CanopyDlg::CanopyDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Canopy_DIALOG, pParent)
{

}

CanopyDlg::~CanopyDlg()
{
}

void CanopyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ClassificationList, m_ClassificationList);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_colorbutton);
}


BEGIN_MESSAGE_MAP(CanopyDlg, CDialog)
	ON_BN_CLICKED(IDC_Modify_BUTTON, &CanopyDlg::OnBnClickedModifyButton)
	ON_BN_CLICKED(IDC_Show_BUTTON, &CanopyDlg::OnBnClickedShowButton)
	ON_NOTIFY(NM_CLICK, IDC_ClassificationList, &CanopyDlg::OnNMClickClassificationlist)
	ON_EN_KILLFOCUS(IDC_ClassNum_EDIT, &CanopyDlg::OnEnKillfocusClassnumEdit)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ClassificationList, &CanopyDlg::OnNMCustomdrawClassificationlist)
END_MESSAGE_MAP()


// CanopyDlg 消息处理程序


BOOL CanopyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化分类列表
	CRect rect;
	m_ClassificationList.GetClientRect(&rect);
	m_ClassificationList.SetExtendedStyle(m_ClassificationList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ClassificationList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, rect.Width() / 3, 0);
	m_ClassificationList.InsertColumn(1, _T("类名"), LVCFMT_CENTER, rect.Width() / 3, 1);
	m_ClassificationList.InsertColumn(2, _T("颜色"), LVCFMT_CENTER, rect.Width() / 3, 2);
	//文本框初始化
	SetDlgItemText(IDC_ClassNum_EDIT, _T("10"));
	classCount = 10;
	//设置颜色
	init();
	//显示列表
	ShowList();
	//锁定修改栏
	ModifyLock(true);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CanopyDlg::OnBnClickedModifyButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CString classname;
	COLORREF cc = CanopyDlg::m_colorbutton.GetColor();
	colorlib[listSeleted] = cc;
	/*HWND hWnd;
	hWnd = GetDlgItem(IDC_ClassificationList)->GetSafeHwnd();*/
	//::SendMessage(hWnd, NM_CUSTOMDRAW, NULL, NULL);
	GetDlgItemText(IDC_ClassName_EDIT, classname);
	//m_ClassificationList.SetItemText(listSeleted, 1, classname);
	name[listSeleted] = classname;
	m_ClassificationList.DeleteAllItems();
	ShowList();
	//锁定修改栏
	ModifyLock(true);
}


void CanopyDlg::OnBnClickedShowButton()
{
	//开始分类
	MainImg.CreateClassifySpace();

	//从控件获取参数
	MainImg.Canopy(40, 30,15);

	//显示分类结果
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
	BOOL flag = MainImg.DisplayImgGray(&hdc, rect.Width() - rectCtrl.right - 25, rect.Height() - rectCtrl.top - 10, rectCtrl.right + 10, rectCtrl.top, MainImg.ImgParaInCls.ImgW, MainImg.ImgParaInCls.ImgH, 0, 0,MainImg.ImgParaInCls.Classify);

	if (flag == false)
	{
		MessageBox("wrong");
	}
	
	//保存文件
	CFileDialog Dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Tag Image Files (*.TIF)||");
	CString WrirtePath;
	CString FileClass;
	if (Dlg.DoModal() == IDOK)
	{

		WrirtePath = Dlg.GetPathName();
	}
	// TODO: 在此添加控件通知处理程序代码
	if (Dlg.m_ofn.nFilterIndex == 1)
	{
		//用户选择了BMP格式
		CString strClass = ".tif";
		WrirtePath = WrirtePath + strClass;
	}
	else
	{
		MessageBox("只能保存为TIF文件呦");
		return;
	}
	//CString ReadPath;
	//CWnd *cWnd;
	//hWnd;
	//hWnd = ::FindWindow(NULL, "主窗口");
	//cWnd = FromHandle(hWnd);
	//cWnd->GetDlgItem(IDC_EDIT1)->GetWindowText(ReadPath);
	//ReadTIF readtif;
	//MessageBox(ReadPath);
	//readtif.TIFCanopy(ReadPath, WrirtePath, 5000, 4500);
	// TODO: 在此添加控件通知处理程序代码
	
}

void CanopyDlg::init()
{
	//设置默认颜色From Envi
	colorlib[0] = RGB(255, 0, 0);
	colorlib[1] = RGB(0, 255, 0);
	colorlib[2] = RGB(0, 0, 255);
	colorlib[3] = RGB(255, 255, 0);
	colorlib[4] = RGB(0, 255, 255);
	colorlib[5] = RGB(255, 0, 255);
	colorlib[6] = RGB(176, 48, 96);
	colorlib[7] = RGB(46, 139, 87);
	colorlib[8] = RGB(160, 32, 240);
	colorlib[9] = RGB(255, 127, 80);
	colorlib[10] = RGB(127, 255, 212);
	colorlib[11] = RGB(218, 112, 214);
	colorlib[12] = RGB(160, 82, 45);
	colorlib[13] = RGB(127, 255, 0);
	colorlib[14] = RGB(216, 191, 216);
	colorlib[15] = RGB(238, 0, 0);
	colorlib[16] = RGB(205, 0, 0);
	colorlib[17] = RGB(139, 0, 0);
	colorlib[18] = RGB(0, 238, 0);
	colorlib[19] = RGB(0, 205, 0);
	colorlib[20] = RGB(0, 139, 0);
	colorlib[21] = RGB(0, 0, 238);
	colorlib[22] = RGB(0, 0, 205);
	colorlib[23] = RGB(0, 0, 139);
	//设置默认类名
	for (int i = 0; i < 40; i++)
	{
		CString str;
		str.Format("类%d", i+1);
		name[i] = str;
	}
	
}

void CanopyDlg::ModifyLock(BOOL flag)
{
	if (flag == true)
	{
		GetDlgItem(IDC_ClassName_EDIT)->EnableWindow(false);
		GetDlgItem(IDC_MFCCOLORBUTTON1)->EnableWindow(false);
		GetDlgItem(IDC_Modify_BUTTON)->EnableWindow(false);
	}
	else
	{
		GetDlgItem(IDC_ClassName_EDIT)->EnableWindow(true);
		GetDlgItem(IDC_MFCCOLORBUTTON1)->EnableWindow(true);
		GetDlgItem(IDC_Modify_BUTTON)->EnableWindow(true);
	}
}


void CanopyDlg::ShowList()
{
	for (int i = 0; i < classCount; i++)
	{
		CString str;
		str.Format("%d", i + 1);
		m_ClassificationList.InsertItem(i, str);
		m_ClassificationList.SetItemText(i, 1, name[i]);
		m_ClassificationList.SetItemText(i, 2, "");
	}
}

void CanopyDlg::OnNMClickClassificationlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (-1 != pNMItemActivate->iItem)        // 如果iItem不是-1，就说明有列表项被选择   	
	{
		listSeleted = pNMItemActivate->iItem;
		//修改栏显示选中信息
		SetDlgItemText(IDC_ClassName_EDIT, m_ClassificationList.GetItemText(listSeleted, 1));
		CanopyDlg::m_colorbutton.SetColor(colorlib[listSeleted]);
		//解锁修改栏
		ModifyLock(false);
	}
	*pResult = 0;
}


void CanopyDlg::OnEnKillfocusClassnumEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CString classnum;
	GetDlgItemText(IDC_ClassNum_EDIT, classnum);
	SetDlgItemText(IDC_ClassNum_EDIT, "");
	classCount = atoi(classnum);
	m_ClassificationList.DeleteAllItems();
	ShowList();
	//锁定修改栏
	ModifyLock(true);
}



void CanopyDlg::OnNMCustomdrawClassificationlist(NMHDR *pNMHDR, LRESULT *pResult)
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
		if (pLVCD->iSubItem == 2)
		{
			if (nItem == 0)
			{
				//cout << "绘制绘制"<<pLVCD->iSubItem << "," << nItem << endl;
				crText = RGB(0, 0, 0);
				crBkgnd = colorlib[nItem];
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
		if (pLVCD->iSubItem == 2)
		{
			if (nItem >= 0)
			{
				crText = RGB(0, 0, 0);
				crBkgnd = colorlib[nItem];
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
		if (pLVCD->iSubItem == 2)
		{
			if (nItem >= 0)
			{
				crText = RGB(0, 0, 0);
				crBkgnd = colorlib[nItem];
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


BOOL CanopyDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		//UpdateData(TRUE);
		SendDlgItemMessage(IDC_ClassNum_EDIT, WM_KILLFOCUS, 0, 0);
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}
