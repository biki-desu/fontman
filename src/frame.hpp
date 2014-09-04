////////////////////////////////////////////////////////////////////////
// Name:        frame.hpp
// Purpose:     fmFrame header
// Author:      biki-desu
// Modified by: biki-desu
// Created:     2014/09/01
// Copyright:   (c) biki-desu
// Licence:     GPLv2
////////////////////////////////////////////////////////////////////////

#pragma once

// ---------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------

#include "wx.hpp"

// ---------------------------------------------------------------------
// constants
// ---------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    fmMenu_File_Quit = wxID_EXIT,
    fmMenu_Help_About = wxID_ABOUT, // it is important for the id corresponding to the "About" command to have this standard value as otherwise it won't be handled properly under Mac (where it is special and put into the "Apple" menu)
};

// =====================================================================
// declarations
// =====================================================================

class fmFrame : public wxFrame
{
public:
    // ctor(s)
    fmFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);
    virtual ~fmFrame();

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& WXUNUSED(event));
    void OnAbout(wxCommandEvent& WXUNUSED(event));
    
    void OnClose(wxCloseEvent& WXUNUSED(event));

private:
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};
