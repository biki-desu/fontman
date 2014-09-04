////////////////////////////////////////////////////////////////////////
// Name:        frame.cpp
// Purpose:     fmFrame class
// Author:      biki-desu
// Modified by: biki-desu
// Created:     2014/09/01
// Copyright:   (c) biki-desu
// Licence:     GPLv2
////////////////////////////////////////////////////////////////////////

// ---------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------

#include "wx/artprov.h"

#include "frame.hpp"

// ---------------------------------------------------------------------
// resources
// ---------------------------------------------------------------------

// the application icon (under Windows and OS/2 it is in resources and even though we could still include the XPM here it would be unused)
//#ifndef wxHAS_IMAGES_IN_RESOURCES
    //#include "sample.xpm"
//#endif

// ---------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ---------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event handlers) which process them. It can be also done at run-time, but for the simple menu events like this the static method is much simpler.
wxBEGIN_EVENT_TABLE(fmFrame, wxFrame)
    EVT_CLOSE(fmFrame::OnClose)

    EVT_MENU(fmMenuFile_Quit,  fmFrame::OnMenuQuit)
    EVT_MENU(fmMenuHelp_About, fmFrame::OnMenuAbout)

    EVT_LIST_END_LABEL_EDIT(fmCL_ID, fmFrame::OnCatEndLabelEdit)
    EVT_LIST_ITEM_SELECTED(fmCL_ID, fmFrame::OnCatItemSelect)
    EVT_LIST_ITEM_DESELECTED(fmCL_ID, fmFrame::OnCatItemDeselect)
    EVT_LIST_ITEM_ACTIVATED(fmCL_ID, fmFrame::OnCatItemActivate)
    EVT_LIST_ITEM_FOCUSED(fmCL_ID, fmFrame::OnCatItemFocus)

    EVT_BUTTON(fmCLBtnIns_ID, fmFrame::OnCatCtrlIns)
    EVT_BUTTON(fmCLBtnDel_ID, fmFrame::OnCatCtrlDel)
    EVT_TEXT(fmCLCtrlSrh_ID, fmFrame::OnCatSearchAsYouType)

    EVT_LIST_ITEM_SELECTED(fmFL_ID, fmFrame::OnFontItemSelect)

    EVT_BUTTON(fmPVBtnInfo_ID, fmFrame::OnPVShowInfo)
    EVT_BUTTON(fmPVBtnChar_ID, fmFrame::OnPVShowChar)
    EVT_COLOURPICKER_CHANGED(fmPVCtrlClr_ID, fmFrame::OnPVClrChange)
    EVT_FONTPICKER_CHANGED(fmPVCtrlFnt_ID, fmFrame::OnPVFntChange)
    EVT_COMBOBOX(fmPVCtrlStl_ID, fmFrame::OnPVStlChange)
    EVT_SPINCTRL(fmPVCtrlSze_ID, fmFrame::OnPVSzeChange)

wxEND_EVENT_TABLE()

// =====================================================================
// implementation
// =====================================================================

