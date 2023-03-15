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

using namespace std;

// Random gen 
int random(int min, int max)
{
	return min + rand() % (max - min + 1);
}

//new image handler

class wxImagePanel : public wxPanel
{
public:
    wxBitmap apple;

    wxBitmap snakeBodyLDDL;
    wxBitmap snakeBodyLUUL;
    wxBitmap snakeBodyRDDR;
    wxBitmap snakeBodyRUUR;

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

    this->snakeBodyLDDL.LoadFile(list[1], format);
    this->snakeBodyLUUL.LoadFile(list[2], format);
    this->snakeBodyRDDR.LoadFile(list[3], format);
    this->snakeBodyRUUR.LoadFile(list[4], format);

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

//Main
class Snake : public wxFrame
{
public:
    enum movSnakeDir
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    Snake();

protected:
    void OnPaint(wxPaintEvent &event);
    void PaintBcgr(wxDC &dc);
    void OnKeyDown(wxKeyEvent &);
    void OnTimer(wxCommandEvent &);
    void OnDrawLargeApple(wxCommandEvent &);
    void OnActiveLargeApple(wxCommandEvent &);
    void OnQuit(wxCommandEvent &);
    void OnReset(wxCommandEvent &);

    void OnSpeedChangeLVL1(wxCommandEvent &);
    void OnSpeedChangeLVL2(wxCommandEvent &);
    void OnSpeedChangeLVL3(wxCommandEvent &);
    void OnSpeedChangeLVL4(wxCommandEvent &);
    void OnSpeedChangeLVL5(wxCommandEvent &);
    void OnSpeedChangeLVL6(wxCommandEvent &);
    void OnSpeedChangeLVL7(wxCommandEvent &);
    void OnSpeedChangeLVL8(wxCommandEvent &);
    void OnSpeedChangeLVL9(wxCommandEvent &);
    void OnSpeedChangeLVL10(wxCommandEvent &);

private:
    wxSize zoneSize;
    wxMenu *menu;
    wxMenuBar *menuBar;
    wxMenuItem *menuQuit;
    wxMenuItem *reset;
    wxMenu *speedChose;
    wxMenuItem *speedLvL1;
    wxMenuItem *speedLvL2;
    wxMenuItem *speedLvL3;
    wxMenuItem *speedLvL4;
    wxMenuItem *speedLvL5;
    wxMenuItem *speedLvL6;
    wxMenuItem *speedLvL7;
    wxMenuItem *speedLvL8;
    wxMenuItem *speedLvL9;
    wxMenuItem *speedLvL10;

    wxPoint gridStart;
    wxPoint gridEnd;
    int xStep;
    int yStep;
    vector<wxPoint> vecSnake;
    wxPoint apple;
    wxPoint largeApple;

    wxTimer *timer;
    int speed;
    wxTimer *largeAppleTimer;
    int largeAppleRespawn;
    int largeAppleTimerMultp;
    bool largeAppleCounter;
    wxTimer *largeAppleTimerActive;
    int largeAppleTimerActiveMultp;

    movSnakeDir snakeDir;
    int score;

    bool start;
    bool pause;
    bool finish;

    wxString *list;
    wxImagePanel *imageLoader;    

