#pragma once
#include <windows.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
//哈希表容器
vector<string> vec_hash;
//分割字符
vector<string> splitStr(const string& str, const string& fileName_Extension);
//生成哈希表
int GenerateHashtable(char* buffer, size_t buffer_length, string fileName_Extension);