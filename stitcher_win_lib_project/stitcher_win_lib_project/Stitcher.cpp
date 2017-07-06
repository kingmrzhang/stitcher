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

//************************************
// Method:    stitchImg	拼接图片
// FullName:  Stitcher::stitchImg
// Access:    public 
// Returns:   cv::Mat	拼接结果的Mat
// Qualifier:
// Parameter: char path[][100]	待拼接图片路径
// Parameter: int size	待拼接图片数量
//************************************
Mat Stitcher::stitchImg(char path[][100], int size)
{
	cv::setBreakOnError(true);

	// Check if have enough images
	if (size < 2)
	{
		cout << "We need more images!" << endl;
		return Mat();
	}

	//load images
	vector<Mat> full_img(size);
	for (int i = 0; i < size; i++)
	{
		string str = string(path[i]);
		full_img[i] = imread(str);
	}

	//stitch images in full_img
	return SdustStitcher().stichImg(full_img);
}

//************************************
// Method:    stitchImg	拼接图片
// FullName:  Stitcher::stitchImg
// Access:    public 
// Returns:   cv::Mat	拼接结果的Mat
// Qualifier:
// Parameter: const vector<Mat> full_img	所有待拼接图片
//************************************
Mat Stitcher::stitchImg(const vector<Mat> full_img)
{
	//stitch images in full_img
	return SdustStitcher().stichImg(full_img);
}

//************************************
// Method:    stitchimg_from_paths_to_path	拼接图片
// FullName:  stitchimg_from_paths_to_path
// Access:    public 
// Returns:   int	拼接是否成功
// Qualifier:
// Parameter: char * * src_path	待拼接图片路径
// Parameter: int size	待拼接图片数量
// Parameter: char * dst_path	拼接结果存储路径
//************************************
int stitchimg_from_paths_to_path(char** src_path, int size, char* dst_path)
{
	//load images
	vector<Mat> full_img(size);
	for (int i = 0; i < size; i++)
	{
		string str = string(src_path[i]);
		full_img[i] = imread(str);
	}
	//stitch images
	Mat result = SdustStitcher().stichImg(full_img);
	imwrite(string(dst_path), result);
	if (result.size <= 0)
		return 1;
	return 0;
}

//************************************
// Method:    stitchimg_from_mats_to_mat	图片拼接
// FullName:  stitchimg_from_mats_to_mat
// Access:    public 
// Returns:   unsigned char*	拼接结果的Mat数据
// Qualifier:
// Parameter: unsigned char * mats	所有待拼接图片的Mat数据
// Parameter: int * mats_rows	待拼接图片的行数组
// Parameter: int * mats_cols	待拼接图片的列数组
// Parameter: int * mats_cvtype	待拼接图片的类型数组
// Parameter: int size			待拼接图片数量
// Parameter: int * mat_rows	返回拼接结果行数
// Parameter: int * mat_cols	返回拼接结果列数
// Parameter: int * mat_cvtype	返回拼接结果类型
//************************************
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

//************************************
// Method:    stitchimg_from_paths_to_mat	拼接图片
// FullName:  stitchimg_from_paths_to_mat
// Access:    public 
// Returns:   unsigned char*				拼接结果Mat数据
// Qualifier:
// Parameter: char * * src_path				待拼接图片路径
// Parameter: int size						待拼接图片数量
// Parameter: int * mat_rows				返回拼接结果行数
// Parameter: int * mat_cols				返回拼接结果列数
// Parameter: int * mat_cvtype				返回拼接结果类型
//************************************
unsigned char*  stitchimg_from_paths_to_mat(char** src_path, int size,
	int* mat_rows, int* mat_cols, int* mat_cvtype)
{
	//load images
	vector<Mat> full_img(size);
	for (int i = 0; i < size; i++)
	{
		string str = string(src_path[i]);
		full_img[i] = imread(str);
	}

	Mat img = SdustStitcher().stichImg(full_img);

	(*mat_rows) = img.rows;
	(*mat_cols) = img.cols;
	(*mat_cvtype) = img.type();
	unsigned char* img_data = (unsigned char*)malloc(img.total() * img.channels());
	if (img_data == NULL)
		cout << "no memory" << endl;
	memcpy(img_data, img.data, img.total() * img.channels());

	return img_data;
}

//************************************
// Method:    show_img					显示图片
// FullName:  show_img
// Access:    public 
// Returns:   int						图片显示是否成功
// Qualifier:
// Parameter: unsigned char * img_data	待显示图片的Mat数据
// Parameter: int rows					带显示图片的行数
// Parameter: int cols					带显示图片的列数
// Parameter: int cvtype				带显示图片的类型
// Parameter: char * window_name		用于显示图片的窗体名
//************************************
int show_img(unsigned char* img_data,int rows,int cols,int cvtype,char* window_name)
{
	Mat img(rows, cols, cvtype, img_data);
	namedWindow(string(window_name), 1);
	imshow(string(window_name), img);
	waitKey(0);
	return 0;
}

//************************************
// Method:    load_img			加载图片
// FullName:  load_img
// Access:    public 
// Returns:   unsigned char*	被加载图片的Mat数据
// Qualifier:
// Parameter: char * img_path	待加载图片的路径
// Parameter: int * rows		被加载图片的行数
// Parameter: int * cols		被加载图片的列数
// Parameter: int * cvtype		被加载图片的类型
//************************************
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

//************************************
// Method:    free_img		释放指针所指向的内存空间
// FullName:  free_img
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: char * p_img	待释放空间的指针
//************************************
void free_img(char* p_img)
{
	if (p_img != NULL)
		free(p_img);
}