#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/wfstream.h>
#include <wx/dcbuffer.h>
#include <wx/dc.h>
#include <wx/event.h>
#include <wx/timer.h>
#include <wx/menu.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <set>
#include <limits>
#include <random>     
#include <chrono> 


class Startup : public wxFrame
{
    public:
        Startup();
        bool startgame;
    
    protected:
        void PaintBcgr(wxDC &dc);
        void PaintStart(wxPaintEvent& event);
        void OnStartButtonClick(wxCommandEvent& event);



        
};

Startup::Startup() : wxFrame(NULL, wxID_ANY, wxT("Snake"), wxDefaultPosition, wxSize(1000, 1000))
{
    startgame = false;
    wxButton* startButton = new wxButton(this, wxID_ANY, "Start Game");
    startButton->Bind(wxEVT_BUTTON, &Startup::OnStartButtonClick, this);
    Connect(wxEVT_PAINT, wxPaintEventHandler(Startup::PaintStart));
}
void Startup::OnStartButtonClick(wxCommandEvent& event)
{
    Snake* game = new Snake();
    game->Centre();
	game->Show(true);
    this->Hide();
}

void Startup::PaintStart(wxPaintEvent& event)
{
    wxBufferedPaintDC dc(this);
    PaintBcgr(dc);
}

void Startup::PaintBcgr(wxDC& dc)
{
    wxColour backgroundColour = GetBackgroundColour();
    if (!backgroundColour.IsOk())
    {
        backgroundColour = wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE);
    }
    dc.SetBrush(wxBrush(backgroundColour));
    dc.SetPen(wxPen(backgroundColour, 1));
    wxRect windowRect(wxPoint(0, 0), GetClientSize());

    dc.DrawRectangle(windowRect);
}