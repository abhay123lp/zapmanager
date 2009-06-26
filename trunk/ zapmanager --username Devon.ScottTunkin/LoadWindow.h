#ifndef LOADWINDOW_H
#define LOADWINDOW_H

#ifndef WX_PRECOMP
    #include <wx/sizer.h>
    #include <wx/stattext.h>
    #include <wx/panel.h>
    #include <wx/dialog.h>
#endif


class LoadWindow: public wxDialog
{
	public:
		LoadWindow( wxWindow* parent, const wxString& some_text1,
                    const wxString& some_text2, wxWindowID id=wxID_ANY );
		virtual ~LoadWindow();

		wxPanel* panel1;
		wxStaticText* text1;
		wxStaticText* text2;

	protected:
		static const long ID_PANEL1;
		static const long ID_TEXT1;
		static const long ID_DIR_PICKER1;
		static const long ID_TEXT2;



	//private:
		void OnInit( wxInitDialogEvent& event );

		DECLARE_EVENT_TABLE()
};

#endif
