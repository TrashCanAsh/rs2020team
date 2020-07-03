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
	int iNum;
	int iFlag;
	virtual BOOL OnInitDialog();
};
