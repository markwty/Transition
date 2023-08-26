/***************************************************************
 * Name:      TransitionApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Mark ()
 * Created:   2020-04-05
 * Copyright: Mark ()
 * License:
 **************************************************************/

#include "wxmApp.hpp"
#include "TransitionMain.h"
#include "wx/image.h"

bool wxmApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	TransitionFrame* Frame = new TransitionFrame(0);
    	Frame->Show(true);
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
