/***************************************************************
 * Name:      ZapManagerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Devon Scott-Tunkin (info@devon-scott-tunkin.com)
 * Created:   2009-02-24
 * Copyright: Devon Scott-Tunkin (devonscott-tunkin.com)
 * License:
 **************************************************************/
#include "ZapManagerMain.h"
#include "DelimParser.h"
#include "LoadWindow.h"

//wxWidgets
#include "wx_pch.h"
#include <wx/msgdlg.h>
#include <wx/dir.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/filefn.h>
#include <wx/progdlg.h>

//STL
#include <sstream>
#include <fstream>
#include <set>
#include <algorithm>
using namespace std;

//(*InternalHeaders(ZapManagerFrame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/fontenum.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//Global variables
const wxColor PARTIAL_COLOR( 255, 255, 208 );
const wxColor COMPLETE_COLOR( 208, 255, 208 );
const wxColor UNRECOGNIZED_COLOR( 255, 208, 208 );
const wxString VERSION = "Zap Manager 1.0b2";
const wxString COPYRIGHT = "Copyright Zapatabase 2009.";
const long ZapManagerFrame::ID_DIRPICKER1 = wxNewId();
const long ZapManagerFrame::ID_BUTTON_COMPARE = wxNewId();

//(*IdInit(ZapManagerFrame)
const long ZapManagerFrame::ID_STATICTEXT1 = wxNewId();
const long ZapManagerFrame::ID_PANEL2 = wxNewId();
const long ZapManagerFrame::ID_GRID1 = wxNewId();
const long ZapManagerFrame::ID_PANEL1 = wxNewId();
const long ZapManagerFrame::idMenuOpen = wxNewId();
const long ZapManagerFrame::idMenuClose = wxNewId();
const long ZapManagerFrame::idMenuFromFolder = wxNewId();
const long ZapManagerFrame::idMenuFromUnfound = wxNewId();
const long ZapManagerFrame::idMenuCreate = wxNewId();
const long ZapManagerFrame::idMenuCpSel = wxNewId();
const long ZapManagerFrame::idMenuCpAll = wxNewId();
const long ZapManagerFrame::idMenuCp = wxNewId();
const long ZapManagerFrame::idMenuRnSel = wxNewId();
const long ZapManagerFrame::idMenuRnAll = wxNewId();
const long ZapManagerFrame::idMenuRename = wxNewId();
const long ZapManagerFrame::idMenuAbout = wxNewId();
const long ZapManagerFrame::ID_STATUSBAR = wxNewId();
//*)

BEGIN_EVENT_TABLE(ZapManagerFrame,wxFrame)
    //(*EventTable(ZapManagerFrame)
    //*)
    EVT_DIRPICKER_CHANGED( ID_DIRPICKER1, ZapManagerFrame::OnSetTarget )
    EVT_BUTTON( ID_BUTTON_COMPARE, ZapManagerFrame::on_compare )
END_EVENT_TABLE()

