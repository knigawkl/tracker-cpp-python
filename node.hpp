#pragma once

#include <opencv2/opencv.hpp>

#include "utils.hpp"
#include "templates.hpp"

struct Box
{
public:
    int x, y, x_min, y_min, x_max, y_max, height, width;
    float area;
    void print() const;
    float calc_iou(Box b);    
};

class Node
{
// Represents an object detection
public:
    int id;
    int cluster_id;
    int next_node_id = -1;
    int prev_node_id = -1;
    Box coords;
    cv::Mat histogram;
    Node()
    {
        ;
    }
    Node(const Box &d, const cv::Mat &frame, int detection_id, int frame_id): 
         coords(d), id(detection_id), cluster_id(frame_id)
    {
        set_histogram(frame);
    }
    Node(const Box &d, int detection_id, int frame_id, const cv::Mat &histogram): 
         coords(d), id(detection_id), cluster_id(frame_id), histogram(histogram) {}
    void print() const;
    static void print_nodes(const vector2d<Node> &nodes);
    static void print_detection_path(const vector<Node> &path);
private:
    void set_histogram(const cv::Mat &frame);
};