    void drawGrid(wxBufferedPaintDC &, const wxPoint &, const wxPoint &);
    void drawSnake(wxBufferedPaintDC &);
    void nextApple(const wxPoint &, const wxPoint &);
    void drawApple(wxBufferedPaintDC &);
    bool collisionAppleSnake(const wxPoint &appleX, const int from = 0, bool firstOnly = false) const;
    void nextLargeApple(const wxPoint &, const wxPoint &);
    void drawLargeApple(wxBufferedPaintDC &);
    bool collisionLargeAppleSnake(const wxPoint &appleX, const int from = 0, bool firstOnly = false) const;
    void moveSnake(movSnakeDir);
};

//Implementation of Snake class
Snake::Snake() : wxFrame(NULL, wxID_ANY, wxT("Snake"), wxDefaultPosition, wxSize(1100, 800)),
                 zoneSize(1100, 800),
                 score(0)
{
    //Image part
    wxImage::AddHandler(new wxPNGHandler);

    list = new wxString[]
    {
    "images/appleImg.png", 
    "images/snakeBodyLDDLS.png",
    "images/snakeBodyLUULS.png",
    "images/snakeBodyRDDRS.png",
    "images/snakeBodyRUURS.png",

    "images/snakeBodyVERTU.png",
    "images/snakeBodyVERTD.png",
    "images/snakeBodyHORIR.png",
    "images/snakeBodyHORIL.png",

    "images/snakeHeadUP.png",
    "images/snakeHeadDOWN.png",
    "images/snakeHeadLEFT.png",
    "images/snakeHeadRIGHT.png",

    "images/largeAppleImg.png"
    };

    imageLoader = new wxImagePanel(this, list, wxBITMAP_TYPE_PNG);

    menuBar = new wxMenuBar;
    menu = new wxMenu;
    speedChose = new wxMenu;
    menuQuit = new wxMenuItem(menu, wxID_EXIT, wxT("&Quit"));
    reset = new wxMenuItem(menu, 6, wxT("&Reset"));
    speedLvL1 = new wxMenuItem(speedChose, 11, wxT("&-3"));
    speedLvL2 = new wxMenuItem(speedChose, 12, wxT("&-2"));
    speedLvL3 = new wxMenuItem(speedChose, 13, wxT("&-1"));
    speedLvL4 = new wxMenuItem(speedChose, 14, wxT("&Normal"));
    speedLvL5 = new wxMenuItem(speedChose, 15, wxT("&+1"));
    speedLvL6 = new wxMenuItem(speedChose, 16, wxT("&+2"));
    speedLvL7 = new wxMenuItem(speedChose, 17, wxT("&+3"));
    speedLvL8 = new wxMenuItem(speedChose, 18, wxT("&+4"));
    speedLvL9 = new wxMenuItem(speedChose, 19, wxT("&+5"));
    speedLvL10 = new wxMenuItem(speedChose, 20, wxT("&+6"));

    menu->Append(menuQuit);
    menu->Append(reset);
    menuBar->Append(menu, wxT("&Menu"));
    speedChose->Append(speedLvL1);
    speedChose->Append(speedLvL2);
    speedChose->Append(speedLvL3);
    speedChose->Append(speedLvL4);
    speedChose->Append(speedLvL5);
    speedChose->Append(speedLvL6);
    speedChose->Append(speedLvL7);
    speedChose->Append(speedLvL8);
    speedChose->Append(speedLvL9);
    speedChose->Append(speedLvL10);
    menuBar->Append(speedChose, wxT("&Change speed"));
    SetMenuBar(menuBar);

    // Grid settings
    gridStart = wxPoint(100, 100);
    gridEnd = wxPoint(zoneSize.GetWidth() - 150, zoneSize.GetHeight() - 150);

    xStep = (gridEnd.x - gridStart.x) / 60; //25
    yStep = (gridEnd.y - gridStart.y) / 60; //25

    // Snake spawn
    vecSnake.push_back(wxPoint(gridStart.x + xStep, gridStart.y + yStep * 12));
    vecSnake.push_back(wxPoint(gridStart.x, gridStart.y + yStep * 12));

    timer = new wxTimer(this, 1);
    speed = 160;
    largeAppleTimer = new wxTimer(this, 2);
    largeAppleTimerMultp = 50;
    largeAppleRespawn = largeAppleTimerMultp*speed*2; //+0000
    largeAppleCounter = false;
    largeAppleTimerActive = new wxTimer(this, 3);
    largeAppleTimerActiveMultp = largeAppleTimerMultp*speed/2;

    start = false;
    pause = false;
    finish = false;

    snakeDir = movSnakeDir::RIGHT;

    nextApple(gridStart, gridEnd);
    nextLargeApple(gridStart, gridEnd);

    Connect(wxEVT_PAINT, wxPaintEventHandler(Snake::OnPaint));
    Connect(wxID_EXIT, wxEVT_MENU, wxCommandEventHandler(Snake::OnQuit));
    Connect(6, wxEVT_MENU, wxCommandEventHandler(Snake::OnReset));

    Connect(11, wxEVT_MENU, wxCommandEventHandler(Snake::OnSpeedChangeLVL1));
    Connect(12, wxEVT_MENU, wxCommandEventHandler(Snake::OnSpeedChangeLVL2));
    Connect(13, wxEVT_MENU, wxCommandEventHandler(Snake::OnSpeedChangeLVL3));
    Connect(14, wxEVT_MENU, wxCommandEventHandler(Snake::OnSpeedChangeLVL4));
    Connect(15, wxEVT_MENU, wxCommandEventHandler(Snake::OnSpeedChangeLVL5));
    Connect(16, wxEVT_MENU, wxCommandEventHandler(Snake::OnSpeedChangeLVL6));
    Connect(17, wxEVT_MENU, wxCommandEventHandler(Snake::OnSpeedChangeLVL7));
    Connect(18, wxEVT_MENU, wxCommandEventHandler(Snake::OnSpeedChangeLVL8));
    Connect(19, wxEVT_MENU, wxCommandEventHandler(Snake::OnSpeedChangeLVL9));
    Connect(20, wxEVT_MENU, wxCommandEventHandler(Snake::OnSpeedChangeLVL10));
    Connect(1, wxEVT_TIMER, wxCommandEventHandler(Snake::OnTimer));
    Connect(2, wxEVT_TIMER, wxCommandEventHandler(Snake::OnDrawLargeApple));
    Connect(3, wxEVT_TIMER, wxCommandEventHandler(Snake::OnActiveLargeApple));

    //Mvement
    wxPanel *sPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);
    sPanel->Bind(wxEVT_CHAR_HOOK, &Snake::OnKeyDown, this);

}

