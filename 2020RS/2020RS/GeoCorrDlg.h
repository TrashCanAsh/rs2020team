#pragma once
#include "Img_kele.h"
#include "GeoCorrImg.h"
#include<vector>
#include"ControlPT.h"
using namespace std;
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
	static Img_kele BaseImg;
	static Img_kele WrapImg;
	//
	//static GeoCorrImg dlg11;
	//static GeoCorrImg dlg12;
	//static GeoCorrImg dlg13;
	////
	//static GeoCorrImg dlg21;
	//static GeoCorrImg dlg22;
	//static GeoCorrImg dlg23;
	//
	afx_msg void OnEnChangeWrapMfceditbrowse();
	afx_msg void OnBnClickedGeobeginButton();
	CListCtrl m_GCPsList;


	//点击listcontrol的指令
	int now_click_GCP = -1; //默认值为 - 1.表示没有点击任何gcp
	vector<GcpStruct> GcpDate;//所有控制点的数据

	afx_msg void OnBnClickedAddpointButton();//添加控制点
	afx_msg void OnBnClickedDelpointButton();//删除控制点
	afx_msg void OnNMClickList3(NMHDR *pNMHDR, LRESULT *pResult);//点击获取listcontrol的位置
	afx_msg void OnBnClickedWrapedoutButton();
	afx_msg void OnBnClickedDelpointButton2();
	afx_msg void OnBnClickedDelpointButton3();
};
