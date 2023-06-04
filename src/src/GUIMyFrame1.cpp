#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1(wxWindow *parent)
	: MainFrame(parent)
{
	setPanelsOnLoad();
	lupaX = _width/2;
	lupaY = _height/2;
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

	// draw sides of rectangle with mouse position in panel0 of size _pDownSize

	dc.SetPen(wxPen(RGB(0, 0, 0)));
	dc.DrawLine(lupaX - _pDownSize.GetHeight()/2., lupaY - _pDownSize.GetWidth()/2., lupaX + _pDownSize.GetHeight()/2., lupaY - _pDownSize.GetWidth()/2.);
	dc.DrawLine(lupaX - _pDownSize.GetHeight()/2., lupaY - _pDownSize.GetWidth()/2., lupaX - _pDownSize.GetHeight()/2., lupaY + _pDownSize.GetWidth()/2.);
	dc.DrawLine(lupaX - _pDownSize.GetHeight()/2., lupaY + _pDownSize.GetWidth()/2., lupaX + _pDownSize.GetHeight()/2., lupaY + _pDownSize.GetWidth()/2.);
	dc.DrawLine(lupaX + _pDownSize.GetHeight()/2., lupaY - _pDownSize.GetWidth()/2., lupaX + _pDownSize.GetHeight()/2., lupaY + _pDownSize.GetWidth()/2.);

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
	std::cout << "x: " << mX_temp << " y: " << mY_temp << std::endl;
	std::cout << "x_p: " << _p0size.GetWidth() << " y_p: " << _p0size.GetHeight()<< std::endl;

	if(mX_temp < _width - _pDownSize.GetWidth()/2. && mX_temp > _pDownSize.GetWidth()/2.)
		lupaX = mX_temp;
	if(mY_temp < _height - _pDownSize.GetHeight()/2. && mY_temp > _pDownSize.GetHeight()/2.)
		lupaY = mY_temp;
	Refresh();
}

void GUIMyFrame1::setPanelsOnLoad(wxString path)
{
	_Image.AddHandler(new wxJPEGHandler);
	_Image.LoadFile(path);

	_height = _Image.GetHeight();
	_width = _Image.GetWidth();

	_p0size.Set(_width, _height);
	_pDownSize.Set(_width/4 -20, _width/4 -20);
	setPanelSize();

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