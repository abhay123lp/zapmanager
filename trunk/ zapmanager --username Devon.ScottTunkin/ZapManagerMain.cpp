/***************************************************************
 * Name:      ZapManagerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Devon Scott-Tunkin (info@devon-scott-tunkin.com)
 * Created:   2009-02-24
 * Copyright: Devon Scott-Tunkin (devonscott-tunkin.com)
 * License:
 **************************************************************/
#include "ZapManagerMain.h"

//wxWidgets
#include "wx_pch.h"
#include <wx/msgdlg.h>
#include <wx/dir.h>

//std
#include <sstream>
#include <string>
using namespace std;

//(*InternalHeaders(ShamanFrame)
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

const long ShamanFrame::ID_DIRPICKER1 = wxNewId();
//(*IdInit(ShamanFrame)
const long ShamanFrame::ID_STATICTEXT1 = wxNewId();
const long ShamanFrame::ID_PANEL2 = wxNewId();
const long ShamanFrame::ID_GRID1 = wxNewId();
const long ShamanFrame::ID_PANEL1 = wxNewId();
const long ShamanFrame::idMenuOpen = wxNewId();
const long ShamanFrame::idMenuClose = wxNewId();
const long ShamanFrame::idMenuFromFolder = wxNewId();
const long ShamanFrame::idMenuFromUnfound = wxNewId();
const long ShamanFrame::idMenuCreate = wxNewId();
const long ShamanFrame::idMenuExit = wxNewId();
const long ShamanFrame::idMenuCpSel = wxNewId();
const long ShamanFrame::idMenuCpAll = wxNewId();
const long ShamanFrame::idMenuCp = wxNewId();
const long ShamanFrame::idMenuRnSel = wxNewId();
const long ShamanFrame::idMenuRnAll = wxNewId();
const long ShamanFrame::idMenuRename = wxNewId();
const long ShamanFrame::idMenuAbout = wxNewId();
const long ShamanFrame::ID_STATUSBAR1 = wxNewId();
//*)



BEGIN_EVENT_TABLE(ShamanFrame,wxFrame)
    //(*EventTable(ShamanFrame)
    //*)
    EVT_DIRPICKER_CHANGED(ID_DIRPICKER1, ShamanFrame::OnSetTarget)
END_EVENT_TABLE()

