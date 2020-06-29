// MainDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "2020RS.h"
#include "MainDlg.h"
#include "afxdialogex.h"


// MainDlg 对话框

IMPLEMENT_DYNAMIC(MainDlg, CDialog)

MainDlg::MainDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MY2020RS_DIALOG, pParent)
{

}

MainDlg::~MainDlg()
{
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MainDlg, CDialog)
END_MESSAGE_MAP()


// MainDlg 消息处理程序
