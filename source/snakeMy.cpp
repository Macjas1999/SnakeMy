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

#include "imageHandlerClass.h"

using namespace std;


// Pseudorandom genrerator
int random(int min, int max)
{
	return min + rand() % (max - min + 1);
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
    wxMenu *speedChoice;
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

    int step;

    int gridResolution;

    wxPoint gridStart;
    wxPoint gridEnd;
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
    void nextLargeApple(const wxPoint &, const wxPoint &);
    void drawLargeApple(wxBufferedPaintDC &);
    void moveSnake(movSnakeDir);
    void changeDirection(movSnakeDir);
    bool detectCollision(const wxPoint& object, const int from) const;
    bool detectCollisionSized(const wxPoint& object, const int from, const int size) const;
    bool onLostGame();
    void aroundEdgeWrapping();

};

//Implementation of Snake class
Snake::Snake() : wxFrame(NULL, wxID_ANY, wxT("Snake"), wxDefaultPosition, wxSize(1000, 1000)),
                 zoneSize(1000, 1000),
                 score(0)
{
    //Image part
    wxImage::AddHandler(new wxPNGHandler);

    list = new wxString[]
    {
    "images/appleImg.png", 
    "images/snakeBodyDLRU.png",
    "images/snakeBodyDRLU.png",
    "images/snakeBodyULRD.png",
    "images/snakeBodyURLD.png",

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
    speedChoice = new wxMenu;
    menuQuit = new wxMenuItem(menu, wxID_EXIT, wxT("&Quit"));
    reset = new wxMenuItem(menu, 6, wxT("&Reset"));
    speedLvL1 = new wxMenuItem(speedChoice, 11, wxT("&-3"));
    speedLvL2 = new wxMenuItem(speedChoice, 12, wxT("&-2"));
    speedLvL3 = new wxMenuItem(speedChoice, 13, wxT("&-1"));
    speedLvL4 = new wxMenuItem(speedChoice, 14, wxT("&Normal"));
    speedLvL5 = new wxMenuItem(speedChoice, 15, wxT("&+1"));
    speedLvL6 = new wxMenuItem(speedChoice, 16, wxT("&+2"));
    speedLvL7 = new wxMenuItem(speedChoice, 17, wxT("&+3"));
    speedLvL8 = new wxMenuItem(speedChoice, 18, wxT("&+4"));
    speedLvL9 = new wxMenuItem(speedChoice, 19, wxT("&+5"));
    speedLvL10 = new wxMenuItem(speedChoice, 20, wxT("&+6"));

    menu->Append(menuQuit);
    menu->Append(reset);
    menuBar->Append(menu, wxT("&Menu"));
    speedChoice->Append(speedLvL1);
    speedChoice->Append(speedLvL2);
    speedChoice->Append(speedLvL3);
    speedChoice->Append(speedLvL4);
    speedChoice->Append(speedLvL5);
    speedChoice->Append(speedLvL6);
    speedChoice->Append(speedLvL7);
    speedChoice->Append(speedLvL8);
    speedChoice->Append(speedLvL9);
    speedChoice->Append(speedLvL10);
    menuBar->Append(speedChoice, wxT("&Change speed"));
    SetMenuBar(menuBar);

    // Grid settings
    gridStart = wxPoint(100, 100);
    gridEnd = wxPoint(zoneSize.GetWidth() - 100, zoneSize.GetHeight() - 100);

    gridResolution = 100;

    step = (gridEnd.x - gridStart.x) / gridResolution; //25

    // Snake spawn
    vecSnake.push_back(wxPoint(gridStart.x + step, gridStart.y + step * 12));
    vecSnake.push_back(wxPoint(gridStart.x, gridStart.y + step * 12));

    timer = new wxTimer(this, 1);
    speed = 120;
    largeAppleTimer = new wxTimer(this, 2);
    largeAppleTimerMultp = 140;
    largeAppleRespawn = largeAppleTimerMultp*speed*2; //+0000
    largeAppleCounter = false;
    largeAppleTimerActive = new wxTimer(this, 3);
    largeAppleTimerActiveMultp = largeAppleTimerMultp*speed;

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

    wxPanel *sPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);
    sPanel->Bind(wxEVT_CHAR_HOOK, &Snake::OnKeyDown, this);

}

