// GeoCorrImg.cpp: 实现文件
//

#include "stdafx.h"
#include "2020RS.h"
#include "GeoCorrImg.h"
#include "afxdialogex.h"
#include"img_kele.h"
#include"GeoCorrDlg.h"
#include"matrix.h"


// GeoCorrImg 对话框
CPoint  GeoCorrImg::Click_dlg2;
CPoint  GeoCorrImg::Click_dlg1;
IMPLEMENT_DYNAMIC(GeoCorrImg, CDialog)

GeoCorrImg::GeoCorrImg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_GeoCorrImg_DIALOG, pParent)
{
	iNum = -1;
	iFlag = -1;
	oldPoint.x = -1;
	oldPoint.y = -1;
}

GeoCorrImg::GeoCorrImg(int num, int flag, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_GeoCorrImg_DIALOG, pParent)
{
	iNum = num;
	iFlag = flag;
	oldPoint.x = -1;
	oldPoint.y = -1;
}

GeoCorrImg::~GeoCorrImg()
{
}

void GeoCorrImg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GeoCorrImg, CDialog)
	ON_WM_MOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// GeoCorrImg 消息处理程序


BOOL GeoCorrImg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString title;
	title.Format(_T("dialog%d%d"), iNum, iFlag);//在标题栏动态显示Id的值
	this->SetWindowText(title);
	if (iFlag == 1)
	{
		this->MoveWindow((iNum - 1) * 1000, 20, 400, 400);
	
	}
	else if (iFlag == 2)
	{
		//int right = GetSystemMetrics(SM_CYCAPTION);
		
		this->MoveWindow((iNum - 1) * 1000, 440, 1280/2, 1024/2);
		
	}
	else if (iFlag == 3)
	{
		this->MoveWindow((iNum - 1) * 1000 + 640, 440, 400, 400);
		
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void GeoCorrImg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);
	if (iFlag == 1)
	{
		CString title;
		CWnd* pWnd;
		title.Format(_T("dialog%d%d"), iNum, 2);
		pWnd = CWnd::FindWindow(NULL, title);
		if (pWnd == NULL)
			return;
		pWnd->MoveWindow(x , y + 420, 300, 300);
		title.Format(_T("dialog%d%d"), iNum, 3);
		pWnd = CWnd::FindWindow(NULL, title);
		if (pWnd == NULL)
			return;
		pWnd->MoveWindow(x + 320, y + 420, 300, 300);
	}
	// TODO: 在此处添加消息处理程序代码
}


