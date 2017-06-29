#include <iostream>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../include/stitcher.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    vector<string> img_names;
    int n;
    cout << "请输入拼接图片的数量" << endl;
    cin >> n;

    for (int i =1; i <= n; i++)
    {
        char img_path[100] = {0};
        sprintf(img_path,"../images/7-43/img (%d).jpg",i);
        img_names.push_back(String(img_path));

        memset(img_path,0,100);
        sprintf(img_path,"../images/5-44/img (%d).jpg",i);
        img_names.push_back(String(img_path));
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
        full_img[i] = imread(img_names[i]);
    }

    //stich images in full_img
    Stitcher m_sticher;
    Mat result = m_sticher.stichImg(full_img);

    //show result
    resize(result,result,Size(640,480),0,0,CV_INTER_LINEAR);
    namedWindow("result", 1);
    imshow("result", result);
    waitKey(0);

    return 0;
}
