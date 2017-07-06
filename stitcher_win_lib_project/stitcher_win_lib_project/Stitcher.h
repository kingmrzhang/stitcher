#pragma once

#ifdef STITCHER_WIN_LIB_PROJECT_EXPORTS
#define EXPORTS_STITCHER _declspec( dllexport )
#else
#define EXPORTS_STITCHER _declspec(dllimport)
#endif

#include <iostream>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class EXPORTS_STITCHER Stitcher
{
public:
	Stitcher();
	~Stitcher();
	Mat stitchImg(char path[][100],int size);
	Mat stitchImg(const vector<Mat> full_img);
};

extern "C" EXPORTS_STITCHER int stitchimg_from_paths_to_path(char** src_path, int size, char* dst_path);
extern "C" EXPORTS_STITCHER unsigned char*  stitchimg_from_mats_to_mat(unsigned char* mats, 
	int* mats_rows, int* mats_cols, int* mats_cvtype, int size,
	int* mat_rows, int* mat_cols, int* mat_cvtype);
extern "C" EXPORTS_STITCHER unsigned char*  stitchimg_from_paths_to_mat(char** src_path, int size,
	int* mat_rows, int* mat_cols, int* mat_cvtype);

extern "C" EXPORTS_STITCHER void free_img(char* p_img);

//Interfaces for test
extern "C" EXPORTS_STITCHER int show_img(unsigned char* img_data, int rows, int cols, int cvtype,char* window_name);
extern "C" EXPORTS_STITCHER unsigned char* load_img(char* img_path,int* rows,int* cols,int* cvtype);
