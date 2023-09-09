#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/wfstream.h>
#include <wx/dcbuffer.h>
#include <wx/dc.h>
#include <wx/event.h>
#include <wx/timer.h>
#include <wx/menu.h>

class wxImagePanel : public wxPanel
{
public:
    wxBitmap apple;

    wxBitmap snakeBodyDLRU;
    wxBitmap snakeBodyDRLU;
    wxBitmap snakeBodyULRD;
    wxBitmap snakeBodyURLD;

    wxBitmap snakeBodyVERTU;
    wxBitmap snakeBodyVERTD;
    wxBitmap snakeBodyHORIR;
    wxBitmap snakeBodyHORIL;

    wxBitmap snakeHeadUP;
    wxBitmap snakeHeadDOWN;
    wxBitmap snakeHeadLEFT;
    wxBitmap snakeHeadRIGHT;

    wxBitmap largeApple;

    wxBitmapType format;    

    wxImagePanel(wxFrame* parent, wxString* list, wxBitmapType format);

};

wxImagePanel::wxImagePanel(wxFrame* parent,
wxString* list,
wxBitmapType format):
wxPanel(parent)
{
    this->apple.LoadFile(list[0], format);

    this->snakeBodyDLRU.LoadFile(list[1], format);
    this->snakeBodyDRLU.LoadFile(list[2], format);
    this->snakeBodyULRD.LoadFile(list[3], format);
    this->snakeBodyURLD.LoadFile(list[4], format);

    this->snakeBodyVERTU.LoadFile(list[5], format);
    this->snakeBodyVERTD.LoadFile(list[6], format);
    this->snakeBodyHORIR.LoadFile(list[7], format);
    this->snakeBodyHORIL.LoadFile(list[8], format);

    this->snakeHeadUP.LoadFile(list[9], format);
    this->snakeHeadDOWN.LoadFile(list[10], format);
    this->snakeHeadLEFT.LoadFile(list[11], format);
    this->snakeHeadRIGHT.LoadFile(list[12], format);

    this->largeApple.LoadFile(list[13], format);
}