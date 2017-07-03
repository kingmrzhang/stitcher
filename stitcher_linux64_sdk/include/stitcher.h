#ifndef STITCHER_H
#define STITCHER_H

#include <vector>
#include <opencv2/highgui.hpp>
class Stitcher
{
public:
    Stitcher();
    cv::Mat stichImg(std::vector<cv::Mat> full_img);
};

#endif // STITCHER_H
