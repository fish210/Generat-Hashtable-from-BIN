#pragma once
#include <windows.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<string> vec_hash;

vector<string> splitStr(const string& str, const string& fileName_Extension);//分割字符
int GenerateHashtable(char* buffer, size_t buffer_length, string fileName_Extension);//生成哈希表