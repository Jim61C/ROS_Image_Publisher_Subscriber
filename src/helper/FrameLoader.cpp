#include "FrameLoader.h"
FrameLoader::FrameLoader(string input_dir, 
		string data_source, 
		int begin_frame, 
		int end_frame, 
		int step):
	input_dir(input_dir), 
	data_source(data_source), 
	begin_frame(begin_frame), 
	end_frame(end_frame), 
	step(step)
{
}


void FrameLoader::load(vector<Mat> &frames) {
    if (input_dir.back()!='/') {
        input_dir += '/';
    }

    DIR *p_dir;
    int index=0;
    struct dirent *entry;
    vector<string> img_name_list;
    if( (p_dir=opendir(input_dir.c_str())) !=NULL){
        while((entry = readdir(p_dir))!= NULL){
            if( has_suffix(entry->d_name, ".png") || has_suffix(entry->d_name, ".jpg") ) {
                string this_img_path = (input_dir + entry->d_name);
                // cout << this_img_path << endl;
                img_name_list.push_back(this_img_path);
                index++;
            }
        }
        closedir(p_dir);
    }
    sort(img_name_list.begin(), img_name_list.end());

    for (int i=begin_frame; i<MIN(end_frame, img_name_list.size()); i+=step){
        cv::Mat frame_buffer =imread(img_name_list[i], CV_LOAD_IMAGE_UNCHANGED);
        frames.push_back(frame_buffer);
        // imshow("read in frame", frame_buffer);
        // waitKey(0);
    }
}


bool FrameLoader::has_suffix(const string& s, const string& suffix)
{
    return (s.size() >= suffix.size()) && equal(suffix.rbegin(), suffix.rend(), s.rbegin());
}