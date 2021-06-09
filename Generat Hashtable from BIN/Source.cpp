#include "Source.h"

int main()
{
	FILE* fp = 0;
	int err = fopen_s(&fp, "skin8.bin", "rb");
	if (err == 0)
	{
		fseek(fp, 0, SEEK_END);//ָ���Ƶ��ļ�β��
		UINT size = ftell(fp);//ȡ�ļ���С
		char* buf = new char[size]();//�����ڴ�
		rewind(fp);//ָ�����»ص��ļ�ͷ��
		fread(buf, 1, size, fp);//�����ļ�

		//********************* ���ɹ�ϣ��
		GenerateHashtable(buf, size, "skl");
		GenerateHashtable(buf, size, "skn");
		GenerateHashtable(buf, size, "dds");
		GenerateHashtable(buf, size, "DDS");
		GenerateHashtable(buf, size, "anm");
		GenerateHashtable(buf, size, "sco");
		GenerateHashtable(buf, size, "scb");
		GenerateHashtable(buf, size, "bin");
		GenerateHashtable(buf, size, "bnk");
		GenerateHashtable(buf, size, "wpk");

		//********************* ����������
		for (size_t i = 0; i < vec_hash.size(); i++)
		{
			cout << "Hashtable ��ϣ��: " << vec_hash[i] << endl;
		}

		fclose(fp);//�ر��ļ�
		delete[] buf;//�ͷ��ڴ�
		buf = 0;//�������ֵΪ�� �´��ļ�ָ���п��ܻ���䵽ͬһ����ַ ����ظ����� ������ȫ���� delete����������ָ���ַ
	}
	else
	{
		cout << "Return value ���ش������: " << err << endl;
	}
	return 0;

}
//�ָ��ַ�
std::vector<string> splitStr(const string& str, const string& fileName_Extension)
{
	std::vector<std::string> res;
	if (str == "")
	{
		return res;
	}
	//��ȡ���һ������ 
	string strs = str + fileName_Extension;
	size_t pos = strs.find(fileName_Extension);
	size_t size = strs.size();
	size_t length = fileName_Extension.length();
	while (pos != string::npos)
	{
		string x = strs.substr(0, pos);
		res.push_back(x);
		strs = strs.substr(pos + length, size);
		pos = strs.find(fileName_Extension);
	}
	return res;
}
//���ɹ�ϣ��
int GenerateHashtable(char* buffer, size_t buffer_length, string fileName_Extension)
{
	string pstr(buffer, buffer_length);//�����ִ�����
	pstr.push_back('\0');

	string s_left;
	if (fileName_Extension == "bin")
	{
		s_left = "DATA/";

	}
	else
	{
		s_left = "ASSETS/";
	}
	vector<string> allStr = splitStr(pstr, fileName_Extension);

	for (int i = 0; i < allStr.size(); i++)
	{
		size_t strSize = allStr[i].size();
		string Point = allStr[i].substr(strSize - 1, strSize);
		if (Point != ".") { continue; }//û�е�� ����
		size_t position = allStr[i].rfind(s_left);
		if (position == string::npos) { continue; }//û���ҵ��ַ��� ����

		string subStr = allStr[i].substr(position, strSize) + fileName_Extension;
		if (strSize > 4)//С��4���ֽ�һ�㲻��Ŀ������ DATA��ռ4���ֽ�
		{
			transform(subStr.begin(), subStr.end(), subStr.begin(), ::tolower);//תСд
			vec_hash.push_back(subStr);//��������
		}
	}
	return 0;
}