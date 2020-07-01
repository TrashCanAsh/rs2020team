#pragma once

//#include<vector>
//#include <fstream>  
#include<iostream>
//#include <string> 
#include"SpectralIO.h"
using namespace std;

#define MAX_DAT   100 
// SpectralViewDlg 对话框

struct CurColorStruct {
	CString name;
	COLORREF CurColor;
} ;

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

	//光谱列表关联变量
	CListCtrl m_specList;

	//绘图属性列表关联变量
	CListCtrl m_PropList;
	afx_msg void OnNMDblclkPropertyList(NMHDR *pNMHDR, LRESULT *pResult);
	bool OpenConsole();

	//属性列表中改变ItemText借助的Edit关联的变量
	CEdit m_PropEdit;
//	afx_msg void OnLvnItemchangedPropertyList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeMfceditbrowse1();
	
	afx_msg void OnBnClickedClosespeButton();
//	afx_msg void OnHdnItemchangedSpeclineList(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnLvnItemchangedSpeclineList(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg  void OnItemchangedListSpeclineList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnItemchangedSpeclineList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEdit1();

	//修改属性ListControl时指示修改的行列
	int currRow;
	int currCol;

	//属性列表中曲线颜色的Color ComboBox关联的变量
	CMFCColorButton m_CurveColor;

	//曲线显示颜色数组
	COLORREF colorlib[256];
	BOOL ReadColorLib();

	//字符打断
	char *SS_Dat[MAX_DAT + 1];
	int SsToStr60(char *str, char *s_dat[]);
//	afx_msg void OnNMCustomdrawPropertyList(NMHDR *pNMHDR, LRESULT *pResult);

	int colorNum = 0;//用于选择下一个显示的颜色
	//用于存储当前已读入的光谱曲线名、绘制曲线的颜色
	vector<CurColorStruct>CurrentColor;
	afx_msg void OnLvnInsertitemSpeclineList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSpeclineList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickSpeclineList(NMHDR *pNMHDR, LRESULT *pResult);
	



	/**
	* @brief 绘制光谱曲线
	* @param [in] PicID    控件ID
	* @param [in] index/name  绘制光谱曲线下标或者名称
	* @param [in] penStyle    画笔样式，只能输入以下参数：
	*	-# PS_SOLID
	*	-# PS_DASH       / -------  /
	*	-# PS_DOT        / .......  /
	*	-# PS_DASHDOT    / _._._._  /
	*	-# PS_DASHDOTDOT / _.._.._  /
	* @param [in] penWidth    画笔宽度
	* @param [in] color    画笔颜色
	* @param [in] gap    波长间隔，每隔gap个波长值进行画线
	* @param [in] esp    反射率分辨率，折线图上允许出现的最小的反射率差异。
	*
	* @retval true     成功
	* @retval false    失败
	* @pre PicID 必须使用PictureControl类型的控件ID
	* @note 擦除操作需要使用相同的下标或者名称来进行擦除
	*/
	bool DrawSpectralPic(int PicID, int index, int penStyle, int penWidth, COLORREF color, int gap, double esp);
	bool DrawSpectralPic(int PicID, CString name, int penStyle, int penWidth, COLORREF color, int gap, double esp);
//	afx_msg void OnBnKillfocusCurveMfccolorbutton();
//	afx_msg void OnBnHotItemChangeCurveMfccolorbutton(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCurveMfccolorbutton();
};
