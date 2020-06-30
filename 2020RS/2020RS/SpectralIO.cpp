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

//�ַ����ָ�  ", .;\t\r\n \\"   ���� �ո� �ֺ�
//������ȡ��������
int __fastcall  SsToStr2(char *str, char *s_dat[])
{

	int  nn;
	char ch, *pstr;
	s_dat[0] = str;
	ch = *str;
	if (ch == '\0' || ch == '\n') return 0;
	nn = 0; pstr = strtok(str, ",.:;\t\r\n\\");
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
		pstr = strtok(NULL, ",.:;\t\r\n\\");
	}

	return nn;
}
BOOL SpectralIO::readfile(CString FilePath)
{
	vector<PT> data_asd;

	CFileDialog Dlg(TRUE);
	//��ȡ�ļ���
	CString datename;
	int flag0 = -1;//0��ʾʵ�ز������� ��1��ʾ��������
	int file_nn = 0;
	char *SS[10];
	CString tempnnn;
	char *temp = (LPSTR)(LPCSTR)tempnnn;
	strcpy(temp, FilePath);
	file_nn = SsToStr2(temp, SS);

	for (int ii = 0;; ii++)
	{
		if (strcmp(SS[ii + 1], "txt") == 0)
		{
			datename = SS[ii];
			flag0 = 0;
			break;
		}
		else if (strcmp(SS[ii + 1], "asc") == 0)
		{

			datename = SS[ii - 1];
			CString tempname = SS[ii];
			datename = datename + "." + tempname;
			flag0 = 1;
			break;
		}
	}
	if (flag0 == -1)
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
			//����ڶ�λ��־���� == ��-1.23e34������Ӹõ�
			//����λ��ʾ��׼���֪��������
			if (strcmp(SS_Dat[1], "-1.23e34") == 1)
			{
				float XX = atof(SS_Dat[0]);
				float YY = atof(SS_Dat[1]);
				point.xx = XX; point.yy = YY;
				data_asd.push_back(point);
			}
		}
		fclose(fp);
	}

	//�����ASDdata
	ASDstruct date;
	date.name = datename;
	date.data = data_asd;
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
