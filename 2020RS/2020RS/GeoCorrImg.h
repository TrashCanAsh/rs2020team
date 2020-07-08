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
	int iNum;
	int iFlag;

	virtual BOOL OnInitDialog();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	static CPoint Click_dlg2;//点击2窗口的坐标
	static CPoint Click_dlg1;//点击1窗口的坐标
};
