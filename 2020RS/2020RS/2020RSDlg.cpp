
// 2020RSDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "2020RS.h"
#include "2020RSDlg.h"
#include "afxdialogex.h"
#include "SpectralViewDlg.h"
#include "GeoCorrDlg.h"
#include "DensitySliceDlg.h"
#include "outvar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern Img_kele MainImg;
extern GeoCorrImg dlg11;
extern GeoCorrImg dlg12;
extern GeoCorrImg dlg13;
//
extern GeoCorrImg dlg21;
extern GeoCorrImg dlg22;
extern GeoCorrImg dlg23;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDensityslice();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(ID_DensitySlice, &CAboutDlg::OnDensityslice)
END_MESSAGE_MAP()


// CMy2020RSDlg 对话框



CMy2020RSDlg::CMy2020RSDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MY2020RS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy2020RSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_TREE, m_tree);
}

BEGIN_MESSAGE_MAP(CMy2020RSDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_SpecView, &CMy2020RSDlg::OnClkSpecview)
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREE, &CMy2020RSDlg::OnItemexpandedTree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, &CMy2020RSDlg::OnSelchangedTree)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, &CMy2020RSDlg::OnItemchangedList)
	ON_COMMAND(ID_Geometric, &CMy2020RSDlg::OnGeometric)
	ON_COMMAND(ID_DensitySlice, &CMy2020RSDlg::OnDensityslice)
END_MESSAGE_MAP()


// CMy2020RSDlg 消息处理程序

BOOL CMy2020RSDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	if (!OpenConsole()) AfxMessageBox("控制台打开失败");

	//gsyd
	m_ImageList.Create(32, 32, ILC_COLOR32, 10, 30);     //创建图像序列CImageList对象 
	m_list.SetImageList(&m_ImageList, LVSIL_NORMAL);  //为树形控件设置图像序列   
	m_tree.ModifyStyle(NULL, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_EDITLABELS);
	m_hRoot = m_tree.InsertItem("此电脑");         //插入根节点
	GetLogicalDrives(m_hRoot);                       //自定义函数 获取驱动
	GetDriveDir(m_hRoot);                            //自定义函数 获取驱动子项
	m_tree.Expand(m_hRoot, TVE_EXPAND);               //展开或折叠子项列表 TVE_EXPAND展开列表 
	//gsyd

	//
	dlg11.iNum = 1; dlg11.iFlag = 1;
	dlg11.Create(IDD_GeoCorrImg_DIALOG, this);
	dlg12.iNum = 1; dlg12.iFlag = 2;
	dlg12.Create(IDD_GeoCorrImg_DIALOG, this);
	dlg13.iNum = 1; dlg13.iFlag = 3;
	dlg13.Create(IDD_GeoCorrImg_DIALOG, this);
	dlg21.iNum = 2; dlg21.iFlag = 1;
	dlg21.Create(IDD_GeoCorrImg_DIALOG, this);
	dlg22.iNum = 2; dlg22.iFlag = 2;
	dlg22.Create(IDD_GeoCorrImg_DIALOG, this);
	dlg23.iNum = 2; dlg23.iFlag = 3;
	dlg23.Create(IDD_GeoCorrImg_DIALOG, this);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy2020RSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy2020RSDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy2020RSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CMy2020RSDlg::OnClkSpecview()
{
	//点击菜单中“光谱显示”，弹出光谱显示对话框
	SpectralViewDlg dlg;
	dlg.DoModal();
}

bool CMy2020RSDlg::OpenConsole()
{
	if (!AllocConsole()) return FALSE; //控制台调试窗口开启

	freopen("CONOUT$", "w", stdout);//开启中文控制台输出支持

	return TRUE;
}


//函数功能:获取驱动器 参数:路径名                       
void CMy2020RSDlg::GetLogicalDrives(HTREEITEM hParent)
{
	//获取系统分区驱动器字符串信息
	size_t szAllDriveStrings = GetLogicalDriveStrings(0, NULL);           //驱动器总长度
	char *pDriveStrings = new char[szAllDriveStrings + sizeof(_T(""))];  //建立数组
	GetLogicalDriveStrings(szAllDriveStrings, pDriveStrings);
	size_t szDriveString = strlen(pDriveStrings);                        //驱动大小
	while (szDriveString > 0)
	{
		m_tree.InsertItem(pDriveStrings, hParent);       //在父节点hParent添加盘符
		pDriveStrings += szDriveString + 1;             //pDriveStrings即C:\ D:\ E:\盘
		szDriveString = strlen(pDriveStrings);
	}
}//gsyd

