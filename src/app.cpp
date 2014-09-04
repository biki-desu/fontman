////////////////////////////////////////////////////////////////////////
// Name:        app.cpp
// Purpose:     fmApp class
// Author:      biki-desu
// Modified by: biki-desu
// Created:     2014/09/01
// Copyright:   (c) biki-desu
// Licence:     GPLv2
////////////////////////////////////////////////////////////////////////

// ---------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------

#include "app.hpp"
#include "frame.hpp"

// ---------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ---------------------------------------------------------------------

IMPLEMENT_APP(fmApp)

// =====================================================================
// implementation
// =====================================================================

bool fmApp::OnInit()
{
    // call the base class initialization method, currently it only parses a few common command-line options but it could be do more in the future
    if (!wxApp::OnInit())
        return false;

    SetVendorName(wxT("fontman"));
    SetAppName(wxT("fontman"));

    wxConfigBase *pConfig = wxConfigBase::Get();
    pConfig->SetRecordDefaults();

    fmFrame *frame = new fmFrame(NULL, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE);
    frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message loop and the application will run. If we returned false here, the application would exit immediately.
    return true;
}

int fmApp::OnExit()
{
    // clean up: Set() returns the active config object as Get() does, but unlike Get() it doesn't try to create one if there is none (definitely not what we want here!)
    delete wxConfigBase::Set((wxConfigBase *) NULL);

    return 0;
}
