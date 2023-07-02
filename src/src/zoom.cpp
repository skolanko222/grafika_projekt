#include "GUIMyFrame1.h"

/**
 * @brief Performs Hermite interpolation on the image.
 * This function applies Hermite interpolation to the provided image, which enhances the quality of the image by smoothing out the pixel values and reducing pixelation. Hermite interpolation is a method of interpolating data points using cubic polynomials.
 * @param image The input image to be interpolated.
 * @param factor The factor by which the image is to be interpolated.
 * @return wxImage interpolated image.
 */
wxImage InterpolateImage_Hermit(const wxImage& image, double factor)
{
    wxImage interpolatedImage(image.GetWidth() * factor, image.GetHeight() * factor);
    
    if (image.IsOk() && interpolatedImage.IsOk() &&
        interpolatedImage.GetWidth() > 0 && interpolatedImage.GetHeight() > 0)
    {
        for (int y = 0; y < interpolatedImage.GetHeight(); y++)
        {
            for (int x = 0; x < interpolatedImage.GetWidth(); x++)
            {
                double srcX = x / factor;
                double srcY = y / factor;
                
                int x0 = static_cast<int>(srcX);
                int y0 = static_cast<int>(srcY);
                
                if (x0 >= 0 && x0 < image.GetWidth() - 1 && y0 >= 0 && y0 < image.GetHeight() - 1)
                {
                    double dx = srcX - x0;
                    double dy = srcY - y0;
                    
                    double red = image.GetRed(wxCoord(x0), wxCoord(y0)) * (1 - dx) * (1 - dy) +
                                 image.GetRed(wxCoord(x0 + 1), wxCoord(y0)) * dx * (1 - dy) +
                                 image.GetRed(wxCoord(x0), wxCoord(y0 + 1)) * (1 - dx) * dy +
                                 image.GetRed(wxCoord(x0 + 1), wxCoord(y0 + 1)) * dx * dy;
                    
                    double green = image.GetGreen(wxCoord(x0), wxCoord(y0)) * (1 - dx) * (1 - dy) +
                                   image.GetGreen(wxCoord(x0 + 1), wxCoord(y0)) * dx * (1 - dy) +
                                   image.GetGreen(wxCoord(x0), wxCoord(y0 + 1)) * (1 - dx) * dy +
                                   image.GetGreen(wxCoord(x0 + 1), wxCoord(y0 + 1)) * dx * dy;
    
                    double blue = image.GetBlue(wxCoord(x0), wxCoord(y0)) * (1 - dx) * (1 - dy) +
                                  image.GetBlue(wxCoord(x0 + 1), wxCoord(y0)) * dx * (1 - dy) +
                                  image.GetBlue(wxCoord(x0), wxCoord(y0 + 1)) * (1 - dx) * dy +
                                  image.GetBlue(wxCoord(x0 + 1), wxCoord(y0 + 1)) * dx * dy;
                    
                    interpolatedImage.SetRGB(x, y, static_cast<unsigned char>(red),
                                             static_cast<unsigned char>(green),
                                             static_cast<unsigned char>(blue));
                }
            }
        }
    }
    return interpolatedImage;
}

/**
 * @brief Performs Lanczos interpolation on the image.
 * This function applies Lanchos interpolation to the provided image, which is a method of interpolating data points using a combination of cubic interpolation and local weighted averaging. Lanchos interpolation is effective in preserving image details while reducing pixelation and artifacts.
 * @param image The input image to be interpolated.
 * @param scaleFactor The factor by which the image is to be interpolated.
 * @return wxImage interpolated image.
 */
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

/**
 * @brief Performs events and changes in Panel 1. Performs Bilinear interpolation on the image.
 * This function applies bi-linear interpolation to the provided image, which is a method of interpolating data points using a weighted average of the nearest four pixels. Bi-linear interpolation is commonly used in image processing to upscale or downscale images while preserving smoothness and reducing aliasing artifacts. For the interpolation, the build-in wxWidgets function Scale() is used.
 * @param event 
 */
