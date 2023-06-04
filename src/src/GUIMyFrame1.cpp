#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1(wxWindow *parent)
	: MainFrame(parent)
{
	setPanelsOnLoad();
	lupaX = _width/2;
	lupaY = _height/2;
	m_slider1->SetValue(0);
	m_panel0->Bind(wxEVT_MOTION, GUIMyFrame1::Mouse_Move, this);

}

GUIMyFrame1::~GUIMyFrame1()
{

	// m_panel0->Disconnect(wxEVT_MOTION, GUIMyFrame1::Mouse_Move, this);
	// m_panel5->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::m_panel5OnUpdateUI ), NULL, this );

}

void GUIMyFrame1::m_panel1OnPaint(wxPaintEvent &event)
{

	wxClientDC dc1(m_panel0);
	wxBufferedDC dc(&dc1);
	dc.SetBackground(wxBrush(RGB(255, 255, 255)));
	dc.Clear();
	
	setPanelSize();

	if (_Bitmap.IsOk())
		dc.DrawBitmap(_Bitmap, 0, 0, false);


	dc.SetPen(wxPen(RGB(0, 0, 0)));

	// draws rectangle on top of image
	dc.DrawLine(lupaX - lupaHeight/2., lupaY - lupaWidth/2., lupaX + lupaHeight/2., lupaY - lupaWidth/2.);
	dc.DrawLine(lupaX - lupaHeight/2., lupaY - lupaWidth/2., lupaX - lupaHeight/2., lupaY + lupaWidth/2.);
	dc.DrawLine(lupaX - lupaHeight/2., lupaY + lupaWidth/2., lupaX + lupaHeight/2., lupaY + lupaWidth/2.);
	dc.DrawLine(lupaX + lupaHeight/2., lupaY - lupaWidth/2., lupaX + lupaHeight/2., lupaY + lupaWidth/2.);

}

void GUIMyFrame1::m_panel0OnUpdateUI(wxUpdateUIEvent &event)
{
	setPanelSize();
}

void GUIMyFrame1::m_filePicker2OnFileChanged(wxFileDirPickerEvent &event)
{
	wxString path = event.GetPath();
	setPanelsOnLoad(path);
}
void GUIMyFrame1::Mouse_Move(wxMouseEvent& event) {
	size mX_temp = event.GetX();
	size mY_temp = event.GetY();

	// temporary
	// std::cout << "x: " << mX_temp << " y: " << mY_temp << std::endl;
	// std::cout << "x_p: " << _p0size.GetWidth() << " y_p: " << _p0size.GetHeight()<< std::endl;

	// checks if mouse is in image
	if(mX_temp < _width - lupaWidth/2. && mX_temp > lupaWidth/2.)
		lupaX = mX_temp;
	if(mY_temp < _height - lupaHeight/2. && mY_temp > lupaHeight/2.)
		lupaY = mY_temp;
	Refresh();
}

void GUIMyFrame1::m_slider1OnScroll( wxScrollEvent& event )
{
	zoomFactor = 1. - event.GetPosition()/200.;
	std::cout << zoomFactor << std::endl;
	lupaWidth = _pDownSize.GetWidth()*zoomFactor;
	lupaHeight = _pDownSize.GetHeight()*zoomFactor;
	
	if(lupaX > _width - lupaWidth/2. )
		lupaX -= 1;
	if(lupaY > _height - lupaHeight/2. )
		lupaY -= 1;
	if(lupaX < lupaWidth/2. )
		lupaX += 1;
	if(lupaY < lupaHeight/2. )
		lupaY += 1;
	
	Refresh();
}

/**
 * @brief Sets panels size on load
 * 			
 * 				Panel0 - image panel
 * 				Panel1 - zoomed image panel
 * 				...
 * 
 * 				calculates:
 * 				- size of panel0
 * 				- size of zoomed panels
 * 
 * @param path 
 */
void GUIMyFrame1::setPanelsOnLoad(wxString path)
{
	_Image.AddHandler(new wxJPEGHandler);
	_Image.LoadFile(path);

	_height = _Image.GetHeight();
	_width = _Image.GetWidth();


	_p0size.Set(_width, _height);

	// calculates size of zoomed panels
	_pDownSize.Set(_width/4 -20, _width/4 -20);

	lupaWidth = _pDownSize.GetWidth()*zoomFactor;
	lupaHeight = _pDownSize.GetHeight()*zoomFactor;

	// sets panels size 
	setPanelSize();

	// sets frame size
	this->SetMinSize(wxSize(_width + 330, _height + _pDownSize.GetY() + 20));

	_Bitmap = wxBitmap(_Image);
	Refresh();

}

void GUIMyFrame1::setPanelSize()
{
	m_panel0->SetSize(_p0size);
	m_panel1->SetSize(_pDownSize);
	m_panel2->SetSize(_pDownSize);
	m_panel3->SetSize(_pDownSize);
	m_panel4->SetSize(_pDownSize);
	m_panel5->SetSize(_pDownSize);
	
}