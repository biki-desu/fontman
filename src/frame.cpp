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

#include "wx.hpp"
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
    EVT_MENU(fmMenu_File_Quit,  fmFrame::OnQuit)
    EVT_MENU(fmMenu_Help_About, fmFrame::OnAbout)

    EVT_CLOSE(fmFrame::OnClose)
wxEND_EVENT_TABLE()

// =====================================================================
// implementation
// =====================================================================

fmFrame::fmFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style) : wxFrame(parent, id, title, pos, size, style)
{
    // set the frame icon
    //SetIcon(wxICON(sample));

#if wxUSE_MENUS
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(fmMenu_File_Quit, "E&xit\tAlt-F4", "Quit this program");

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(fmMenu_Help_About, "&About\tF1", "Show about dialog");

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    #ifdef FM_DEBUG
        SetStatusText(wxString::Format("Welcome to fontman %s (debug version)!", FM_VERSION));
    #else
        SetStatusText(wxString::Format("Welcome to fontman %s!", FM_VERSION));
    #endif
#endif // wxUSE_STATUSBAR

    wxConfigBase *pConfig = wxConfigBase::Get();

    // restore frame position and size
    pConfig->SetPath(wxT("/ui/frame/"));
    int x = pConfig->Read(wxT("x"), 50),
        y = pConfig->Read(wxT("y"), 50),
        w = pConfig->Read(wxT("w"), 350),
        h = pConfig->Read(wxT("h"), 200);
    Move(x, y);
    SetClientSize(w, h);
    pConfig->SetPath(wxT("/"));
}

fmFrame::~fmFrame()
{
    wxConfigBase *pConfig = wxConfigBase::Get();
    if ( pConfig == NULL )
        return;

    // save the frame position
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

void fmFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
#ifdef FM_DEBUG
    wxMessageBox(wxString::Format("Welcome to fontman %s (debug version)!\n\nWe're using %s.\n\nOur OS is %s.", FM_VERSION, wxVERSION_STRING, wxGetOsDescription()), "About fontman", wxOK | wxICON_INFORMATION, this);
#else
    wxMessageBox(wxString::Format("Welcome to fontman %s! \n\nWe're using %s.\n\nOur OS is %s.", FM_VERSION, wxVERSION_STRING, wxGetOsDescription()), "About fontman", wxOK | wxICON_INFORMATION, this);
#endif

}

void fmFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void fmFrame::OnClose(wxCloseEvent& WXUNUSED(event))
{
    Destroy();
}
