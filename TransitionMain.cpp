/***************************************************************
 * Name:      TransitionMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Mark ()
 * Created:   2020-04-05
 * Copyright: Mark ()
 * License:
 **************************************************************/

#include "TransitionMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(TransitionFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(TransitionFrame)
const long TransitionFrame::ID_LEFTBTN = wxNewId();
const long TransitionFrame::ID_RIGHTBTN = wxNewId();
const long TransitionFrame::ID_SLIDETEXTCTRL = wxNewId();
const long TransitionFrame::ID_BROWSEBTN = wxNewId();
const long TransitionFrame::ID_RESTARTBTN = wxNewId();
const long TransitionFrame::ID_REFRESHBUTTON = wxNewId();
const long TransitionFrame::ID_EXTENSIONTEXTCTRL = wxNewId();
const long TransitionFrame::ID_MAINNOTEBOOK = wxNewId();
const long TransitionFrame::ID_SIZETEXTCTRL = wxNewId();
const long TransitionFrame::ID_ADDBTN = wxNewId();
const long TransitionFrame::ID_MINUSBTN = wxNewId();
//*)

BEGIN_EVENT_TABLE(TransitionFrame,wxFrame)
    //(*EventTable(TransitionFrame)
    //*)
END_EVENT_TABLE()

TransitionFrame::TransitionFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(TransitionFrame)
    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxMAXIMIZE_BOX, _T("wxID_ANY"));
    SetClientSize(wxSize(234,544));
    LeftBtn = new wxBitmapButton(this, ID_LEFTBTN, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_BACK")),wxART_BUTTON), wxPoint(0,0), wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_LEFTBTN"));
    LeftBtn->Disable();
    RightBtn = new wxBitmapButton(this, ID_RIGHTBTN, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_FORWARD")),wxART_BUTTON), wxPoint(24,0), wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_RIGHTBTN"));
    RightBtn->Disable();
    SlideTextCtrl = new wxTextCtrl(this, ID_SLIDETEXTCTRL, wxEmptyString, wxPoint(0,28), wxSize(70,20), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_SLIDETEXTCTRL"));
    SlideTextCtrl->Disable();
    BrowseBtn = new wxButton(this, ID_BROWSEBTN, _("Browse"), wxPoint(0,48), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BROWSEBTN"));
    RestartBtn = new wxBitmapButton(this, ID_RESTARTBTN, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_REDO")),wxART_BUTTON), wxPoint(48,0), wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_RESTARTBTN"));
    RestartBtn->Disable();
    RefreshButton = new wxButton(this, ID_REFRESHBUTTON, _("Refresh"), wxPoint(76,48), wxDefaultSize, 0, wxDefaultValidator, _T("ID_REFRESHBUTTON"));
    ExtensionTextCtrl = new wxTextCtrl(this, ID_EXTENSIONTEXTCTRL, wxEmptyString, wxPoint(151,48), wxSize(64,26), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_EXTENSIONTEXTCTRL"));
    ExtensionTextCtrl->SetToolTip(_("Extension"));
    MainNotebook = new wxNotebook(this, ID_MAINNOTEBOOK, wxPoint(0,108), wxSize(216,436), 0, _T("ID_MAINNOTEBOOK"));
    SizeTextCtrl = new wxTextCtrl(this, ID_SIZETEXTCTRL, _("100"), wxPoint(152,8), wxSize(64,30), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_SIZETEXTCTRL"));
    SizeTextCtrl->SetToolTip(_("Zoom (%)"));
    AddBtn = new wxButton(this, ID_ADDBTN, _("+"), wxPoint(0,80), wxSize(32,28), 0, wxDefaultValidator, _T("ID_ADDBTN"));
    MinusBtn = new wxButton(this, ID_MINUSBTN, _("-"), wxPoint(32,80), wxSize(32,28), 0, wxDefaultValidator, _T("ID_MINUSBTN"));
    dirDialog = new wxDirDialog(this, _("Select directory"), wxEmptyString, wxDD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxDirDialog"));

    Connect(ID_LEFTBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TransitionFrame::OnLeftBtnClick);
    Connect(ID_RIGHTBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TransitionFrame::OnRightBtnClick);
    Connect(ID_SLIDETEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&TransitionFrame::OnSlideTextCtrlTextEnter);
    Connect(ID_BROWSEBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TransitionFrame::OnBrowseBtnClick);
    Connect(ID_RESTARTBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TransitionFrame::OnRestartBtnClick);
    Connect(ID_REFRESHBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TransitionFrame::OnRefreshButtonClick);
    Connect(ID_EXTENSIONTEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&TransitionFrame::OnRefreshButtonClick);
    Connect(ID_SIZETEXTCTRL,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&TransitionFrame::OnSizeTextCtrlTextEnter);
    Connect(ID_ADDBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TransitionFrame::OnAddBtnClick);
    Connect(ID_MINUSBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TransitionFrame::OnMinusBtnClick);
    Connect(wxEVT_KEY_DOWN,(wxObjectEventFunction)&TransitionFrame::OnKeyDown);
    //*)
    SetIcon(wxICON(app_logo));
    TransitionFrame::Initialise();
}

TransitionFrame::~TransitionFrame()
{
    TransitionFrame::Save();
    //(*Destroy(TransitionFrame)
    //*)
}

void TransitionFrame::Initialise()
{
    wxDir dir(wxGetCwd());
    dirName = dir.GetName();
    wxString params[] = {"Default images directory", "Extension", "Height"};
    //Keys are specified here
    int num_params =  sizeof(params)/sizeof(wxString);
    for(int i = 0; i < num_params; i++)
    {
       configmap[params[i]] = "";
    }

    wxString filename;
    filename = dirName + "\\config.txt";
    //config.txt should be in the same directory as the application
    wxFile wxofsFile;
    if (!wxofsFile.Exists(filename))
    {
        return;
    }
    wxFileInputStream input(filename);
    wxTextInputStream text(input, wxT("\x09"), wxConvUTF8 );
    wxString line, key, value;
    while(!input.Eof())
    {
        line = text.ReadLine();
        wxStringTokenizer tkz(line, wxT(":"));
        key = tkz.GetNextToken().Trim(false).Trim(true);
        //Removes whitespace
        if (configmap.find(key) != configmap.end())
        //Include only known keys
        {
            value = tkz.GetString().Trim(false).Trim(true);
            //Removes whitespace
            configmap[key] = value;
        }
    }

    wxStringTokenizer tkz(configmap["Default images directory"], wxT(","));
    while (tkz.HasMoreTokens()) {
        imageDirs.push_back(tkz.GetNextToken().Trim(false).Trim(true));
    }
    char* p;
    unsigned long long height = strtoull(configmap["Height"], &p, 10);
    if(*p){
        height = 0;
    }
    wxSize windowSize = GetClientSize();
    SetClientSize(wxSize(windowSize.GetWidth(), windowSize.GetHeight() + height));
    windowSize = MainNotebook->GetClientSize();
    MainNotebook->SetClientSize(wxSize(windowSize.GetWidth(), windowSize.GetHeight() + height));
    for (int i = 0; i < (int)imageDirs.size(); i++) {
        wxPanel* panel = new wxPanel(MainNotebook, wxID_ANY);
        MainNotebook->InsertPage(i, panel, wxString::Format("%d", i));
        sws.push_back(new wxScrolledWindow(panel, wxID_ANY, wxPoint(0,0), wxSize(224,425 + height), wxVSCROLL, _T("ID_IMAGESCROLLEDWINDOW")));//400
        curr_image.push_back(1);
        sws[i]->SetScrollRate(10, 10);
        wxBoxSizer* ImageBoxSizer = new wxBoxSizer(wxVERTICAL);
        sws[i]->SetSizer(ImageBoxSizer);
        //SetSizer(ImageBoxSizer);
    }

    wxStringTokenizer tkz2(configmap["Extension"], wxT(","));
    while (tkz2.HasMoreTokens()) {
        extensions.push_back(tkz2.GetNextToken().Trim(false).Trim(true));
    }
    for (int i = 0; i < (int)imageDirs.size(); i++) {
        if (i < (int)extensions.size()) {
            if (extensions[i].compare("") == 0)
            {
                extensions[i] = ".png";
            }
        } else {
            extensions.push_back(".png");
        }
    }
    if (extensions.size() > imageDirs.size()) {
        extensions.erase(extensions.begin() + (imageDirs.size() - 1), extensions.end());
    }
    if (imageDirs.size() > 0) {
        ExtensionTextCtrl->SetValue(extensions[0]);
    }

    /*
    for (int i = 0; i < (int)imageDirs.size(); i++) {
        wxDir dir2(imageDirs[i]);
        if (dir2.IsOpened())
        {
            int numEntries = TransitionFrame::InitialiseImageList(i);
            sws[i]->SetVirtualSize(wxSize(178+40, numEntries * 108));
        }
    }
    */
    wxCommandEvent event = wxCommandEvent();
    TransitionFrame::OnSizeTextCtrlTextEnter(event);

    LeftBtn->Enable();
    RightBtn->Enable();
    RestartBtn->Enable();
    SlideTextCtrl->Enable();
}

int TransitionFrame::InitialiseImageList(int index)
{
    wxString extension = extensions[index];
    sws[index]->Scroll(0,0);
    sws[index]->GetSizer()->Clear(true);

    wxString filename;
    wxFile wxofsFile;
    int curr_index = 1, j = 1;
    while(true)
    {
        filename = wxString::Format("%s\\Slide%i%s", imageDirs[index], curr_index, extension);
        if (!wxofsFile.Exists(filename))
        {
            break;
        }
        wxImage image(filename, wxBITMAP_TYPE_ANY, -1);
        image.Rescale(floor(178 * proportion / 100.0), proportion, wxIMAGE_QUALITY_HIGH);

        wxBitmap bitmap(image, -1);
        long btn_id = wxNewId();
        wxButton* bitmap_btn = new wxButton(sws[index], btn_id);
        bitmap_btn->SetBitmapLabel(bitmap);
        wxString text = "";
        text << j;
        btn_to_order[btn_id] = j;
        bitmap_btn->SetLabel(text);
        Connect(btn_id, wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TransitionFrame::OnImageListItemSelect);
        sws[index]->GetSizer()->Add(bitmap_btn, 0, 0, 0);
        curr_index++;
        j++;
    }
    sws[index]->GetSizer()->SetDimension(0, 0, sws[index]->GetClientSize().x, 108*(j-1));
    curr_image[index] = 1;
    return j-1;
}

void TransitionFrame::Save()
{
    wxString joined = "";
    for (int i = 0; i < (int)imageDirs.size(); i++) {
        joined << imageDirs[i] << ",";
    }
    configmap["Default images directory"] = joined;
    joined = "";
    for (int i = 0; i < (int)extensions.size(); i++) {
        joined << extensions[i] << ",";
    }
    configmap["Extension"] = joined;

    wxString filename = dirName + "\\config.txt";
    wxFile wxofsFile(filename, wxFile::write);
    StringHashMap::iterator it;
    wxString line;
    for(it = configmap.begin(); it != configmap.end(); ++it )
    {
        line = it->first;
        line << ":" << it->second << "\n";
        wxofsFile.Write(line, line.Len());
    }
    wxofsFile.Close();
}

BOOL SetFileToCurrentTime(HANDLE hFile)
{
    FILETIME ft;
    SYSTEMTIME st;
    BOOL f;

    GetSystemTime(&st);
    SystemTimeToFileTime(&st, &ft);
    f = SetFileTime(hFile, (LPFILETIME) NULL, (LPFILETIME) NULL, &ft);
    return f;
}

void TransitionFrame::OnLeftBtnClick(wxCommandEvent& event)
{
    int index = MainNotebook->GetSelection();
    if (index == wxNOT_FOUND) {
        return;
    }
    wxString extension = extensions[index];
    if (curr_image[index] == 1){
        return;
    }
    curr_image[index]--;
    wxString filename = wxString::Format("%s\\Slide%i%s", imageDirs[index], curr_image[index], extension);
    wxFile wxofsFile;
    if (!wxofsFile.Exists(filename))
    {
        curr_image[index]++;
        return;
    }
    wxString zero_file = wxString::Format("%s\\Slide0%s", imageDirs[index], extension);
    CopyFile(filename, zero_file, false);
    HANDLE hFile = CreateFileA(zero_file, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    SetFileToCurrentTime(hFile);
    CloseHandle(hFile);
}

void TransitionFrame::OnRightBtnClick(wxCommandEvent& event)
{
    int index = MainNotebook->GetSelection();
    if (index == wxNOT_FOUND) {
        return;
    }
    wxString extension = extensions[index];
    curr_image[index]++;
    wxString filename = wxString::Format("%s\\Slide%i%s", imageDirs[index], curr_image[index], extension);
    wxFile wxofsFile;
    if (!wxofsFile.Exists(filename))
    {
        curr_image[index]--;
        return;
    }
    wxString zero_file = wxString::Format("%s\\Slide0%s", imageDirs[index], extension);
    CopyFile(filename, zero_file, false);
    HANDLE hFile = CreateFileA(zero_file, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    SetFileToCurrentTime(hFile);
    CloseHandle(hFile);
}

void TransitionFrame::OnRestartBtnClick(wxCommandEvent& event)
{
    int index = MainNotebook->GetSelection();
    if (index == wxNOT_FOUND) {
        return;
    }
    wxString extension = extensions[index];
    int prev = curr_image[index];
    curr_image[index] = 1;
    wxString filename = wxString::Format("%s\\Slide%i%s", imageDirs[index], curr_image[index], extension);
    wxFile wxofsFile;
    if (!wxofsFile.Exists(filename))
    {
        curr_image[index] = prev;
        return;
    }
    wxString zero_file = wxString::Format("%s\\Slide0%s", imageDirs[index], extension);
    CopyFile(filename, zero_file, false);
    HANDLE hFile = CreateFileA(zero_file, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    SetFileToCurrentTime(hFile);
    CloseHandle(hFile);
}

void TransitionFrame::OnSlideTextCtrlTextEnter(wxCommandEvent& event)
{
    int index = MainNotebook->GetSelection();
    if (index == wxNOT_FOUND) {
        return;
    }
    wxString extension = extensions[index];
    int previous = curr_image[index];
    curr_image[index] = atoi(SlideTextCtrl->GetValue());
    if(curr_image[index] <= 0){
        curr_image[index] = previous;
        return;
    }
    wxString filename = wxString::Format("%s\\Slide%i%s", imageDirs[index], curr_image[index], extension);
    wxFile wxofsFile;
    if (!wxofsFile.Exists(filename))
    {
        curr_image[index] = previous;
        return;
    }
    wxString zero_file = wxString::Format("%s\\Slide0%s", imageDirs[index], extension);
    CopyFile(filename, zero_file, false);
    HANDLE hFile = CreateFileA(zero_file, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    SetFileToCurrentTime(hFile);
    CloseHandle(hFile);
}

void TransitionFrame::OnSizeTextCtrlTextEnter(wxCommandEvent& event)
{
    int value = atoi(SizeTextCtrl->GetValue());
    if (value < 5) {
        return;
    }
    proportion = value;
    int width = floor(178 * proportion / 100.0) + 40;
    int height = floor(108 * proportion / 100.0);

    SetClientSize(wxSize(width + 10, GetClientSize().GetHeight()));
    MainNotebook->SetClientSize(wxSize(width + 10, MainNotebook->GetClientSize().GetHeight()));
    for (int i = 0; i < (int)sws.size(); i++) {
        int numEntries = TransitionFrame::InitialiseImageList(i);
        sws[i]->SetVirtualSize(wxSize(width, numEntries * height));
        sws[i]->SetClientSize(wxSize(width + 10, sws[i]->GetClientSize().GetHeight()));
    }
}

void TransitionFrame::OnBrowseBtnClick(wxCommandEvent& event)
{
    int index = MainNotebook->GetSelection();
    if (index == wxNOT_FOUND) {
        return;
    }
    dirDialog = new wxDirDialog(this);
    if (dirDialog->ShowModal() == wxID_OK)
    {
        wxString selectedFolder = dirDialog->GetPath();
        wxDir dir(selectedFolder);
        if(dir.IsOpened())
        {
            extensions[index] = ExtensionTextCtrl->GetLineText(0);
            imageDirs[index] = selectedFolder;
            int numEntries = TransitionFrame::InitialiseImageList(index);
            sws[index]->SetVirtualSize(wxSize(floor(178 * proportion / 100.0) + 40
                              , numEntries * floor(108 * proportion / 100.0)));
        }
    }
}

void TransitionFrame::OnRefreshButtonClick(wxCommandEvent& event)
{
    int index = MainNotebook->GetSelection();
    if (index == wxNOT_FOUND) {
        return;
    }
    extensions[index] = ExtensionTextCtrl->GetLineText(0);
    int numEntries = TransitionFrame::InitialiseImageList(index);
    sws[index]->SetVirtualSize(wxSize(floor(178 * proportion / 100.0) + 40
                                  , numEntries * floor(108 * proportion / 100.0)));
}

void TransitionFrame::OnAddBtnClick(wxCommandEvent& event)
{
    int i = sws.size();
    wxPanel* panel = new wxPanel(MainNotebook, wxID_ANY);
    MainNotebook->InsertPage(i, panel, wxString::Format("%d", i));
    sws.push_back(new wxScrolledWindow(panel, wxID_ANY, wxPoint(0,0), wxSize(224,400), wxVSCROLL|wxALWAYS_SHOW_SB, _T("ID_IMAGESCROLLEDWINDOW")));
    curr_image.push_back(1);
    sws[i]->SetScrollRate(10, 10);
    wxBoxSizer* ImageBoxSizer = new wxBoxSizer(wxVERTICAL);
    sws[i]->SetSizer(ImageBoxSizer);
    imageDirs.push_back("");
    extensions.push_back(".png");
}

void TransitionFrame::OnMinusBtnClick(wxCommandEvent& event)
{
    int index = MainNotebook->GetSelection();
    if (index == wxNOT_FOUND) {
        return;
    }
    MainNotebook->DeletePage(index);
    sws.erase(sws.begin() + index);
    curr_image.erase(curr_image.begin() + index);
    imageDirs.erase(imageDirs.begin() + index);
    extensions.erase(extensions.begin() + index);
}

void TransitionFrame::OnImageListItemSelect(wxCommandEvent& event)
{
    int index = MainNotebook->GetSelection();
    if (index == wxNOT_FOUND) {
        return;
    }
    wxString extension = extensions[index];
    int previous = curr_image[index];
    int btn_id = event.GetId();
    curr_image[index] = btn_to_order[btn_id];
    wxString filename = wxString::Format("%s\\Slide%i%s", imageDirs[index], curr_image[index], extension);
    wxFile wxofsFile;
    if (!wxofsFile.Exists(filename))
    {
        curr_image[index] = previous;
        return;
    }
    wxString zero_file = wxString::Format("%s\\Slide0%s", imageDirs[index], extension);
    CopyFile(filename, zero_file, false);
    HANDLE hFile = CreateFileA(zero_file, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    SetFileToCurrentTime(hFile);
    CloseHandle(hFile);
}

void TransitionFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void TransitionFrame::OnKeyDown(wxKeyEvent& event)
{
    if (event.GetKeyCode() == wxKeyCode::WXK_SPACE)
    {
        wxCommandEvent cevent = wxCommandEvent();
        TransitionFrame::OnRightBtnClick(cevent);
    }
}
