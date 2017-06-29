#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "stitcher.h"

using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{
    vector<string> img_names;

    //int n;
    int n1;
    cout << "请输入拼接7度图片的数量" << endl;
    //cin >> n;
    cout << "请输入拼接5度图片的数量" << endl;
    cin >> n1;
    String str = "../stitching_pic/stitcher_demo/images/7-43/img (";
    String str1 = ").jpg";
    String str2, str6;
    String str_= "../stitching_pic/stitcher_demo/images/5-44/img (";
    String str1_ = ").jpg";
    String str2_, str3_;
    for (int i =1; i <= n1; i++)
    {
        stringstream stream,stream1;
        int j=i;
        stream <<j;
        stream >> str6;
        stream1<<i;
        stream1>>str3_;
        str2 = str + str6 + str1;
        str2_ = str_ + str3_ + str1_;
        img_names.push_back(str2);
        img_names.push_back(str2_);
    }

    cv::setBreakOnError(true);

    // Check if have enough images
    int num_images = static_cast<int>(img_names.size());
    if (num_images < 2)
    {
        cout<<"需要更多图片"<<endl;
        return -1;
    }

    //load images
    vector<Mat> full_img(num_images);
    for (int i = 0; i < num_images; ++i)
    {
        cout << "name" << i << ":" << img_names[i] << endl;
        full_img[i] = imread(img_names[i]);
    }

    //stich images in full_img
    Stitcher m_sticher;
    Mat result = m_sticher.stichImg(full_img);
    resize(result,result,Size(640,480),0,0,CV_INTER_LINEAR);
    namedWindow("result", 1);
    imshow("result", result);
    waitKey(0);
    return 0;
}
