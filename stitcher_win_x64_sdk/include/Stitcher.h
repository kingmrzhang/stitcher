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
	Mat stichImg(char path[][100],int size);
};

extern "C" EXPORTS_STITCHER int stichImg_by_path(char** full_path, int size);

extern "C" EXPORTS_STITCHER int stichimg_from_path(char** src_path, int size);
extern "C" EXPORTS_STITCHER int stichimg_from_path_to_path(char** src_path, int size, char* dst_path);