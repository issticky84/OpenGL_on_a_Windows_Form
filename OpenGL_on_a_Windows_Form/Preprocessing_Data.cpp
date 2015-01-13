#include "stdafx.h"
#include "Preprocessing_Data.h"

#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include "tapkee/tapkee.hpp"
#include "tapkee/callbacks/dummy_callbacks.hpp"
#include <opencv2/core/eigen.hpp> //cv2eigen
#include "mtxlib.h"//vector2
#include <vector>
#include <map>
#include <iostream>

using namespace tapkee;
using namespace Eigen;

void Preprocessing_Data::start(vector < vector<float> > raw_data,int k)
{
	select_gravity = true;
	select_linear_acc = true;
	select_gyro = true;
	select_distance = true;
	//=================Read CSV file====================//
	//clock_t begin = clock();
	//strcpy(file_csv_data,"../../csv_data/BigData_20141121_0723_new.csv");
	//read_raw_data();
	//clock_t end = clock();
	//printf("Read csv elapsed time: %f\n",double(end - begin) / CLOCKS_PER_SEC);
	//==================================================//

	int attribute_title_size = 11;
	int attribute_title[] = {4,5,6,7,8,9,10,11,12,22,23};//(gravity_x,gravity_y,gravity_z),(linear_acc_x,linear_acc_y,linear_acc_z),(gyro_x,gyro_y,gyro_z),(latitude,longitude)
	int time_title[] = {29,30,31,32,33};//hour(30),minute(31)
	
	//============Setting matrix for K-means============//
	clock_t begin2 = clock();
	set_hour_data(raw_data,time_title);
	Mat model = set_matrix(raw_data,attribute_title,attribute_title_size).clone();
	clock_t end2 = clock();
	printf("Setting matrix elapsed time: %f\n",double(end2 - begin2) / CLOCKS_PER_SEC);
	//==================================================//
	//output_mat_as_txt_file("model.txt",model);
    //int k = 50; 
    Mat cluster_tag; //Tag:0~k-1
    int attempts = 2;//應該是執行次數
	Mat cluster_centers;
	//==============K means clustering==================//
    
	//使用k means分群
	clock_t begin3 = clock();
	kmeans(model, k, cluster_tag,TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10, 0.0001), attempts,KMEANS_PP_CENTERS,cluster_centers);
	clock_t end3 = clock();
    //TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10, 1),  這裡有三個參數，決定k-means何時結束，第二個參數是指迭代最大次數，第三個參數是精確度多少，第一個參數是指依照前兩個參數的哪一個為準，以範例中就是兩者都參照，以 or 的方式決定
	printf("Kmeans (K = %d) elapsed time: %f\n",k,double(end3 - begin3) / CLOCKS_PER_SEC);
	//==================================================//
	
	voting(k,cluster_tag,model.rows); // Type: int
	cluster_tag.release();
	//===================PCA RGB=======================//
	Mat components, result;
	int rDim = 3;
	clock_t begin4 = clock();
	reduceDimPCA(cluster_centers, rDim, components, result);
	clock_t end4 = clock();
	printf("PCA RGB elapsed time: %f\n",double(end4 - begin4) / CLOCKS_PER_SEC);
	rgb_mat = result.clone();
	for(int i=0;i<result.cols;i++)
		normalize(result.col(i),rgb_mat.col(i),0,1,NORM_MINMAX); //normalize to 0-1
	//output_mat_as_txt_file("rgb_mat.txt",rgb_mat);
	//===============Position (MDS)=====================//
	clock_t begin5 = clock();
	position = Position_by_MDS(cluster_centers,k,20).clone(); //Type:double
	clock_t end5 = clock();
	printf("MDS Position elapsed time: %f\n",double(end5 - begin5) / CLOCKS_PER_SEC);
	cluster_centers.release();
	//===================PCA raw data 3 dim=======================//
	reduceDimPCA(model, rDim, components, result);
	raw_data_3D = result.clone();
	for(int i=0;i<result.cols;i++)
		normalize(result.col(i),raw_data_3D.col(i),0,1,NORM_MINMAX); //normalize to 0-1
	//model.release();	
}

void Preprocessing_Data::output_mat_as_txt_file(char file_name[],Mat mat)
{
	ofstream fout(file_name);
	fout << mat;
}

void Preprocessing_Data::output_mat_as_csv_file(char file_name[],Mat mat)
{
	ofstream fout(file_name); 
	for(int i=0;i<mat.rows;i++)
	{
		for(int j=0;j<mat.cols;j++)
		{
			fout << mat.at<float>(i,j) << ",";
		}
		fout << endl;
	}
}            