void GUIMyFrame1::m_panel1OnPaint( wxPaintEvent& event )
{
	wxClientDC dc1(m_panel1);
	wxBufferedDC dc(&dc1);
	dc.SetBackground(wxBrush(RGB(255, 255, 255)));
	dc.Clear();
	wxImage copyImage = subImage.Copy();
	wxImage image2( copyImage.Scale( subImage.GetWidth()*zoomFactor, subImage.GetHeight()*zoomFactor, wxIMAGE_QUALITY_BILINEAR ) );
	wxBitmap bitmap = wxBitmap(image2);
	
	
	if (bitmap.IsOk())
		dc.DrawBitmap(bitmap, 0, 0, false);

	_arrZoomedImages[0] = image2;

}

/**
 * @brief Performs events and changes in Panel 2. Performs Bicubic bi-spline interpolation on the image.
 * This function applies bicubic B-spline interpolation to the provided image, which is a method of interpolating data points using a cubic B-spline function. Bicubic B-spline interpolation is commonly used in image processing to upscale images while preserving smoothness and reducing artifacts. For the interpolation, the build-in wxWidgets function Scale() is used.
 * @param event 
 */
void GUIMyFrame1::m_panel2OnPaint( wxPaintEvent& event )
{

	wxClientDC dc1(m_panel2);
	wxBufferedDC dc(&dc1);
	dc.SetBackground(wxBrush(RGB(255, 255, 255)));
	dc.Clear();
	wxImage copyImage = subImage.Copy();
	wxImage image2( copyImage.Scale( subImage.GetWidth()*zoomFactor, subImage.GetHeight()*zoomFactor, wxIMAGE_QUALITY_BICUBIC ) );
	wxBitmap bitmap = wxBitmap(image2);
	
	
	if (bitmap.IsOk())
		dc.DrawBitmap(bitmap, 0, 0, false);

	_arrZoomedImages[1] = image2;
}

/**
 * @brief Performs events and changes in Panel 3. Shows original object.
 * Panel shows original object without interpolation, image when zoomed in is pixelated.
 * @param event 
 */
void GUIMyFrame1::m_panel3OnPaint( wxPaintEvent& event )
{

	wxClientDC dc1(m_panel3);
	wxBufferedDC dc(&dc1);
	dc.SetBackground(wxBrush(RGB(255, 255, 255)));
	dc.Clear();
	wxImage copyImage = subImage.Copy();
	copyImage.Rescale(subImage.GetWidth()*zoomFactor, subImage.GetHeight()*zoomFactor);
	wxBitmap bitmap = wxBitmap(copyImage);
	
	
	if (bitmap.IsOk())
		dc.DrawBitmap(bitmap, 0, 0, false);

	_arrZoomedImages[2] = copyImage;

}

/**
 * @brief Performs events and changes in Panel 4. Performs Lanchos interpolation on the image.
 * Code that performs Lanchos interpolation is located in InterpolateImage_Lanchos() function.
 * @param event 
 */
void GUIMyFrame1::m_panel4OnPaint( wxPaintEvent& event )
{
	wxClientDC dc1(m_panel4);
	wxBufferedDC dc(&dc1);
	dc.SetBackground(wxBrush(RGB(255, 255, 255)));
	dc.Clear();
	wxImage copyImage = subImage.Copy();
	copyImage = InterpolateImage_Lanchos(copyImage, zoomFactor);
	wxBitmap bitmap = wxBitmap(copyImage);
	
	if (bitmap.IsOk())
		dc.DrawBitmap(bitmap, 0, 0, false);

	_arrZoomedImages[3] = copyImage;

}

/**
 * @brief Performs events and changes in Panel 5. Performs Hermite interpolation on the image.
 * Code that performs Hermite interpolation is located in InterpolateImage_Hermit() function.
 * @param event 
 */
void GUIMyFrame1::m_panel5OnPaint( wxPaintEvent& event )
{
	wxClientDC dc1(m_panel5);
	wxBufferedDC dc(&dc1);
	dc.SetBackground(wxBrush(RGB(255, 255, 255)));
	dc.Clear();
	wxImage copyImage = subImage.Copy();
	copyImage = InterpolateImage_Hermit(copyImage, zoomFactor);
	wxBitmap bitmap = wxBitmap(copyImage);
	
	
	if (bitmap.IsOk())
		dc.DrawBitmap(bitmap, 0, 0, false);
  
  _arrZoomedImages[4] = copyImage;

}