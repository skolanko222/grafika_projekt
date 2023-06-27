#include "GUIMyFrame1.h"

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

//Interpolacja dwuliniowa (Bilinear interpolation)
void GUIMyFrame1::m_panel1OnPaint( wxPaintEvent& event )
{
	wxClientDC dc1(m_panel1);
	wxBufferedDC dc(&dc1);
	dc.SetBackground(wxBrush(RGB(255, 255, 255)));
	dc.Clear();

	// TODO: Implement zoom
	wxImage copyImage = subImage.Copy();
	//
	const wxImageResizeQuality quality =  wxIMAGE_QUALITY_BILINEAR;
	wxImage image2( copyImage.Scale( subImage.GetWidth()*zoomFactor, subImage.GetHeight()*zoomFactor, quality ) );
	wxBitmap bitmap = wxBitmap(image2);
	
	
	if (bitmap.IsOk())
		dc.DrawBitmap(bitmap, 0, 0, false);

	_arrZoomedImages[0] = image2;

}

//Bicubic interpolation b-spline
void GUIMyFrame1::m_panel2OnPaint( wxPaintEvent& event )
{
	wxClientDC dc1(m_panel2);
	wxBufferedDC dc(&dc1);
	dc.SetBackground(wxBrush(RGB(255, 255, 255)));
	dc.Clear();

	// TODO: Implement zoom

	wxImage copyImage = subImage.Copy();
	//
	const wxImageResizeQuality quality =  wxIMAGE_QUALITY_BICUBIC;
	wxImage image2( copyImage.Scale( subImage.GetWidth()*zoomFactor, subImage.GetHeight()*zoomFactor, quality ) );
	wxBitmap bitmap = wxBitmap(image2);
	
	
	if (bitmap.IsOk())
		dc.DrawBitmap(bitmap, 0, 0, false);

	_arrZoomedImages[1] = image2;
}

//ORIGINAL OBJECT
void GUIMyFrame1::m_panel3OnPaint( wxPaintEvent& event )
{
	wxClientDC dc1(m_panel3);
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

	_arrZoomedImages[2] = copyImage;

}

// Funkcja dokonująca interpolacji metodą Lanczosa
wxImage InterpolateImage_Lanchos(const wxImage& image, double scaleFactor)
{
    int width = image.GetWidth();
    int height = image.GetHeight();

    int newWidth = static_cast<int>(width * scaleFactor);
    int newHeight = static_cast<int>(height * scaleFactor);

    wxImage newImage(newWidth, newHeight);

    for (int y = 0; y < newHeight; ++y)
    {
        for (int x = 0; x < newWidth; ++x)
        {
            double srcX = static_cast<double>(x) / scaleFactor;
            double srcY = static_cast<double>(y) / scaleFactor;

            int x1 = static_cast<int>(srcX);
            int y1 = static_cast<int>(srcY);

            int x2 = x1 + 1;
            int y2 = y1 + 1;

            if (x2 >= width)
                x2 = width - 1;
            if (y2 >= height)
                y2 = height - 1;

            double fractionX = srcX - x1;
            double fractionY = srcY - y1;

            unsigned char r1 = image.GetRed(x1, y1);
            unsigned char g1 = image.GetGreen(x1, y1);
            unsigned char b1 = image.GetBlue(x1, y1);

            unsigned char r2 = image.GetRed(x2, y1);
            unsigned char g2 = image.GetGreen(x2, y1);
            unsigned char b2 = image.GetBlue(x2, y1);

            unsigned char r3 = image.GetRed(x1, y2);
            unsigned char g3 = image.GetGreen(x1, y2);
            unsigned char b3 = image.GetBlue(x1, y2);

            unsigned char r4 = image.GetRed(x2, y2);
            unsigned char g4 = image.GetGreen(x2, y2);
            unsigned char b4 = image.GetBlue(x2, y2);

            int r = static_cast<int>((r1 * (1 - fractionX) * (1 - fractionY) +
                                      r2 * fractionX * (1 - fractionY) +
                                      r3 * (1 - fractionX) * fractionY +
                                      r4 * fractionX * fractionY) + 0.5);

            int g = static_cast<int>((g1 * (1 - fractionX) * (1 - fractionY) +
                                      g2 * fractionX * (1 - fractionY) +
                                      g3 * (1 - fractionX) * fractionY +
                                      g4 * fractionX * fractionY) + 0.5);

            int b = static_cast<int>((b1 * (1 - fractionX) * (1 - fractionY) +
                                      b2 * fractionX * (1 - fractionY) +
                                      b3 * (1 - fractionX) * fractionY +
                                      b4 * fractionX * fractionY) + 0.5);

            newImage.SetRGB(x, y, r, g, b);
        }
    }

 return newImage;  
}

//Lanczos
void GUIMyFrame1::m_panel4OnPaint( wxPaintEvent& event )
{
	wxClientDC dc1(m_panel4);
	wxBufferedDC dc(&dc1);
	dc.SetBackground(wxBrush(RGB(255, 255, 255)));
	dc.Clear();

	// TODO: Implement zoom

	wxImage copyImage = subImage.Copy();
	copyImage = InterpolateImage_Lanchos(copyImage, zoomFactor);
	wxBitmap bitmap = wxBitmap(copyImage);
	
	
	if (bitmap.IsOk())
		dc.DrawBitmap(bitmap, 0, 0, false);

	_arrZoomedImages[3] = copyImage;

}

