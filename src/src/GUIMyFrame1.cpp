#include "GUIMyFrame1.h"

/**
 * @brief Construct a new GUIMyFrame1 object
 * 
 * @param parent 
 */
GUIMyFrame1::GUIMyFrame1(wxWindow *parent)
	: MainFrame(parent)
{
	_Image.InitStandardHandlers();
	subImage.InitStandardHandlers();
	if (!wxFileExists("kotek.bmp")) // if file doesn't exist, setting default sizes
	{
		_Image = wxImage(250, 200);
		subImage = wxImage(50, 50);
		for (auto &x : _arrZoomedImages)
			x = wxImage(50, 50);
		this->SetMinSize(wxSize(250 + 240, 200 + 50 + 100));
	}
	else // if file exists, loading it
	{
		_Image.LoadFile("kotek.bmp");
		loaded = true;
	}
	setPanelsOnLoad(); // calling function calculating all necessary params
	m_slider1->SetValue(0);
	m_panel0->Bind(wxEVT_MOTION, GUIMyFrame1::Mouse_Move, this);
	m_panel0->Bind(wxEVT_LEFT_DOWN, GUIMyFrame1::LMB_click, this);
}
/**
 * @brief Function called when panel0 is repainted
 *			panel0 - main image panel  	
 *
 * @param event 
 */
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
	dc.DrawLine(lupaX - lupaHeight / 2., lupaY - lupaWidth / 2., lupaX + lupaHeight / 2., lupaY - lupaWidth / 2.);
	dc.DrawLine(lupaX - lupaHeight / 2., lupaY - lupaWidth / 2., lupaX - lupaHeight / 2., lupaY + lupaWidth / 2.);
	dc.DrawLine(lupaX - lupaHeight / 2., lupaY + lupaWidth / 2., lupaX + lupaHeight / 2., lupaY + lupaWidth / 2.);
	dc.DrawLine(lupaX + lupaHeight / 2., lupaY - lupaWidth / 2., lupaX + lupaHeight / 2., lupaY + lupaWidth / 2.);
}
/**
 * @brief  Function called when size of UI is changed
 * 
 * @param event 
 */
void GUIMyFrame1::m_panel0OnUpdateUI(wxUpdateUIEvent &event)
{
	setPanelSize();
}

/**
 * @brief Function called when left mouse button is clicked - to hold zoom in place
 * 
 * @param event 
 */
void GUIMyFrame1::LMB_click(wxMouseEvent &event)
{
	if (LMB_clicked)
		LMB_clicked = false;
	else
		LMB_clicked = true;

	lupaImageCrop();
	Refresh();
}
/**
 * @brief Function called when mouse is moved
 * 
 * @param event 
 */
void GUIMyFrame1::Mouse_Move(wxMouseEvent &event)
{
	size mX_temp = event.GetX();
	size mY_temp = event.GetY();

	// checks if mouse is in image
	if (LMB_clicked)
		return;

	if (mX_temp < _width - lupaWidth / 2. && mX_temp > lupaWidth / 2.)
		lupaX = mX_temp;
	if (mY_temp < _height - lupaHeight / 2. && mY_temp > lupaHeight / 2.)
		lupaY = mY_temp;

	lupaImageCrop();
	Refresh();
}
/**
 * @brief Function called when slider is scrolled
 * 			 - changes zoom factor	
 * 
 * @param event 
 */
