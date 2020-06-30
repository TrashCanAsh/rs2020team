#pragma once


// SpectralViewDlg 对话框

class SpectralViewDlg : public CDialog
{
	DECLARE_DYNAMIC(SpectralViewDlg)

public:
	SpectralViewDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SpectralViewDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SpectralView_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_SpecTree;
	virtual BOOL OnInitDialog();
	CListCtrl m_specList;
	CListCtrl m_PropList;
	afx_msg void OnNMDblclkPropertyList(NMHDR *pNMHDR, LRESULT *pResult);
	bool OpenConsole();
	CEdit m_PropEdit;
	afx_msg void OnLvnItemchangedPropertyList(NMHDR *pNMHDR, LRESULT *pResult);
};