double MitchellFilter(double p0, double p1, double p2, double p3, double t)
{
    double q0 = (-(1.0 / 6.0) * t + 0.5 * t * t - 0.5 * t * t * t);
    double q1 = (0.5 - t * t + 0.5 * t * t * t);
    double q2 = (-(1.0 / 3.0) + 0.5 * t + 0.5 * t * t - t * t * t * 0.5);
    double q3 = (t * t * 0.5 - 0.5 * t * t * t);
    return p0 * q0 + p1 * q1 + p2 * q2 + p3 * q3;
}

wxImage InterpolateImage_Mitchell(const wxImage& image, double scaleFactor)
{
	int width = image.GetWidth();
	int height = image.GetHeight();

	int newWidth = static_cast<int>(width * scaleFactor);
	int newHeight = static_cast<int>(height * scaleFactor);

	wxImage newImage(newWidth, newHeight);

	for (int y = 0; y < newHeight; ++y)
	{
		for (int x = 0; x < newWidth; ++x)
		{
			double srcX = static_cast<double>(x) / scaleFactor;
			double srcY = static_cast<double>(y) / scaleFactor;
 			int x1 = static_cast<int>(srcX);
            int y1 = static_cast<int>(srcY);

            int x0 = x1 - 1;
            int y0 = y1 - 1;

            int x2 = x1 + 1;
            int y2 = y1 + 1;

            int x3 = x1 + 2;
            int y3 = y1 + 2;

            if (x0 < 0) x0 = 0;
            if (y0 < 0) y0 = 0;
            if (x2 >= width) x2 = width - 1;
            if (y2 >= height) y2 = height - 1;
            if (x3 >= width) x3 = width - 1;
            if (y3 >= height) y3 = height - 1;

            double fractionX = srcX - x1;
            double fractionY = srcY - y1;

            double p0x = MitchellFilter(image.GetRed(x0, y0), image.GetRed(x1, y0), image.GetRed(x2, y0), image.GetRed(x3, y0), fractionX);
            double p1x = MitchellFilter(image.GetRed(x0, y1), image.GetRed(x1, y1), image.GetRed(x2, y1), image.GetRed(x3, y1), fractionX);
            double p2x = MitchellFilter(image.GetRed(x0, y2), image.GetRed(x1, y2), image.GetRed(x2, y2), image.GetRed(x3, y2), fractionX);
            double p3x = MitchellFilter(image.GetRed(x0, y3), image.GetRed(x1, y3), image.GetRed(x2, y3), image.GetRed(x3, y3), fractionX);

            double p0y = MitchellFilter(p0x, p1x, p2x, p3x, fractionY);

            p0x = MitchellFilter(image.GetGreen(x0, y0), image.GetGreen(x1, y0), image.GetGreen(x2, y0), image.GetGreen(x3, y0), fractionX);
            p1x = MitchellFilter(image.GetGreen(x0, y1), image.GetGreen(x1, y1), image.GetGreen(x2, y1), image.GetGreen(x3, y1), fractionX);
            p2x = MitchellFilter(image.GetGreen(x0, y2), image.GetGreen(x1, y2), image.GetGreen(x2, y2), image.GetGreen(x3, y2), fractionX);
            p3x = MitchellFilter(image.GetGreen(x0, y3), image.GetGreen(x1, y3), image.GetGreen(x2, y3), image.GetGreen(x3, y3), fractionX);

            double p1y = MitchellFilter(p0x, p1x, p2x, p3x, fractionY);

            p0x = MitchellFilter(image.GetBlue(x0, y0), image.GetBlue(x1, y0), image.GetBlue(x2, y0), image.GetBlue(x3, y0), fractionX);
            p1x = MitchellFilter(image.GetBlue(x0, y1), image.GetBlue(x1, y1), image.GetBlue(x2, y1), image.GetBlue(x3, y1), fractionX);
            p2x = MitchellFilter(image.GetBlue(x0, y2), image.GetBlue(x1, y2), image.GetBlue(x2, y2), image.GetBlue(x3, y2), fractionX);
            p3x = MitchellFilter(image.GetBlue(x0, y3), image.GetBlue(x1, y3), image.GetBlue(x2, y3), image.GetBlue(x3, y3), fractionX);

            double p2y = MitchellFilter(p0x, p1x, p2x, p3x, fractionY);

            int r = static_cast<int>(p0y + 0.5);
            int g = static_cast<int>(p1y + 0.5);
            int b = static_cast<int>(p2y + 0.5);

            newImage.SetRGB(x, y, r, g, b);
        }
    }

    return newImage;


}



//Mitchel
void GUIMyFrame1::m_panel5OnPaint( wxPaintEvent& event )
{
	wxClientDC dc1(m_panel5);
	wxBufferedDC dc(&dc1);
	dc.SetBackground(wxBrush(RGB(255, 255, 255)));
	dc.Clear();

	// TODO: Implement zoom

	wxImage copyImage = subImage.Copy();
	//
	copyImage = InterpolateImage_Mitchell(copyImage, zoomFactor);
	wxBitmap bitmap = wxBitmap(copyImage);
	
	
	if (bitmap.IsOk())
		dc.DrawBitmap(bitmap, 0, 0, false);

	_arrZoomedImages[4] = copyImage;
}
