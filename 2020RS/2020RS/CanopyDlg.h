#pragma once
#define MAX_DAT 100
#include"Img_kele.h"

// CanopyDlg 对话框


class CanopyDlg : public CDialog
{
	DECLARE_DYNAMIC(CanopyDlg)

public:
	CanopyDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CanopyDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Canopy_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ClassificationList;
	int listSeleted;
	int classCount;
	Img_kele copyImg;
	afx_msg void OnBnClickedModifyButton();
	afx_msg void OnBnClickedShowButton();
	//类名列表
	CString name[40];
	//颜色列表
	COLORREF colorlib[40];
	//初始化
	void init();

	//t-锁定修改栏/f-解锁修改栏
	void ModifyLock(BOOL flag);
	//显示列表
	void ShowList();
	afx_msg void OnNMClickClassificationlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusClassnumEdit();
	CMFCColorButton m_colorbutton;
	afx_msg void OnNMCustomdrawClassificationlist(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CProgressCtrl m_Canopy_PROGESS;
	afx_msg void OnBnClickedModifyButton2();

	//分类
	Img_kele BMP_Class(CString path);
	//显示
	void BMP_DisplayInScreen(Img_kele copyImg);
	//保存
	void BMP_Save();
};
