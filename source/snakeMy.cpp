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

#include "game.h"


class Startup : public wxFrame
{
public:
    Startup();

protected:
    wxBitmap image;
    wxButton* startButton;

    void OnStartButtonClick(wxCommandEvent& event);
};

Startup::Startup() : wxFrame(NULL, wxID_ANY, wxT("Snake"), wxDefaultPosition, wxSize(1100, 1200))
{
    wxImage::AddHandler(new wxPNGHandler);
    wxString pathToImg = "images/intro.png";
    wxImage originalImage;

    if (originalImage.LoadFile(pathToImg, wxBITMAP_TYPE_PNG)) {
        wxSize imageSize(600, 600);
        originalImage.Rescale(imageSize.GetWidth(), imageSize.GetHeight(), wxIMAGE_QUALITY_HIGH);

        this->image = wxBitmap(originalImage);

        wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

        vbox->Add(new wxStaticBitmap(this, wxID_ANY, image), 0, wxALIGN_CENTER | wxALL, 10);

        startButton = new wxButton(this, wxID_ANY, "Start Game");
        startButton->SetSize(wxSize(400, 200));
        wxFont buttonFont = startButton->GetFont();
        buttonFont.SetPointSize(16);
        startButton->SetFont(buttonFont);
        vbox->Add(startButton, 0, wxALIGN_CENTER | wxALL, 10);
        vbox->AddStretchSpacer(); // This pushes menu up

        startButton->Bind(wxEVT_BUTTON, &Startup::OnStartButtonClick, this);

        SetSizer(vbox);
    } else {
        wxMessageBox("Failed to load the image file.", "Error", wxICON_ERROR | wxOK);
        Close();
    }
}

void Startup::OnStartButtonClick(wxCommandEvent& event)
{
    Snake* game = new Snake();
    game->Centre();
    game->Show(true);
    this->Close(true);
}

///////////////////////////// 
// MyApp
/////////////////////////////
class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};


IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	srand(time(NULL));
    Startup* startscr = new Startup();

    startscr->Center();
    startscr->Show();

	return true;
}