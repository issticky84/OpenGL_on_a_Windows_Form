#include "stdafx.h"
#include "DetailVisualization.h"

namespace OpenGLForm{
	DetailVisualization::DetailVisualization(Form ^ parentForm,Panel ^ parentPanel, GLsizei iWidth, GLsizei iHeight,ReadCSV read_csv_ref,Preprocessing_Data preprocessing_data_ref):VisualizationPanel(parentForm,parentPanel,iWidth,iHeight,read_csv_ref,preprocessing_data_ref){
			title_string();
			//Initialize mouse handler variable
			scale_x[2] = 0.0; scale_y[2] = 0.0; scale_z[2] = 0.0;
			scale_size[2] = 0.05;
			move_x[2] = 0.0; move_y[2] = 0.0; move_z[2] = 0.0;
			scale_factor[2] = 0.6;
			//Initialize window size
			windowWidth[2] = iWidth; 
			windowHeight[2] = iHeight;	
	}
	System::Void DetailVisualization::Render(int detail_width,int detial_height){
			wglmakecur();

			windowWidth[2] = detail_width;
			windowHeight[2] = detial_height;

			glClearColor(0.0, 0.0, 0.0, 0.0);  //Set the cleared screen colour to black
			glViewport(0, 0, windowWidth[2], windowHeight[2]);   //This sets up the viewport so that the coordinates (0, 0) are at the top left of the window		
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, windowWidth[2], windowHeight[2], 0, -10, 10);

			//Back to the modelview so we can draw stuff 
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the screen and depth buffer

			glTranslatef(0.0+move_x[2],0.0+move_y[2],0.0+move_z[2]);
			glScalef(scale_factor[2]+scale_x[2],scale_factor[2]+scale_y[2],scale_factor[2]+scale_z[2]);
			vector<float> color;
			color.resize(3);

