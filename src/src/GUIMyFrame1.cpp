#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MainFrame( parent )
{
	_Image.AddHandler(new wxJPEGHandler);
	_Image.LoadFile("kotek.jpg", wxBITMAP_TYPE_JPEG);
	_Bitmap = wxBitmap(_Image);

}


GUIMyFrame1::~GUIMyFrame1()
{

}

void GUIMyFrame1::m_panel1OnPaint(wxPaintEvent& event)  
{
	wxClientDC dc1( m_panel0 );
	wxBufferedDC dc( &dc1 );

	if(_Bitmap.IsOk())
		dc.DrawBitmap(_Bitmap, 0, 0, false);
	
}

void GUIMyFrame1::m_panel0OnUpdateUI(wxUpdateUIEvent& event)  
{
	
}
