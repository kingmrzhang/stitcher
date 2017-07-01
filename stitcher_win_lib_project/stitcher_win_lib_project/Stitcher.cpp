#include "stdafx.h"
#include "Stitcher.h"
#include <string>
#include "../../Common/SdustStitcher/SdustStitcher.h"

#include <sstream>
#include <vector>
#include <iterator>

template<typename Out>
void split(const std::string &s, char delim, Out result) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

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

int Add(int a, int b)
{
	return (a + b);
}

Mat Stitcher_stichImg(char path[][100], int size)
{
	Stitcher s;
	return s.stichImg(path, size);
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