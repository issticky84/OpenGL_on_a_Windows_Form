#ifndef Preprocessing_DataH
#define Preprocessing_DataH

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <highgui.h>
#include <vector>
#include "cv.h"
#include "mtxlib.h"//vector2

#define LENGTH 1000

using namespace std; 
using namespace cv;

class Preprocessing_Data
{
private:
	char file_csv_data[200];
	map<int,int> hour_map;
	vector < vector<float> > raw_data;

	void output_mat_as_txt_file(char file_name[],Mat);
	void output_mat_as_csv_file(char file_name[],Mat);
	void calcCovMat(Mat&, Mat&, Mat&);
	void reduceDimPCA(Mat&, int, Mat&, Mat&);
	void read_raw_data();
	float degtorad(float);
	float norm_value(float,float,float);
	float DistanceOfLontitudeAndLatitude(float,float,float,float);
	void set_hour_data(int time_title[]);
	Mat Gaussian_filter(int attribute_title[],int);
	Mat set_matrix(int attribute_title[],int);
	void voting(int,Mat,int);
	Mat Position_by_MDS(Mat,int ,float);
public:
	void start();

	int num_of_five_minutes;
	vector <int> hour_data;
	Mat histogram;//int
	Mat rgb_mat;//float
	Mat position;//double
	Mat raw_data_3D;//float
	vector<vector2> hour_range;
	vector<int> hour_index;
	int num_of_begin_hour,begin_hour;
};



#endif	