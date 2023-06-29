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
#include <iostream>

#include <exception>
#include "wx/wxprec.h"
#include "wx/image.h"
#include "wx/log.h"
#include "wx/utils.h"
#include "wx/math.h"
#include "wx/module.h"
#include "wx/palette.h"
#include "wx/intl.h"
#include "wx/colour.h"
#include "wx/wfstream.h"
#include "wx/xpmdecod.h"


/** Implementing MyFrame1 */
class GUIMyFrame1 : public MainFrame
{
	public:
		/** Constructor */
		GUIMyFrame1( wxWindow* parent );
	//// end generated class members
		~GUIMyFrame1();
	protected:
		using size = short unsigned int;

		size _width = wxDefaultSize.GetWidth(); // image width
		size _height = wxDefaultSize.GetHeight(); // image height
		
		wxSize _p0size = wxSize(_width, _height); // main panel size
		wxSize _pDownSize = wxSize(wxDefaultSize.GetWidth(), wxDefaultSize.GetHeight()); // zoom panel size

		// center position of lupa
		size lupaX;
		size lupaY;

		// zoom size
		size lupaWidth;
		size lupaHeight;

		// zoom rectange data
		// x, y, width, height
		wxRect lupaRect;

		// zoom factors
		double cropFactor = 1.;
		double zoomFactor = 1.;
    
		wxImage _Image;
		wxImage subImage;
		
		// array of zoomed images (to save as bitmap)
		std::array<wxImage,5> _arrZoomedImages;

		wxBitmap _Bitmap;

		
		//static lupa
		bool LMB_clicked = false;
		bool loaded = false;

		void setPanelsOnLoad(wxString path = _("kotek.jpg"));
		void setPanelSize();
		void lupaImageCrop();

		void Mouse_Move(wxMouseEvent& event);
		void LMB_click(wxMouseEvent& event);


	public:

		virtual void m_panel0OnPaint(wxPaintEvent& event) override;
		virtual void m_panel0OnUpdateUI(wxUpdateUIEvent& event) override;

		virtual void m_slider1OnScroll( wxScrollEvent& event ) override;

		virtual void m_panel1OnPaint( wxPaintEvent& event ) override;
		virtual void m_panel2OnPaint( wxPaintEvent& event ) override;
		virtual void m_panel3OnPaint( wxPaintEvent& event ) override;
		virtual void m_panel4OnPaint( wxPaintEvent& event ) override;
		virtual void m_panel5OnPaint( wxPaintEvent& event ) override;

		virtual void m_button3OnButtonClick( wxCommandEvent& event ) override;
		virtual void m_button2OnButtonClick( wxCommandEvent& event ) override;




};

#endif // __GUIMyFrame1__
