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
// Method:    stitchImg	ƴ��ͼƬ
// FullName:  Stitcher::stitchImg
// Access:    public 
// Returns:   cv::Mat	ƴ�ӽ����Mat
// Qualifier:
// Parameter: char path[][100]	��ƴ��ͼƬ·��
// Parameter: int size	��ƴ��ͼƬ����
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
// Method:    stitchImg	ƴ��ͼƬ
// FullName:  Stitcher::stitchImg
// Access:    public 
// Returns:   cv::Mat	ƴ�ӽ����Mat
// Qualifier:
// Parameter: const vector<Mat> full_img	���д�ƴ��ͼƬ
//************************************
Mat Stitcher::stitchImg(const vector<Mat> full_img)
{
	//stitch images in full_img
	return SdustStitcher().stichImg(full_img);
}

//************************************
// Method:    stitchimg_from_paths_to_path	ƴ��ͼƬ
// FullName:  stitchimg_from_paths_to_path
// Access:    public 
// Returns:   int	ƴ���Ƿ�ɹ�
// Qualifier:
// Parameter: char * * src_path	��ƴ��ͼƬ·��
// Parameter: int size	��ƴ��ͼƬ����
// Parameter: char * dst_path	ƴ�ӽ���洢·��
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
// Method:    stitchimg_from_mats_to_mat	ͼƬƴ��
// FullName:  stitchimg_from_mats_to_mat
// Access:    public 
// Returns:   unsigned char*	ƴ�ӽ����Mat����
// Qualifier:
// Parameter: unsigned char * mats	���д�ƴ��ͼƬ��Mat����
// Parameter: int * mats_rows	��ƴ��ͼƬ��������
// Parameter: int * mats_cols	��ƴ��ͼƬ��������
// Parameter: int * mats_cvtype	��ƴ��ͼƬ����������
// Parameter: int size			��ƴ��ͼƬ����
// Parameter: int * mat_rows	����ƴ�ӽ������
// Parameter: int * mat_cols	����ƴ�ӽ������
// Parameter: int * mat_cvtype	����ƴ�ӽ������
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
// Method:    stitchimg_from_paths_to_mat	ƴ��ͼƬ
// FullName:  stitchimg_from_paths_to_mat
// Access:    public 
// Returns:   unsigned char*				ƴ�ӽ��Mat����
// Qualifier:
// Parameter: char * * src_path				��ƴ��ͼƬ·��
// Parameter: int size						��ƴ��ͼƬ����
// Parameter: int * mat_rows				����ƴ�ӽ������
// Parameter: int * mat_cols				����ƴ�ӽ������
// Parameter: int * mat_cvtype				����ƴ�ӽ������
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
// Method:    show_img					��ʾͼƬ
// FullName:  show_img
// Access:    public 
// Returns:   int						ͼƬ��ʾ�Ƿ�ɹ�
// Qualifier:
// Parameter: unsigned char * img_data	����ʾͼƬ��Mat����
// Parameter: int rows					����ʾͼƬ������
// Parameter: int cols					����ʾͼƬ������
// Parameter: int cvtype				����ʾͼƬ������
// Parameter: char * window_name		������ʾͼƬ�Ĵ�����
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
// Method:    load_img			����ͼƬ
// FullName:  load_img
// Access:    public 
// Returns:   unsigned char*	������ͼƬ��Mat����
// Qualifier:
// Parameter: char * img_path	������ͼƬ��·��
// Parameter: int * rows		������ͼƬ������
// Parameter: int * cols		������ͼƬ������
// Parameter: int * cvtype		������ͼƬ������
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
// Method:    free_img		�ͷ�ָ����ָ����ڴ�ռ�
// FullName:  free_img
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: char * p_img	���ͷſռ��ָ��
//************************************
void free_img(char* p_img)
{
	if (p_img != NULL)
		free(p_img);
}