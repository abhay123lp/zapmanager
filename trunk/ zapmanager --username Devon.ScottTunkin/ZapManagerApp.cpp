/***************************************************************
 * Name:      ZapManagerApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Devon Scott-Tunkin (info@devon-scott-tunkin.com)
 * Created:   2009-02-24
 * Copyright: Devon Scott-Tunkin (devonscott-tunkin.com)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "ZapManagerApp.h"

//(*AppHeaders
#include "ZapManagerMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(ZapManagerApp);

bool ZapManagerApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	ZapManagerFrame* Frame = new ZapManagerFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