fmFrame::fmFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style) : wxFrame(parent, id, title, pos, size, style)
{
    // get the config object
    wxConfigBase *pConfig = wxConfigBase::Get();

    // set the window icon
    SetIcon(wxArtProvider::GetIcon(wxART_HELP_SETTINGS, wxART_FRAME_ICON, wxDefaultSize));

    // set the window title
#ifdef FM_DEBUG
    SetTitle(wxString::Format("%s %s [DEBUG VERSION]", FM_NAME, FM_VERSION));
#else
    SetTitle(wxString::Format("%s %s", FM_NAME, FM_VERSION));
#endif

    {// restore frame position and size
        pConfig->SetPath(wxT("/ui/frame/"));

        int x = pConfig->Read(wxT("x"), 50),
            y = pConfig->Read(wxT("y"), 50),
            w = pConfig->Read(wxT("w"), 350),
            h = pConfig->Read(wxT("h"), 200);
        Move(x, y);
        SetClientSize(w, h);

        pConfig->SetPath(wxT("/"));
    }

    {// create a menu bar
        fmMenuFile = new wxMenu;
        fmMenuFile->Append(fmMenuFile_Quit, "E&xit\tAlt-F4", "Quit this program");

        fmMenuHelp = new wxMenu;
        fmMenuHelp->Append(fmMenuHelp_About, "&About\tF1", "Show about dialog");

        fmMenuBar = new wxMenuBar();
        fmMenuBar->Append(fmMenuFile, "&File");
        fmMenuBar->Append(fmMenuHelp, "&Help");

    }
    SetMenuBar(fmMenuBar);

    {// create a status bar just for fun (by default with 1 pane only)
        fmStatusBar = new wxStatusBar(this, wxID_ANY, wxSTB_DEFAULT_STYLE);

#ifdef FM_DEBUG
        fmStatusBar->PushStatusText(wxString::Format("Welcome to %s %s (debug version)!", FM_NAME, FM_VERSION), 0);
#else
        fmStatusBar->PushStatusText(wxString::Format("Welcome to %s %s!", FM_NAME, FM_VERSION), 0);
#endif
    }
    SetStatusBar(fmStatusBar);


    fmVSplit = new wxSplitterWindow(this, fmVS_ID, wxDefaultPosition, wxDefaultSize, wxSP_3D);

    {
        fmCLPanel = new wxPanel(fmVSplit, fmCLPanel_ID, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
        fmCLVSizer = new wxBoxSizer(wxVERTICAL);
        fmCLPanel->SetSizer(fmCLVSizer);

        {
            fmCL = new wxListCtrl(fmCLPanel, fmCL_ID, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_EDIT_LABELS, wxDefaultValidator); //wxLC_NO_HEADER
            fmCL->AppendColumn(wxT("Category name"), wxLIST_FORMAT_LEFT, -1);
            fmCL->InsertItem(0, wxT("All"));
            fmCL->InsertItem(1, wxT("System"));
            fmCL->InsertItem(2, wxT("User"));
            fmCL->InsertItem(3, wxT("Uncategorised"));
            fmCL->InsertItem(4, wxT(""));
            fmCL->InsertItem(5, wxT("USR CAT 1"));
            fmCL->InsertItem(6, wxT("USR CAT 2"));
            fmCL->InsertItem(7, wxT("USR CAT 3"));
        }
        fmCLVSizer->Add(fmCL, 1, wxEXPAND | wxALIGN_LEFT | wxALIGN_TOP, 0);

        fmCLHSizer = new wxBoxSizer(wxHORIZONTAL);

        {
            fmCLBtnIns = new wxBitmapButton(fmCLPanel, fmCLBtnIns_ID, wxArtProvider::GetBitmap(wxART_PLUS, wxART_BUTTON, wxDefaultSize), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator);
            fmCLHSizer->Add(fmCLBtnIns, 0, wxEXPAND | wxALIGN_LEFT | wxALIGN_TOP, 0);

            fmCLBtnDel = new wxBitmapButton(fmCLPanel, fmCLBtnDel_ID, wxArtProvider::GetBitmap(wxART_MINUS, wxART_BUTTON, wxDefaultSize), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator);
            fmCLHSizer->Add(fmCLBtnDel, 0, wxEXPAND | wxALIGN_LEFT | wxALIGN_TOP, 0);

            fmCLHSizer->AddStretchSpacer(1);

            fmCLCtrlSrh = new wxSearchCtrl(fmCLPanel, fmCLCtrlSrh_ID, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator);
            fmCLHSizer->Add(fmCLCtrlSrh, 1, wxEXPAND | wxALIGN_RIGHT | wxALIGN_TOP, 0);
        }

        fmCLVSizer->Add(fmCLHSizer, 0, wxEXPAND | wxALIGN_LEFT | wxALIGN_BOTTOM, 0);
    }

    fmHSplit = new wxSplitterWindow(fmVSplit, fmHS_ID, wxDefaultPosition, wxDefaultSize, wxSP_3D);

    {
        fmVSplit->SplitVertically(fmCLPanel, fmHSplit);
        fmVSplit->SetMinimumPaneSize(20);
        fmVSplit->SetSashGravity(0.25);
        fmVSplit->SetSashPosition(20, true);
    }

    {
        fmFL = new wxListCtrl(fmHSplit, fmFL_ID, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL, wxDefaultValidator);
        fmFL->AppendColumn(wxT("Font name"), wxLIST_FORMAT_LEFT, -1);
        fmFL->InsertItem(0, wxT("Font 1"));
        fmFL->InsertItem(1, wxT("Font 2"));
        fmFL->InsertItem(2, wxT("Font 3"));
        fmFL->InsertItem(3, wxT("Font 4"));
    }

    {
        pConfig->SetPath(wxT("/ui/preview/"));

        fmPVPanel = new wxPanel(fmHSplit, fmPVPanel_ID, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
        fmPVVSizer = new wxBoxSizer(wxVERTICAL);
        fmPVPanel->SetSizer(fmPVVSizer);

        {
            wxString fmPVDefaultText = pConfig->Read(wxT("default-text"), wxT("abcdefghijklmnopqrstuvxyz\nABCDEFGHIJKLMNOPQRSTUVXYZ\n`1234567890-=[];'#\\,./\n¬!\"£$%^&*()_+{}:@~|<>?"));
            fmPV = new wxTextCtrl(fmPVPanel, fmPV_ID, fmPVDefaultText, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE, wxDefaultValidator);
            fmPVVSizer->Add(fmPV, 1, wxEXPAND | wxALIGN_LEFT | wxALIGN_TOP, 0);
        }

        fmPVHSizer = new wxBoxSizer(wxHORIZONTAL);

        {
            fmPVBtnInfo = new wxBitmapButton(fmPVPanel, fmPVBtnInfo_ID, wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_BUTTON, wxDefaultSize), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator);
            fmPVHSizer->Add(fmPVBtnInfo, 0, wxEXPAND | wxALIGN_LEFT | wxALIGN_TOP, 0);

            fmPVBtnChar = new wxBitmapButton(fmPVPanel, fmPVBtnChar_ID, wxArtProvider::GetBitmap(wxART_HELP_SETTINGS, wxART_BUTTON, wxDefaultSize), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator);
            fmPVHSizer->Add(fmPVBtnChar, 0, wxEXPAND | wxALIGN_LEFT | wxALIGN_TOP, 0);

            fmPVCtrlClr = new wxColourPickerCtrl(fmPVPanel, fmPVCtrlClr_ID, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE, wxDefaultValidator);
            fmPVHSizer->Add(fmPVCtrlClr, 0, wxEXPAND | wxALIGN_LEFT | wxALIGN_TOP, 0);

            fmPVCtrlFnt = new wxFontPickerCtrl(fmPVPanel, fmPVCtrlFnt_ID, wxNullFont, wxDefaultPosition, wxDefaultSize, wxFNTP_DEFAULT_STYLE, wxDefaultValidator);
            fmPVHSizer->Add(fmPVCtrlFnt, 1, wxEXPAND | wxALIGN_LEFT | wxALIGN_TOP, 0);

            fmPVHSizer->AddStretchSpacer(1);

            fmPVCtrlStl = new wxComboCtrl(fmPVPanel, fmPVCtrlStl_ID, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxCB_READONLY | wxCB_SORT, wxDefaultValidator);
            fmPVHSizer->Add(fmPVCtrlStl, 0, wxEXPAND | wxALIGN_RIGHT | wxALIGN_TOP, 0);

            int fmPVCtrlSzeMin = pConfig->Read(wxT("min-size"), 6),
                fmPVCtrlSzeMax = pConfig->Read(wxT("max-size"), 72),
                fmPVCtrlSzeDft = pConfig->Read(wxT("default-size"), 12);
            fmPVCtrlSze = new wxSpinCtrl(fmPVPanel, fmPVCtrlSze_ID, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, fmPVCtrlSzeMin, fmPVCtrlSzeMax, fmPVCtrlSzeDft);
            fmPVHSizer->Add(fmPVCtrlSze, 0, wxEXPAND | wxALIGN_RIGHT | wxALIGN_TOP, 0);
        }

        fmPVVSizer->Add(fmPVHSizer, 0, wxEXPAND | wxALIGN_LEFT | wxALIGN_BOTTOM, 0);

        pConfig->SetPath(wxT("/"));
    }

    {
        fmHSplit->SplitHorizontally(fmFL, fmPVPanel);
        fmHSplit->SetMinimumPaneSize(20);
        fmHSplit->SetSashGravity(1);
        fmHSplit->SetSashPosition(20, true);
    }
}

fmFrame::~fmFrame()
{
    wxConfigBase *pConfig = wxConfigBase::Get();
    if ( pConfig == NULL )
        return;

    {// save the frame position
        pConfig->SetPath(wxT("/ui/frame/"));

        int x, y, w, h;
        GetClientSize(&w, &h);
        GetPosition(&x, &y);
        pConfig->Write(wxT("x"), (long) x);
        pConfig->Write(wxT("y"), (long) y);
        pConfig->Write(wxT("w"), (long) w);
        pConfig->Write(wxT("h"), (long) h);

        pConfig->SetPath(wxT("/"));
    }
}

void fmFrame::OnMenuAbout(wxCommandEvent& WXUNUSED(event))
{
#ifdef FM_DEBUG
    wxMessageBox(wxString::Format("Welcome to fontman %s (debug version)!\n\nWe're using %s.\n\nOur OS is %s.", FM_VERSION, wxVERSION_STRING, wxGetOsDescription()), "About fontman", wxOK | wxICON_INFORMATION, this);
#else
    wxMessageBox(wxString::Format("Welcome to fontman %s! \n\nWe're using %s.\n\nOur OS is %s.", FM_VERSION, wxVERSION_STRING, wxGetOsDescription()), "About fontman", wxOK | wxICON_INFORMATION, this);
#endif

}

void fmFrame::OnMenuQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void fmFrame::OnClose(wxCloseEvent& WXUNUSED(event))
{
    Destroy();
}
