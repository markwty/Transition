/***************************************************************
 * Name:      TransitionMain.h
 * Purpose:   Defines Application Frame
 * Author:    Mark ()
 * Created:   2020-04-05
 * Copyright: Mark ()
 * License:
 **************************************************************/

#ifndef TRANSITIONMAIN_H
#define TRANSITIONMAIN_H

//(*Headers(TransitionFrame)
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/dirdlg.h>
#include <wx/frame.h>
#include <wx/notebook.h>
#include <wx/textctrl.h>
//*)

#include <wx/dir.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/tokenzr.h>
#include <wx/imaglist.h>
#include <wx/filename.h>
#include <wx/scrolwin.h>
#include <wx/sizer.h>

WX_DECLARE_STRING_HASH_MAP(wxString, StringHashMap);
WX_DECLARE_HASH_MAP(long, int, wxIntegerHash, wxIntegerEqual, IntHashMap);

class TransitionFrame: public wxFrame
{
    public:

        TransitionFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~TransitionFrame();
        void Initialise();
        int InitialiseImageList(int index);
        void Save();

    private:

        //(*Handlers(TransitionFrame)
        void OnQuit(wxCommandEvent& event);
        void OnLeftBtnClick(wxCommandEvent& event);
        void OnRightBtnClick(wxCommandEvent& event);
        void OnSlideTextCtrlTextEnter(wxCommandEvent& event);
        void OnRestartBtnClick(wxCommandEvent& event);
        void OnSizeSliderCmdSliderUpdated(wxScrollEvent& event);
        void OnBrowseBtnClick(wxCommandEvent& event);
        void OnRefreshButtonClick(wxCommandEvent& event);
        void OnImageListItemSelect(wxCommandEvent& event);
        void OnAddBtnClick(wxCommandEvent& event);
        void OnMinusBtnClick(wxCommandEvent& event);
        void OnSizeTextCtrlTextEnter(wxCommandEvent& event);
        void OnMainNotebookPageChanged(wxNotebookEvent& event);
        void OnKeyDown(wxKeyEvent& event);
        //*)

        //(*Identifiers(TransitionFrame)
        static const long ID_LEFTBTN;
        static const long ID_RIGHTBTN;
        static const long ID_SLIDETEXTCTRL;
        static const long ID_BROWSEBTN;
        static const long ID_RESTARTBTN;
        static const long ID_REFRESHBUTTON;
        static const long ID_EXTENSIONTEXTCTRL;
        static const long ID_MAINNOTEBOOK;
        static const long ID_SIZETEXTCTRL;
        static const long ID_ADDBTN;
        static const long ID_MINUSBTN;
        //*)

        //(*Declarations(TransitionFrame)
        wxBitmapButton* LeftBtn;
        wxBitmapButton* RestartBtn;
        wxBitmapButton* RightBtn;
        wxButton* AddBtn;
        wxButton* BrowseBtn;
        wxButton* MinusBtn;
        wxButton* RefreshButton;
        wxDirDialog* dirDialog;
        wxNotebook* MainNotebook;
        wxTextCtrl* ExtensionTextCtrl;
        wxTextCtrl* SizeTextCtrl;
        wxTextCtrl* SlideTextCtrl;
        //*)
        wxString dirName;
        wxVector <int> curr_image;
        wxVector <wxString> imageDirs;
        wxVector <wxString> extensions;
        wxVector <wxScrolledWindow*> sws;
        int proportion = 100;
        StringHashMap configmap;
        IntHashMap btn_to_order;

        DECLARE_EVENT_TABLE()
};

#endif // TRANSITIONMAIN_H
