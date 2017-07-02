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
	return stichimg_from_path(full_path,size);
}

int stichimg_from_path(char** src_path, int size)
{
	//load images
	vector<Mat> full_img(size);
	for (int i = 0; i < size; i++)
	{
		string str = string(src_path[i]);
		cout << str << endl;
		full_img[i] = imread(str);
	}
	Mat result = SdustStitcher().stichImg(full_img);
	imwrite("result.jpg", result);
	if (result.size <= 0)
		return 1;
	return 0;
}

int stichimg_from_path_to_path(char** src_path, int size, char* dst_path)
{
	//load images
	vector<Mat> full_img(size);
	for (int i = 0; i < size; i++)
	{
		string str = string(src_path[i]);
		cout << str << endl;
		full_img[i] = imread(str);
	}
	//stitich images
	Mat result = SdustStitcher().stichImg(full_img);
	imwrite(string(dst_path), result);
	if (result.size <= 0)
		return 1;
	return 0;
}