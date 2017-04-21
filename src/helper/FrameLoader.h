#include <iostream>
#include <string.h>
#include "Common.h"
#include "CommonCV.h"

class FrameLoader {

private:
	string input_dir;
	string data_source;
	int begin_frame;
	int end_frame;
	int step;

public:
	FrameLoader(string input_dir, 
		string data_source, 
		int begin_frame, 
		int end_frame, 
		int step);


	void load(vector<Mat> &frames);
	bool has_suffix(const string& s, const string& suffix);

};