////////////////////////////////////////////////////////////////////////
// Name:        app.hpp
// Purpose:     fmApp header
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

// =====================================================================
// declarations
// =====================================================================

class fmApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------
    virtual bool OnInit() wxOVERRIDE;
    virtual int OnExit() wxOVERRIDE;
};
