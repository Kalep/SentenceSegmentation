#ifndef _SEGMENTER_H
#define _SEGMNETER_H
#include <string>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

#define MAX_LEN 100
/**
按句号分割
*/
class Segmenter{
public:
	Segmenter(const string& input_file,const string& output_file);
	void do_segment();
	void do_segment_string(const string& content);
	string get_next_word(const string& content,string::size_type start = 0) const;
	bool is_quote(const string& word) const;
	void report() const;
	/**把string转换成characters**/
	void string_to_characters(const string& content, vector<string>& characters);
private:
	bool is_delimiter(const string& character) const;
	bool segment_short(const vector<string>& characters) ;
	bool segment_long(const vector<string>& characters)  ;
	//按中点分割
	bool segment_by_midpoint(const vector<string>& characters);
	bool segment_by_midpoint(const vector<string>& characters, int start, int end);
	//根据标点分割
	bool segment_by_punc(const vector<string>& characters, const vector<int>& punc_positions);
	bool tryToOutput(const vector<string>& characters, int start ,int end) ;

	string input_file;
	ofstream fout;//最后的结果
	ofstream long_out;//长句子的结构
	ofstream ref_out;//参考集的输出
	set<string> punc_set;

	int cut_count ;
	int count;
	int mid_count ;
};
#endif