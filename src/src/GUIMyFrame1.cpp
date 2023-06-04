#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1(wxWindow *parent)
	: MainFrame(parent)
{
	setPanelsOnLoad();
}

GUIMyFrame1::~GUIMyFrame1()
{
}

void GUIMyFrame1::m_panel1OnPaint(wxPaintEvent &event)
{

	wxClientDC dc1(m_panel0);
	wxBufferedDC dc(&dc1);

	dc.Clear();
	
	setPanelSize();

	if (_Bitmap.IsOk())
		dc.DrawBitmap(_Bitmap, 0, 0, false);
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