			//DrawLine(0,480,windowWidth[2]*2,480);
			//DrawLine(450,0,450,1000);
			if(!raw_data_index.empty())
			{
					int index = raw_data_index[0];
					float factor = 50.0;
					int x_position,y_position;
					//==========Gravity X Y Z==========//
					DrawTitle_FTGL(2,70,100);
					x_position = 70;
					y_position = 250;
					for(int j=0;j<raw_data_index.size();j++)
					{
						RECTANGLE *rect;
						index = raw_data_index[j];
						rect = new RECTANGLE();
						rect->h = factor*abs(preprocessing_data.raw_data_mat.at<float>(index,0));
						rect->w = 50.0;
						rect->x = x_position;
						rect->y = y_position;
						color[0] = preprocessing_data.raw_data_3D.at<float>(index,0);
						color[1] = preprocessing_data.raw_data_3D.at<float>(index,1);
						color[2] = preprocessing_data.raw_data_3D.at<float>(index,2);
						if(preprocessing_data.raw_data_mat.at<float>(index,0)>0)
						{
							rect->y -= factor*abs(preprocessing_data.raw_data_mat.at<float>(index,0));
							float current_position_y = rect->y;
							double nearest = round(preprocessing_data.raw_data_mat.at<float>(index,0));
							DrawText_FTGL(nearest,x_position,current_position_y-20);
						}
						else
						{
							float current_position_y = rect->y + rect->h;
							double nearest = round(preprocessing_data.raw_data_mat.at<float>(index,0));
							DrawText_FTGL(nearest,x_position,current_position_y+5);
						}

						DrawRectWithOpenGL(rect,color);
						delete(rect);

						x_position+=50;
					}
					x_position+=70;
					//==========Linear Acceleration X Y Z==========//
					DrawTitle_FTGL(1,750,100);
					x_position = 750;
					y_position = 250;
					for(int j=0;j<raw_data_index.size();j++)
					{
						index = raw_data_index[j];
						RECTANGLE *rect;
						rect = new RECTANGLE();
						rect->h = factor*abs(preprocessing_data.raw_data_mat.at<float>(index,1));
						rect->w = 50.0;
						rect->x = x_position;
						rect->y = y_position;
						color[0] = preprocessing_data.raw_data_3D.at<float>(index,0);
						color[1] = preprocessing_data.raw_data_3D.at<float>(index,1);
						color[2] = preprocessing_data.raw_data_3D.at<float>(index,2);
						if(preprocessing_data.raw_data_mat.at<float>(index,1)>0)
						{
							rect->y -= factor*abs(preprocessing_data.raw_data_mat.at<float>(index,1));
							float current_position_y = rect->y;
							double nearest = round(preprocessing_data.raw_data_mat.at<float>(index,1));
							DrawText_FTGL(nearest,x_position-10,current_position_y-20);
						} 
						else
						{
							float current_position_y = rect->y + rect->h;
							double nearest = round(preprocessing_data.raw_data_mat.at<float>(index,1));
							DrawText_FTGL(nearest,x_position-10,current_position_y+5);
						}

						DrawRectWithOpenGL(rect,color);
						delete(rect);

						x_position+=50;
					}
					x_position+=100;
					//==========Gyroscope X Y Z==========//
					DrawTitle_FTGL(3,70, 500);
					x_position = 70;
					y_position = 750;
					int factor2 = 100;
					for(int j=0;j<raw_data_index.size();j++)
					{
						index = raw_data_index[j];
						RECTANGLE *rect;
						rect = new RECTANGLE();
						rect->h = factor2*abs(preprocessing_data.raw_data_mat.at<float>(index,2));
						rect->w = 50.0;
						rect->x = x_position;
						rect->y = y_position;
						color[0] = preprocessing_data.raw_data_3D.at<float>(index,0);
						color[1] = preprocessing_data.raw_data_3D.at<float>(index,1);
						color[2] = preprocessing_data.raw_data_3D.at<float>(index,2);
						if(preprocessing_data.raw_data_mat.at<float>(index,2)>0)
						{
							rect->y -= factor2*abs(preprocessing_data.raw_data_mat.at<float>(index,2));
							float current_position_y = rect->y;
							double nearest = round(preprocessing_data.raw_data_mat.at<float>(index,2));
							DrawText_FTGL(nearest,x_position,current_position_y-20);
						}
						else
						{
							float current_position_y = rect->y + rect->h;
							double nearest = round(preprocessing_data.raw_data_mat.at<float>(index,2));
							DrawText_FTGL(nearest,x_position,current_position_y+5);
						}

						DrawRectWithOpenGL(rect,color);
						delete(rect);

						x_position+=50.0;
					}
					x_position+=100;
					//==========first order of Longitude & Latitude==========//
					DrawTitle_FTGL(0,750,500);
					x_position = 750;
					y_position = 750;	
						
					for(int j=0;j<raw_data_index.size();j++)
					{
						RECTANGLE *rect;
						index = raw_data_index[j];
						rect = new RECTANGLE();
						rect->h = factor*abs(preprocessing_data.raw_data_mat.at<float>(index,3)*1000.0);
						rect->w = 50.0;
						rect->x = x_position;
						rect->y = y_position;
						color[0] = preprocessing_data.raw_data_3D.at<float>(index,0);
						color[1] = preprocessing_data.raw_data_3D.at<float>(index,1);
						color[2] = preprocessing_data.raw_data_3D.at<float>(index,2);
						if(preprocessing_data.raw_data_mat.at<float>(index,3)*1000.0>0)
						{
							rect->y -= factor*abs(preprocessing_data.raw_data_mat.at<float>(index,3)*1000.0);
							float current_position_y = rect->y;
							double nearest = round(preprocessing_data.raw_data_mat.at<float>(index,3)*1000.0);
							DrawText_FTGL(nearest,x_position,current_position_y-20);
						}
						else if(preprocessing_data.raw_data_mat.at<float>(index,3)==0.0)
						{
							float current_position_y = rect->y;
							DrawText_FTGL(0,x_position,current_position_y-20);
						}
						else
						{
							float current_position_y = rect->y + rect->h;
							//double nearest = round(preprocessing_data.raw_data_mat.at<float>(index,3));
							DrawText_FTGL(preprocessing_data.raw_data_mat.at<float>(index,3)*1000.0,x_position,current_position_y+5);
						}

						DrawRectWithOpenGL(rect,color);
						delete(rect);

						x_position+=50;
					}
					x_position+=70;		
			}
		
			SwapOpenGLBuffers();
			
		}
		 
		System::Void DetailVisualization::DrawText_FTGL(float n,int x, int y)
		{
			glPushMatrix();

			float font_size = 10*(scale_factor[2]+0.4+scale_x[2]);
			font.FaceSize(font_size);
			glColor3f(1.0, 1.0, 1.0);
			glRasterPos2f(x , y + font.LineHeight());
			stringstream ss;
			ss << n;
			string str = ss.str();
			text = (char*)str.c_str();
			font.Render(text);

			glPopMatrix();
		
		}

		System::Void DetailVisualization::DrawTitle_FTGL(int t,int x, int y)
		{
			glPushMatrix();

			float font_size = 20*(scale_factor[2]+0.4+scale_x[2]);
			font.FaceSize(font_size);
			glColor3f(1.0, 1.0, 1.0);
			glRasterPos2f(x , y + font.LineHeight());
			font.Render(title[t]);

			glPopMatrix();			
		}

		System::Void DetailVisualization::title_string()
		{
			strcpy(title[0],"First Order of Distance");
			strcpy(title[1],"Linear Acceleration");
			strcpy(title[2],"Gravity");
			strcpy(title[3],"Gyroscope");
		}

		System::Void DetailVisualization::DrawLine(int x1,int y1,int x2,int y2)
		{
			glPushMatrix();
			glLineWidth(2.0);
			glBegin(GL_LINES);
				glColor3f(1.0,1.0,1.0);
				glVertex3f(x1,y1,0.0);
				glVertex3f(x2,y2,0.0);
			glEnd();
			glPopMatrix();	
		}

		System::Void DetailVisualization::clear()
		{
			raw_data_index.clear();
		}
}