void GUIMyFrame1::m_slider1OnScroll(wxScrollEvent &event)
{
	cropFactor = 1. - event.GetPosition() / 200.;
	zoomFactor = -2 * cropFactor + 3.;
	lupaWidth = _pDownSize.GetWidth() * cropFactor;
	lupaHeight = _pDownSize.GetHeight() * cropFactor;

	if (lupaX > _width - lupaWidth / 2.)
		lupaX -= 1;
	if (lupaY > _height - lupaHeight / 2.)
		lupaY -= 1;
	if (lupaX < lupaWidth / 2.)
		lupaX += 1;
	if (lupaY < lupaHeight / 2.)
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
	lupaX = _width / 2;
	lupaY = _height / 2;

	_height = _Image.GetHeight();
	_width = _Image.GetWidth();

	_p0size.Set(_width, _height);

	// calculates size of zoomed panels
	_pDownSize.Set(_width / 4 - 20, _width / 4 - 20);

	lupaWidth = _pDownSize.GetWidth() * cropFactor;
	lupaHeight = _pDownSize.GetHeight() * cropFactor;
	lupaX = _width / 2;
	lupaY = _height / 2;

	// sets panels size
	setPanelSize();

	_Bitmap = wxBitmap(_Image);
	if (loaded)
	{
		size a = 5 * lupaWidth + 240;
		size b = _width + 240;
		this->SetMinSize(wxSize(a > b ? a : b, _height * 1.59));
		this->SetSize(wxSize(a > b ? a : b, _height * 1.59));
	}

	lupaImageCrop();
	Refresh();
}
/**
 * @brief function cropping image to zoom
 * 
 */
void GUIMyFrame1::lupaImageCrop()
{

	lupaRect.SetX(lupaX - lupaWidth / 2.);
	lupaRect.SetY(lupaY - lupaHeight / 2.);
	lupaRect.SetWidth(lupaWidth);
	lupaRect.SetHeight(lupaHeight);

	size dif_x = lupaRect.GetX() + lupaWidth;
	size dif_y = lupaRect.GetY() + lupaHeight;

	if (dif_x > _width)
	{
		lupaRect.SetX(lupaRect.GetX() - (dif_x - _width));
	}
	if (dif_y > _height)
	{
		lupaRect.SetY(lupaRect.GetY() - (dif_y - _height));
	}

	if (lupaRect.GetX() < 0)
		lupaRect.SetX(0);

	if (lupaRect.GetY() < 0)
		lupaRect.SetY(0);

	subImage = _Image.GetSubImage(lupaRect);
}
/**
 * @brief setter of panels size
 * 
 */
void GUIMyFrame1::setPanelSize()
{
	m_panel0->SetSize(_p0size);
	m_panel1->SetSize(_pDownSize);
	m_panel2->SetSize(_pDownSize);
	m_panel3->SetSize(_pDownSize);
	m_panel4->SetSize(_pDownSize);
	m_panel5->SetSize(_pDownSize);
}
/**
 * @brief Function called when save button is cliced
 * 
 * @param event 
 */
void GUIMyFrame1::m_button3OnButtonClick(wxCommandEvent &event)
{
	wxString cwd = wxGetCwd();

	wxFileDialog saveFileDialog(this, _("Save BMP file"), cwd, "", "BMP files (*.bmp)|*.bmp", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;
	wxFileOutputStream output_stream(saveFileDialog.GetPath());
	if (!output_stream.IsOk())
		return;
	wxImage image = _arrZoomedImages[0];
	image.Resize(wxSize(_arrZoomedImages[0].GetWidth() * 5, _arrZoomedImages[0].GetHeight()), wxPoint(0, 0));
	for (size i = 1; i < _arrZoomedImages.size(); i++)
	{
		image.Paste(_arrZoomedImages[i], _arrZoomedImages[i].GetWidth() * i, 0);
	}
	image.SaveFile(output_stream, wxBITMAP_TYPE_BMP);
}
/**
 * @brief Function called when load button is clicked
 * 
 * @param event 
 */
void GUIMyFrame1::m_button2OnButtonClick(wxCommandEvent &event)
{
	wxString cwd = wxGetCwd();
	wxFileDialog openFileDialog(this, _("Open BMP file"), cwd, "", "BMP files (*.bmp)|*.bmp", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;

	wxFileInputStream input_stream(openFileDialog.GetPath());
	loaded = true;
	if (!input_stream.IsOk())
		return;
	_Image.LoadFile(input_stream);
	setPanelsOnLoad(openFileDialog.GetPath());
}