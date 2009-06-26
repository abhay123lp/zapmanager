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

//(*Headers(ZapManagerFrame)
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

#include "Database.h"
#include "Target.h"
using namespace shaman::model;

#include <fstream>
#include <vector>
using namespace std;
using std::vector;

#include "DelimParser.h"

class ZapManagerFrame: public wxFrame {
    public:
        ZapManagerFrame( wxWindow* parent, wxWindowID id = -1 );
        virtual ~ZapManagerFrame();

        void TargetToData( wxString );
        void fit_to_grid();
        bool get_target_data();
        void reset_grid_color();

    private:

        //(*Handlers(ZapManagerFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnSize();
        void OnGrid1CellLeftClick(wxGridEvent& event);
        void OnOpenData(wxCommandEvent& event);
        void OnCreateData(wxCommandEvent& event);
        void OnCloseData(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void on_create_from_unfound(wxCommandEvent& event);
        void on_rename_found(wxCommandEvent& event);
        void on_rename_selected(wxCommandEvent& event);
        void on_about(wxCommandEvent& event);
        //*)
        void OnSetTarget( wxFileDirPickerEvent& event );
        void on_compare( wxCommandEvent& event );
        void compare_database_to_target();

        //(*Identifiers(ZapManagerFrame)
        static const long ID_STATICTEXT1;
        static const long ID_PANEL2;
        static const long ID_GRID1;
        static const long ID_PANEL1;
        static const long idMenuOpen;
        static const long idMenuClose;
        static const long idMenuFromFolder;
        static const long idMenuFromUnfound;
        static const long idMenuCreate;
        static const long idMenuCpSel;
        static const long idMenuCpAll;
        static const long idMenuCp;
        static const long idMenuRnSel;
        static const long idMenuRnAll;
        static const long idMenuRename;
        static const long idMenuAbout;
        static const long ID_STATUSBAR;
        //*)

        static const long ID_DIRPICKER1;
        static const long ID_BUTTON_COMPARE;

        //(*Declarations(ZapManagerFrame)
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
        wxMenuItem* MenuItem6;
        wxStatusBar* status_bar;
        wxPanel* Panel2;
        wxMenu* MenuItem5;
        wxMenuItem* MenuItem9;
        wxMenu* MenuItem11;
        //*)
        //wxBoxSizer* BoxSizer2;
        //wxBoxSizer* BoxSizer1;
        wxDirPickerCtrl* DirPicker1;
        wxButton* my_button_compare;
        bool my_target_exists;

        Database my_database;
        Target my_target;

        DECLARE_EVENT_TABLE()
};


#endif // ZAPMANAGERMAIN_H