void Snake::moveSnake(movSnakeDir snakeDir)
{
    wxPoint previousV = vecSnake[0];
    switch (snakeDir)
    {
    case movSnakeDir::LEFT: { vecSnake[0].x = vecSnake[0].x - xStep; } break;
	case movSnakeDir::RIGHT: { vecSnake[0].x = vecSnake[0].x + xStep; } break;
	case movSnakeDir::UP: { vecSnake[0].y = vecSnake[0].y - yStep; } break;
	case movSnakeDir::DOWN: { vecSnake[0].y = vecSnake[0].y + yStep; } break;
    }

    for (int i = 1; i < vecSnake.size(); ++i)
    {
        if (collisionAppleSnake(vecSnake[0], 1))
        {
            // finish = true;
            wxMessageBox(wxT("LOST GAME\n To restart after closing this window press \'S\'"), wxT("END"));

            if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
            score = 0;
            vecSnake.clear();
            vecSnake.push_back(wxPoint(gridStart.x + xStep, gridStart.y + yStep * 10));
            vecSnake.push_back(wxPoint(gridStart.x, gridStart.y + yStep * 10));
            this->snakeDir = movSnakeDir::RIGHT;
            return;
        }
    }
    
    wxPoint previousVTemp;
    for (int i = 1; i < vecSnake.size(); ++i)
    {
        previousVTemp = vecSnake[i];
        vecSnake[i] = previousV;
        previousV = previousVTemp;
    }

    if (vecSnake[0].x > gridStart.x + xStep * 60)
    {
        vecSnake[0].x = gridStart.x;
    }else if (vecSnake[0].x < gridStart.x)
    {
        vecSnake[0].x = gridStart.x + xStep * 60;
    }

    if (vecSnake[0].y > gridStart.y + yStep * 60)
    {
        vecSnake[0].y = gridStart.y;
    }else if (vecSnake[0].y < gridStart.y)
    {
        vecSnake[0].y = gridStart.y + yStep *60;
    }
}

