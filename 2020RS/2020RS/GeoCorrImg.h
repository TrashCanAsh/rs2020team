#pragma once


// GeoCorrImg 对话框

class GeoCorrImg : public CDialog
{
	DECLARE_DYNAMIC(GeoCorrImg)

public:
	GeoCorrImg(CWnd* pParent = nullptr);   // 标准构造函数
	GeoCorrImg(int num, int flag, CWnd* pParent = nullptr);
	virtual ~GeoCorrImg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GeoCorrImg_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CPoint oldPoint;
	int iNum;//1代表baseimg，2表示wrapimg
	int iFlag;//1、2、3分别表示窗口

	double fac1;//原影像到dlg2的放大倍数
	double fac2;//dlg2到dlg1的放大倍数
	double fac3;//dlg2到dlg3的放大倍数

	virtual BOOL OnInitDialog();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	static CPoint Click_dlg2;//点击2窗口的坐标
	static CPoint Click_dlg1;//点击1窗口的坐标
	static CPoint Last_Click_dlg3;//上次十字线显示在dlg3的位置
	afx_msg void OnClose();
};
