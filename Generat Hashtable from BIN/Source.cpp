#include "Source.h"

int main()
{
	FILE* fp = 0;
	int err = fopen_s(&fp, "skin8.bin", "rb");
	if (err == 0)
	{
		fseek(fp, 0, SEEK_END);//指针移到文件尾部
		UINT size = ftell(fp);//取文件大小
		char* buf = new char[size]();//申请内存
		rewind(fp);//指针重新回到文件头部
		fread(buf, 1, size, fp);//读入文件

		//********************* 生成哈希表
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

		//********************* 调试输出结果
		for (size_t i = 0; i < vec_hash.size(); i++)
		{
			cout << "Hashtable 哈希表: " << vec_hash[i] << endl;
		}

		fclose(fp);//关闭文件
		delete[] buf;//释放内存
		buf = 0;//如果不赋值为零 下次文件指针有可能会分配到同一个地址 造成重复引用 发生安全隐患 delete并不会清零指针地址
	}
	else
	{
		cout << "Return value 返回错误代码: " << err << endl;
	}
	return 0;

}
//分割字符
std::vector<string> splitStr(const string& str, const string& fileName_Extension)
{
	std::vector<std::string> res;
	if (str == "")
	{
		return res;
	}
	//截取最后一段数据 
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
//生成哈希表
int GenerateHashtable(char* buffer, size_t buffer_length, string fileName_Extension)
{
	string pstr(buffer, buffer_length);//加入字串符类
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
		if (Point != ".") { continue; }//没有点号 跳出
		size_t position = allStr[i].rfind(s_left);
		if (position == string::npos) { continue; }//没有找到字符串 跳出

		string subStr = allStr[i].substr(position, strSize) + fileName_Extension;
		if (strSize > 4)//小于4个字节一般不是目标数据 DATA都占4个字节
		{
			transform(subStr.begin(), subStr.end(), subStr.begin(), ::tolower);//转小写
			vec_hash.push_back(subStr);//加入容器
		}
	}
	return 0;
}