#pragma once
#define MAX_DAT   100 
#include "Img_kele.h"
#include"ReadTIF.h"
#include<cstring>
#include<string>
#include"io.h" //实现遍历文件夹
using namespace std;

// DensitySliceDlg 对话框

class DensitySliceDlg : public CDialog
{
	DECLARE_DYNAMIC(DensitySliceDlg)

public:
	DensitySliceDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DensitySliceDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DensitySliceDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_DSList;
	CListBox m_ColorLibList;
	int flag;
	//
	//遍历色彩库
	bool TraverseFiles(string inPath);
	COLORREF colorlib[256];
	BOOL ReadColorLib(CString FilePath);
	//字符打断
	char *SS_Dat[MAX_DAT + 1];
	int SsToStr60(char *str, char *s_dat[]);

	Img_kele copyImg1;
	ReadTIF copyImg2;



	//分级显示
	void show_list(COLORREF* colorlibhead,int degree);
	COLORREF GetColorLevel(UCHAR DN_Date,int listNum, double fac1, int *LevelList);
	//
	BOOL DrawColorLib(int PicID, COLORREF* colorlibhead, int flag);
	afx_msg void OnBnClickedReverseButton();
	afx_msg void OnPaint();
	afx_msg void OnEnKillfocusLevelEdit();
	afx_msg void OnBnClickedOutputButton();
	afx_msg void OnNMCustomdrawDensityslicelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLbnDblclkColorliblist();
	CComboBox m_SelectBand_COMBO;
	CProgressCtrl m_SLICE_PROGRESS;
	Img_kele Read(Img_kele MainImg);
	ReadTIF Read2(ReadTIF m_TIFIMG);
	void Save(Img_kele copyImg);
	void Save2(ReadTIF copyImg);
};