//函数功能:获取驱动盘符下所有子项文件夹                 
void CMy2020RSDlg::GetDriveDir(HTREEITEM hParent)
{
	HTREEITEM hChild = m_tree.GetChildItem(hParent);   //获取指定位置中的子项
	while (hChild)
	{
		CString strText = m_tree.GetItemText(hChild);  //检索列表中项目文字
		if (strText.Right(1) != "\\")                   //从右边1开始获取从右向左nCount个字符
			strText += _T("\\");
		strText += "*.*";
		//将当前目录下文件枚举并InsertItem树状显示
		CFileFind file;                                       //定义本地文件查找
		BOOL bContinue = file.FindFile(strText);              //查找包含字符串的文件
		while (bContinue)
		{
			bContinue = file.FindNextFile();                  //查找下一个文件
			if (file.IsDirectory() && !file.IsDots())          //找到文件为内容且不为点"."
				m_tree.InsertItem(file.GetFileName(), hChild); //添加盘符路径下树状文件夹
		}
		GetDriveDir(hChild);                                  //递归调用
		hChild = m_tree.GetNextItem(hChild, TVGN_NEXT);        //获取树形控件(TVGN_NEXT)下一兄弟项
	}
}//gsyd


//函数功能:展开事件函数                    
void CMy2020RSDlg::OnItemexpandedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	TVITEM item = pNMTreeView->itemNew;                  //发送\接受关于树形视图项目信息
	if (item.hItem == m_hRoot)
		return;
	HTREEITEM hChild = m_tree.GetChildItem(item.hItem);  //获取指定位置中的子项
	while (hChild)
	{
		AddSubDir(hChild);                               //添加子目录

		hChild = m_tree.GetNextItem(hChild, TVGN_NEXT);   //获取树形控件TVGN_NEXT下兄弟项
	}
	*pResult = 0;
}//gsyd
 
//函数功能:添加子目录                   
void CMy2020RSDlg::AddSubDir(HTREEITEM hParent)
{
	CString strPath = GetFullPath(hParent);     //获取全路径
	if (strPath.Right(1) != "\\")
		strPath += "\\";
	strPath += "*.*";
	CFileFind file;
	BOOL bContinue = file.FindFile(strPath);    //查找包含字符串的文件
	while (bContinue)
	{
		bContinue = file.FindNextFile();        //查找下一个文件
		if (file.IsDirectory() && !file.IsDots())
			m_tree.InsertItem(file.GetFileName(), hParent);
	}
}//gsyd

//函数功能:获取树项目全根路径                      
CString CMy2020RSDlg::GetFullPath(HTREEITEM hCurrent)
{
	CString strTemp;
	CString strReturn = "";
	while (hCurrent != m_hRoot)
	{
		strTemp = m_tree.GetItemText(hCurrent);    //检索列表中项目文字
		if (strTemp.Right(1) != "\\")
			strTemp += "\\";
		strReturn = strTemp + strReturn;
		hCurrent = m_tree.GetParentItem(hCurrent); //返回父项目句柄
	}
	return strReturn;
}//gsyd

//函数功能:选中事件显示图标               
void CMy2020RSDlg::OnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_list.DeleteAllItems();
	m_fileList.RemoveAll();
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	TVITEM item = pNMTreeView->itemNew;
	if (item.hItem == m_hRoot)
		return;
	CString str = GetFullPath(item.hItem);
	if (str.Right(1) != "\\")
		str += "\\";
	str += "*.*";
	CFileFind file;
	BOOL bContinue = file.FindFile(str);
	while (bContinue)
	{
		bContinue = file.FindNextFile();
		if (!file.IsDirectory() && !file.IsDots())
		{
			SHFILEINFO info;
			CString temp = str;
			int index = temp.Find("*.*");
			temp.Delete(index, 3);
			SHGetFileInfo(temp + file.GetFileName(), 0, &info, sizeof(&info), SHGFI_DISPLAYNAME | SHGFI_ICON);
			//MessageBox(temp + file.GetFileName());
			int i = m_ImageList.Add(info.hIcon);
			m_list.InsertItem(i, info.szDisplayName, i);
			m_fileList.SetAt(info.szDisplayName, file.GetFilePath());
		}
	}

	*pResult = 0;
}//gsyd



