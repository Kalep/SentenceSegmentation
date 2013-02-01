#ifndef _STRING_HELPER_H
#define _STRING_HELPER_H
#pragma once
#include<string>
#include<vector>
#include<sstream>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;
/**
   将字符串按某一个分隔符分割
   source:源字符串
   del:分隔符
   res:分割后的结果
*/
void token(const string& source,const char del,vector<string>& res);

/**按空格分割开*/
template<typename T>
void token(const string& source, vector<T>& res)
{
	stringstream sin(source);
	T temp;
	while(sin>>temp)
		res.push_back(temp);
}
//按单词计数
template<typename T>
void token(const string& source, map<T,int> & grams)
{
	istringstream sin(source);
	T temp;
	while(sin>> temp);
	   grams[temp]++;
}

void split(const string& source, const string& del, vector<string>& res);
/**
  将source中的字符串合并到target
*/
void transfer(const vector<string>& source, int start,int end, string& target);

template<typename T>
void transfer(const string& source, T& target){
	stringstream sin(source);
	sin>>target;
};
/**获得两个字符串的编辑距离*/
int getEditDistance(const string& left,const string& right);
/**将string连接起来，去掉空格*/
void trimto(const string& source,string& result);
/**将vector中的string连接起来*/
void trimto(const vector<string>& source, string& target, string delimiter="");
/**将vector中的string连接起来*/
void trimto(vector<string>::const_iterator& begin,vector<string>::const_iterator& end, string& target,string delimiter="");
//大小写转换
void tolowercase(string& input);
/**把string转换成characters**/
void string_to_characters(const string& content, vector<string>& characters);
string get_next_word(const string& content,string::size_type start = 0) ;
#endif

