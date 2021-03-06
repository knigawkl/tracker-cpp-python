#pragma once

#include <stdlib.h>
#include <chrono>
#include <utility>

#include <opencv2/opencv.hpp>

#include "templates.hpp"


namespace utils
{
    namespace sys
    {
        void make_tmp_dirs(std::string tmp_folder);
        void clear_tmp(std::string tmp_folder);
        void mv(std::string what, std::string where);
        void cp(std::string what, std::string where);
    }
    namespace printing
    {
        void print_usage_info();
        void print_parameters(int segment_size, std::string in_video, std::string out_video, 
                              std::string detector, std::string detector_cfg, std::string tmp_folder);
        void print_exec_time(std::chrono::steady_clock::time_point begin, std::chrono::steady_clock::time_point end);
        void print_detect_time(std::chrono::steady_clock::time_point begin, std::chrono::steady_clock::time_point end);
        void print_track_time(std::chrono::steady_clock::time_point begin, std::chrono::steady_clock::time_point end);
    }
    namespace regression
    {
        std::pair<double, double> get_linear_fit(vector<double> x, vector<double> y, int n);
        double euclidean_dist(double x1, double y1, double x2, double y2);
    }
    vector<cv::Scalar> get_colors(int vec_len);
    std::string get_frame_path(int frame, std::string tmp_folder);
}
