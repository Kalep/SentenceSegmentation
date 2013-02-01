#include "Segmenter.h"
#include <iostream>

int main(int argc, char* argv[])
{
	//string input_file = "I:\\TCorpus\\mfdcorpus\\fbis.tok.ch.sent";//fbis.tok.ch.sent
	//string output_file = "I:\\TCorpus\\mfdcorpus\\fbis.tok.ch.sent.character.2";//fbis.tok.ch.character.test";

	string input_file = "I:\\TCorpus\\sighan\\icwb2-data\\icwb2-data\\msr\\msr.total";//fbispku.total
	string output_file = "I:\\TCorpus\\sighan\\icwb2-data\\icwb2-data\\msr\\msr.ch";

	//string input_file = "I:\\TCorpus\\mfdcorpus\\long.test";//fbis.tok.ch.sent
	//string output_file = "I:\\TCorpus\\mfdcorpus\\long.character.2";//fbis.tok.ch.character.test";

	Segmenter seg(input_file,output_file);
	//test_word(seg);
	seg.do_segment();
	seg.report();
	//seg.do_segment_string(test_string);
	system("pause");
	return 0;
}