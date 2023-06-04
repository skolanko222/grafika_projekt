///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/slider.h>
#include <wx/filepicker.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame
{
	private:
		
	protected:
		wxPanel* m_panel0;
		wxPanel* m_panel1;
		wxPanel* m_panel2;
		wxPanel* m_panel3;
		wxPanel* m_panel4;
		wxPanel* m_panel5;
		wxButton* m_button2;
		wxButton* m_button3;
		wxSlider* m_slider1;
		wxFilePickerCtrl* m_filePicker2;



		// Virtual event handlers, override them in your derived class
		virtual void m_panel0OnPaint( wxPaintEvent& event ) { event.Skip(); } // main panel
		virtual void m_panel0OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_panel1OnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void m_panel1OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_panel2OnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void m_panel2OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_panel3OnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void m_panel3OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_panel4OnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void m_panel4OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_panel5OnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void m_panel5OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_button2OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button3OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_slider1OnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void m_slider1OnSlider( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_filePicker2OnFileChanged( wxFileDirPickerEvent& event ) { event.Skip(); }

		// prevents flashing panel0
		void erase_bacground(wxEraseEvent& event) {};


	public:

		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("RASTER GRAPHICS INTERPOLATION"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 623,345 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainFrame();

};