void Snake::OnTimer(wxCommandEvent& event)
{

    if (!pause && !finish)
    {
        moveSnake(snakeDir);
    }
    if (collisionAppleSnake(apple))
    {
        vecSnake.push_back(vecSnake[vecSnake.size() - 1]);
        nextApple(gridStart, gridEnd);
        ++score;
        
    }
    if(collisionLargeAppleSnake(largeApple))
    {   
        nextLargeApple(gridStart, gridEnd);
        for (int i = 0; i < 5; i++)
        {
            vecSnake.push_back(vecSnake[vecSnake.size() - 1]);
            largeApple = wxPoint(0,0);
        }
        score += 5;
        largeAppleTimer->Stop();
        largeAppleTimerActive->Start(largeAppleTimerActiveMultp);
    }
    Refresh();
}

void Snake::OnDrawLargeApple(wxCommandEvent& event)
{   
    if (largeAppleCounter)
    {
        largeAppleCounter = false;
    }
    else if(!largeAppleCounter)
    {
        largeAppleCounter = true;
    }
    nextLargeApple(gridStart, gridEnd);
    Refresh();
}

void Snake::OnActiveLargeApple(wxCommandEvent& event){
    largeAppleCounter = false;
    largeAppleTimerActive->Stop();
    largeAppleTimer->Start(largeAppleRespawn);
}


void Snake::OnKeyDown(wxKeyEvent& event)
{
    int key = event.GetKeyCode();
    switch (key)
    {
		case 's': case 'S':
            if (!start) { start = true; pause = false; timer->Start(speed); largeAppleTimer->Start(largeAppleRespawn);} return;
		case 'p': case 'P': 
            if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();} return;
		case WXK_LEFT:
            if (snakeDir != RIGHT)
            {
                snakeDir = movSnakeDir::LEFT;
            }
            break;
		case WXK_RIGHT: 
            if (snakeDir != LEFT)
            {
                snakeDir = movSnakeDir::RIGHT;
            }
            break;
		case WXK_UP: 
            if (snakeDir != DOWN)
            {
                snakeDir = movSnakeDir::UP;
            }
            break;
		case WXK_DOWN: 
            if (snakeDir != UP)
            {
                snakeDir = movSnakeDir::DOWN;
            }
            break;
        default:
            event.Skip();
    }
}

void Snake::PaintBcgr(wxDC& dc)
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

