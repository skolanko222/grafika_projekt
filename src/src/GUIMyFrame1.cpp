#include "GUIMyFrame1.h"

#include <exception>


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

void GUIMyFrame1::m_panel0OnPaint(wxPaintEvent &event)
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

	// create rectange of 
	// wxRect rect(lupaX - lupaHeight/2., lupaY - lupaWidth/2., lupaWidth, lupaHeight);

	// wxBitmap _Bitmap = wxBitmap(subImage);
	// if (subImage.IsOk())
	// 	std::cout << "ok" << std::endl;
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


	lupaImageCrop();
	Refresh();
}

void GUIMyFrame1::m_slider1OnScroll( wxScrollEvent& event )
{
	cropFactor = 1. - event.GetPosition()/200.;
	zoomFactor = -2*cropFactor  + 3.;
	lupaWidth = _pDownSize.GetWidth()*cropFactor;
	lupaHeight = _pDownSize.GetHeight()*cropFactor;
	
	if(lupaX > _width - lupaWidth/2. )
		lupaX -= 1;
	if(lupaY > _height - lupaHeight/2. )
		lupaY -= 1;
	if(lupaX < lupaWidth/2. )
		lupaX += 1;
	if(lupaY < lupaHeight/2. )
		lupaY += 1;
	
	lupaImageCrop();
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

	lupaWidth = _pDownSize.GetWidth()*cropFactor;
	lupaHeight = _pDownSize.GetHeight()*cropFactor;
	lupaX = _width/2;
	lupaY = _height/2;

	// sets panels size 
	setPanelSize();

	// sets frame size
	this->SetMinSize(wxSize(_width + 330, _height + _pDownSize.GetY() + 20));


	_Bitmap = wxBitmap(_Image);

	lupaImageCrop();
	Refresh();

}

