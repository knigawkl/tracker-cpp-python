#include "video.hpp"
#include "utils.hpp"

int get_video_capture_frame_cnt(const cv::VideoCapture& cap)
{
    return cap.get(cv::CAP_PROP_FRAME_COUNT);
}

int get_trimmed_frame_cnt(const cv::VideoCapture& cap, int frames_in_segment) 
{
    int video_in_frame_cnt = get_video_capture_frame_cnt(cap);
    std::cout << "Input video frames count: " << video_in_frame_cnt << std::endl;
    return video_in_frame_cnt / frames_in_segment * frames_in_segment;
}

void trim_video(std::string video_in, std::string video_out, int frame_cnt) 
{
    std::stringstream ss;
    ss << "ffmpeg -i " << video_in << " -vframes " << std::to_string(frame_cnt) 
       << " -acodec copy -vcodec copy " << video_out << " -y";
    std::string trim_command = ss.str();
    std::cout << "Executing: " << trim_command << std::endl;
    system(trim_command.c_str());
}

void prepare_tmp_video(const cv::VideoCapture& in_cap, int desired_frame_cnt, 
                       std::string tmp_folder, std::string in_video, std::string tmp_video)
{
    const int video_in_frame_cnt = get_video_capture_frame_cnt(in_cap);
    if (video_in_frame_cnt != desired_frame_cnt)
    {
        std::string const trimmed_video = tmp_folder + "/trim.mp4";
        trim_video(in_video, trimmed_video, desired_frame_cnt);
        std::cout << "Input video frames count cut to: " << desired_frame_cnt << std::endl;
        mv(trimmed_video, tmp_video);
    }
    else
    {
        cp(in_video, tmp_video);
    }
}