ShamanFrame::ShamanFrame(wxWindow* parent,wxWindowID id)
{

    //(*Initialize(ShamanFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("ZapManager v1.0a3"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(-1,-1));
    {
     wxBitmap bmp(wxBITMAP(ICON16));
     wxMask mask(bmp, wxColor(0,255,0));
     bmp.SetMask(&mask);
     	wxIcon FrameIcon;
     	FrameIcon.CopyFromBitmap(bmp);
     	SetIcon(FrameIcon);
     }
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetMinSize(wxSize(-1,-1));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Target Folder:"), wxDefaultPosition, wxSize(72,18), 0, _T("ID_STATICTEXT1"));
    BoxSizer3->Add(StaticText1, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer2->Add(BoxSizer3, 0, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 0);
    Panel2 = new wxPanel(Panel1, ID_PANEL2, wxDefaultPosition, wxSize(0,2), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    BoxSizer2->Add(Panel2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Grid1 = new wxGrid(Panel1, ID_GRID1, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER|wxCLIP_CHILDREN, _T("ID_GRID1"));
    Grid1->CreateGrid(0,3);
    Grid1->SetMinSize(wxSize(-1,-1));
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
    Grid1->SetColLabelValue(0, _("File Name"));
    Grid1->SetColLabelValue(1, _("File Size (Bytes)"));
    Grid1->SetColLabelValue(2, _("File Hash (SHA-256)"));
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
    MenuItem7 = new wxMenuItem(MenuItem5, idMenuFromUnfound, _("from &Unfound Files..."), wxEmptyString, wxITEM_NORMAL);
    MenuItem5->Append(MenuItem7);
    Menu1->Append(idMenuCreate, _("Cre&ate Database"), MenuItem5, wxEmptyString);
    Menu1->AppendSeparator();
    MenuItem1 = new wxMenuItem(Menu1, idMenuExit, _("E&xit"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItem8 = new wxMenu();
    MenuItem9 = new wxMenuItem(MenuItem8, idMenuCpSel, _("&Selected Files"), wxEmptyString, wxITEM_NORMAL);
    MenuItem8->Append(MenuItem9);
    MenuItem10 = new wxMenuItem(MenuItem8, idMenuCpAll, _("&All Found Files"), wxEmptyString, wxITEM_NORMAL);
    MenuItem8->Append(MenuItem10);
    Menu3->Append(idMenuCp, _("&Copy"), MenuItem8, wxEmptyString);
    MenuItem11 = new wxMenu();
    MenuItem12 = new wxMenuItem(MenuItem11, idMenuRnSel, _("&Selected Files"), wxEmptyString, wxITEM_NORMAL);
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
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    OpenCSVDialog = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, _("Comma separated values (CSV) file (*.csv;*.txt)|*.csv;*.txt"), wxFD_DEFAULT_STYLE|wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_CHANGE_DIR, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    SaveCSVDialog = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, _("Comma separated values (CSV) file (*.csv)|*.csv"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT|wxFD_CHANGE_DIR, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    BoxSizer1->SetSizeHints(this);

    Connect(idMenuOpen,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ShamanFrame::OnOpenData);
    Connect(idMenuClose,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ShamanFrame::OnCloseData);
    Connect(idMenuFromFolder,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ShamanFrame::OnCreateData);
    Connect(idMenuExit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ShamanFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ShamanFrame::OnAbout);
    //*)
    my_csv_is_open = false;
    my_target_exists = false;
    DirPicker1 = new wxDirPickerCtrl(Panel1,ID_DIRPICKER1, wxEmptyString,
    _("Select a target folder containing files to process"), wxDefaultPosition,
    wxDefaultSize, wxDIRP_DEFAULT_STYLE, wxDefaultValidator, _T("ID_BUTTON1"));
    //DirPicker1->GetTextCtrl()->SetEditable(false);
    DirPicker1->GetTextCtrl()->SetSize(wxSize(500,24));
    DirPicker1->GetTextCtrl()->Disable();
    DirPicker1->SetTextCtrlGrowable(true);
    BoxSizer3->Add(DirPicker1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
    //Grid1->AutoSizeColumns(true);
    Grid1->SetSelectionMode(wxGrid::wxGridSelectRows);
    BoxSizer2->SetSizeHints(Panel1);
    BoxSizer1->SetSizeHints(this);
    this->SendSizeEvent();

    //Connect(ID_DIRPICKER1,EVT_DIRPICKER_CHANGED,(wxObjectEventFunction)&ShamanFrame::OnSetTarget);


}

ShamanFrame::~ShamanFrame()
{
    //(*Destroy(ShamanFrame)
    //*)
}

void ShamanFrame::OnQuit( wxCommandEvent& event ) {
    Close();
}

void ShamanFrame::OnAbout( wxCommandEvent& event ) {
    wxString msg = _("ZapManager 1.0a2");
    wxMessageBox( msg, _("Welcome to...") );
}

void ShamanFrame::OnGrid1CellLeftClick( wxGridEvent& event ) {
    Grid1->SelectRow(Grid1->GetGridCursorRow(), false);
}

void ShamanFrame::size_to_grid() {
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

void ShamanFrame::OnOpenData( wxCommandEvent& event ) {
    if( is_csv_open() ) {
        Grid1->DeleteRows(0,Grid1->GetNumberRows());
        CSVDatabase.clear();
    }

    if( OpenCSVDialog->ShowModal() == wxID_OK ) {
        set_csv_open( true );
        ifstream opened_CSV_file( OpenCSVDialog->GetPath() );
        string line;
        int row = 0;
        wxString filename = OpenCSVDialog->GetFilename();
        if( filename.IsEmpty() ) return;

        while( getline( opened_CSV_file, line ) ) {
            istringstream line_stream( line );
            string cellData;
            string concatTemp;
            Grid1->AppendRows(1);
            int col = 0;
            FileProperties CSVData;
            CSVDatabase.push_back(CSVData);
            size_t foundQuo;
            size_t nextQuo;
            size_t foundCom;
            size_t nextCom;
            if (line.find("\"\"") == line.npos)
            {
                while (getline(line_stream, cellData))
                {
                    foundQuo = cellData.find("\"");
                    foundCom = 0;
                    string subCell;
                    while (col < 3)
                    {
                        nextQuo = cellData.find("\"", foundQuo + 1);
                        nextCom = cellData.find(",", foundCom);
                        if (((foundCom < foundQuo && nextCom < foundQuo) || foundQuo == string::npos))
                        {
                            subCell = cellData.substr(foundCom, nextCom - foundCom);
                            //stringstream
                            //getline(subCell);
                            nextQuo = nextCom;
                        }
                        else
                        {
                            subCell = cellData.substr(foundQuo + 1, nextQuo - foundQuo - 1);
                            nextCom = nextQuo + 1;
                        }

                        Grid1->SetCellValue(row, col, subCell);
                        CSVDatabase[row].set_property(col, subCell);
                        foundQuo = cellData.find("\"", nextQuo + 1);
                        foundCom = nextCom + 1;
                        col++;
                    }
                }
                row++;
                CSVDatabase.push_back(CSVData);
            }
            else
            {
                wxMessageBox( filename << "is not a valid database" );
                opened_CSV_file.close();
                return;
            }

        }
    opened_CSV_file.close();
    MenuItem4->Enable( true );
    size_to_grid();

        //opened_CSV_file.open(OpenCSVDialog->GetPath());

        //wxFFile Bob = opened_CSV_filem_file;

    }
    else return;


    //FileName points to selected file
    //wxMessageBox( FileName );
}

void ShamanFrame::OnSetTarget( wxFileDirPickerEvent& event ) {
    TargetDatabase.clear();
    set_target( true );
    wxString dir_name = DirPicker1->GetPath();
    wxDir target_dir( _T( dir_name ) );
    wxString file_name;
    FileProperties TargetData;
    SHA256 hash_type;
    bool more_files = target_dir.GetFirst( &file_name, wxEmptyString, wxDIR_FILES );

    while( more_files ) {
        TargetDatabase.push_back( TargetData );
        TargetDatabase.back().load_from_dir( _( file_name ), _( dir_name ), hash_type );

        more_files = target_dir.GetNext( &file_name );
    }

    //if (is_csv_open())
    //{

    //    wxMessageBox( dir_name );
    //}
}

void ShamanFrame::OnCreateData(wxCommandEvent& event)
{
    if (SaveCSVDialog->ShowModal() == wxID_OK )
    {
        wxString FilePath = SaveCSVDialog->GetPath();
        SaveDataToCSV(FilePath);
    }
    else
        return;
}

void ShamanFrame::OnCloseData( wxCommandEvent& event ) {
    set_csv_open( false );
    Grid1->DeleteRows( 0, Grid1->GetNumberRows() );
    MenuItem4->Enable( false );
    //SizeFrameFromGrid();
}

bool ShamanFrame::is_csv_open() {
    return my_csv_is_open;
}

void ShamanFrame::set_csv_open( bool tf ) {
    my_csv_is_open = tf;
}

bool ShamanFrame::has_target() {
    return my_target_exists;
}

void ShamanFrame::set_target( bool tf ) {
    my_target_exists = tf;
}

string ShamanFrame::get_file_hash() {
    return "test";
}



void ShamanFrame::SaveDataToCSV(wxString FilePath)
{
    ofstream OutFile(_(FilePath));
    for (unsigned int i = 0; i < TargetDatabase.size(); i++)
    {
        OutFile << "\"" << TargetDatabase[i].get_property(0) <<
                "\",\"" << TargetDatabase[i].get_property(1) <<
                "\",\"" << TargetDatabase[i].get_property(2) << "\"\n";
    }
    OutFile.close();
}