/**
 * 從data計算平均與covariance matrix
 * http://en.wikipedia.org/wiki/Covariance_matrix#Definition
 *
 */
void Preprocessing_Data::calcCovMat(Mat& data, Mat& mean, Mat& cov){
    // 初始化
	cov = Mat::zeros(data.cols, data.cols, CV_32F);

	// 計算資料點的重心(平均)
	mean = Mat::zeros(1, data.cols, CV_32F);
	for (int i = 0; i < data.rows; i++){
		mean += data.row(i);
	}
	mean /= double(data.rows);

	// 計算covariance matrix
	for (int i = 0; i < data.rows; i++){
		cov += (data.row(i) - mean).t() * (data.row(i) - mean);
	}
	cov /= double(data.rows);
}



/**
 * 用Principal Component Analysis (PCA) 做降維
 *
 */
void Preprocessing_Data::reduceDimPCA(Mat& data, int rDim, Mat& components, Mat& result){
	// 計算covariance matrix
	Mat cov, mean;
	calcCovMat(data, mean, cov);

	// 從covariance matrix計算eigenvectors
	// http://docs.opencv.org/modules/core/doc/operations_on_arrays.html?highlight=pca#eigen
	Mat eigenVal, eigenVec;
	eigen(cov, eigenVal, eigenVec);

	// 記錄前rDim個principal components
	components = Mat(rDim, data.cols, CV_32F);
	for (int i = 0; i < rDim; i++){
		// http://docs.opencv.org/modules/core/doc/basic_structures.html?highlight=mat%20row#mat-row
		eigenVec.row(i).copyTo(components.row(i));

		// http://docs.opencv.org/modules/core/doc/operations_on_arrays.html?highlight=normalize#normalize
		normalize(components.row(i), components.row(i));
	}

	// 計算結果
	result = Mat(data.rows, rDim, CV_32F);
	for (int i = 0; i < data.rows; i++){
		for (int j = 0; j < rDim; j++){
			// 內積(投影到principal component上)
			// http://docs.opencv.org/modules/core/doc/basic_structures.html?highlight=dot#mat-dot
			result.at<float>(i, j) = (data.row(i) - mean).dot(components.row(j));
		}
	}
}

//void Preprocessing_Data::read_raw_data()
//{
//	FILE *csv_file;
//	csv_file = fopen(file_csv_data,"r");
//	if(!csv_file) 
//	{
//		cout << "Can't open config file!" << endl;
//		exit(1);
//	}
//
//	char line[LENGTH];
//	char *token;
//	int i,j;
//	i = j = 0;
//	fgets(line,LENGTH,csv_file); //ignore sep=
//	fgets(line,LENGTH,csv_file); //ignore title
//
//	while(!feof(csv_file))
//	{
//		fgets(line,LENGTH,csv_file);
//		//token = strtok(line,";");
//		token = strtok(line,";");
//		raw_data.push_back(vector<float> (1));
//		//printf("%s ",token);
//		while(token!=NULL)
//		{
//			raw_data.back().push_back(atof(token));
//			//token = strtok(NULL," ;:");
//			token = strtok(NULL," ;:/");
//		}
//	}
//
//	//cout << raw_data[0][1] << " " << raw_data[0][29] << " " << raw_data[0][30] << " " << raw_data[0][31] << " " << raw_data[0][32]  << " " << raw_data[0][33] << endl;
//	//29:Year,30:Hour,31:Minute,32:second,33:millisecond
//
//	cout << "Csv Data Size: " << raw_data.size() <<endl;
//	//cout << raw_data[0].size() << endl;
//
//	raw_data_size = raw_data.size();
//
//	fclose(csv_file);
//}

float Preprocessing_Data::degtorad(float deg)
{
	float rad = deg *3.14159265 / 180;
	return rad;
}

float Preprocessing_Data::norm_value(float v1,float v2,float v3)
{
	return sqrt(v1*v1 + v2*v2 + v3*v3);
}

float Preprocessing_Data::DistanceOfLontitudeAndLatitude(float lat1,float lat2,float lon1,float lon2)
{
	float R = 6371; //km
	float theta1 = degtorad(lat1);
	float theta2 = degtorad(lat2);
	float delta_theta = degtorad(lat2-lat1);
	float delta_lumda = degtorad(lon2-lon1);
	float a = sin(delta_theta/2) * sin(delta_theta/2) + cos(theta1) * cos(theta2) * sin(delta_lumda/2) * sin(delta_lumda/2);
	float c = 2 * atan2((double)sqrt(a),(double)sqrt(1.0-a));
	float d = R * c;

	if(d>1.0) 
		return 0.01;
	else 
		return d;
}

