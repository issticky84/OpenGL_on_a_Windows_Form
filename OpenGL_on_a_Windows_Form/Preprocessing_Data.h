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
	//vector < vector<float> > raw_data;
	vector < vector<float> > lab_vertices;

	void output_mat_as_txt_file(char file_name[],Mat);
	void output_mat_as_csv_file(char file_name[],Mat);
	void calcCovMat(Mat&, Mat&, Mat&);
	void reduceDimPCA(Mat&, int, Mat&, Mat&);
	//void read_raw_data();
	float degtorad(float);
	float norm_value(float,float,float);
	float DistanceOfLontitudeAndLatitude(float,float,float,float);
	void set_hour_data(vector < vector<float> > ,int time_title[]);
	Mat Gaussian_filter(vector < vector<float> >,int attribute_title[],int);
	Mat set_matrix(vector < vector<float> >,int attribute_title[],int);
	void voting(int,Mat,int);
	Mat Position_by_MDS(Mat,int ,float);
	Mat lab_alignment(Mat,int);
	Mat lab_alignment_dim1(Mat,int);
	Mat lab_alignment_dim2(Mat,int);
	void read_lab_csv();
	bool lab_boundary_test(float,float,float);
	Mat LAB2RGB(Mat);
	Mat compute_centroid(Mat);
	void gray2rgb(float,float& ,float& ,float&);
	Mat normalize_column(Mat);
	void output_mat_as_csv_file_float(char file_name[],Mat);
public:
	Preprocessing_Data();
	void start(vector < vector<float> >,int);
	void Initial_selection_flag(bool,bool,bool,bool);

	int num_of_five_minutes;
	//int raw_data_size;
	vector <int> hour_data;
	Mat histogram;//int
	Mat rgb_mat;//float
	Mat rgb_mat3;//float
	Mat position;//double
	Mat raw_data_3D;//float
	Mat raw_data_mat;//float
	vector<vector2> hour_range;
	vector<int> hour_index;
	int num_of_begin_hour,begin_hour;
	bool waiting_flag;
	bool select_gravity,select_linear_acc,select_gyro,select_distance;
	int progress_value;
};



#endif	