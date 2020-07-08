// GeoCorrImg.cpp: 实现文件
//

#include "stdafx.h"
#include "2020RS.h"
#include "GeoCorrImg.h"
#include "afxdialogex.h"
#include"img_kele.h"
#include"GeoCorrDlg.h"
#include"matrix.h"

//全局变量6个小窗口
extern GeoCorrImg dlg11;
extern GeoCorrImg dlg12;
extern GeoCorrImg dlg13;
extern GeoCorrImg dlg21;
extern GeoCorrImg dlg22;
extern GeoCorrImg dlg23;

//初始化静态变量
CPoint  GeoCorrImg::Click_dlg2;
CPoint  GeoCorrImg::Click_dlg1;
CPoint  GeoCorrImg::Last_Click_dlg3;

// GeoCorrImg 对话框
IMPLEMENT_DYNAMIC(GeoCorrImg, CDialog)

GeoCorrImg::GeoCorrImg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_GeoCorrImg_DIALOG, pParent)
{
	iNum = -1;
	iFlag = -1;
	oldPoint.x = -1;
	oldPoint.y = -1;

	Last_Click_dlg3.x = -1;
	Last_Click_dlg3.y = -1;

	//初始化fac1、fac2、fac3
	fac1 = 4;
	fac2 = 0.25;
	fac3 = 0.25;
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
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// GeoCorrImg 消息处理程序


BOOL GeoCorrImg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//::SetWindowPos(this->m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE);
	CString title;
	title.Format(_T("dialog%d%d"), iNum, iFlag);//在标题栏动态显示Id的值
	this->SetWindowText(title);
	if (iFlag == 1)
	{
		this->MoveWindow((iNum - 1) * 800, 20, 100 / fac2 + 16, 100 / fac2 + 38);//+18考虑对话框的边框，+47表示考虑标题栏
		CRect crect;
	}
	else if (iFlag == 2)
	{

		/*int ww = GeoCorrDlg::BaseImg.ImgParaInCls.ImgW;
		int hh = GeoCorrDlg::BaseImg.ImgParaInCls.ImgH;
		int xxxxxx = 1;*/
		//问题，初始化在读取数据之前，无法根据图像大小进行显示
		this->MoveWindow((iNum - 1) * 800, 440,1280/fac1+16, 1024/fac1+38);//+18考虑对话框的边框，+47表示考虑标题栏

	}
	else if (iFlag == 3)
	{
		this->MoveWindow((iNum - 1) *800 + 400, 440, 100 / fac2 + 16, 100 / fac2 + 38);//+18考虑对话框的边框，+47表示考虑标题栏
		
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
		int ww = GeoCorrDlg::BaseImg.ImgParaInCls.ImgW;
		int hh = GeoCorrDlg::BaseImg.ImgParaInCls.ImgH;
		pWnd->MoveWindow(x , y + 420, ww / fac1 + 16, hh / fac1 + 38);
		title.Format(_T("dialog%d%d"), iNum, 3);
		pWnd = CWnd::FindWindow(NULL, title);
		if (pWnd == NULL)
			return;
		pWnd->MoveWindow(x + 320, y + 420, 100 / fac2 + 16, 100 / fac2 + 38);
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
	
			hWnd = ::FindWindow(NULL, "dialog13");
			hdc = ::GetDC(hWnd);
			::GetClientRect(hWnd, &rect2);
			GeoCorrDlg::BaseImg.DisplaySquareImgColor(&hdc,100/fac3, 100 / fac3, Click_dlg2.x - 50, Click_dlg2.y-50, point.x - 50, point.y -50, fac1, fac2, fac3);

			//消除上一次的十字线
			dlg13.oldPoint.x = -1;
			dlg13.oldPoint.y = -1;
		}
		else if (iNum == 2)
		{

			//点击后，在dlg1显示新的区域
			hWnd = ::FindWindow(NULL, "dialog22");
			hdc = ::GetDC(hWnd);
			::GetClientRect(hWnd, &rect2);
			int dlg2height = rect2.Height();

			hWnd = ::FindWindow(NULL, "dialog23");
			hdc = ::GetDC(hWnd);
			::GetClientRect(hWnd, &rect2);
			
			GeoCorrDlg::WrapImg.DisplaySquareImgColor(&hdc, 100 / fac3, 100 / fac3, Click_dlg2.x - 50, Click_dlg2.y - 50, point.x - 50,point.y - 50, fac1, fac2, fac3);

			//消除上一次的十字线
			dlg23.oldPoint.x = -1;
			dlg23.oldPoint.y = -1;
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
	
			hWnd = ::FindWindow(NULL, "dialog11");
			hdc = ::GetDC(hWnd);
			::GetClientRect(hWnd, &rect2);
			GeoCorrDlg::BaseImg.DisplaySquareImgColor(&hdc, 100 / fac2, 100 / fac2,point.x - 50, (point.y-50), fac1, fac2);
			
			//消除上一次的方框
			dlg11.oldPoint.x = -1;
			dlg11.oldPoint.y = -1;
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
	
			hWnd = ::FindWindow(NULL, "dialog21");
			hdc = ::GetDC(hWnd);
			::GetClientRect(hWnd, &rect2);
			GeoCorrDlg::WrapImg.DisplaySquareImgColor(&hdc, 100 / fac2, 100 / fac2, point.x - 50, point.y - 50, fac1, fac2);

			//消除上一次的方框
			dlg21.oldPoint.x = -1;
			dlg21.oldPoint.y = -1;
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
		Last_Click_dlg3 = point;

		/*By_WYY*/
		//点击第三个窗口后实时显示控制点坐标

		HWND hWnd;
		hWnd = ::FindWindow(NULL, "几何校正");
		CWnd* m_parentDLG;
		m_parentDLG = FromHandle(hWnd);
		CString str_BaseX;
		CString str_BaseY;
		CString str_WrapX;
		CString str_WrapY;
		if (iNum == 1)
		{
			double X = point.x * fac1 * fac2 * fac3 + fac1 * ((Click_dlg2.x-50) + fac2 * (Click_dlg1.x-50));
			double Y = point.y * fac1 * fac2 * fac3 + fac1 * ((Click_dlg2.y-50) + fac2 * (Click_dlg1.y-50));

			//仅保留两档数据0.0 和0.5
			X = floor(X * 10 + 0.5) / 10; //四舍五入，保留一位
			//仅保留0.0和0.5
			if (X - floor(X) > 0.5)
				X = floor(X) + 0.5;
			else
				X = floor(X);
			Y = floor(Y * 10 + 0.5) / 10;//四舍五入，保留一位
			//仅保留0.0和0.5
			if (Y - floor(Y) > 0.5)
				Y = floor(Y) + 0.5;
			else
				Y = floor(Y);
			str_BaseX.Format("%.1lf", X);
			str_BaseY.Format("%.1lf", Y);
			m_parentDLG->SetDlgItemText(IDC_BaseX_EDIT, str_BaseX);
			m_parentDLG->SetDlgItemText(IDC_BaseY_EDIT, str_BaseY);
		}
		else
		{
			double X = point.x * fac1 * fac2 * fac3 + fac1 * ((Click_dlg2.x - 50) + fac2 * (Click_dlg1.x - 50));
			double Y = point.y * fac1 * fac2 * fac3 + fac1 * ((Click_dlg2.y - 50) + fac2 * (Click_dlg1.y - 50));
			X = floor(X * 10 + 0.5) / 10; //四舍五入，保留一位
			//仅保留0.0和0.5
			if (X - floor(X) > 0.5)
				X = floor(X) + 0.5;
			else
				X = floor(X);
			Y = floor(Y * 10 + 0.5) / 10;//四舍五入，保留一位
			//仅保留0.0和0.5
			if (Y - floor(Y ) > 0.5)
				Y = floor(Y) + 0.5;
			else
				Y = floor(Y);
			str_WrapX.Format("%.1lf", X);
			str_WrapY.Format("%.1lf", Y);
			m_parentDLG->SetDlgItemText(IDC_WrapX_EDIT, str_WrapX);
			m_parentDLG->SetDlgItemText(IDC_WrapY_EDIT, str_WrapY);
		}
		/*By_WYY*/
		//释放CDC资源
		ReleaseDC(pDC);
	}
	CDialog::OnLButtonDown(nFlags, point);
}

//实现点击dlg11和dlg21联动删除其他两个窗口
void GeoCorrImg::OnClose()
{
	CString str;
	HWND hWnd;
	this->GetWindowText(str);
	if (str=="dialog11")
	{
		CWnd *pp;
		//点击后，在dlg3显示新的区域
		hWnd = ::FindWindow(NULL, "dialog12");
		pp = FromHandle(hWnd);
		if (pp)
			pp->ShowWindow(SW_HIDE);

		CWnd *pp2;
		hWnd = ::FindWindow(NULL, "dialog13");
		pp2 = FromHandle(hWnd);
		if (pp2)
			pp2->ShowWindow(SW_HIDE);
		ShowWindow(SW_HIDE);
	}
	else if(str=="dialog21")
	{
		CWnd *pp;
		hWnd = ::FindWindow(NULL, "dialog22");
		pp = FromHandle(hWnd);
		if (pp)
			pp->ShowWindow(SW_HIDE);

		CWnd *pp2;
		hWnd = ::FindWindow(NULL, "dialog23");
		pp2 = FromHandle(hWnd);
		if (pp)
			pp2->ShowWindow(SW_HIDE);

		ShowWindow(SW_HIDE);
	}
	else
		ShowWindow(SW_HIDE);
}
