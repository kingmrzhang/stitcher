#ifndef SDUSTSTITCHER_H
#define SDUSTSTITCHER_H
#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/stitching/detail/autocalib.hpp"
#include "opencv2/stitching/detail/blenders.hpp"
#include "opencv2/stitching/detail/camera.hpp"
#include "opencv2/stitching/detail/exposure_compensate.hpp"
#include "opencv2/stitching/detail/matchers.hpp"
#include "opencv2/stitching/detail/motion_estimators.hpp"
#include "opencv2/stitching/detail/seam_finders.hpp"
#include "opencv2/stitching/detail/util.hpp"
#include "opencv2/stitching/detail/warpers.hpp"
#include "opencv2/stitching/warpers.hpp"

using namespace std;
using namespace cv;
using namespace cv::detail;

class SdustStitcher
{
public:
    SdustStitcher();
    Mat stichImg(vector<Mat> full_img);

private:
    // Default command line args
    bool preview;
    bool try_gpu;
    double work_megapix;//图像的尺寸大小
    double seam_megapix;//拼接缝像素的大小
    double compose_megapix;//拼接分辨率
    float conf_thresh;//来自同一全景图置信度
    string ba_cost_func;
    string ba_refine_mask;
    bool do_wave_correct;
    WaveCorrectKind wave_correct;//水平波形校检
    bool save_graph;
    std::string save_graph_to;
    int expos_comp_type;//光照补偿方法
    float match_conf;//特征点检测置信等级，最近邻匹配距离和次近邻匹配距离比值
    int blend_type;//融合方法
    float blend_strength;
    string result_name;


};

#endif // STITCHER_H
