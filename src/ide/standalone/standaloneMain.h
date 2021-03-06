/***************************************************************
 * Name:      standaloneMain.h
 * Purpose:   Defines Application Frame
 * Author:    OpenClovis ()
 * Created:   2014-11-11
 * Copyright: OpenClovis (www.openclovis.com)
 * License:
 **************************************************************/

#ifndef STANDALONEMAIN_H
#define STANDALONEMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "standalone.h"
#include "standaloneApp.h"

#define SAFPLUS_IDE_VERSION "7.0.1"

class standaloneFrame: public wxFrame
{
    public:
        standaloneFrame(wxFrame *frame, const wxString& title);
        ~standaloneFrame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout
        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};

#endif // STANDALONEMAIN_H
