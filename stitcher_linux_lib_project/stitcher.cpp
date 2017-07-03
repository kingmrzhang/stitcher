#include "stitcher.h"
#include "../Common/SdustStitcher/SdustStitcher.h"
Stitcher::Stitcher()
{

}

Mat Stitcher::stichImg(vector<Mat> full_img)
{
    return SdustStitcher().stichImg(full_img);
}
