/***************************************************************
 * Name:      ZapManagerMain.h
 * Purpose:   Defines Application Frame
 * Author:    Devon Scott-Tunkin (info@devon-scott-tunkin.com)
 * Created:   2009-02-24
 * Copyright: Devon Scott-Tunkin (devonscott-tunkin.com)
 * License:
 **************************************************************/

#ifndef ZAPMANAGERMAIN_H
#define ZAPMANAGERMAIN_H

//(*Headers(ShamanFrame)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include <wx/filepicker.h>
#include "ZapManagerData.h"
#include <fstream>
#include <vector>
using namespace std;
using std::vector;

class ShamanFrame: public wxFrame {
    public:
        ShamanFrame( wxWindow* parent,wxWindowID id = -1 );
        virtual ~ShamanFrame();

        bool is_csv_open();
        void set_csv_open( bool );
        bool has_target();
        void set_target( bool );
        void TargetToData( wxString );
        void size_to_grid();
        string get_file_hash();
        void SaveDataToCSV( wxString );

    private:

        //(*Handlers(ShamanFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnSize();
        void OnGrid1CellLeftClick(wxGridEvent& event);
        void OnOpenData(wxCommandEvent& event);
        void OnCreateData(wxCommandEvent& event);
        void OnCloseData(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        //*)
        void OnSetTarget(wxFileDirPickerEvent& event);

        //(*Identifiers(ShamanFrame)
        static const long ID_STATICTEXT1;
        static const long ID_PANEL2;
        static const long ID_GRID1;
        static const long ID_PANEL1;
        static const long idMenuOpen;
        static const long idMenuClose;
        static const long idMenuFromFolder;
        static const long idMenuFromUnfound;
        static const long idMenuCreate;
        static const long idMenuExit;
        static const long idMenuCpSel;
        static const long idMenuCpAll;
        static const long idMenuCp;
        static const long idMenuRnSel;
        static const long idMenuRnAll;
        static const long idMenuRename;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        static const long ID_DIRPICKER1;

        //(*Declarations(ShamanFrame)
        wxMenuItem* MenuItem7;
        wxFileDialog* OpenCSVDialog;
        wxMenu* Menu3;
        wxMenuItem* MenuItem4;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxMenuItem* MenuItem13;
        wxGrid* Grid1;
        wxMenu* MenuItem8;
        wxMenuItem* MenuItem10;
        wxMenuItem* MenuItem12;
        wxMenuItem* MenuItem3;
        wxFileDialog* SaveCSVDialog;
        wxStatusBar* StatusBar1;
        wxMenuItem* MenuItem6;
        wxPanel* Panel2;
        wxMenu* MenuItem5;
        wxMenuItem* MenuItem9;
        wxMenu* MenuItem11;
        //*)
        //wxBoxSizer* BoxSizer2;
        //wxBoxSizer* BoxSizer1;
        wxDirPickerCtrl* DirPicker1;
        vector<FileProperties> CSVDatabase;
        vector<FileProperties> TargetDatabase;
        bool my_csv_is_open;
        bool my_target_exists;

        DECLARE_EVENT_TABLE()
};

#endif // ZAPMANAGERMAIN_H