void Snake::drawSnake(wxBufferedPaintDC& dc)
{
    //Snake Body

    //Segments display hand
    for (int i = 1; i < vecSnake.size(); ++i) {
        // xSTEP
        //TurnVerti
		if(vecSnake[i-2].x == vecSnake[i-1].x && vecSnake[i].y == vecSnake[i-1].y)
        {
            if(vecSnake[i].x < vecSnake[i-1].x && vecSnake[i-1].y < vecSnake[i-2].y)
            {//ADC
                dc.DrawBitmap(imageLoader->snakeBodyRUUR, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep);
                continue;
            }
            else if(vecSnake[i].x > vecSnake[i-1].x && vecSnake[i-1].y < vecSnake[i-2].y)
            {//BAD
                dc.DrawBitmap(imageLoader->snakeBodyLUUL, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep, false);
                continue;
            }
            else if(vecSnake[i].x < vecSnake[i-1].x && vecSnake[i-1].y > vecSnake[i-2].y)
            {//DCB
                dc.DrawBitmap(imageLoader->snakeBodyRDDR, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep, false);
                continue;
            }
            else if(vecSnake[i].x > vecSnake[i-1].x && vecSnake[i-1].y > vecSnake[i-2].y)
            {//ABC
                dc.DrawBitmap(imageLoader->snakeBodyLDDL, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep, false);
                continue;
            }
        }

        // ySTEP
        //TurnHori
		if(vecSnake[i-2].y == vecSnake[i-1].y && vecSnake[i].x == vecSnake[i-1].x)
        {
            if(vecSnake[i].y > vecSnake[i-1].y && vecSnake[i-1].x > vecSnake[i-2].x)
            {//CDA
                dc.DrawBitmap(imageLoader->snakeBodyRUUR, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep, false);
                continue;
            }
            else if(vecSnake[i].y > vecSnake[i-1].y && vecSnake[i-1].x < vecSnake[i-2].x)
            {//DAB
                dc.DrawBitmap(imageLoader->snakeBodyLUUL, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep, false);
                continue;
            }
            else if(vecSnake[i].y < vecSnake[i-1].y && vecSnake[i-1].x > vecSnake[i-2].x)
            {//BCD
                dc.DrawBitmap(imageLoader->snakeBodyRDDR, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep, false);
                continue;
            }
            else if(vecSnake[i].y < vecSnake[i-1].y && vecSnake[i-1].x < vecSnake[i-2].x)
            {//CBA
                dc.DrawBitmap(imageLoader->snakeBodyLDDL, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep, false);
                continue;
            }
        }


        if(vecSnake[i].y == vecSnake[i-1].y && vecSnake[i].x < vecSnake[i-1].x)
        {
            dc.DrawBitmap(imageLoader->snakeBodyHORIL, vecSnake[i-1].x-xStep, vecSnake[i-1].y-yStep, false);
            continue;
        }
        else if(vecSnake[i].y == vecSnake[i-1].y && vecSnake[i].x > vecSnake[i-1].x)
        {
            dc.DrawBitmap(imageLoader->snakeBodyHORIR, vecSnake[i-1].x-xStep, vecSnake[i-1].y-yStep, false);
            continue;
        }
        else if(vecSnake[i].x == vecSnake[i-1].x && vecSnake[i].y > vecSnake[i-1].y)
        { 
            dc.DrawBitmap(imageLoader->snakeBodyVERTD, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep, false);
            continue;
        }
        else if(vecSnake[i].x == vecSnake[i-1].x && vecSnake[i].y < vecSnake[i-1].y)
        { 
            dc.DrawBitmap(imageLoader->snakeBodyVERTU, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep, false);
            continue;
        }

    }

    //Snake Head
    switch (snakeDir)
    {
    case UP:
        dc.DrawBitmap(imageLoader->snakeHeadUP, vecSnake[0].x-(xStep/4)*3, vecSnake[0].y-(yStep/4)*6, false);
        break;
    case DOWN:
        dc.DrawBitmap(imageLoader->snakeHeadDOWN, vecSnake[0].x-(xStep/4)*3, vecSnake[0].y-(yStep/4)*3, false);
        break;
    case RIGHT:
        dc.DrawBitmap(imageLoader->snakeHeadRIGHT, vecSnake[0].x-(xStep/4)*3, vecSnake[0].y-yStep, false);
        break;
    case LEFT:
        dc.DrawBitmap(imageLoader->snakeHeadLEFT, vecSnake[0].x-(xStep/4)*6, vecSnake[0].y-yStep, false);
        break;

    default:
        break;
    }
}

bool Snake::collisionAppleSnake(const wxPoint& appleX, const int from, bool first_only) const
{
    if (first_only || vecSnake.size() == 1)
    {
        return vecSnake[0].x == appleX.x && vecSnake[0].y == appleX.y;
    }
    for (int i = from; i < vecSnake.size(); ++i)
    {
        if (vecSnake[i].x == appleX.x && vecSnake[i].y == appleX.y)
        {
			return true;
        }
    }
	return false;
}

//Draw apple with image
void Snake::drawApple(wxBufferedPaintDC& dc)
{
    dc.DrawBitmap(imageLoader->apple, apple.x - 6, apple.y - 6, false);
}

void Snake::nextApple(const wxPoint& pa, const wxPoint& pb)
{
	do {
		apple.x = pa.x + random(0, 60) * xStep;
		apple.y = pa.y + random(0, 60) * yStep;
	} while (collisionAppleSnake(apple));
}

