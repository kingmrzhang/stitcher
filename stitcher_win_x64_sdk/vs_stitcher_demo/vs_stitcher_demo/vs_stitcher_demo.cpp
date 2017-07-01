// vs_stitcher_demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "..\\..\\include\\Stitcher.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

#pragma comment(lib, "..\\..\\lib\\stitcher_win_lib_project.lib")
int _tmain(int argc, _TCHAR* argv[])
{
	char path[100][100];
	int n;
	cout << "Please input the number of row-picture" << endl;
	cin >> n;

	memset(path, 0, 100*100);
	for (int i = 1; i <= n; i++)
	{
		sprintf_s(path[i*2-2], "..\\..\\..\\Common\\images\\7-43\\img (%d).jpg", i);
		sprintf_s(path[i*2-1], "..\\..\\..\\Common\\images\\5-44\\img (%d).jpg", i);
	}

	cv::setBreakOnError(true);

	// Check if have enough images
	int size = n*2;
	if (size < 2)
	{
		cout << "We need more pictures" << endl;
		return -1;
	}

	//stich images in full_img
	Stitcher m_sticher;
	Mat result = m_sticher.stichImg(path, size);

	//show result
	resize(result, result, Size(640, 480), 0, 0, CV_INTER_LINEAR);
	namedWindow("result", 1);
	imshow("result", result);
	waitKey(0);
	return 0;
}