void GeoCorrImg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (iFlag == 1)
	{
		CDC* pDC;
		CRect rect;
		CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
		pDC = this->GetDC();
		this->GetClientRect(rect);
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
		{
			point.x = 50;
		}
		if (point.x + 50 > rect.right)
		{
			point.x = rect.right - 50;
		}
		if (point.y < 50)
		{
			point.y = 50;
		}
		if (point.y + 50 > rect.bottom)
		{
			point.y = rect.bottom - 50;
		}
		//
		pDC->MoveTo(point.x - 50, point.y + 50);
		pDC->LineTo(point.x + 50, point.y + 50);
		pDC->MoveTo(point.x + 50, point.y + 50);
		pDC->LineTo(point.x + 50, point.y - 50);
		pDC->MoveTo(point.x + 50, point.y - 50);
		pDC->LineTo(point.x - 50, point.y - 50);
		pDC->MoveTo(point.x - 50, point.y - 50);
		pDC->LineTo(point.x - 50, point.y + 50);
		//
		oldPoint = point;

		//记录点的坐标
		Click_dlg1 = point;
		
		//
		/*By_WYY*/
		HWND hWnd;
		HDC hdc;
		CRect rect2;
		if (iNum == 1)
		{
			//点击后，在dlg3显示新的区域
			hWnd = ::FindWindow(NULL, "dialog12");
			hdc = ::GetDC(hWnd);
			::GetClientRect(hWnd, &rect2);
			int dlg2height = rect2.Height();
			double fac1 = max(1.0*GeoCorrDlg::BaseImg.ImgParaInCls.ImgW / rect2.Width(), 1.0*GeoCorrDlg::BaseImg.ImgParaInCls.ImgH / rect2.Height());
			
			//double fac2 = 1.0 / 400 * 100;
			//double fac3 = 1.0 / 400 * 100;

			double fac2 = 1.0 / 400 * 100;
			double fac3 = 1.0 / 400 * 100;

			hWnd = ::FindWindow(NULL, "dialog13");
			hdc = ::GetDC(hWnd);
			::GetClientRect(hWnd, &rect2);
			GeoCorrDlg::BaseImg.DisplaySquareImgColor(&hdc, rect2.Width(), rect2.Height(), Click_dlg2.x - 50, Click_dlg2.y-50, point.x - 50, point.y -50, fac1, fac2, fac3);
			
			//消除上一次的十字线
			GeoCorrDlg::dlg13.oldPoint.x = -1;
			GeoCorrDlg::dlg13.oldPoint.y = -1;
		}
		else if (iNum == 2)
		{

			//点击后，在dlg1显示新的区域
			hWnd = ::FindWindow(NULL, "dialog22");
			hdc = ::GetDC(hWnd);
			::GetClientRect(hWnd, &rect2);
			int dlg2height = rect2.Height();
			double fac1 = max(1.0*GeoCorrDlg::WrapImg.ImgParaInCls.ImgW / rect2.Width(), 1.0*GeoCorrDlg::WrapImg.ImgParaInCls.ImgH / rect2.Height());
			
			double fac2 = 1.0 / 400 * 100;
			double fac3 = 1.0 / 400 * 100;
			hWnd = ::FindWindow(NULL, "dialog23");
			hdc = ::GetDC(hWnd);
			::GetClientRect(hWnd, &rect2);
			
			GeoCorrDlg::WrapImg.DisplaySquareImgColor(&hdc, rect2.Width(), rect2.Height(), Click_dlg2.x - 50, Click_dlg2.y - 50, point.x - 50,point.y - 50, fac1, fac2, fac3);

			//消除上一次的十字线
			GeoCorrDlg::dlg23.oldPoint.x = -1;
			GeoCorrDlg::dlg23.oldPoint.y = -1;
		}

		
		//释放CDC资源
		ReleaseDC(pDC);
	}
	else if (iFlag == 2)
	{
		CDC* pDC;
		CRect rect;
		CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
		pDC = this->GetDC();
		this->GetClientRect(rect);
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
		{
			point.x = 50;
		}
		if (point.x + 50 > rect.right)
		{
			point.x = rect.right - 50;
		}
		if (point.y < 50)
		{
			point.y = 50;
		}
		if (point.y + 50 > rect.bottom)
		{
			point.y = rect.bottom - 50;
		}
		//
		pDC->MoveTo(point.x - 50, point.y + 50);
		pDC->LineTo(point.x + 50, point.y + 50);
		pDC->MoveTo(point.x + 50, point.y + 50);
		pDC->LineTo(point.x + 50, point.y - 50);
		pDC->MoveTo(point.x + 50, point.y - 50);
		pDC->LineTo(point.x - 50, point.y - 50);
		pDC->MoveTo(point.x - 50, point.y - 50);
		pDC->LineTo(point.x - 50, point.y + 50);
		//
		oldPoint = point;

		Click_dlg2 = point;
		//保存点击dlg2的方框
		/*By_WYY*/
		if (iNum == 1)
		{
			//点击后，在dlg1显示新的区域
			HWND hWnd;
			HDC hdc;
			CRect rect2;
			hWnd = ::FindWindow(NULL, "dialog12");
			hdc = ::GetDC(hWnd);
			::GetClientRect(hWnd, &rect2);
			double fac1 = max(1.0*GeoCorrDlg::BaseImg.ImgParaInCls.ImgW / rect2.Width(), 1.0*GeoCorrDlg::BaseImg.ImgParaInCls.ImgH / rect2.Height());
			//double fac1 = max(1.0*GeoCorrDlg::BaseImg.ImgParaInCls.ImgW / 400, 1.0*GeoCorrDlg::BaseImg.ImgParaInCls.ImgH / 400);

			int xxxxx = 1;

			//double fac2 = 1.0 / 400 * 100;
			double fac2 = 1.0 / 400 * 100;
			hWnd = ::FindWindow(NULL, "dialog11");
			hdc = ::GetDC(hWnd);
			::GetClientRect(hWnd, &rect2);
			GeoCorrDlg::BaseImg.DisplaySquareImgColor(&hdc, rect2.Width(), rect2.Height(),point.x - 50, (point.y-50), fac1, fac2);
			//GeoCorrDlg::BaseImg.DisplaySquareImgColor(&hdc, 400, 400, point.x - 50, 400 - (point.y + 50), fac1, fac2);
			//消除上一次的方框
			GeoCorrDlg::dlg11.oldPoint.x = -1;
			GeoCorrDlg::dlg11.oldPoint.y = -1;
			int xxxxxxx = 1;
		}
		else if (iNum == 2)
		{

			//点击后，在dlg1显示新的区域
			HWND hWnd;
			HDC hdc;
			CRect rect2;
			hWnd = ::FindWindow(NULL, "dialog22");
			hdc = ::GetDC(hWnd);
			::GetClientRect(hWnd, &rect2);
			double fac1 = max(1.0*GeoCorrDlg::WrapImg.ImgParaInCls.ImgW / rect2.Width(), 1.0*GeoCorrDlg::WrapImg.ImgParaInCls.ImgH / rect2.Height());

			double fac2 = 1.0 / 400 * 100;
			hWnd = ::FindWindow(NULL, "dialog21");
			hdc = ::GetDC(hWnd);
			::GetClientRect(hWnd, &rect2);
			GeoCorrDlg::WrapImg.DisplaySquareImgColor(&hdc, rect2.Width(), rect2.Height(), point.x - 50, point.y - 50, fac1, fac2);

			//消除上一次的方框
			GeoCorrDlg::dlg21.oldPoint.x = -1;
			GeoCorrDlg::dlg21.oldPoint.y = -1;
		}
		//释放CDC资源
		ReleaseDC(pDC);
	}
	else if (iFlag == 3)
	{
	CDC* pDC;
	CRect rect;
	CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
	pDC = this->GetDC();
	this->GetClientRect(rect);
	//设置绘图格式为反色绘图
	int nRopMode = pDC->SetROP2(R2_NOTXORPEN);
	//擦除上次绘制
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
	oldPoint = point;

	/*By_WYY*/
	//点击第三个窗口后实时显示控制点坐标
	CWnd *m_parentDLG = GetOwner();
	CString str_BaseX;
	CString str_BaseY;
	CString str_WrapX;
	CString str_WrapY;
	if (iNum == 1)
	{
		
		
		double X = point.x * 2 * 0.25*0.25 + 2*((Click_dlg2.x-50) + 0.25*(Click_dlg1.x-50));
		double Y = point.y * 2 * 0.25*0.25 + 2*((Click_dlg2.y-50) + 0.25*(Click_dlg1.y-50));
		str_BaseX.Format("%lf", X);
		str_BaseY.Format("%lf", Y);
		m_parentDLG->SetDlgItemText(IDC_BaseX_EDIT, str_BaseX);
		m_parentDLG->SetDlgItemText(IDC_BaseY_EDIT, str_BaseY);
	}
	else
	{
		double X = point.x * 2 * 0.25*0.25 + 2 * ((Click_dlg2.x - 50) + 0.25*(Click_dlg1.x - 50));
		double Y = point.y * 2 * 0.25*0.25 + 2 * ((Click_dlg2.y - 50) + 0.25*(Click_dlg1.y - 50));
		str_WrapX.Format("%lf", X);
		str_WrapY.Format("%lf", Y);
		m_parentDLG->SetDlgItemText(IDC_WrapX_EDIT, str_WrapX);
		m_parentDLG->SetDlgItemText(IDC_WrapY_EDIT, str_WrapY);
	}
	/*By_WYY*/
	//释放CDC资源
	ReleaseDC(pDC);
	}
	CDialog::OnLButtonDown(nFlags, point);
}
