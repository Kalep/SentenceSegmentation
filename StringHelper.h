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
   ���ַ�����ĳһ���ָ����ָ�
   source:Դ�ַ���
   del:�ָ���
   res:�ָ��Ľ��
*/
void token(const string& source,const char del,vector<string>& res);

/**���ո�ָ*/
template<typename T>
void token(const string& source, vector<T>& res)
{
	stringstream sin(source);
	T temp;
	while(sin>>temp)
		res.push_back(temp);
}
//�����ʼ���
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
  ��source�е��ַ����ϲ���target
*/
void transfer(const vector<string>& source, int start,int end, string& target);

template<typename T>
void transfer(const string& source, T& target){
	stringstream sin(source);
	sin>>target;
};
/**��������ַ����ı༭����*/
int getEditDistance(const string& left,const string& right);
/**��string����������ȥ���ո�*/
void trimto(const string& source,string& result);
/**��vector�е�string��������*/
void trimto(const vector<string>& source, string& target, string delimiter="");
/**��vector�е�string��������*/
void trimto(vector<string>::const_iterator& begin,vector<string>::const_iterator& end, string& target,string delimiter="");
//��Сдת��
void tolowercase(string& input);
/**��stringת����characters**/
void string_to_characters(const string& content, vector<string>& characters);
string get_next_word(const string& content,string::size_type start = 0) ;
#endif

