///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizerPanels;
	bSizerPanels = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerUpperPanel;
	bSizerUpperPanel = new wxBoxSizer( wxVERTICAL );

	m_panel0 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel0->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );
	m_panel0->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );

	bSizerUpperPanel->Add( m_panel0, 1, wxEXPAND | wxALL, 5 );


	bSizerPanels->Add( bSizerUpperPanel, 2, wxEXPAND, 5 );

	wxBoxSizer* bSizerLowerPanels;
	bSizerLowerPanels = new wxBoxSizer( wxHORIZONTAL );

	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel1->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );
	m_panel1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );

	bSizerLowerPanels->Add( m_panel1, 1, wxEXPAND | wxALL, 5 );

	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel2->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );
	m_panel2->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );

	bSizerLowerPanels->Add( m_panel2, 1, wxEXPAND | wxALL, 5 );

	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel3->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );
	m_panel3->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );

	bSizerLowerPanels->Add( m_panel3, 1, wxEXPAND | wxALL, 5 );

	m_panel4 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel4->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );
	m_panel4->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );

	bSizerLowerPanels->Add( m_panel4, 1, wxEXPAND | wxALL, 5 );

	m_panel5 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel5->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );
	m_panel5->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );

	bSizerLowerPanels->Add( m_panel5, 1, wxEXPAND | wxALL, 5 );


	bSizerPanels->Add( bSizerLowerPanels, 1, wxEXPAND, 5 );


	bSizerMain->Add( bSizerPanels, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizerButtons;
	bSizerButtons = new wxBoxSizer( wxVERTICAL );

	m_button2 = new wxButton( this, wxID_ANY, wxT("Load File"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons->Add( m_button2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_button3 = new wxButton( this, wxID_ANY, wxT("Save File"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerButtons->Add( m_button3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_slider1 = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizerButtons->Add( m_slider1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizerMain->Add( bSizerButtons, 0, wxEXPAND, 5 );

	
	this->SetSizer( bSizerMain );
	this->Layout();

	this->Centre( wxBOTH );

	m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("To hold zoom borders\nin place click LMB :-) \n"), wxDefaultPosition, wxDefaultSize, 0);
	bSizerButtons->Add(m_staticText1, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("1.Bilinear interpolation"), wxDefaultPosition, wxDefaultSize, 0);
	bSizerButtons->Add(m_staticText1, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("2.Bicubic b-spline interpolation"), wxDefaultPosition, wxDefaultSize, 0);
	bSizerButtons->Add(m_staticText2, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticText3 = new wxStaticText(this, wxID_ANY, wxT("3.Original image"), wxDefaultPosition, wxDefaultSize, 0);
	bSizerButtons->Add(m_staticText3, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticText4 = new wxStaticText(this, wxID_ANY, wxT("4.Lanchos interpolation"), wxDefaultPosition, wxDefaultSize, 0);
	bSizerButtons->Add(m_staticText4, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticText5 = new wxStaticText(this, wxID_ANY, wxT("5.Hermit interpolation"), wxDefaultPosition, wxDefaultSize, 0);
	bSizerButtons->Add(m_staticText5, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);


	// Connect Events
	m_panel0->Connect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::m_panel0OnPaint ), NULL, this );
	m_panel0->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::m_panel0OnUpdateUI ), NULL, this );
	m_panel0->Connect( wxEVT_ERASE_BACKGROUND , wxEraseEventHandler( MainFrame::erase_bacground ), NULL, this );
	m_panel1->Connect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::m_panel1OnPaint ), NULL, this );
	m_panel1->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::m_panel1OnUpdateUI ), NULL, this );
	m_panel1->Connect( wxEVT_ERASE_BACKGROUND , wxEraseEventHandler( MainFrame::erase_bacground ), NULL, this );
	m_panel2->Connect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::m_panel2OnPaint ), NULL, this );
	m_panel2->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::m_panel2OnUpdateUI ), NULL, this );
	m_panel2->Connect( wxEVT_ERASE_BACKGROUND , wxEraseEventHandler( MainFrame::erase_bacground ), NULL, this );
	m_panel3->Connect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::m_panel3OnPaint ), NULL, this );
	m_panel3->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::m_panel3OnUpdateUI ), NULL, this );
	m_panel3->Connect( wxEVT_ERASE_BACKGROUND , wxEraseEventHandler( MainFrame::erase_bacground ), NULL, this );
	m_panel4->Connect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::m_panel4OnPaint ), NULL, this );
	m_panel4->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::m_panel4OnUpdateUI ), NULL, this );
	m_panel4->Connect( wxEVT_ERASE_BACKGROUND , wxEraseEventHandler( MainFrame::erase_bacground ), NULL, this );
	m_panel5->Connect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::m_panel5OnPaint ), NULL, this );
	m_panel5->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::m_panel5OnUpdateUI ), NULL, this );
	m_panel5->Connect( wxEVT_ERASE_BACKGROUND , wxEraseEventHandler( MainFrame::erase_bacground ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button2OnButtonClick ), NULL, this );
	m_button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button3OnButtonClick ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainFrame::m_slider1OnScroll ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainFrame::m_slider1OnScroll ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrame::m_slider1OnScroll ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrame::m_slider1OnScroll ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrame::m_slider1OnScroll ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrame::m_slider1OnScroll ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainFrame::m_slider1OnScroll ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrame::m_slider1OnScroll ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrame::m_slider1OnScroll ), NULL, this );
	m_slider1->Connect( wxEVT_SLIDER, wxCommandEventHandler( MainFrame::m_slider1OnSlider ), NULL, this );

}

MainFrame::~MainFrame()
{
	// Disconnect Events
	m_panel0->Disconnect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::m_panel0OnPaint ), NULL, this );
	m_panel0->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::m_panel0OnUpdateUI ), NULL, this );
	
	// TODO: Figure out why this is crashing xd
	// m_panel0->Disconnect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( MainFrame::erase_bacground ), NULL, this );
	m_panel1->Disconnect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::m_panel1OnPaint ), NULL, this );
	m_panel1->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::m_panel1OnUpdateUI ), NULL, this );
	m_panel2->Disconnect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::m_panel2OnPaint ), NULL, this );
	m_panel2->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::m_panel2OnUpdateUI ), NULL, this );
	m_panel3->Disconnect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::m_panel3OnPaint ), NULL, this );
	m_panel3->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::m_panel3OnUpdateUI ), NULL, this );
	m_panel4->Disconnect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::m_panel4OnPaint ), NULL, this );
	m_panel4->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::m_panel4OnUpdateUI ), NULL, this );
	m_panel5->Disconnect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::m_panel5OnPaint ), NULL, this );
	m_panel5->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrame::m_panel5OnUpdateUI ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button2OnButtonClick ), NULL, this );
	m_button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::m_button3OnButtonClick ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainFrame::m_slider1OnScroll ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainFrame::m_slider1OnScroll ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrame::m_slider1OnScroll ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrame::m_slider1OnScroll ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrame::m_slider1OnScroll ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrame::m_slider1OnScroll ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainFrame::m_slider1OnScroll ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrame::m_slider1OnScroll ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrame::m_slider1OnScroll ), NULL, this );
	m_slider1->Disconnect( wxEVT_SLIDER, wxCommandEventHandler( MainFrame::m_slider1OnSlider ), NULL, this );

}