//Movement logick
void Snake::changeDirection(movSnakeDir snakeDir)
{
    switch (snakeDir)
    {
    case movSnakeDir::LEFT: { vecSnake[0].x = vecSnake[0].x - step; } break;
	case movSnakeDir::RIGHT: { vecSnake[0].x = vecSnake[0].x + step; } break;
	case movSnakeDir::UP: { vecSnake[0].y = vecSnake[0].y - step; } break;
	case movSnakeDir::DOWN: { vecSnake[0].y = vecSnake[0].y + step; } break;
    }
}

bool Snake::detectCollision(const wxPoint& object, const int from) const
{
    for (int i = from; i < vecSnake.size(); ++i)
    {
        if (vecSnake[i].x == object.x && vecSnake[i].y == object.y)
        {
			return true;
        }
    }
	return false;
}

bool Snake::detectCollisionSized(const wxPoint& object, const int from, const int size) const
{
    for (int i = from; i < vecSnake.size(); ++i)
    {
        if (vecSnake[i].x == object.x && vecSnake[i].y == object.y
        || vecSnake[i].x == object.x && (vecSnake[i].y-size) == object.y
        || vecSnake[i].x == object.x && (vecSnake[i].y+size) == object.y
        || (vecSnake[i].x-size) == object.x && vecSnake[i].y == object.y
        || (vecSnake[i].x+size) == object.x && vecSnake[i].y == object.y)
        {
			return true;
        }
    }
	return false;
}

bool Snake::onLostGame()
{
    for (int i = 1; i < vecSnake.size(); ++i)
    {
        if (detectCollision(vecSnake[0], 1))
        {
            wxMessageBox(wxT("LOST GAME\n To restart after closing this window press \'S\'"), wxT("END"));

            this->pause = true;
            this->start = false;
            timer->Stop();
            nextLargeApple(this->gridStart, this->gridEnd);
            largeAppleTimer->Stop();
            this->score = 0;
            vecSnake.clear();
            vecSnake.push_back(wxPoint(gridStart.x + step, gridStart.y + step * 10));
            vecSnake.push_back(wxPoint(gridStart.x, gridStart.y + step * 10));
            this->snakeDir = movSnakeDir::RIGHT;
            Refresh();
            return true;
        }
    }
    return false;
}

void Snake::aroundEdgeWrapping()
{
    if (vecSnake[0].x > gridStart.x + step * gridResolution)
    {
        vecSnake[0].x = gridStart.x;
    }else if (vecSnake[0].x < gridStart.x + step)
    {
        vecSnake[0].x = gridStart.x + step * gridResolution;
    }

    if (vecSnake[0].y > gridStart.y + step * gridResolution)
    {
        vecSnake[0].y = gridStart.y;
    }else if (vecSnake[0].y < gridStart.y + step)
    {
        vecSnake[0].y = gridStart.y + step * gridResolution;
    }
}

void Snake::moveSnake(movSnakeDir snakeDir)
{
    wxPoint previousV = vecSnake[0];
    changeDirection(snakeDir);

    if (onLostGame()){ return; }
    
    
    wxPoint previousVTemp;
    for (int i = 1; i < vecSnake.size(); ++i)
    {
        previousVTemp = vecSnake[i];
        vecSnake[i] = previousV;
        previousV = previousVTemp;
    }

    aroundEdgeWrapping();

}

void Snake::nextApple(const wxPoint& pa, const wxPoint& pb)
{
	do {
		apple.x = pa.x + random(1, gridResolution-1) * step;
		apple.y = pa.y + random(1, gridResolution-1) * step;
	} while (detectCollision(apple, 1));
}

void Snake::nextLargeApple(const wxPoint& pa, const wxPoint& pb)
{

	do {
		largeApple.x = pa.x + random(1, gridResolution-1) * step;
		largeApple.y = pa.y + random(1, gridResolution-1) * step;
	} while (detectCollisionSized(largeApple, 1, step));

}

