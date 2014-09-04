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

#include <wx/clrpicker.h>
#include <wx/combo.h>
#include <wx/fontpicker.h>
#include "wx/listctrl.h"
#include <wx/spinctrl.h>
#include "wx/splitter.h"
#include <wx/srchctrl.h>

// ---------------------------------------------------------------------
// constants
// ---------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    fmMenuFile_Quit = wxID_EXIT,
    fmMenuHelp_About = wxID_ABOUT, // it is important for the id corresponding to the "About" command to have this standard value as otherwise it won't be handled properly under Mac (where it is special and put into the "Apple" menu)

    // controls
    fmVS_ID,
    fmCLPanel_ID,
    fmCL_ID,
    fmCLBtnIns_ID,
    fmCLBtnDel_ID,
    fmCLCtrlSrh_ID,
    fmHS_ID,
    fmFL_ID,
    fmPVPanel_ID,
    fmPV_ID,
    fmPVBtnInfo_ID,
    fmPVBtnChar_ID,
    fmPVCtrlClr_ID,
    fmPVCtrlFnt_ID,
    fmPVCtrlStl_ID,
    fmPVCtrlSze_ID,
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
    // exit
    void OnClose(wxCloseEvent& WXUNUSED(event));

    // menu
    void OnMenuQuit(wxCommandEvent& WXUNUSED(event));
    void OnMenuAbout(wxCommandEvent& WXUNUSED(event));

    // categories list
    void OnCatEndLabelEdit(wxListEvent& event) { event.Skip(); }
    void OnCatItemSelect(wxListEvent& event) { event.Skip(); }
    void OnCatItemDeselect(wxListEvent& event) { event.Skip(); }
    void OnCatItemActivate(wxListEvent& event) { event.Skip(); }
    void OnCatItemFocus(wxListEvent& event) { event.Skip(); }

    // categories controls
    void OnCatCtrlIns(wxCommandEvent& event) { event.Skip(); }
    void OnCatCtrlDel(wxCommandEvent& event) { event.Skip(); }
    void OnCatSearchAsYouType(wxCommandEvent& event) { event.Skip(); }

    // font list
    void OnFontItemSelect(wxListEvent& event) { event.Skip(); }

    // preview controls
    void OnPVShowInfo(wxCommandEvent& event) { event.Skip(); }
    void OnPVShowChar(wxCommandEvent& event) { event.Skip(); }
    void OnPVClrChange(wxColourPickerEvent& event) { event.Skip(); }
    void OnPVFntChange(wxFontPickerEvent& event) { event.Skip(); }
    void OnPVStlChange(wxCommandEvent& event) { event.Skip(); }
    void OnPVSzeChange(wxSpinEvent& event) { event.Skip(); }

protected:
    // menu bar
    wxMenuBar *fmMenuBar;
    wxMenu *fmMenuFile;
    wxMenu *fmMenuHelp;

    // status bar
    wxStatusBar *fmStatusBar;

    // categories sizers
    wxSplitterWindow *fmVSplit;
    wxPanel *fmCLPanel;
    wxBoxSizer *fmCLVSizer;
    wxBoxSizer *fmCLHSizer;

    // categories list
    wxListCtrl *fmCL;

    // categories controls
    wxBitmapButton *fmCLBtnIns;
    wxBitmapButton *fmCLBtnDel;
    wxSearchCtrl *fmCLCtrlSrh;

    // preview sizers
    wxSplitterWindow *fmHSplit;
    wxPanel *fmPVPanel;
    wxBoxSizer *fmPVVSizer;
    wxBoxSizer *fmPVHSizer;

    // font list
    wxListCtrl *fmFL;

    // preview text control
    wxTextCtrl *fmPV;

    // preview controls
    wxBitmapButton *fmPVBtnInfo;
    wxBitmapButton *fmPVBtnChar;
    wxColourPickerCtrl *fmPVCtrlClr;
    wxFontPickerCtrl *fmPVCtrlFnt;
    wxComboCtrl *fmPVCtrlStl;
    wxSpinCtrl *fmPVCtrlSze;

private:
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};
