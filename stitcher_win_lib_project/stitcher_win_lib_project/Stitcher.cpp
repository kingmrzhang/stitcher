#include "stdafx.h"
#include "Stitcher.h"
#include <string>
#include "../../Common/SdustStitcher/SdustStitcher.h"

Stitcher::Stitcher()
{
}


Stitcher::~Stitcher()
{
}

Mat Stitcher::stichImg(char path[][100], int size)
{
	cv::setBreakOnError(true);

	// Check if have enough images
	if (size < 2)
	{
		cout << "需要更多图片" << endl;
		return Mat();
	}

	//load images
	vector<Mat> full_img(size);
	for (int i = 0; i < size; i++)
	{
		string str = string(path[i]);
		cout << i << str << endl;
		full_img[i] = imread(str);
	}

	//stich images in full_img
	return SdustStitcher().stichImg(full_img);
}

int stichImg_by_path(char** full_path,int size)
{
	//load images
	system("cd");
	vector<Mat> full_img(size);
	for (int i = 0; i < size; i++)
	{
		string str = string(full_path[i]);
		cout << str << endl;
		full_img[i] = imread(str);
	}

	Mat result = SdustStitcher().stichImg(full_img);

	imwrite("result.jpg", result);
	return 0;
}