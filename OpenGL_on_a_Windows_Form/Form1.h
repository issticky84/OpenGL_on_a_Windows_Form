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
			
			read_csv.read_all_csv();
			rawData = gcnew RawDataVisualization(this,this->panel1,panel1->Width,panel1->Height,read_csv);
			detail = gcnew DetailVisualization(this,this->panel2,panel2->Width,panel2->Height,read_csv);
			histogram = gcnew HistogramVisualization(this,this->panel3,panel3->Width,panel3->Height,read_csv);
			/*OpenGL = gcnew COpenGL(this,this->panel1,panel1->Width,panel1->Height,read_csv);
			OpenGL_2 = gcnew COpenGL(this,this->panel2,panel2->Width,panel2->Height,read_csv);
			OpenGL_3 = gcnew COpenGL(this,this->panel3,panel3->Width,panel3->Height,read_csv);
			*/
			//OpenGL_4 = gcnew COpenGL(this->panel4,panel4->Width,panel4->Height);
			
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

	private: System::Windows::Forms::Button^  button1;
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
	
	private: System::Boolean NoMoveHoriz_flag;
	private: System::Boolean NoMoveHoriz_move_flag;


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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
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
			this->panel1->Size = System::Drawing::Size(752, 421);
			this->panel1->TabIndex = 0;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::panel1_Paint);
			this->panel1->MouseEnter += gcnew System::EventHandler(this, &Form1::panel1_MouseEnter);
			// 
			// panel2
			// 
			this->panel2->Location = System::Drawing::Point(671, 439);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(752, 603);
			this->panel2->TabIndex = 1;
			this->panel2->MouseEnter += gcnew System::EventHandler(this, &Form1::panel2_MouseEnter);
			// 
			// panel3
			// 
			this->panel3->Location = System::Drawing::Point(12, 12);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(653, 1030);
			this->panel3->TabIndex = 2;
			this->panel3->CursorChanged += gcnew System::EventHandler(this, &Form1::panel3_CursorChanged);
			this->panel3->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::panel3_Paint);
			this->panel3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::panel3_MouseDown);
			this->panel3->MouseEnter += gcnew System::EventHandler(this, &Form1::panel3_MouseEnter);
			this->panel3->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::panel3_MouseMove);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(1798, 723);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(50, 24);
			this->button1->TabIndex = 4;
			this->button1->Text = L"<";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(1854, 723);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(50, 24);
			this->button2->TabIndex = 5;
			this->button2->Text = L">";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(1844, 529);
			this->trackBar1->Maximum = 20;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->trackBar1->Size = System::Drawing::Size(45, 188);
			this->trackBar1->TabIndex = 6;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1916, 1054);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Name = L"Form1";
			this->Text = L"OpenGL on a Windows Form using Managed C++";
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseMove_1);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e)
			 {
				 if(rawData)
					 rawData->Render();
				 if(detail)
					 detail->Render();
				 if(histogram)
					 histogram->Render();
				 /*
				 OpenGL->wglmakecur();
				 OpenGL->Render();
				 OpenGL->SwapOpenGLBuffers();
                
                 OpenGL_2->wglmakecur();
				 OpenGL_2->Render2();
				 OpenGL_2->SwapOpenGLBuffers();

				 OpenGL_3->wglmakecur();
				 //OpenGL_3->Render();
				 OpenGL_3->DrawHistogramVisualization();
				 OpenGL_3->SwapOpenGLBuffers();
				 */
				 //OpenGL_4->wglmakecur();
				 //OpenGL_4->Render();
				 //OpenGL_4->SwapOpenGLBuffers();
				 if(NoMoveHoriz_flag==false) this->Cursor = System::Windows::Forms::Cursors::Default;
			 }

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 //OpenGL_4->rtri-=trackBar1->Value;
				 this->Cursor = System::Windows::Forms::Cursors::NoMoveVert;
			 }

    private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				//OpenGL_4->rtri+=trackBar1->Value;
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
				 //this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
				 //this->Cursor = System::Windows::Forms::Cursors::Default;
				 //this->Cursor = System::Windows::Forms::Cursors::NoMoveHoriz;
				 //this->Cursor = System::Windows::Forms::Cursors::NoMoveVert;
			 }

	private: System::Void panel3_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

			}

	private: System::Void panel3_CursorChanged(System::Object^  sender, System::EventArgs^  e) {
			 //System::Windows::Forms::MessageBox::Show(sender->GetType() + " ");
			 }

	private: System::Void panel3_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

			 }

	private: System::Void Form1_MouseMove_1(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
					 int side_x1 = panel3->Location.X + panel3->Width;
					 int side_x2 = panel1->Location.X;
					 System::Windows::Forms::MessageBox::Show(e->X + " " + side_x1 + " " + side_x2);
					 if(e->X > side_x1 && e->X < side_x2)
					 {
						 NoMoveHoriz_flag = true;
						 this->Cursor = System::Windows::Forms::Cursors::NoMoveHoriz;
					 }
					 else
					 {
						 this->Cursor = System::Windows::Forms::Cursors::Default;
					 }
			 }
};
}