void Preprocessing_Data::set_hour_data(vector < vector<float> > raw_data,int time_title[])
{
	int hour_id = time_title[1];
	int time_step_amount = floor(raw_data.size()/600.0);
	num_of_five_minutes = time_step_amount;
	hour_data.resize(time_step_amount);
	int t = 0;
	for(int i=0;i<time_step_amount;i++)
	{
		hour_data[i] = raw_data[t][hour_id]; 
		t += 600;
	}
	//////////////////////////////////////////////////////////////////
	num_of_five_minutes = hour_data.size()-1;
	int num_of_end_hour,end_hour;
	for(int i=0;i<hour_data.size();i++)
	{
		hour_map[hour_data[i]]++;
	}

	map<int,int>::iterator it;
	int start = 0;
	int hour_num;
	for(it = hour_map.begin(); it!=hour_map.end(); ++it)
	{
		hour_num = 11;
		if(it == hour_map.begin())
		{
			begin_hour = it->first;
			num_of_begin_hour = it->second;
			hour_num = num_of_begin_hour - 1;
		}
		else if(next(it,1)==hour_map.end())
		{
			end_hour = it->first;
			num_of_end_hour = it->second;
			hour_num = num_of_end_hour - 1 - 1;
		}

		vector2 temp;
		temp.x = start;
		temp.y = start + hour_num;
		hour_range.push_back(temp);
		hour_index.push_back(it->first);
		
		start += (hour_num+1);
		
	}
}

Mat Preprocessing_Data::Gaussian_filter(vector < vector<float> > raw_data,int attribute_title[],int MAX_KERNEL_LENGTH)
{
	Mat Gaussian_filter_mat(raw_data.size(),9, CV_32F);

	//Apply Gaussian filter to raw data(0~8)
	for(int i=0;i<raw_data.size();i++)
	{
		for(int j=0;j<9;j++)
		{
			Gaussian_filter_mat.at<float>(i,j) = raw_data[i][attribute_title[j]];
		}
	}

	//int MAX_KERNEL_LENGTH = 20;
    for(int i=1;i<MAX_KERNEL_LENGTH;i=i+2)
    { 
		GaussianBlur( Gaussian_filter_mat, Gaussian_filter_mat, Size( i, i ), 0.5, 0.5 );
	}

	return Gaussian_filter_mat;
}

Mat Preprocessing_Data::set_matrix(vector < vector<float> > raw_data,int attribute_title[],int attribute_title_size)
{
	Mat handle_mat;

	Mat Gaussian_filter_mat = Gaussian_filter(raw_data,attribute_title,20).clone();

	Mat norm_gravity(1, raw_data.size(), CV_32F);
	Mat norm_linear_acc(1, raw_data.size(), CV_32F);
	Mat norm_gyro(1, raw_data.size(), CV_32F);
	//Compute norm
	for(int i=0;i<raw_data.size();i++)
	{
		norm_gravity.at<float>(0,i) = norm_value(Gaussian_filter_mat.at<float>(i,attribute_title[0]),Gaussian_filter_mat.at<float>(i,attribute_title[1]),Gaussian_filter_mat.at<float>(i,attribute_title[2]));
		norm_linear_acc.at<float>(0,i) = norm_value(Gaussian_filter_mat.at<float>(i,attribute_title[3]),Gaussian_filter_mat.at<float>(i,attribute_title[4]),Gaussian_filter_mat.at<float>(i,attribute_title[5]));
		norm_gyro.at<float>(0,i) = norm_value(Gaussian_filter_mat.at<float>(i,attribute_title[6]),Gaussian_filter_mat.at<float>(i,attribute_title[7]),Gaussian_filter_mat.at<float>(i,attribute_title[8]));
	}

	if(select_gravity) handle_mat.push_back(norm_gravity);
	if(select_linear_acc) handle_mat.push_back(norm_linear_acc);
	if(select_gyro) handle_mat.push_back(norm_gyro);
	//for(int i=0;i<raw_data.size();i++)
	//{
	//	handle_mat.at<float>(i,0) = norm_value(Gaussian_filter_mat.at<float>(i,attribute_title[0]),Gaussian_filter_mat.at<float>(i,attribute_title[1]),Gaussian_filter_mat.at<float>(i,attribute_title[2]));
	//	handle_mat.at<float>(i,1) = norm_value(Gaussian_filter_mat.at<float>(i,attribute_title[3]),Gaussian_filter_mat.at<float>(i,attribute_title[4]),Gaussian_filter_mat.at<float>(i,attribute_title[5]));
	//	handle_mat.at<float>(i,2) = norm_value(Gaussian_filter_mat.at<float>(i,attribute_title[6]),Gaussian_filter_mat.at<float>(i,attribute_title[7]),Gaussian_filter_mat.at<float>(i,attribute_title[8]));
	//}

	//for(int i=0;i<raw_data.size();i++)
	//{
	//	handle_mat.at<float>(i,0) = norm_value(raw_data[i][attribute_title[0]],raw_data[i][attribute_title[1]],raw_data[i][attribute_title[2]]);
	//	handle_mat.at<float>(i,1) = norm_value(raw_data[i][attribute_title[3]],raw_data[i][attribute_title[4]],raw_data[i][attribute_title[5]]);
	//	handle_mat.at<float>(i,2) = norm_value(raw_data[i][attribute_title[6]],raw_data[i][attribute_title[7]],raw_data[i][attribute_title[8]]);
	//}

	//Compute latitude & longitude
	int lat_index = attribute_title[9];
	int lon_index = attribute_title[10];
	Mat first_order_distance_mat(1, raw_data.size(), CV_32F);
	for(int i=0;i<raw_data.size();i++)
	{
		if(i==0)
			first_order_distance_mat.at<float>(0,i) = 0.0;
		else
		{
			first_order_distance_mat.at<float>(0,i) = DistanceOfLontitudeAndLatitude(raw_data[i-1][lat_index],raw_data[i][lat_index],raw_data[i-1][lon_index],raw_data[i][lon_index]);
		}
	}

	if(select_distance) handle_mat.push_back(first_order_distance_mat);
	Mat handle_mat2 = handle_mat.t();

	raw_data_mat = handle_mat2;

	//cout << handle_mat << endl;
	Mat normalize_mat = handle_mat2;
	for(int i=0;i<handle_mat2.cols;i++)
		normalize(handle_mat2.col(i),normalize_mat.col(i),0,1,NORM_MINMAX);
	//cout << normalize_mat << endl;

	//output_mat_as_csv_file("normalize_mat.csv",normalize_mat);

	return normalize_mat;

}

