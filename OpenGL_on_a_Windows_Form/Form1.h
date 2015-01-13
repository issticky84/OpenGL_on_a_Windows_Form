#pragma once

//#include "OpenGL.h"
#include "VisualizationPanel.h"
#include "RawDataVisualization.h"
#include "DetailVisualization.h"
#include "HistogramVisualization.h"
namespace OpenGL_on_a_Windows_Form 
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace OpenGLForm;
	public ref class Form1 : public System::Windows::Forms::Form 
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//system("matlab -nodesktop -nosplash -r draw_rect_wear2");
			ReadCSV read_csv;
			//read_csv.read_all_csv();
			read_csv.read_raw_data();

			Preprocessing_Data preprocessing_data;
			preprocessing_data.start(read_csv.raw_data,trackBar1->Value);

			//waiting_flag = true;
			start_flag = false;

			histogram = gcnew HistogramVisualization(this,this->panel3,panel3->Width,panel3->Height,read_csv,preprocessing_data);
			rawData = gcnew RawDataVisualization(this,this->panel1,panel1->Width,panel1->Height,read_csv,preprocessing_data);
			detail = gcnew DetailVisualization(this,this->panel2,panel2->Width,panel2->Height,read_csv,preprocessing_data);
	
			/*OpenGL = gcnew COpenGL(this,this->panel1,panel1->Width,panel1->Height,read_csv);
			OpenGL_2 = gcnew COpenGL(this,this->panel2,panel2->Width,panel2->Height,read_csv);
			OpenGL_3 = gcnew COpenGL(this,this->panel3,panel3->Width,panel3->Height,read_csv);
			*/

			
		}
	protected:

		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^  components;
	protected: 
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Button^  start;


	private: System::Windows::Forms::Button^  button2;

	private:

		RawDataVisualization ^ rawData;
		DetailVisualization ^ detail;
		HistogramVisualization ^ histogram;
		/*OpenGLForm2::COpenGL ^ OpenGL;
		OpenGLForm2::COpenGL ^ OpenGL_2;
		OpenGLForm2::COpenGL ^ OpenGL_3;
		OpenGLForm2::COpenGL ^ OpenGL_4;*/
	private: System::Windows::Forms::TrackBar^  trackBar1;
	
	private: System::Boolean Move_3_21_flag,Down_3_21_flag;
	private: System::Boolean Move_12_horiz_flag,Down_12_horiz_flag;
	private: System::Boolean Move_12_vert_flag,Down_12_vert_flag;
	private: System::Int32 last_x,last_y;
	private: System::Windows::Forms::Button^  Detail_Clear;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Boolean waiting_flag;
	private: System::Boolean start_flag;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->start = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->Detail_Clear = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 10;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(671, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(813, 447);
			this->panel1->TabIndex = 0;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::panel1_Paint);
			this->panel1->MouseEnter += gcnew System::EventHandler(this, &Form1::panel1_MouseEnter);
			this->panel1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::panel1_MouseMove);
			// 
			// panel2
			// 
			this->panel2->Location = System::Drawing::Point(671, 465);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(813, 577);
			this->panel2->TabIndex = 1;
			this->panel2->MouseEnter += gcnew System::EventHandler(this, &Form1::panel2_MouseEnter);
			this->panel2->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::panel2_MouseMove);
			// 
			// panel3
			// 
			this->panel3->Location = System::Drawing::Point(12, 12);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(653, 1030);
			this->panel3->TabIndex = 2;
			this->panel3->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::panel3_Paint);
			this->panel3->MouseEnter += gcnew System::EventHandler(this, &Form1::panel3_MouseEnter);
			this->panel3->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::panel3_MouseMove);
			// 
			// start
			// 
			this->start->Location = System::Drawing::Point(1553, 842);
			this->start->Name = L"start";
			this->start->Size = System::Drawing::Size(134, 67);
			this->start->TabIndex = 4;
			this->start->Text = L"Start";
			this->start->UseVisualStyleBackColor = true;
			this->start->Click += gcnew System::EventHandler(this, &Form1::start_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(1502, 12);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(83, 50);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Clear";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(1682, 135);
			this->trackBar1->Maximum = 100;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->trackBar1->Size = System::Drawing::Size(45, 188);
			this->trackBar1->TabIndex = 50;
			this->trackBar1->Value = 50;
			this->trackBar1->TickFrequency = 5;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &Form1::trackBar1_Scroll);
			// 
			// Detail_Clear
			// 
			this->Detail_Clear->Location = System::Drawing::Point(1502, 465);
			this->Detail_Clear->Name = L"Detail_Clear";
			this->Detail_Clear->Size = System::Drawing::Size(83, 50);
			this->Detail_Clear->TabIndex = 7;
			this->Detail_Clear->Text = L"Clear";
			this->Detail_Clear->UseVisualStyleBackColor = true;
			this->Detail_Clear->Click += gcnew System::EventHandler(this, &Form1::Detail_Clear_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(1682, 320);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(24, 22);
			this->textBox1->TabIndex = 51;
			this->textBox1->Text = L"50";
			//this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1916, 1054);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->Detail_Clear);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->start);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Name = L"Form1";
			this->Text = L"OpenGL on a Windows Form using Managed C++";
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseDown);
			this->MouseEnter += gcnew System::EventHandler(this, &Form1::Form1_MouseEnter);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseMove_1);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e)
			 {
				 if(rawData)
					 rawData->Render(panel1->Width,panel1->Height);
				 if(detail)
					 detail->Render(panel2->Width,panel2->Height);
				 if(histogram)
					 histogram->Render(panel3->Width,panel3->Height);

				 if(Move_3_21_flag==false && Move_12_horiz_flag==false && Move_12_vert_flag==false) 
					 this->Cursor = System::Windows::Forms::Cursors::Default;
			 }

	private: System::Void start_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 //waiting_flag = false;
				 histogram->clear();
				 rawData->clear();
				 detail->clear();
				 preprocessing_data.start(read_csv.raw_data,trackBar1->Value);
				 System::Windows::Forms::MessageBox::Show(trackBar1->Value.ToString());
				 //waiting_flag = true;
			 }

    private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				//OpenGL_4->rtri+=trackBar1->Value;
				 rawData->clear();
			 }

	private: System::Void Detail_Clear_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 detail->clear();
			 }

	private: System::Void trackBar1_Scroll(System::Object^  sender, System::EventArgs^  e) 
			 {
				 textBox1->Text = "" + trackBar1->Value;
				 //System::Windows::Forms::MessageBox::Show(trackBar1->Value.ToString());		
			 }

	private: System::Void panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
			 {
			 }

	private: System::Void panel3_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 }

	private: System::Void panel3_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
				 this->panel3->Focus();
			 }
	private: System::Void panel1_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
				 this->panel1->Focus();
			 }
	private: System::Void panel2_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
				 this->panel2->Focus();
			 }

	private: System::Void panel3_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 Move_3_21_flag = false;
				 Move_12_horiz_flag = false;
				 Move_12_vert_flag = false;
			}
	private: System::Void panel1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 Move_3_21_flag = false;
				 Move_12_horiz_flag = false;
				 Move_12_vert_flag = false;
			 }
	private: System::Void panel2_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 Move_3_21_flag = false;
				 Move_12_horiz_flag = false;
				 Move_12_vert_flag = false;
				
			 }

	private: System::Void Form1_MouseMove_1(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
					 ///////////////move panel3 vs panel12 horizontally///////////////
					 int side_3_21_x1 = panel3->Location.X + panel3->Width;
					 int side_3_21_x2 = panel1->Location.X;
					 if(e->X > side_3_21_x1 && e->X < side_3_21_x2)
					 {
						 Move_3_21_flag = true;
						 this->Cursor = System::Windows::Forms::Cursors::NoMoveHoriz;
					 }

					 int move_3_21_x = e->X - last_x;
					 if(Down_3_21_flag)
					 {
						panel3->Width += move_3_21_x;
						panel1->Location = System::Drawing::Point(panel1->Location.X+move_3_21_x, panel1->Location.Y);
						panel1->Width -= move_3_21_x;
						panel2->Location = System::Drawing::Point(panel2->Location.X+move_3_21_x, panel2->Location.Y);
						panel2->Width -= move_3_21_x;	
					 }
					 ///////////////////move pane1 & panel2 horizontally//////////////////////
					 int side_12_x1 = panel2->Location.X + panel2->Width;
					 int side_12_x2 = side_12_x1 + 5;
					 int side_12_y1 = panel1->Location.Y;
					 int side_12_y2 = panel2->Location.Y + panel2->Height;
					 if(e->X > side_12_x1 && e->X < side_12_x2 && e->Y > side_12_y1 && e->Y < side_12_y2)
					 {
						 Move_12_horiz_flag = true;
						 this->Cursor = System::Windows::Forms::Cursors::NoMoveHoriz;							
					 }
					 else
					 {
						Move_12_horiz_flag = false;
					 }

					 int move_12_x = e->X - last_x;
					 if(Down_12_horiz_flag)
					 {
						 //panel2->Location = System::Drawing::Point(panel2->Location.X,panel2->Location.Y+move_12_y);
						 panel1->Width += move_12_x;
						 panel2->Width += move_12_x;
					 }
					 ///////////////move panel1 & panel2 vertically///////////////
					 side_12_x1 = panel1->Location.X;
					 side_12_x2 = panel1->Location.X + panel1->Width;
					 side_12_y1 = panel1->Location.Y;
					 side_12_y2 = panel2->Location.Y;
					 if(e->X > side_12_x1 && e->X < side_12_x2 && e->Y > side_12_y1 && e->Y < side_12_y2)
					 {
						 Move_12_vert_flag = true;
						 this->Cursor = System::Windows::Forms::Cursors::NoMoveVert;							
					 }
					 else
					 {
						Move_12_vert_flag = false;
					 }

					 int move_y = e->Y - last_y;
					 if(Down_12_vert_flag)
					 {
						 panel2->Location = System::Drawing::Point(panel2->Location.X,panel2->Location.Y+move_y);
						 panel1->Height += move_y;
						 panel2->Height -= move_y;
					 }
					 ////////////////////////////////////////////////////
					 last_x = e->X;
					 last_y = e->Y;
			 }


	private: System::Void Form1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
					last_x = e->X;
					last_y = e->Y;

					if(Move_3_21_flag)
					{
						Down_3_21_flag = true;
					}

					if(Move_12_horiz_flag)
					{
						Down_12_horiz_flag = true;
					}

					if(Move_12_vert_flag)
					{
						Down_12_vert_flag = true;
					}
			 }
	private: System::Void Form1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
					Down_3_21_flag = false;
					Down_12_horiz_flag = false;
					Down_12_vert_flag = false;
			 }

	private: System::Void Form1_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
					Form::Focus();
			 }

};
}

