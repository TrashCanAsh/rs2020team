// GeoCorrImg.cpp: 实现文件
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
}

GeoCorrImg::GeoCorrImg(int num, int flag, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_GeoCorrImg_DIALOG, pParent)
{
	iNum = num;
	iFlag = flag;
}

GeoCorrImg::~GeoCorrImg()
{
}

void GeoCorrImg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GeoCorrImg, CDialog)
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
		this->MoveWindow((iNum - 1) * 600, 20, 400, 600);
	}
	else if (iFlag == 2)
	{
		this->MoveWindow((iNum - 1) * 600, 620, 300, 300);
	}
	else if (iFlag == 3)
	{
		this->MoveWindow((iNum - 1) * 600 + 320, 620, 300, 300);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
