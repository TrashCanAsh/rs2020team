#include "stdafx.h"
#include "SpectralIO.h"

vector<ASDstruct>SpectralIO::ASDdata;
SpectralIO::SpectralIO()
{
}


SpectralIO::~SpectralIO()
{
}


// ASD ��Ϣ�������

//�ַ����ָ�  ", :;\t\r\n\\"   ���� �ո� �ֺ�
//������ȡ��ϸ����
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
	//��ȡ�ļ���
	CString dateclass;
	CString datename;
	dateclass = FilePath.Right(3);
	int flag0 = -1;//0Ϊʵ�ز������ݣ�1Ϊ��������
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
		//MessageBox(_T("�ļ��򿪴���"));
	}

	if (flag0 == 0)//��ȡʵ������
	{
		//��ȡʵ������
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

				//�����Сֵ
				if (YY < minrel)
					minrel = YY;
				if (YY > maxrel)
					maxrel = YY;
			point.xx = XX; point.yy = YY;
			data_asd.push_back(point);
		}

		fclose(fp);

	}
	else if (flag0 == 1)//��ȡ��������
	{

		//��ȡ����
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
			//����ڶ�λ��־���� == ��-1.23e34����Ϊ��
			//����λ��ʾ��׼���֪��������
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

	//�����ASDdata
	ASDstruct date;
	date.name = datename;
	date.data = data_asd;
	date.MaxRel = maxrel;
	date.MinRel = minrel;
	SpectralIO::ASDdata.push_back(date);

	//����list
	/*int maxnum = SpectralIO::ASDdata.size();
	int  now_item = m_list.GetItemCount();
	m_list.InsertItem(now_item + 1, ASD::ASDdata[maxnum - 1].name);*/
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void SpectralIO::delete_data(int nItem)
{
	
	//��ȡ��ǰ�û�ѡ�����Ŀ
	//POSITION pos = m_list.GetFirstSelectedItemPosition();
	//nItem = m_list.GetNextSelectedItem(pos);
	if (nItem == -1)
	{
		cout<<"�װ��ģ�����ѡ��һ��������";
		return;
	}
	//ɾ��vector
	auto delItem = SpectralIO::ASDdata.begin() + nItem;
	SpectralIO::ASDdata.erase(delItem);

	
	//��������ɾ��
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