//Timers
void Snake::OnTimer(wxCommandEvent& event)
{

    if (!pause && !finish)
    {
        moveSnake(snakeDir);
    }
    if (detectCollision(apple, 1))
    {
        vecSnake.push_back(vecSnake[vecSnake.size() - 1]);
        nextApple(gridStart, gridEnd);
        ++score;
        
    }
    if(detectCollisionSized(largeApple, 1, step))
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

//Handling keyboard input
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
    int stepSkewed = (step*6)/5;

    //Segments display logick
    for (int i = 1; i < vecSnake.size(); ++i) {

        //TurnVertical
		if(vecSnake[i-2].x == vecSnake[i-1].x 
        && vecSnake[i].y == vecSnake[i-1].y)
        {
            //Up -> Left
            if(vecSnake[i].x < vecSnake[i-1].x 
            && vecSnake[i-1].y < vecSnake[i-2].y)
            {
                dc.DrawBitmap(imageLoader->snakeBodyULRD, vecSnake[i-1].x-stepSkewed, vecSnake[i-1].y-stepSkewed, false);
                continue;
            }
            //Up -> Right
            else if(vecSnake[i].x > vecSnake[i-1].x 
            && vecSnake[i-1].y < vecSnake[i-2].y)
            {
                dc.DrawBitmap(imageLoader->snakeBodyURLD, vecSnake[i-1].x-stepSkewed, vecSnake[i-1].y-stepSkewed, false);
                continue;
            }
            //Down -> Left
            else if(vecSnake[i].x < vecSnake[i-1].x 
            && vecSnake[i-1].y > vecSnake[i-2].y)
            {
                dc.DrawBitmap(imageLoader->snakeBodyDLRU, vecSnake[i-1].x-stepSkewed, vecSnake[i-1].y-stepSkewed, false);
                continue;
            }
            //Down -> Right
            else if(vecSnake[i].x > vecSnake[i-1].x 
            && vecSnake[i-1].y > vecSnake[i-2].y)
            {
                dc.DrawBitmap(imageLoader->snakeBodyDRLU, vecSnake[i-1].x-stepSkewed, vecSnake[i-1].y-stepSkewed, false);
                continue;
            }
        }

        // step
        //TurnHorizontal
		if(vecSnake[i-2].y == vecSnake[i-1].y 
        && vecSnake[i].x == vecSnake[i-1].x)
        {
            //Right -> Down
            if(vecSnake[i].y > vecSnake[i-1].y 
            && vecSnake[i-1].x > vecSnake[i-2].x)
            {
                dc.DrawBitmap(imageLoader->snakeBodyULRD, vecSnake[i-1].x-stepSkewed, vecSnake[i-1].y-stepSkewed, false);
                continue;
            }
            //Left -> Down
            else if(vecSnake[i].y > vecSnake[i-1].y 
            && vecSnake[i-1].x < vecSnake[i-2].x)
            {
                dc.DrawBitmap(imageLoader->snakeBodyURLD, vecSnake[i-1].x-stepSkewed, vecSnake[i-1].y-stepSkewed, false);
                continue;
            }
            //Right -> Up
            else if(vecSnake[i].y < vecSnake[i-1].y 
            && vecSnake[i-1].x > vecSnake[i-2].x)
            {
                dc.DrawBitmap(imageLoader->snakeBodyDLRU, vecSnake[i-1].x-stepSkewed, vecSnake[i-1].y-stepSkewed, false);
                continue;
            }
            //Left -> Up
            else if(vecSnake[i].y < vecSnake[i-1].y 
            && vecSnake[i-1].x < vecSnake[i-2].x)
            {
                dc.DrawBitmap(imageLoader->snakeBodyDRLU, vecSnake[i-1].x-stepSkewed, vecSnake[i-1].y-stepSkewed, false);
                continue;
            }
        }


        if(vecSnake[i].y == vecSnake[i-1].y 
        && vecSnake[i].x < vecSnake[i-1].x)
        {
            dc.DrawBitmap(imageLoader->snakeBodyHORIL, vecSnake[i-1].x-step, vecSnake[i-1].y-stepSkewed, false);
            continue;
        }
        else if(vecSnake[i].y == vecSnake[i-1].y 
        && vecSnake[i].x > vecSnake[i-1].x)
        {
            dc.DrawBitmap(imageLoader->snakeBodyHORIR, vecSnake[i-1].x-step, vecSnake[i-1].y-stepSkewed, false);
            continue;
        }
        else if(vecSnake[i].x == vecSnake[i-1].x 
        && vecSnake[i].y > vecSnake[i-1].y)
        { 
            dc.DrawBitmap(imageLoader->snakeBodyVERTD, vecSnake[i-1].x-stepSkewed, vecSnake[i-1].y-step, false);
            continue;
        }
        else if(vecSnake[i].x == vecSnake[i-1].x 
        && vecSnake[i].y < vecSnake[i-1].y)
        { 
            dc.DrawBitmap(imageLoader->snakeBodyVERTU, vecSnake[i-1].x-stepSkewed, vecSnake[i-1].y-step, false);
            continue;
        }

    }

    //Snake Head
    switch (snakeDir)
    {
    case UP:
        dc.DrawBitmap(imageLoader->snakeHeadUP, vecSnake[0].x-stepSkewed, vecSnake[0].y-step, false);
        break;
    case DOWN:
        dc.DrawBitmap(imageLoader->snakeHeadDOWN, vecSnake[0].x-stepSkewed, vecSnake[0].y-step, false);
        break;
    case RIGHT:
        dc.DrawBitmap(imageLoader->snakeHeadRIGHT, vecSnake[0].x-step, vecSnake[0].y-stepSkewed, false);
        break;
    case LEFT:
        dc.DrawBitmap(imageLoader->snakeHeadLEFT, vecSnake[0].x-step, vecSnake[0].y-stepSkewed, false);
        break;

    default:
        break;
    }
}

