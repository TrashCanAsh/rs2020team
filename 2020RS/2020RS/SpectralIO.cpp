#include "stdafx.h"
#include "SpectralIO.h"

vector<ASDstruct>SpectralIO::ASDdata;
SpectralIO::SpectralIO()
{
}


SpectralIO::~SpectralIO()
{
}


// ASD 消息处理程序

//字符串分隔  ", :;\t\r\n\\"   逗号 空格 分号
//用于提取详细数据
int __fastcall  SsToStr1(char *str, char *s_dat[])
{
	int  nn;
	char ch, *pstr;
	s_dat[0] = str;
	ch = *str;
	if (ch == '\0' || ch == '\n') return 0;
	nn = 0; pstr = strtok(str, ", :;\t\r\n\\");
	while (pstr)
	{
		/*if (pstr)
		{
			s_dat[nn] = pstr; if (nn < MAX_DAT) nn++;
		}*/
		if (pstr)
		{
			s_dat[nn] = pstr; if (nn < 100) nn++;
		}
		pstr = strtok(NULL, ", :;\t\r\n\\");
	}
	return nn;
}

BOOL SpectralIO::readfile(CString FilePath)
{
	float minrel = 100.0;
	float maxrel = -1.0;

	vector<PT> data_asd;

	CFileDialog Dlg(TRUE);
	//读取文件名
	CString dateclass;
	CString datename;
	dateclass = FilePath.Right(3);
	int flag0 = -1;//0为实地测量数据，1为美国数据
	int position = FilePath.ReverseFind('\\');
	datename = FilePath.Mid(position, FilePath.GetLength() - 4-position);

	if (dateclass== "txt")
	{
		flag0 = 0;
	}
	else if (dateclass =="asc")
	{
		flag0 = 1;
	}
	else 
	{
		return false;
		//MessageBox(_T("文件打开错误"));
	}

	if (flag0 == 0)//读取实地数据
	{
		//读取实地数据
		PT point;
		char ReadStr[100];
		int nn = 0;
		char *SS_Dat[3];
		FILE *fp = fopen(FilePath, "r");
		while (1)
		{
			if (feof(fp))break;
			fgets(ReadStr, 800, fp);
			nn = SsToStr1(ReadStr, SS_Dat);
			float XX = atof(SS_Dat[0]);
			float YY = atof(SS_Dat[1]);

				//查最大小值
				if (YY < minrel)
					minrel = YY;
				if (YY > maxrel)
					maxrel = YY;
			point.xx = XX; point.yy = YY;
			data_asd.push_back(point);
		}

		fclose(fp);

	}
	else if (flag0 == 1)//读取美国数据
	{

		//读取数据
		PT point;
		char ReadStr[100];
		int nn = 0;
		char *SS_Dat[8];
		FILE *fp = fopen(FilePath, "r");
		int ii = 16;
		while (ii)
		{

			if (feof(fp))break;
			fgets(ReadStr, 800, fp);
			ii = ii - 1;
		}

		while (1)
		{
			char *SS_Dat[3];
			if (feof(fp))break;
			fgets(ReadStr, 800, fp);
			nn = SsToStr1(ReadStr, SS_Dat);
			//如果第二位标志符号 == “-1.23e34”则为点
			//第三位表示标准差，不知道干吗用
			float XX, YY;
				XX = atof(SS_Dat[0]);
				YY = atof(SS_Dat[1]);
				if (YY < minrel)
					minrel = YY;
				if (YY > maxrel)
					maxrel = YY;
		}
		fclose(fp);
	}

	//插入进ASDdata
	ASDstruct date;
	date.name = datename;
	date.data = data_asd;
	date.MaxRel = maxrel;
	date.MinRel = minrel;
	SpectralIO::ASDdata.push_back(date);

	//更新list
	/*int maxnum = SpectralIO::ASDdata.size();
	int  now_item = m_list.GetItemCount();
	m_list.InsertItem(now_item + 1, ASD::ASDdata[maxnum - 1].name);*/
	// TODO: 在此添加控件通知处理程序代码
}

void SpectralIO::delete_data(int nItem)
{
	
	//获取当前用户选择的项目
	//POSITION pos = m_list.GetFirstSelectedItemPosition();
	//nItem = m_list.GetNextSelectedItem(pos);
	if (nItem == -1)
	{
		cout<<"亲爱的，请先选择一条数据呦";
		return;
	}
	//删除vector
	auto delItem = SpectralIO::ASDdata.begin() + nItem;
	SpectralIO::ASDdata.erase(delItem);

	
	//根据名字删除
	/*CString delName = SpectralIO::ASDdata[nItem].name;
	int ii;
	for ( ii = 0; ii < SpectralIO::ASDdata.size(); ii++)
	{
		char *tempdata = (LPSTR)(LPCSTR)(SpectralIO::ASDdata[ii].name);
		if (strcpy(tempdata, delName) == 0)
		{
			break;
		}
	}
	auto delItem = SpectralIO::ASDdata.begin() + ii;
	SpectralIO::ASDdata.erase(delItem);*/

}

void SpectralIO::del_data(CString delName)
{
	int  ii;
	for (ii = 0; ii < SpectralIO::ASDdata.size(); ii++)
	{
		int xxxxx = 1;
		if (!delName.CompareNoCase(SpectralIO::ASDdata[ii].name))
		{
			break;
		}
	}

	auto delItem = SpectralIO::ASDdata.begin() + ii;
	SpectralIO::ASDdata.erase(delItem);
}