void Preprocessing_Data::voting(int k,Mat cluster_tag,int row_size)
{
	int time_step_amount = floor(row_size/600.0);
	histogram = Mat::zeros(time_step_amount,k,CV_32S);
	int t = 1;
	for(int i=0;i<time_step_amount;i++)
	{
		for(int j=0;j<600;j++)
		{
			int index = cluster_tag.at<int>(t,0);
			histogram.at<int>(i,index)++;
			t++;
		}
	}

}

Mat Preprocessing_Data::Position_by_MDS(Mat cluster_centers,int k,float larger_weighting)
{
	
	Mat cluster_centers_distance_mat = Mat::zeros(k,k, CV_32F);
	for(int i=0;i<k;i++)
	{
		for(int j=0;j<k;j++)
		{
			if(i!=j)
			{
				cluster_centers_distance_mat.at<float>(i,j) = norm(cluster_centers.row(i),cluster_centers.row(j)); 
			}
		}
	}
	Mat wi; //1xk
	reduce(cluster_centers_distance_mat,wi,0,CV_REDUCE_SUM); //kxk->1xk
	Mat total_distance_mat; //1x1
	reduce(wi,total_distance_mat,1,CV_REDUCE_SUM);//kx1->1x1
	float total_distance_of_cluster_centers = total_distance_mat.at<float>(0,0);
	wi = wi.mul(1.0/total_distance_of_cluster_centers);
	wi *= larger_weighting;

	int time_step_amount = histogram.rows;
	Mat histo_coeff = Mat::zeros(time_step_amount,time_step_amount,CV_64F);
	for(int i=0;i<time_step_amount;i++)
		for(int j=0;j<time_step_amount;j++)
			for(int t=0;t<k;t++)
			{
				histo_coeff.at<double>(i,j) += wi.at<float>(0,t)*abs(histogram.at<int>(i,t)-histogram.at<int>(j,t));
			}
	Matrix<double,Dynamic,Dynamic> histo_coeff_EigenType;//The type pass to Tapkee must be "double" not "float"
	cv2eigen(histo_coeff,histo_coeff_EigenType);
	TapkeeOutput output = tapkee::initialize() 
						   .withParameters((method=MultidimensionalScaling,target_dimension=1))
						   .embedUsing(histo_coeff_EigenType);
	Mat MDS_mat; //Type:double  
	eigen2cv(output.embedding,MDS_mat);
	normalize(MDS_mat.col(0),MDS_mat.col(0),1,100,NORM_MINMAX);//normalize to 1~1000	
	//output_mat_as_txt_file("normalized_MDS_mat.txt",MDS_mat);
	MDS_mat = MDS_mat.mul(20);
	//output_mat_as_txt_file("normalized_MDS_mat_2.txt",MDS_mat);

	return MDS_mat; 
}