ZapManagerFrame::ZapManagerFrame(wxWindow* parent,wxWindowID id)
//    : my_database( false ), my_target_dir( false )
{
    //(*Initialize(ZapManagerFrame)
    wxMenuItem* MenuItem2;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, VERSION, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(-1,-1));

    wxIconBundle icons;
    icons.AddIcon( wxIcon( "aaaa", wxBITMAP_TYPE_ICO_RESOURCE ) );
    SetIcons( icons );

    SetStatusBarPane( -1 );
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetMinSize(wxSize(-1,-1));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Target Folder:"), wxDefaultPosition, wxSize(72,18), 0, _T("ID_STATICTEXT1"));
    BoxSizer3->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer3, 0, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 0);
    Panel2 = new wxPanel(Panel1, ID_PANEL2, wxDefaultPosition, wxSize(-1,2), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    BoxSizer2->Add(Panel2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Grid1 = new wxGrid(Panel1, ID_GRID1, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER|wxCLIP_CHILDREN, _T("ID_GRID1"));
    Grid1->CreateGrid(0,3);
    Grid1->SetTable(&my_database, false, wxGrid::wxGridSelectRows);
    Grid1->SetRowLabelSize(0);
    Grid1->SetColLabelSize(20);
    Grid1->EnableDragGridSize(false);
    Grid1->SetCellHighlightPenWidth(0);
    Grid1->EnableEditing(false);
    Grid1->EnableGridLines(true);
    Grid1->SetDefaultColSize(150, true);
    wxFontEnumerator __FontEnumerator;
    __FontEnumerator.EnumerateFacenames();
    #if wxCHECK_VERSION(2, 8, 0)
    	const wxArrayString& __FontFaces = __FontEnumerator.GetFacenames();
    #else
    	const wxArrayString& __FontFaces = *__FontEnumerator.GetFacenames();
    #endif
    wxString __GridLabelFont_1Face;
    if ( __FontFaces.Index(_T("MS Sans Serif")) != wxNOT_FOUND )
    	__GridLabelFont_1Face = _T("MS Sans Serif");
    else if ( __FontFaces.Index(_T("System")) != wxNOT_FOUND )
    	__GridLabelFont_1Face = _T("System");
    wxFont GridLabelFont_1(wxDEFAULT,wxMODERN,wxFONTSTYLE_NORMAL,wxNORMAL,false,__GridLabelFont_1Face,wxFONTENCODING_DEFAULT);
    Grid1->SetLabelFont(GridLabelFont_1);
    Grid1->SetDefaultCellFont( Grid1->GetFont() );
    Grid1->SetDefaultCellTextColour( Grid1->GetForegroundColour() );
    BoxSizer2->Add(Grid1, 2, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 0);
    Panel1->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel1);
    BoxSizer2->SetSizeHints(Panel1);
    BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, idMenuOpen, _("&Open Database..."), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem4 = new wxMenuItem(Menu1, idMenuClose, _("&Close Database"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem4);
    MenuItem4->Enable(false);
    Menu1->AppendSeparator();
    MenuItem5 = new wxMenu();
    MenuItem6 = new wxMenuItem(MenuItem5, idMenuFromFolder, _("from &Target Folder Contents..."), wxEmptyString, wxITEM_NORMAL);
    MenuItem5->Append(MenuItem6);
    MenuItem6->Enable(false);
    MenuItem7 = new wxMenuItem(MenuItem5, idMenuFromUnfound, _("from &Unfound Files..."), wxEmptyString, wxITEM_NORMAL);
    MenuItem5->Append(MenuItem7);
    MenuItem7->Enable(false);
    Menu1->Append(idMenuCreate, _("Cre&ate Database"), MenuItem5, wxEmptyString);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItem8 = new wxMenu();
    MenuItem9 = new wxMenuItem(MenuItem8, idMenuCpSel, _("&Selected Found Files"), wxEmptyString, wxITEM_NORMAL);
    MenuItem8->Append(MenuItem9);
    MenuItem10 = new wxMenuItem(MenuItem8, idMenuCpAll, _("&All Found Files"), wxEmptyString, wxITEM_NORMAL);
    MenuItem8->Append(MenuItem10);
    Menu3->Append(idMenuCp, _("&Copy"), MenuItem8, wxEmptyString);
    MenuItem11 = new wxMenu();
    MenuItem12 = new wxMenuItem(MenuItem11, idMenuRnSel, _("&Selected Found Files"), wxEmptyString, wxITEM_NORMAL);
    MenuItem11->Append(MenuItem12);
    MenuItem13 = new wxMenuItem(MenuItem11, idMenuRnAll, _("&All Found Files"), wxEmptyString, wxITEM_NORMAL);
    MenuItem11->Append(MenuItem13);
    Menu3->Append(idMenuRename, _("&Rename"), MenuItem11, wxEmptyString);
    MenuBar1->Append(Menu3, _("&Edit"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("&About"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("&Help"));
    SetMenuBar(MenuBar1);
    status_bar = new wxStatusBar(this, ID_STATUSBAR, 0, _T("ID_STATUSBAR"));
    int __wxStatusBarWidths_1[1] = { -10 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    status_bar->SetFieldsCount(1,__wxStatusBarWidths_1);
    status_bar->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(status_bar);
    status_bar->SetExtraStyle( status_bar->GetExtraStyle() | wxWS_EX_BLOCK_EVENTS );
    OpenCSVDialog = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, _("Comma separated values (CSV) file (*.csv;*.txt)|*.csv;*.txt"), wxFD_DEFAULT_STYLE|wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_CHANGE_DIR, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    SaveCSVDialog = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, _("Comma separated values (CSV) file (*.csv)|*.csv"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT|wxFD_CHANGE_DIR, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    BoxSizer1->SetSizeHints(this);

    Connect(idMenuOpen,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ZapManagerFrame::OnOpenData);
    Connect(idMenuClose,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ZapManagerFrame::OnCloseData);
    Connect(idMenuFromFolder,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ZapManagerFrame::OnCreateData);
    Connect(idMenuFromUnfound,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ZapManagerFrame::on_create_from_unfound);
    Connect(idMenuRnSel,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ZapManagerFrame::on_rename_selected);
    Connect(idMenuRnAll,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ZapManagerFrame::on_rename_found);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ZapManagerFrame::on_about);
    //*)
    DirPicker1 = new wxDirPickerCtrl(Panel1,ID_DIRPICKER1, wxEmptyString,
        _("Select a target folder containing files to process"), wxDefaultPosition,
        wxDefaultSize, wxDIRP_DEFAULT_STYLE, wxDefaultValidator, _T("ID_BUTTON1"));
    //DirPicker1->GetTextCtrl()->SetEditable(false);
    //DirPicker1->GetTextCtrl()->SetSize(wxSize(500,24));
    DirPicker1->GetTextCtrl()->Disable();
    DirPicker1->SetTextCtrlGrowable(true);
    BoxSizer3->Add(DirPicker1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
    my_button_compare = new wxButton(Panel1, ID_BUTTON_COMPARE);
    my_button_compare->SetLabel("Compare");
    BoxSizer3->Add(my_button_compare, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    Grid1->AutoSizeColumns(true);
    Grid1->SetSelectionMode(wxGrid::wxGridSelectRows);
    //Grid1->SetSelectionBackground(wxColor(0,0,0,0));
    BoxSizer2->SetSizeHints(Panel1);
    BoxSizer1->SetSizeHints(this);
    this->SendSizeEvent();
    Maximize();

    //Connect(ID_DIRPICKER1,EVT_DIRPICKER_CHANGED,(wxObjectEventFunction)&ZapManagerFrame::OnSetTarget);
}

ZapManagerFrame::~ZapManagerFrame() {
    //(*Destroy(ZapManagerFrame)
    //*)
}

void ZapManagerFrame::OnQuit( wxCommandEvent& event ) {
    Close();
}

void ZapManagerFrame::OnGrid1CellLeftClick( wxGridEvent& event ) {
    Grid1->SelectRow(Grid1->GetGridCursorRow(), false);
}

void ZapManagerFrame::fit_to_grid() {
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer3->Add(StaticText1, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer2->Add(BoxSizer3, 0, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 0);
    BoxSizer2->Add(Panel2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer2->Add(Grid1, 1, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 0);
    Panel1->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel1);
    BoxSizer3->Add(DirPicker1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
    Grid1->AutoSizeColumns(true);
    BoxSizer2->SetSizeHints(Panel1);
    BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
    BoxSizer1->SetSizeHints(this);
}

void ZapManagerFrame::OnOpenData( wxCommandEvent& event ) {
    reset_grid_color();
    MenuItem7->Enable( false );
    LoadWindow load_window( this, "bob", "cat" );
    load_window.ShowModal();

    if( OpenCSVDialog->ShowModal() == wxID_OK ) {
        if( my_database.is_open() )
            my_database.close();

        wxString csv_path = OpenCSVDialog->GetPath();
        if( csv_path.IsEmpty() ) return;
        if( my_database.open( csv_path ) )
            status_bar->SetStatusText( "Opened " + OpenCSVDialog->GetFilename()
                                        + ". " );
        else
            status_bar->SetStatusText( "" );
        MenuItem4->Enable( my_database.is_open() );
        Grid1->SetTable( &my_database, false, wxGrid::wxGridSelectRows );
        Grid1->AutoSizeColumns( true );
    }
    else return;
}

void ZapManagerFrame::OnSetTarget( wxFileDirPickerEvent& event ) {
    wxString dir_path = DirPicker1->GetPath();
    my_target.set_dir( dir_path );
    MenuItem6->Enable();
    reset_grid_color();
}

void ZapManagerFrame::OnCreateData(wxCommandEvent& event) {
    if (SaveCSVDialog->ShowModal() == wxID_OK ) {
        try {
            if( get_target_data() ) {
                SHA256 hash_type;
                my_target.save_as( SaveCSVDialog->GetPath(), hash_type );
            }
        }
        catch( wxString &error ) {
            wxMessageBox( error );
        }
    }
    else return;
}

void ZapManagerFrame::OnCloseData( wxCommandEvent& event ) {
    my_database.close();
    MenuItem4->Enable( my_database.is_open() );
    MenuItem7->Enable( false );
    Grid1->SetTable(&my_database, false, wxGrid::wxGridSelectRows);
}

bool ZapManagerFrame::get_target_data() {
    try {
        my_target.reset_dir();
        SHA256 hash_type;
        int file_count = my_target.get_file_count();
        wxProgressDialog progress_dialog( "", "Hashing Files...", file_count, NULL,
            wxPD_AUTO_HIDE | wxPD_APP_MODAL | wxPD_CAN_ABORT );
        for( int i = 0; i < file_count; ++i ) {
            my_target.get_file( hash_type );
            if( !progress_dialog.Update( i+1 ) )
                return false;
        }
        return true;
    }
    catch( wxString &error ) {
        wxMessageBox( error );
    }
    return false;
}

void ZapManagerFrame::on_compare( wxCommandEvent& event ) {
    compare_database_to_target();
}

void ZapManagerFrame::compare_database_to_target() {
    if( my_database.is_open() && my_target.is_set() ) {
        my_target.reset_dir();
        reset_grid_color();
        if( get_target_data() ) {
            const int MAX_ROW = Grid1->GetNumberRows();
            const int MAX_COL = Grid1->GetNumberCols();
            int match;
            int match_count = 0;
            wxColor match_color;
            wxString status;

            for( int i = 0; i < MAX_ROW; ++i ) {
                match = my_target.find_match(
                    Grid1->GetCellValue( i, Database::NAME ),
                    Grid1->GetCellValue( i, Database::HASH ) );

                //if( match ) {
                    ++match_count;
                    if( match == Target::PARTIAL ) {
                        match_color = PARTIAL_COLOR;
                        wxFont font = Grid1->GetCellFont( i, Database::NAME );
                        font.SetStyle( wxFONTSTYLE_ITALIC );
                        Grid1->SetCellFont( i, Database::NAME, font );
                    }
                    else if( match == Target::COMPLETE ) {
                        match_color = COMPLETE_COLOR;
                        Grid1->SetCellFont( i, Database::NAME,
                                            Grid1->GetDefaultCellFont() );
                    }
                    else
                        match_color = UNRECOGNIZED_COLOR;


                    for( int j = 0; j < MAX_COL; ++j )
                        Grid1->SetCellBackgroundColour( i, j, match_color );
                    Grid1->ForceRefresh();
                //}
            }
            try {
                my_target.move_unrecognized();
            }
            catch( wxString &error ) {
                wxMessageBox( error );
            }
            if( match_count > 0 )
                MenuItem7->Enable();
            else
                MenuItem7->Enable( false );
            status << "Found " << match_count << " of " << MAX_ROW
                   << " possible matches in target folder.";
            status_bar->SetStatusText( status );
        }
    }
}

void ZapManagerFrame::on_create_from_unfound( wxCommandEvent& event ) {
    if( SaveCSVDialog->ShowModal() == wxID_OK ) {
        const int MAX_ROW = Grid1->GetNumberRows();
        ofstream csv_file( SaveCSVDialog->GetPath() );
        for( int i = 0; i < MAX_ROW; ++i ) {
            if( Grid1->GetCellBackgroundColour( i, Database::NAME )
                == Grid1->GetDefaultCellBackgroundColour() )
            {
                csv_file << "\"" << Grid1->GetCellValue( i, Database::NAME )
                      << "\",\"" << Grid1->GetCellValue( i, Database::SIZE )
                      << "\",\"" << Grid1->GetCellValue( i, Database::HASH )
                      << "\"\n";
            }
        }
    }
    else return;
}

void ZapManagerFrame::reset_grid_color() {
    const int MAX_ROW = Grid1->GetNumberRows();
    const int MAX_COL = Grid1->GetNumberCols();
    for( int i = 0; i < MAX_ROW; ++i ) {
        for( int j = 0; j < MAX_COL; ++j )
            Grid1->SetCellBackgroundColour( i, j,
                Grid1->GetDefaultCellBackgroundColour() );
    }
    Grid1->ForceRefresh();
}

void ZapManagerFrame::on_rename_found( wxCommandEvent& event ) {
    if( my_target.rename_all() ) {
        const int MAX_ROW = Grid1->GetNumberRows();
        const int MAX_COL = Grid1->GetNumberCols();
        for( int i = 0; i < MAX_ROW; ++i ) {
            if( Grid1->GetCellBackgroundColour( i, Database::NAME )
                == PARTIAL_COLOR )
            {
                Grid1->SetCellFont( i, Database::NAME,
                                    Grid1->GetDefaultCellFont() );
                for( int j = 0; j < MAX_COL; ++j )
                    Grid1->SetCellBackgroundColour( i, j, COMPLETE_COLOR );
            }
        }
        Grid1->ForceRefresh();
    }
    else
        compare_database_to_target();
}

void ZapManagerFrame::on_rename_selected( wxCommandEvent& event ) {
    try {
        const int MAX_COL = Grid1->GetNumberCols();

        wxArrayInt rows = Grid1->GetSelectedRows();
        for( unsigned int i = 0; i < rows.GetCount(); ++i ) {
            if( my_target.rename_file( Grid1->GetCellValue( rows[i],
                                                            Database::NAME ) ) )
            {
                Grid1->SetCellFont( rows[i], Database::NAME,
                                    Grid1->GetDefaultCellFont() );
                for( int j = 0; j < MAX_COL; ++j )
                    Grid1->SetCellBackgroundColour(
                        rows[i], j, COMPLETE_COLOR );
            }
        }
        wxGridCellCoordsArray cells = Grid1->GetSelectedCells();
        for( unsigned int i = 0; i < cells.GetCount(); ++i ) {
            if( my_target.rename_file( Grid1->GetCellValue( cells[i].GetRow(),
                                                            Database::NAME ) ) )
            {
                Grid1->SetCellFont( cells[i].GetRow(), Database::NAME,
                                    Grid1->GetDefaultCellFont() );
                for( int j = 0; j < MAX_COL; ++j )
                    Grid1->SetCellBackgroundColour( cells[i].GetRow(), j,
                                                    COMPLETE_COLOR );
            }
        }

        wxGridCellCoordsArray block_top_lefts
            = Grid1->GetSelectionBlockTopLeft();
        wxGridCellCoordsArray block_bottom_rights
            = Grid1->GetSelectionBlockBottomRight();
        for( unsigned int i = 0; i < block_top_lefts.GetCount(); ++i ) {
            for( int j = block_top_lefts[i].GetRow();
                 j <= block_bottom_rights[i].GetRow(); ++j )
            {
                if( my_target.rename_file( Grid1->GetCellValue( j,
                    Database::NAME ) ) )
                {
                    Grid1->SetCellFont( j, Database::NAME,
                                        Grid1->GetDefaultCellFont() );
                    for( int k = 0; k < MAX_COL; ++k )
                        Grid1->SetCellBackgroundColour( j, k, COMPLETE_COLOR );
                }
            }
        }
    }
    catch( wxString &error ) {
        wxMessageBox( error );
    }
    Grid1->ForceRefresh();
}

void ZapManagerFrame::on_about(wxCommandEvent& event) {
    wxMessageBox( COPYRIGHT, VERSION );
}

