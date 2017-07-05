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

Mat Stitcher::stitchImg(char path[][100], int size)
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
		full_img[i] = imread(str);
	}

	//stich images in full_img
	return SdustStitcher().stichImg(full_img);
}

int stitchimg_from_path(char** src_path, int size)
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

int stitchimg_from_path_to_path(char** src_path, int size, char* dst_path)
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

unsigned char*  stitchimg_from_mats_to_mat(unsigned char* mats, int* mats_rows, int* mats_cols, int* mats_cvtype, int size,
	int* mat_rows, int* mat_cols, int* mat_cvtype)
{
	vector<Mat> vec_mats;
	int current_offset = 0;
	for (int i = 0; i < size; i++) {
		Mat img(mats_rows[i], mats_cols[i], mats_cvtype[i], mats+current_offset);
		vec_mats.push_back(img);
		current_offset += (img.total() * img.channels());
	}

	Mat img = SdustStitcher().stichImg(vec_mats);

	(*mat_rows) = img.rows;
	(*mat_cols) = img.cols;
	(*mat_cvtype) = img.type();
	unsigned char* img_data = (unsigned char*)malloc(img.total() * img.channels());
	if (img_data == NULL)
		cout << "no memory" << endl;
	memcpy(img_data, img.data, img.total() * img.channels());

	return img_data;
}

int show_img(unsigned char* img_data,int rows,int cols,int cvtype)
{
	Mat img(rows, cols, cvtype, img_data);
	namedWindow("showImg", 1);
	imshow("showImg", img);
	waitKey(0);
	return 0;
}

unsigned char* load_img(char* img_path, int* rows, int* cols, int* cvtype)
{
	Mat img = imread(string(img_path));
	(*rows) = img.rows;
	(*cols) = img.cols;
	(*cvtype) = img.type();
	
	unsigned char* img_data = (unsigned char*)malloc(img.total() * img.channels());
	if (img_data == NULL)
		cout << "no memory" << endl;
	
	memcpy(img_data, img.data,img.total() * img.channels());

	return img_data;
}

void free_img(char* p_img)
{
	free(p_img);
}