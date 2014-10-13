#pragma once

#include "VisualizationPanel.h"



namespace OpenGLForm{
	public ref class HistogramVisualization: public OpenGLForm::VisualizationPanel{
		public:
			HistogramVisualization(Form ^ parentForm,Panel ^ parentPanel, GLsizei iWidth, GLsizei iHeight,ReadCSV read_csv_ref);
			virtual System::Void Render(System::Void) override;
			void  HistogramMouseDown( Object^ /*sender*/, System::Windows::Forms::MouseEventArgs^ e);
			void  HistogramMouseWheel( Object^ /*sender*/, System::Windows::Forms::MouseEventArgs^ e);
			void  HistogramMouseMove( Object^ /*sender*/, System::Windows::Forms::MouseEventArgs^ e);
			void  HistogramMouseUp( Object^ /*sender*/, System::Windows::Forms::MouseEventArgs^ e);

		private:
			System::Void DrawHistogramVisualization(System::Void);
			System::Void DrawTime_FTGL(int l,int x, int y);
			System::Void time_string(System::Void);
			System::Void FindPatternByTable(int x,int y);
			vector3 Unprojection(vector2 _2Dpos);
	};
}