//Large apple
bool Snake::collisionLargeAppleSnake(const wxPoint& largeApple, const int from, bool first_only) const
{
    if (first_only || vecSnake.size() == 1)
    {
        return vecSnake[0].x == largeApple.x && vecSnake[0].y == largeApple.y;
    }
    for (int i = from; i < vecSnake.size(); ++i)
    {
        if (vecSnake[i].x == largeApple.x && vecSnake[i].y == largeApple.y)
        {
			return true;
        }
    }
	return false;
}

void Snake::drawLargeApple(wxBufferedPaintDC& dc)
{
    dc.DrawBitmap(imageLoader->largeApple, largeApple.x - 10, largeApple.y - 10, false);   
}

void Snake::nextLargeApple(const wxPoint& pa, const wxPoint& pb)
{

	do {
		largeApple.x = pa.x + random(0, 60) * xStep;
		largeApple.y = pa.y + random(0, 60) * yStep;
	} while (collisionLargeAppleSnake(largeApple));

}

//Grid
void Snake::drawGrid(wxBufferedPaintDC& dc, const wxPoint& pa, const wxPoint& pb)
{ 
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.SetPen(wxPen(*wxColor(90, 242, 232), 1, wxPENSTYLE_DOT)); //*wxLIGHT_GREY

	for (int i = pa.y; i < pb.y; i += yStep)
		dc.DrawLine(wxPoint(pa.x, i), wxPoint(pb.x, i)); //90, 242, 232
	for (int i = pa.x; i < pb.x; i += xStep)
		dc.DrawLine(wxPoint(i, pa.y), wxPoint(i, pb.y));
}

void Snake::OnPaint(wxPaintEvent& event)
{
	wxBufferedPaintDC dc(this);

	dc.SetBrush(*wxBLACK_BRUSH);
	dc.SetPen(wxPen(*wxBLUE, 4, wxPENSTYLE_SOLID));
	dc.DrawRectangle(wxPoint(0, 0), zoneSize);
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.SetPen(wxPen(*wxBLACK, 4, wxPENSTYLE_SOLID));
	dc.DrawRectangle(wxPoint(100, 100), wxSize(zoneSize.GetWidth() - 250, zoneSize.GetHeight() - 250));

	drawGrid(dc, gridStart, gridEnd);
	if (!finish && !pause) {
		drawApple(dc);
		drawSnake(dc);     
	}
    if (largeAppleCounter)
    {
        drawLargeApple(dc);
    }

	dc.SetBrush(*wxWHITE_BRUSH);
	dc.SetPen(wxPen(*wxColour(50, 143, 168), 4, wxPENSTYLE_SOLID));
	dc.DrawRectangle(wxPoint(10, 10), wxSize(120, 80));

	wxString x;
	x << score;
	wxFont font(40, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
	dc.SetFont(font);
	dc.SetTextForeground(wxColour(50, 143, 168));
	dc.DrawText(x, wxPoint(10, 10));

	dc.SetPen(wxNullPen); 
}

void Snake::OnReset(wxCommandEvent& event)
{ 
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    score = 0;
    vecSnake.clear();
    vecSnake.push_back(wxPoint(gridStart.x + xStep, gridStart.y + yStep * 12));
    vecSnake.push_back(wxPoint(gridStart.x, gridStart.y + yStep * 12));
    snakeDir = movSnakeDir::RIGHT;
}

void Snake::OnSpeedChangeLVL1(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 220;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnSpeedChangeLVL2(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 200;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnSpeedChangeLVL3(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 180;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnSpeedChangeLVL4(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 160;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnSpeedChangeLVL5(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 140;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnSpeedChangeLVL6(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 120;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnSpeedChangeLVL7(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 100;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnSpeedChangeLVL8(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 80;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnSpeedChangeLVL9(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 60;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnSpeedChangeLVL10(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 40;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnQuit(wxCommandEvent& event)
{
	Close(true);
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
	Snake* game = new Snake();
	game->Centre();
	game->Show(true);

	return true;
}