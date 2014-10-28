#include "stdafx.h"
#include "ReadCSV.h"
#include <string.h>
#include <fstream>


void ReadCSV::read_all_csv()
{
	//call matlab script
	//system(" \"D:\\Program Files\\MATLAB\\R2011a\\bin\\matlab.exe\" -r draw_rect_wear2");
	//system("pause");

	strcpy(file_position,"csv_data/position_20140925_0000_refine_c50.csv");
	strcpy(file_RGB,"csv_data/RGB_20140925_0000_refine_c50.csv");
	strcpy(file_histo,"csv_data/histo_20140925_0000_refine_c50.csv");
	strcpy(file_hour,"csv_data/hour_20140925_0000_refine_c50.csv");
	strcpy(file_cluster,"csv_data/cluster_center_20140925_0000_refine_c50.csv");
	strcpy(file_raw_data_3D,"csv_data/raw_data_3D_20140925_0000_refine_c50.csv");
	strcpy(file_raw_data,"csv_data/20140925_0000_refine.csv");

	read_csv_position();
	read_csv_histo();
	read_csv_color();
	read_csv_time();
	read_csv_clustercenter();
	read_csv_raw_data_3D();
	read_csv_raw_data();
}


void ReadCSV::read_csv_position()
{
	FILE *csv_file;
	csv_file = fopen(file_position,"r");
	if(!csv_file) 
	{
		cout << "Can't open config file!" << endl;
	}

	//vector < vector<float> > data;
	vector < string > title;
	char line[LENGTH];
	char *token;
	int i,j;
	i = j = 0;
	//fgets(line,LENGTH,csv_file); //ignore sep=
	//fgets(line,LENGTH,csv_file); //ignore title

	while(!feof(csv_file))
	{
		fgets(line,LENGTH,csv_file);
		//token = strtok(line,";");
		token = strtok(line,",");
		position_data.push_back(vector<float> (1));
		//printf("%s ",token);
		while(token!=NULL)
		{
			position_data.back().push_back(atof(token));
			//token = strtok(NULL," ;:");
			token = strtok(NULL," ,;:");
		}
	
	}	
	fclose(csv_file);
}

void ReadCSV::read_csv_histo()
{
	FILE *csv_file;
	csv_file = fopen(file_histo,"r");
	if(!csv_file) 
	{
		cout << "Can't open config file!" << endl;
	}

	//vector < vector<float> > data;
	vector < string > title;
	char line[LENGTH];
	char *token;
	int i,j;
	i = j = 0;
	//fgets(line,LENGTH,csv_file); //ignore sep=
	//fgets(line,LENGTH,csv_file); //ignore title

	while(!feof(csv_file))
	{
		fgets(line,LENGTH,csv_file);
		//token = strtok(line,";");
		token = strtok(line,",");
		histogram_data.push_back(vector<float> (1));
		//printf("%s ",token);
		while(token!=NULL)
		{
			histogram_data.back().push_back(atof(token));
			//token = strtok(NULL," ;:");
			token = strtok(NULL," ,;:");
		}
	
	}	
	fclose(csv_file);
}

void ReadCSV::read_csv_color()
{
	FILE *csv_file;
	csv_file = fopen(file_RGB,"r");
	if(!csv_file) 
	{
		cout << "Can't open config file!" << endl;
	}

	//vector < vector<float> > data;
	vector < string > title;
	char line[LENGTH];
	char *token;
	int i,j;
	i = j = 0;
	//fgets(line,LENGTH,csv_file); //ignore sep=
	//fgets(line,LENGTH,csv_file); //ignore title

	while(!feof(csv_file))
	{
		fgets(line,LENGTH,csv_file);
		//token = strtok(line,";");
		token = strtok(line,",");
		color_data.push_back(vector<float> (1));
		//printf("%s ",token);
		while(token!=NULL)
		{
			color_data.back().push_back(atof(token));
			//token = strtok(NULL," ;:");
			token = strtok(NULL," ,;:");
		}
	
	}	
	fclose(csv_file);
}

