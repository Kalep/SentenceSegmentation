#include "Segmenter.h"
#include <fstream>
#include <iostream>
#include "StringHelper.h"
#include <iterator>
#include <algorithm>

Segmenter::Segmenter(const string& in,const string& out):input_file(in), ref_out((in+".ref").c_str()),\
	fout(out.c_str()),long_out((out+".long").c_str()),count(0),mid_count(0),cut_count(0){
	punc_set.insert(",");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert(":");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert(";");//Ӣ�ĵķֺ�
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("����");
	punc_set.insert("����");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("\"");
	punc_set.insert("(");
	punc_set.insert(")");
};
void Segmenter::do_segment()
{
	 ifstream fin(this->input_file.c_str());
	 while(!fin)
	 {
		 cerr<<"�ļ�"<<input_file<<"������"<<endl;
		 exit(-1);
	 }
	 string line;
	 while(getline(fin,line))
	 {
		 count++;
		 if(line!=""&&line!="\t"&&line!=" "&&line!="����")
			this->do_segment_string(line);
		 if(count %10000 ==0 )
			 cout<<"��"<<count<<"��"<<endl;
	 }
	 fin.close();
	 fout.close();
	 long_out.close();
	 ref_out.close();
}
string Segmenter::get_next_word(const string& content, string::size_type start ) const
{
	string word ;
	if(start >= content.size() )
		word = " ";
	else if(content[start]&128) //��������ģ��Ǿ�ȡ������
		word = content.substr(start,2);
	else 
		word = content.substr(start,1);
	return word;
}

bool Segmenter::is_quote(const string& word) const
{
	bool result = false;
	if( word == "��")
	    result = true;
	else if( word == "��")
		result = true;
	return result ;
}

void Segmenter::string_to_characters(const string& content, vector<string>& characters)
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

//�ָ����
void Segmenter::do_segment_string(const string& content)
{
	
	vector<string> characters;
	this->string_to_characters(content,characters);
	vector<string>::size_type word_count = characters.size();
	bool can_output = true;
	if(word_count >= MAX_LEN)
	{
		can_output = this->segment_long(characters);
	}
	else
	{
		can_output = this->segment_short(characters);
	}
	if( can_output)
		ref_out << content<<endl;
	else
	{
		cut_count++;
	}
}

bool Segmenter::segment_long(const vector<string>& characters)
{
	//��¼һ�³�����
	copy(characters.begin() ,characters.end() , ostream_iterator<string>(long_out," "));
	long_out<<endl;
	//
	//1,�ҵ�����λ��
	vector<int> punc_positions;
	int index = 0;
	for(index = 0 ; index< characters.size() ;index ++)
	{
		if(this->is_delimiter(characters[index]))
			punc_positions.push_back(index);
	}
	punc_positions.push_back(characters.size()-1);
	//2, ���ݱ����ŵ�λ�ý��зָ�
	//cout<<character_positions.size()<<endl;
	//		2.1 ���ֻ��һ�����
	if(punc_positions.size() <2) 
		return this->segment_by_midpoint(characters);
	else
	//		2.2 ����ж�����
		return this->segment_by_punc(characters, punc_positions);
	//return true;
}
//������
bool Segmenter::tryToOutput( const vector<string>& characters,int start, int end)
{
	if(start > end)
	{
		cerr <<"error:"<<start<<"\t"<<end<<endl;
		return false;
	}
	bool is_same = true;//�ǲ���ȫ��ͬһ����
	//cout<< start << "\t "<< end <<"\t" << characters.size() <<endl;
	for( unsigned int word_index = start+1;  is_same && word_index < end ; word_index ++)
		if( characters[word_index-1] != characters[word_index])
				is_same = false;
	if(is_same)
	{
		cout<<this->count<<endl;
		copy(characters.begin() + start,characters.begin() + end, ostream_iterator<string>(cout," "));
		cout<<endl;
		return false;
	}
	else
	{
		copy(characters.begin() +start,characters.begin()+end, ostream_iterator<string>(fout," "));
		fout<<endl;
		return true;
	}
}

bool Segmenter::segment_short(const vector<string>& characters)
{	 
	return this->tryToOutput(characters,0, characters.size() );
}

void Segmenter::report() const
{
	cout<<"�������ˣ�"<<this->mid_count<<"�α����з�"<<endl;
    cout<<"����ȥ�ˣ�"<<this->cut_count<<"���������з�"<<endl;
}

bool Segmenter::is_delimiter(const string& character) const
{
	bool result = this->punc_set.find(character) != this->punc_set.end();
	return result ;
}

bool Segmenter::segment_by_midpoint(const vector<string>& characters)
{
	return this->segment_by_midpoint(characters,0,characters.size()-1);
}

bool Segmenter::segment_by_punc(const vector<string>& characters, const vector<int>& punc_positions)
{
	bool result = true;
	vector<int>::size_type begin = 0;
	for(unsigned int index = 1;  index < punc_positions.size() ; index++)
	{
		//�������֮��ĳ��ȴ������ĳ���
		if(punc_positions[index] - begin+1 > MAX_LEN) 
		{
			//��ô�ͼ�����һ��
			int prev_index = punc_positions[index-1];//���ֻ��һ��������
			//�����begin��prev_index���֣�����������Ȼ��100�ֶ࣬��ֱ�Ӵ��м�ֿ�
			if(prev_index - begin+1 >MAX_LEN)
			{
				result = this->segment_by_midpoint(characters,begin,prev_index);
			}
			else{//�����ľ���
				result = this->tryToOutput(characters,begin,prev_index+1);
			}
			begin = prev_index +1;
		}
		if(!result ) 
			return false;
	}
	//����� begin������end��
	if(begin < characters.size() )
	{
		if(characters.size() -begin > MAX_LEN)
		{
			result = this->segment_by_midpoint(characters, begin,characters.size()-1);
		}
		else
		{
			result = this->tryToOutput(characters, begin, characters.size());
			//copy(characters.begin() + begin, characters.end(),ostream_iterator<string>(fout," "));
			//fout<<endl;
		}
	}
	fout.flush();
	return result ;
}
//������
bool Segmenter::segment_by_midpoint(const vector<string>& characters, int start , int end)
{
	this->mid_count++;
	int mid = (end -start+1)/2+1;
	bool result = true;
	result &= this->tryToOutput(characters, start, mid);
	if( !result ) return result;
	result  &= this->tryToOutput(characters,mid, end+1);
	return result;
}
