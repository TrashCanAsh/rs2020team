
// 2020RS.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

#include"io.h" //实现遍历文件夹

//定义文件结构
//struct _finddata_t
//{
//	unsigned attrib;     //文件属性
//	time_t time_create;  //文件创建时间
//	time_t time_access;  //文件上一次访问时间
//	time_t time_write;   //文件上一次修改时间
//	_fsize_t size;  //文件字节数
//	char name[_MAX_FNAME]; //文件名
//};

// CMy2020RSApp:
// 有关此类的实现，请参阅 2020RS.cpp
//

class CMy2020RSApp : public CWinApp
{
public:
	CMy2020RSApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMy2020RSApp theApp;
