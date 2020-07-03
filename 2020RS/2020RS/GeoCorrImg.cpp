﻿// GeoCorrImg.cpp: 实现文件
//

#include "stdafx.h"
#include "2020RS.h"
#include "GeoCorrImg.h"
#include "afxdialogex.h"


// GeoCorrImg 对话框

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
		this->MoveWindow((iNum - 1) * 500, 20, 400, 400);
	}
	else if (iFlag == 2)
	{
		this->MoveWindow((iNum - 1) * 500, 440, 300, 300);
	}
	else if (iFlag == 3)
	{
		this->MoveWindow((iNum - 1) * 500 + 320, 440, 300, 300);
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
		pWnd->MoveWindow(x , y + 380, 300, 300);
		title.Format(_T("dialog%d%d"), iNum, 3);
		pWnd = CWnd::FindWindow(NULL, title);
		if (pWnd == NULL)
			return;
		pWnd->MoveWindow(x + 320, y + 380, 300, 300);
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
		//释放CDC资源
		ReleaseDC(pDC);
	}
	CDialog::OnLButtonDown(nFlags, point);
}
