
// 2020RSDlg.h: 头文件
//
#include "Img_kele.h" 
#pragma once

#include <iostream>
using namespace std;

// CMy2020RSDlg 对话框
class CMy2020RSDlg : public CDialog
{
// 构造
public:
	CMy2020RSDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY2020RS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnClkSpecview();

	bool OpenConsole();

	//gsyd
	CListCtrl m_list;
	CTreeCtrl m_tree;
	CImageList m_ImageList;  //图像列表(相同大小图像集合) 
	HTREEITEM m_hRoot;       //句柄 CTreeCtrl的根结点"我的电脑"
	void GetLogicalDrives(HTREEITEM hParent);  //获取驱动
	void GetDriveDir(HTREEITEM hParent);       //获取子项
	void AddSubDir(HTREEITEM hParent);         //添加子目录
	CString GetFullPath(HTREEITEM hCurrent);   //获取树项目全根路径
	afx_msg void OnItemexpandedTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
	//
	

	CMap <CString, LPCTSTR, CString, LPCTSTR>m_fileList;
	afx_msg void OnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	//gsyd
	afx_msg void OnGeometric();
	afx_msg void OnDensityslice();

	//显示影像部分

	 
	afx_msg void OnCanopy();
	afx_msg void On32779();
	afx_msg void On32781();
};
