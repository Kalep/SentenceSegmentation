#ifndef _SEGMENTER_H
#define _SEGMNETER_H
#include <string>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

#define MAX_LEN 100
/**
����ŷָ�
*/
class Segmenter{
public:
	Segmenter(const string& input_file,const string& output_file);
	void do_segment();
	void do_segment_string(const string& content);
	string get_next_word(const string& content,string::size_type start = 0) const;
	bool is_quote(const string& word) const;
	void report() const;
	/**��stringת����characters**/
	void string_to_characters(const string& content, vector<string>& characters);
private:
	bool is_delimiter(const string& character) const;
	bool segment_short(const vector<string>& characters) ;
	bool segment_long(const vector<string>& characters)  ;
	//���е�ָ�
	bool segment_by_midpoint(const vector<string>& characters);
	bool segment_by_midpoint(const vector<string>& characters, int start, int end);
	//���ݱ��ָ�
	bool segment_by_punc(const vector<string>& characters, const vector<int>& punc_positions);
	bool tryToOutput(const vector<string>& characters, int start ,int end) ;

	string input_file;
	ofstream fout;//���Ľ��
	ofstream long_out;//�����ӵĽṹ
	ofstream ref_out;//�ο��������
	set<string> punc_set;

	int cut_count ;
	int count;
	int mid_count ;
};
#endif