/***************************************************************
 * Name:      TransitionApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Mark ()
 * Created:   2020-04-05
 * Copyright: Mark ()
 * License:
 **************************************************************/

#include "TransitionApp.h"

//(*AppHeaders
#include "TransitionMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(TransitionApp);

bool TransitionApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	TransitionFrame* Frame = new TransitionFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