void GUIMyFrame1::lupaImageCrop()
{
	
	lupaRect.SetX(lupaX - lupaWidth/2.);	
	lupaRect.SetY(lupaY - lupaHeight/2.);	
	lupaRect.SetWidth(lupaWidth);
	lupaRect.SetHeight(lupaHeight);

	// std::cout << "x: " << lupaRect.GetX()  << " y: " << lupaRect.GetY() << std::endl;
	// std::cout << "w: " << lupaRect.GetWidth()  << " h: " << lupaRect.GetHeight() << std::endl;

	size dif_x = lupaRect.GetX() + lupaWidth;
	size dif_y = lupaRect.GetY() + lupaHeight;
	// std::cout << "dif: " << dif << "\n\n";

	if(dif_x > _width)
	{
		// std::cout << "new cor_x" << lupaRect.GetX() - (dif_x - _width) << std::endl;
		lupaRect.SetX(lupaRect.GetX() - (dif_x - _width));

		// dif_x = lupaRect.GetX() + lupaWidth;
		// std::cout << "naprawa dif_x " << dif_x << std::endl;
	}
	if(dif_y > _height)
	{
		// std::cout << "new cor_x" << lupaRect.GetX() - (dif - _width) << std::endl;
		lupaRect.SetY(lupaRect.GetY() - (dif_y - _height));

		// dif_y = lupaRect.GetY() + lupaWidth;
		// std::cout << "naprawa dif_y " << dif_y << std::endl;

	}

	if(lupaRect.GetX() < 0)
		lupaRect.SetX(0);


	if(lupaRect.GetY() < 0)
		lupaRect.SetY(0);
	
	subImage = _Image.GetSubImage(lupaRect);
	// std::cout << "\n\n";

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

void GUIMyFrame1::m_panel1OnPaint( wxPaintEvent& event )
{
	wxClientDC dc1(m_panel1);
	wxBufferedDC dc(&dc1);
	dc.SetBackground(wxBrush(RGB(255, 255, 255)));
	dc.Clear();

	// TODO: Implement zoom

	wxImage copyImage = subImage.Copy();
	// std::cout << "zoomFactor: " << zoomFactor << std::endl;
	copyImage.Rescale(subImage.GetWidth()*zoomFactor, subImage.GetHeight()*zoomFactor);
	wxBitmap bitmap = wxBitmap(copyImage);
	
	
	if (bitmap.IsOk())
		dc.DrawBitmap(bitmap, 0, 0, false);

	_arrZoomedImages[0] = copyImage;
}

void GUIMyFrame1::m_panel2OnPaint( wxPaintEvent& event )
{
	wxClientDC dc1(m_panel2);
	wxBufferedDC dc(&dc1);
	dc.SetBackground(wxBrush(RGB(255, 255, 255)));
	dc.Clear();

	// TODO: Implement zoom

	wxImage copyImage = subImage.Copy();
	copyImage.Rescale(subImage.GetWidth()*zoomFactor, subImage.GetHeight()*zoomFactor);
	wxBitmap bitmap = wxBitmap(copyImage);
	if (bitmap.IsOk())
		dc.DrawBitmap(bitmap, 0, 0, false);
	_arrZoomedImages[1] = copyImage;
}

void GUIMyFrame1::m_panel3OnPaint( wxPaintEvent& event )
{
	wxClientDC dc1(m_panel3);
	wxBufferedDC dc(&dc1);
	dc.SetBackground(wxBrush(RGB(255, 255, 255)));
	dc.Clear();

	// TODO: Implement zoom

	wxImage copyImage = subImage.Copy();
	copyImage.Rescale(subImage.GetWidth()*zoomFactor, subImage.GetHeight()*zoomFactor);
	wxBitmap bitmap = wxBitmap(copyImage);
	if (bitmap.IsOk())
		dc.DrawBitmap(bitmap, 0, 0, false);
	_arrZoomedImages[2] = copyImage;
}

void GUIMyFrame1::m_panel4OnPaint( wxPaintEvent& event )
{
	wxClientDC dc1(m_panel4);
	wxBufferedDC dc(&dc1);
	dc.SetBackground(wxBrush(RGB(255, 255, 255)));
	dc.Clear();

	// TODO: Implement zoom

	wxImage copyImage = subImage.Copy();
	copyImage.Rescale(subImage.GetWidth()*zoomFactor, subImage.GetHeight()*zoomFactor);
	wxBitmap bitmap = wxBitmap(copyImage);
	if (bitmap.IsOk())
		dc.DrawBitmap(bitmap, 0, 0, false);
	_arrZoomedImages[3] = copyImage;
}

void GUIMyFrame1::m_panel5OnPaint( wxPaintEvent& event )
{
	wxClientDC dc1(m_panel5);
	wxBufferedDC dc(&dc1);
	dc.SetBackground(wxBrush(RGB(255, 255, 255)));
	dc.Clear();

	// TODO: Implement zoom

	wxImage copyImage = subImage.Copy();
	copyImage.Rescale(subImage.GetWidth()*zoomFactor, subImage.GetHeight()*zoomFactor);
	wxBitmap bitmap = wxBitmap(copyImage);
	if (bitmap.IsOk())
		dc.DrawBitmap(bitmap, 0, 0, false);
	_arrZoomedImages[4] = copyImage;
}

void GUIMyFrame1::m_button3OnButtonClick( wxCommandEvent& event )
{
	wxFileDialog saveFileDialog(this, _("Save BMP file"), "", "", "BMP files (*.bmp)|*.bmp", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;
	wxFileOutputStream output_stream(saveFileDialog.GetPath());
    if (!output_stream.IsOk())
            return;
	wxImage image = _arrZoomedImages[0];
	image.Resize(wxSize(_arrZoomedImages[0].GetWidth()*5, _arrZoomedImages[0].GetHeight()), wxPoint(0,0));
	for (size i = 1; i < _arrZoomedImages.size(); i++)
	{
		std::cout << "i: " << i << std::endl;
		image.Paste(_arrZoomedImages[i], _arrZoomedImages[i].GetWidth()*i, 0);
	
	} 
	image.SaveFile(output_stream, wxBITMAP_TYPE_BMP);
	
}