//Apple
void Snake::drawApple(wxBufferedPaintDC& dc)
{
    dc.DrawBitmap(imageLoader->apple, apple.x - 6, apple.y - 6, false);
}

//Large apple
void Snake::drawLargeApple(wxBufferedPaintDC& dc)
{
    dc.DrawBitmap(imageLoader->largeApple, largeApple.x - 10, largeApple.y - 10, false);   
}

//Grid
void Snake::drawGrid(wxBufferedPaintDC& dc, const wxPoint& pa, const wxPoint& pb)
{ 
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.SetPen(wxPen(*wxColor(90, 242, 232), 1, wxPENSTYLE_DOT)); //*wxLIGHT_GREY

	for (int i = pa.y; i < pb.y; i += step)
		dc.DrawLine(wxPoint(pa.x, i), wxPoint(pb.x, i)); //90, 242, 232
	for (int i = pa.x; i < pb.x; i += step)
		dc.DrawLine(wxPoint(i, pa.y), wxPoint(i, pb.y));
}

//Main paint event
void Snake::OnPaint(wxPaintEvent& event)
{
	wxBufferedPaintDC dc(this);

	dc.SetBrush(*wxBLACK_BRUSH);
	dc.SetPen(wxPen(*wxBLUE, 4, wxPENSTYLE_SOLID));
	dc.DrawRectangle(wxPoint(0, 0), zoneSize);
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.SetPen(wxPen(*wxBLACK, 4, wxPENSTYLE_SOLID));
	dc.DrawRectangle(wxPoint(100, 100), wxSize(zoneSize.GetWidth() - 200, zoneSize.GetHeight() - 200));

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

//Gameplay controll functions
void Snake::OnReset(wxCommandEvent& event)
{ 
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    score = 0;
    vecSnake.clear();
    vecSnake.push_back(wxPoint(gridStart.x + step, gridStart.y + step * 12));
    vecSnake.push_back(wxPoint(gridStart.x, gridStart.y + step * 12));
    snakeDir = movSnakeDir::RIGHT;
}

void Snake::OnSpeedChangeLVL1(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 180;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnSpeedChangeLVL2(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 160;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnSpeedChangeLVL3(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 140;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnSpeedChangeLVL4(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 120;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnSpeedChangeLVL5(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 100;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnSpeedChangeLVL6(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 80;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnSpeedChangeLVL7(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 60;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnSpeedChangeLVL8(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 40;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnSpeedChangeLVL9(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 20;
    this->largeAppleRespawn = largeAppleTimerMultp*speed;
}

void Snake::OnSpeedChangeLVL10(wxCommandEvent& event)
{
    if (!pause) { pause = true; start = false; timer->Stop(); largeAppleTimer->Stop();}
    this->speed = 10;
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