void ReadCSV::read_csv_time()
{
	FILE *csv_file;
	csv_file = fopen(file_hour,"r");
	if(!csv_file) 
	{
		cout << "Can't open config file!" << endl;
	}

	vector < string > title;
	char line[LENGTH];
	char *token;
	int i,j;
	i = j = 0;
	//fgets(line,LENGTH,csv_file); //ignore sep=
	//fgets(line,LENGTH,csv_file); //ignore title

	while(!feof(csv_file))
	{
		fgets(line,LENGTH,csv_file);
		//token = strtok(line,";");
		token = strtok(line,",");
		hour_data.push_back(vector<float> (1));
		//printf("%s ",token);
		while(token!=NULL)
		{
			hour_data.back().push_back(atof(token));
			//token = strtok(NULL," ;:");
			token = strtok(NULL," ,;:");
		}
	
	}	

	num_of_five_minutes = hour_data.size()-1;

	for(int i=0;i<hour_data.size();i++)
	{
		for(int j=1;j<hour_data[i].size();j++)
		{
			hour_map[hour_data[i][j]]++;
		}
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
		//cout << temp.x << " " << temp.y << endl;
		hour_range.push_back(temp);
		hour_index.push_back(it->first);

		start += (hour_num+1);
		
	}



	fclose(csv_file);
}

void ReadCSV::read_csv_clustercenter()
{
	FILE *csv_file;
	csv_file = fopen(file_cluster,"r");
	if(!csv_file) 
	{
		cout << "Can't open config file!" << endl;
	}

	//vector < vector<float> > data;
	vector < string > title;
	char line[LENGTH];
	char *token;
	int i,j;
	i = j = 0;
	//fgets(line,LENGTH,csv_file); //ignore sep=
	//fgets(line,LENGTH,csv_file); //ignore title

	while(!feof(csv_file))
	{
		fgets(line,LENGTH,csv_file);
		//token = strtok(line,";");
		token = strtok(line,",");
		cluster_data.push_back(vector<float> (1));
		//printf("%s ",token);
		while(token!=NULL)
		{
			cluster_data.back().push_back(atof(token));
			//token = strtok(NULL," ;:");
			token = strtok(NULL," ,;:");
		}
	
	}	
	fclose(csv_file);
}

void ReadCSV::read_csv_raw_data_3D()
{
	FILE *csv_file;
	csv_file = fopen(file_raw_data_3D,"r");
	if(!csv_file) 
	{
		cout << "Can't open config file!" << endl;
	}

	vector < string > title;
	char line[LENGTH];
	char *token;
	int i,j;
	i = j = 0;
	//fgets(line,LENGTH,csv_file); //ignore sep=
	//fgets(line,LENGTH,csv_file); //ignore title

	while(!feof(csv_file))
	{
		fgets(line,LENGTH,csv_file);
		//token = strtok(line,";");
		token = strtok(line,",");
		raw_data_3D.push_back(vector<float> (1));
		//printf("%s ",token);
		while(token!=NULL)
		{
			raw_data_3D.back().push_back(atof(token));
			//token = strtok(NULL," ;:");
			token = strtok(NULL," ,;:");
		}
	
	}

	//cout << raw_data.size() - 1;
	//cout << raw_data[2].size() - 1;	
	fclose(csv_file);
}

////////////////////seperate by ';'////////////////////////
void ReadCSV::read_csv_raw_data()
{
	FILE *csv_file;
	csv_file = fopen(file_raw_data,"r");
	if(!csv_file) 
	{
		cout << "Can't open config file!" << endl;
	}

	vector < string > title;
	char line[LENGTH];
	char *token;
	int i,j;
	i = j = 0;
	fgets(line,LENGTH,csv_file); //ignore sep=
	fgets(line,LENGTH,csv_file); //ignore title

	while(!feof(csv_file))
	{
		fgets(line,LENGTH,csv_file);
		//token = strtok(line,";");
		token = strtok(line,";");
		raw_data.push_back(vector<float> (1));
		//printf("%s ",token);
		while(token!=NULL)
		{
			raw_data.back().push_back(atof(token));
			//token = strtok(NULL," ;:");
			token = strtok(NULL," ;:");
		}
	
	}

	//cout << raw_data.size() - 1;
	//cout << raw_data[2].size() - 1;
	fclose(csv_file);	
}