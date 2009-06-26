#include "wx_pch.h"
#include "LoadWindow.h"

#ifndef WX_PRECOMP
	#include <wx/intl.h>
	#include <wx/string.h>
#endif

#include <wx/button.h>
#include <wx/filepicker.h>

const long LoadWindow::ID_PANEL1 = wxNewId();
const long LoadWindow::ID_TEXT1 = wxNewId();
const long LoadWindow::ID_DIR_PICKER1 = wxNewId();
const long LoadWindow::ID_TEXT2 = wxNewId();

BEGIN_EVENT_TABLE( LoadWindow,wxDialog )
END_EVENT_TABLE()

LoadWindow::LoadWindow( wxWindow* parent, const wxString& some_text1,
                        const wxString& some_text2, wxWindowID id )
{
	wxBoxSizer* box_sizer1;
	wxStdDialogButtonSizer* okcancel_button_sizer;
	wxBoxSizer* box_sizer2;
	wxDirPickerCtrl* dir_picker1;
	wxButton* button_ok;
	wxButton* button_cancel;

	Create( parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize,
            wxDEFAULT_DIALOG_STYLE, _T("id") );
	box_sizer1 = new wxBoxSizer( wxHORIZONTAL );
	panel1 = new wxPanel( this, ID_PANEL1, wxDefaultPosition, wxDefaultSize,
                          wxTAB_TRAVERSAL, _T("ID_PANEL1") );

	box_sizer2 = new wxBoxSizer( wxVERTICAL );

	text1 = new wxStaticText( panel1, ID_TEXT1, some_text1,
                              wxDefaultPosition, wxDefaultSize, 0,
                              _T("ID_TEXT1") );
	box_sizer2->Add( text1, 1,
	                 wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

    //Directory selection
	text2 = new wxStaticText( panel1, ID_TEXT2, some_text2,
                              wxDefaultPosition, wxDefaultSize, 0,
                              _T("ID_TEXT2") );
	box_sizer2->Add( text2, 0,
                     wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
    dir_picker1 = new wxDirPickerCtrl( panel1, ID_DIR_PICKER1 );
    dir_picker1->GetTextCtrl()->Disable();
    dir_picker1->SetTextCtrlGrowable( true );
    box_sizer2->Add( dir_picker1, 0,
                     wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0 );

    // Ok and cancel buttons
	okcancel_button_sizer = new wxStdDialogButtonSizer();
	button_ok = new wxButton( panel1, wxID_OK, wxEmptyString );
	button_ok->Enable( false );
	okcancel_button_sizer->AddButton( button_ok );
	button_cancel = new wxButton( panel1, wxID_CANCEL, wxEmptyString );
	okcancel_button_sizer->AddButton( button_cancel );
	okcancel_button_sizer->Realize();
	box_sizer2->Add( okcancel_button_sizer, 1, wxTOP|wxLEFT|wxRIGHT
                     |wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 20 );

	panel1->SetSizer( box_sizer2 );
	box_sizer2->Fit( panel1 );
	box_sizer2->SetSizeHints( panel1 );
	box_sizer1->Add( panel1, 1,
                     wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	SetSizer( box_sizer1 );
	box_sizer1->Fit( this );
	box_sizer1->SetSizeHints( this );

	Connect( wxID_ANY, wxEVT_INIT_DIALOG,
             (wxObjectEventFunction)&LoadWindow::OnInit );
}

LoadWindow::~LoadWindow() {
}

void LoadWindow::OnInit( wxInitDialogEvent& event ) {
}
