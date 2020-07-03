#pragma once
#include "Img_kele.h"
#include "GeoCorrImg.h"

// GeoCorrDlg 对话框

class GeoCorrDlg : public CDialog
{
	DECLARE_DYNAMIC(GeoCorrDlg)

public:
	GeoCorrDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~GeoCorrDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GeoCorr_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeBaseMfceditbrowse();
	virtual BOOL OnInitDialog();
	CListCtrl m_BaseInfoList;
	CListCtrl m_WrapInfoList;

	//或许在这里实例类对象
	Img_kele BaseImg;
	Img_kele WrapImg;
	//
	GeoCorrImg dlg11;
	GeoCorrImg dlg12;
	GeoCorrImg dlg13;
	//
	GeoCorrImg dlg21;
	GeoCorrImg dlg22;
	GeoCorrImg dlg23;
	//
	afx_msg void OnEnChangeWrapMfceditbrowse();
	afx_msg void OnBnClickedGeobeginButton();
};
