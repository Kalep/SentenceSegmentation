#include "StringHelper.h"
#include <iterator>

void token(const string& source,const char del,vector<string>& res)
{
#ifdef SOURCE
	printf("source:%s\n",source.c_str());
#endif
	stringstream cin(source);
	string pos;
	while(getline(cin,pos,del))
	{
		if(pos!=""&&pos!=" ")
			res.push_back(pos);
	}
}

void split(const string& source, const string& del, vector<string>& res)
{
	//用find的方法实现吧
	int start = 0;
	int end = source.find(del);
	if(end == string::npos)  { //没有分隔符
		res.push_back(source);
		return ;
	}
	while(start<source.size()){
		//printf("start,end:\t %d,%d\n",start,end);
		string& token =  source.substr(start,end-start);
		if(token!=""||token!=" ")
			res.push_back(token);
		//printf("token:%s\n",token.c_str());
		start = end+del.size();
		end = source.find(del,start);
		if(end == string::npos)  { //没有分隔符
			res.push_back(source.substr(start));
			return ;
		}
	}
}

void transfer(const vector<string>& source, int start,int end,string& target)
{
	ostringstream out;
	int span_length = end - start+1;
	if(span_length ==1)
		out<<*(source.begin()+start);
	else if( span_length == 2)
		out<<*(source.begin()+start)<<" "<<*(source.begin()+end);
	else{
	//要试试长度为2的
		copy(source.begin()+start,source.begin()+end-1,ostream_iterator<string>(out," "));
		out<<*(source.begin()+end);
	}
	target = out.str();
}

int getEditDistance(const string& left,const string& right)
{
	if(left.size() ==0) return right.size();
	if( right.size() == 0) return left.size();

	int left_length = left.size()+1;
	int right_length = right.size()+1;
	int row_max = left_length, col_max = right_length;
	string row_string = left, col_string = right;
	if( left_length < right_length) //让行为较小的长度,这样申请的空间小一点
	{
		row_max = right_length;
		row_string = right;
		col_max = left_length;
		col_string = left;
	}
	int* firstLine = new int[col_max];
	int* secondLine = new int[col_max];
	//1,初始化边界
	int row,col;
	//初始行[0][x]
	for(col = 0; col < col_max; col++)
		*(firstLine+col) = col;
	//初始化[1][0]
	for( row = 1; row < row_max; row++)
	{
		for( col =0 ;col < col_max; col++)
		{
			if( col == 0)  {
				*secondLine = row;
				continue;
			}
			if( col_string[col-1] == row_string[row-1]) //字符相等，直接移过来
				*(secondLine+ col) = *(firstLine+col-1);
			else{
				//比大小
				//[row][col]
				*(secondLine+col) = *(secondLine+col-1)+1;// (row,col-1) +1
				int d2 = *(firstLine+col)+1;// (row-1,col)+1
				if(*(secondLine+col) >d2)
					*(secondLine+col) = d2;
				int d3 = *(firstLine+col-1)+1;// (row-1,col-1)+1
				if(*(secondLine+col) > d3)
					*(secondLine+col) = d3;
			}
		}
		int * temp = firstLine;
		firstLine = secondLine;
		secondLine = temp;
	}
	int distance = *(firstLine+col_max-1);
	delete[] firstLine;
	delete[] secondLine;
	return distance;
}

void trimto(const string& source,string& result)
{
	istringstream sin(source);
	string temp;
	while(sin>>temp)
		result.insert(result.end(),temp.begin(),temp.end());
}

void trimto(const vector<string>& source, string& target, string delimiter)
{
	ostringstream sout;
	copy(source.begin(),source.end(),ostream_iterator<string>(sout,delimiter.c_str()));
	target = sout.str();
}

void trimto(vector<string>::const_iterator& begin,vector<string>::const_iterator& end, string& target,string delimiter)
{
	ostringstream sout;
	copy(begin,end,ostream_iterator<string>(sout,delimiter.c_str()));
	target = sout.str();
}

void tolowercase(string& input)
{
	transform(input.begin(),input.end(),input.begin(),tolower);
}

void string_to_characters(const string& content, vector<string>& characters)
{
	int start = 0;
	while(start < content.size())
	{
		const string&  character = get_next_word(content,start);
		if(character != " ")
			characters.push_back(character);
		start += character.size();
	}
}

string get_next_word(const string& content, string::size_type start ) 
{
	string word ;
	if(start >= content.size() )
		word = " ";
	else if(content[start]&128) //如果是中文，那就取两个字
		word = content.substr(start,2);
	else 
		word = content.substr(start,1);
	return word;
}