//函数功能：输出点击的文件路径                          gsyd
void CMy2020RSDlg::OnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_list.GetFirstSelectedItemPosition();

	if (pos == NULL)
	{
		GetDlgItem(IDC_EDIT1)->SetWindowText("");
	}
	else
	{
		//有选中
		CString content;
		CString strMessage;
		while (pos)
		{
			int nItem = m_list.GetNextSelectedItem(pos);
			strMessage = m_list.GetItemText(nItem, 0);

			CString  pLook;

			m_fileList.Lookup(strMessage, pLook);

			//content = content + pLook + "\r\n";
			//zjr
			content = content + pLook ;

		}
		GetDlgItem(IDC_EDIT1)->SetWindowText(content);

		//zjr
		//显示图像时的清屏实现
		//获取主窗口句柄
		HWND hWnd;
		hWnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
		HDC hdc;
		hdc = ::GetDC(hWnd);
		//获取影像信息		
		//content = content + pLook;
		content.Replace(_T("\\"), _T("\\\\"));
		cout << "文件路径：" << content;
		BOOL flag = MainImg.ReadBmpInfo(content);
		if (flag == FALSE)
		{
			MessageBox("获取BMP文件信息失败！");
		}
		else
		{
			//创建波段存储空间
			flag = MainImg.CreateBandSpace();
			if (flag == FALSE)
			{
				MessageBox("主影像数据空间开辟失败！");
				return;
			}
			{
				flag = FALSE;
				//读取BMP波段数据
				flag = MainImg.ReadBmpData(content);
				if (flag == FALSE)
				{
					MessageBox("主影像数据读入失败！");
					return;
				}
				else
				{
					cout << "主影像数据读入成功!" << endl;
					CRect rectCtrl, rectCtrl2;
					//GetDlgItem(IDC_TREE)->GetClientRect(rectCtrl);
					GetDlgItem(IDC_EDIT1)->GetWindowRect(&rectCtrl); //获取被选中的控件大小
					ScreenToClient(&rectCtrl);  //转化为客户区坐标
					cout << "Edit客户区坐标：";
					cout << rectCtrl.left << "," << rectCtrl.top << "," << rectCtrl.left + rectCtrl.Width() << "," << rectCtrl.top + rectCtrl.Height() << endl;
					GetDlgItem(IDC_LIST)->GetWindowRect(&rectCtrl2); //获取被选中的控件大小
					ScreenToClient(&rectCtrl2);  //转化为客户区坐标
					cout << "List控件坐标：";
					cout << rectCtrl2.left << "," << rectCtrl2.top << "," << rectCtrl2.left + rectCtrl2.Width() << "," << rectCtrl2.top + rectCtrl2.Height() << endl;
					cout << rectCtrl2.left << "," << rectCtrl2.top << "," << rectCtrl2.right << "," << rectCtrl2.bottom << endl;
					//MessageBox(str);

					//创建实线，宽度为1，灰色的笔
					HPEN hPen = CreatePen(PS_SOLID, 1, RGB(240, 240, 240));
					//将笔选入DC
					HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

					//创建一个灰色的刷子
					HBRUSH hBrush = CreateSolidBrush(RGB(240, 240, 240));
					HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

					//绘制矩形，灰色边框，灰色区域的
					CRect rect;
					::GetClientRect(hWnd, &rect);
					Rectangle(hdc, rectCtrl.right + 10, rectCtrl.top, rect.Width(), rect.Height());
					cout << "客户区坐标：";
					cout << rect.left << "," << rect.top << "," << rect.right << "," << rect.bottom << endl;

					//恢复绘图对象
					SelectObject(hdc, hOldPen);
					SelectObject(hdc, hOldBrush);
					//删除绘图对象
					DeleteObject(hPen);
					DeleteObject(hBrush);

					cout << "Display宽高：" << endl;
					cout << rect.Width() - rectCtrl.right - 10 << "," << rect.Height() - rectCtrl2.bottom - 10 << endl;
					flag = MainImg.DisplayImgColor(&hdc, rect.Width() - rectCtrl.right - 25, rect.Height() - rectCtrl.top - 10, rectCtrl.right + 10, rectCtrl.top, MainImg.ImgParaInCls.ImgW, MainImg.ImgParaInCls.ImgH, 0, 0);
					if (flag == FALSE)
						MessageBox("影像显示失败！");
				}

			}

			
		}

	
	}
	
	*pResult = 0;
	*pResult = 0;
	
}//gsyd


void CMy2020RSDlg::OnGeometric()
{
	// TODO: 在此添加命令处理程序代码
	GeoCorrDlg Dlg;
	Dlg.DoModal();
	CWnd *pWnd;
	HWND hWnd;
	pWnd = CWnd::FindWindow(NULL, "dialog11");
	hWnd = pWnd->GetSafeHwnd();
	::SendMessage(hWnd, WM_CLOSE, NULL, NULL);
	pWnd = CWnd::FindWindow(NULL, "dialog12");
	hWnd = pWnd->GetSafeHwnd();
	::SendMessage(hWnd, WM_CLOSE, NULL, NULL);
	pWnd = CWnd::FindWindow(NULL, "dialog13");
	hWnd = pWnd->GetSafeHwnd();
	::SendMessage(hWnd, WM_CLOSE, NULL, NULL);
	pWnd = CWnd::FindWindow(NULL, "dialog21");
	hWnd = pWnd->GetSafeHwnd();
	::SendMessage(hWnd, WM_CLOSE, NULL, NULL);
	pWnd = CWnd::FindWindow(NULL, "dialog22");
	hWnd = pWnd->GetSafeHwnd();
	::SendMessage(hWnd, WM_CLOSE, NULL, NULL);
	pWnd = CWnd::FindWindow(NULL, "dialog23");
	hWnd = pWnd->GetSafeHwnd();
	::SendMessage(hWnd, WM_CLOSE, NULL, NULL);
}


void CAboutDlg::OnDensityslice()
{
	// TODO: 在此添加命令处理程序代码
	
}


void CMy2020RSDlg::OnDensityslice()
{
	// TODO: 在此添加命令处理程序代码
	DensitySliceDlg DSDlg;
	DSDlg.DoModal();
}
