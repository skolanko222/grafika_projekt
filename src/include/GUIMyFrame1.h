#ifndef __GUIMyFrame1__
#define __GUIMyFrame1__

/**
@file
Subclass of MyFrame1, which is generated by wxFormBuilder.
*/

#include "GUI.h"

//// end generated include

#include <wx/dcclient.h>
#include <wx/dcbuffer.h>

/** Implementing MyFrame1 */
class GUIMyFrame1 : public MainFrame
{
	public:
		/** Constructor */
		GUIMyFrame1( wxWindow* parent );
	//// end generated class members
		~GUIMyFrame1();
	private:
		using size = short unsigned int;

		size _width;
		size _height;

		wxImage _Image;
		wxBitmap _Bitmap;

	public:

		virtual void m_panel1OnPaint(wxPaintEvent& event) override;
		virtual void m_panel0OnUpdateUI(wxUpdateUIEvent& event) override;

		virtual void m_filePicker2OnFileChanged( wxFileDirPickerEvent& event ) override 
		{ 
			wxString path = event.GetPath();
			_Image.AddHandler(new wxJPEGHandler);
			_Image.LoadFile(path);

			_height = _Image.GetHeight();
			_width = _Image.GetWidth();

			m_panel0->SetSize(_width, _height);

			_Bitmap = wxBitmap(_Image);
			Refresh();
		}



};

#endif // __GUIMyFrame1__
