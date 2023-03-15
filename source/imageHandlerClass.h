// for (int i = 1; i < vecSnake.size(); ++i) {


//         if(vecSnake[i].y == vecSnake[i-1].y == vecSnake[i-2].y && vecSnake[i].x < vecSnake[i-1].x < vecSnake[i-2].x)
//         {
//             dc.DrawBitmap(imageLoader->snakeBodyHORIL, vecSnake[i].x-xStep, vecSnake[i].y-yStep, false);
//         }
//         else if(vecSnake[i].y == vecSnake[i-1].y == vecSnake[i-2].y && vecSnake[i].x > vecSnake[i-1].x > vecSnake[i-2].x)
//         {
//             dc.DrawBitmap(imageLoader->snakeBodyHORIR, vecSnake[i].x-xStep, vecSnake[i].y-yStep, false);
//         }
//         else if(vecSnake[i].x == vecSnake[i-1].x == vecSnake[i-2].x && vecSnake[i].y > vecSnake[i-1].y > vecSnake[i-2].y)
//         { 
//             dc.DrawBitmap(imageLoader->snakeBodyVERTD, vecSnake[i].x-(xStep/4)*3, vecSnake[i].y-yStep, false);
//         }
//         else if(vecSnake[i].x == vecSnake[i-1].x == vecSnake[i-2].x && vecSnake[i].y < vecSnake[i-1].y < vecSnake[i-2].y)
//         { 
//             dc.DrawBitmap(imageLoader->snakeBodyVERTU, vecSnake[i].x-(xStep/4)*3, vecSnake[i].y-yStep, false);
//         }

//         // xSTEP
//         //TurnVerti
// 		else if(vecSnake[i-2].x == vecSnake[i-1].x && vecSnake[i].y == vecSnake[i-1].y)
//         {
//             if(vecSnake[i].x < vecSnake[i-1].x && vecSnake[i-1].y < vecSnake[i-2].y)
//             {//ADC
//                 dc.DrawBitmap(imageLoader->snakeBodyRUUR, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep
//             }
//             else if(vecSnake[i].x > vecSnake[i-1].x && vecSnake[i-1].y < vecSnake[i-2].y)
//             {//DAB
//                 dc.DrawBitmap(imageLoader->snakeBodyLUUL, vecSnake[i-1].x-xStep, vecSnake[i-1].y-yStep, false);
//             }
//             else if(vecSnake[i].x < vecSnake[i-1].x && vecSnake[i-1].y > vecSnake[i-2].y)
//             {//BCD
//                 dc.DrawBitmap(imageLoader->snakeBodyRDDR, vecSnake[i-1].x-xStep, vecSnake[i-1].y-yStep, false);
//             }
//             else if(vecSnake[i].x > vecSnake[i-1].x && vecSnake[i-1].y > vecSnake[i-2].y)
//             {//CBA
//                 dc.DrawBitmap(imageLoader->snakeBodyLDDL, vecSnake[i-1].x-xStep, vecSnake[i-1].y-yStep, false);
//             }
//         }

//         // ySTEP
//         //TurnHori
// 		else if(vecSnake[i-2].y == vecSnake[i-1].y && vecSnake[i].x == vecSnake[i-1].x)
//         {
//             if(vecSnake[i].y > vecSnake[i-1].y && vecSnake[i-1].x > vecSnake[i-2].x)
//             {//CDA
//                 dc.DrawBitmap(imageLoader->snakeBodyRUUR, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep, false);
//             }
//             else if(vecSnake[i].y > vecSnake[i-1].y && vecSnake[i-1].x < vecSnake[i-2].x)
//             {//BAD
//                 dc.DrawBitmap(imageLoader->snakeBodyLUUL, vecSnake[i-1].x-xStep, vecSnake[i-1].y-yStep, false);
//             }
//             else if(vecSnake[i].y < vecSnake[i-1].y && vecSnake[i-1].x > vecSnake[i-2].x)
//             {//DCB
//                 dc.DrawBitmap(imageLoader->snakeBodyRDDR, vecSnake[i-1].x-xStep, vecSnake[i-1].y-yStep, false);
//             }
//             else if(vecSnake[i].y < vecSnake[i-1].y && vecSnake[i-1].x < vecSnake[i-2].x)
//             {//ABC
//                 dc.DrawBitmap(imageLoader->snakeBodyLDDL, vecSnake[i-1].x-xStep, vecSnake[i-1].y-yStep, false);
//             }
//         }
//     }



// class wxImagePanel : public wxPanel
// {
// public:
//     wxBitmap apple;

//     wxBitmap snakeBodyLDDL;
//     wxBitmap snakeBodyLUUL;
//     wxBitmap snakeBodyRDDR;
//     wxBitmap snakeBodyRUUR;

//     wxBitmap snakeBodyVERTU;
//     wxBitmap snakeBodyVERTD;
//     wxBitmap snakeBodyHORIR;
//     wxBitmap snakeBodyHORIL;

//     wxBitmap snakeHeadUP;
//     wxBitmap snakeHeadDOWN;
//     wxBitmap snakeHeadLEFT;
//     wxBitmap snakeHeadRIGHT;

//     wxBitmapType format;    



//     wxImagePanel(wxFrame* parent, wxString[]*, wxBitmapType format);

// };
// wxImagePanel::wxImagePanel(wxFrame* parent,
// wxString[]* list,
// wxBitmapType format):
// wxPanel(parent)
// {
//     this->apple.LoadFile(list[0], format);

//     this->snakeBodyLDDL.LoadFile(list[1], format);
//     this->snakeBodyLUUL.LoadFile(list[2], format);
//     this->snakeBodyRDDR.LoadFile(list[3], format);
//     this->snakeBodyRUUR.LoadFile(list[4], format);

//     this->snakeBodyVERTU.LoadFile(list[5], format);
//     this->snakeBodyVERTD.LoadFile(list[6], format);
//     this->snakeBodyHORIR.LoadFile(list[7], format);
//     this->snakeBodyHORIL.LoadFile(list[8], format);

//     this->snakeHeadUP.LoadFile(list[9], format);
//     this->snakeHeadDOWN.LoadFile(list[10], format);
//     this->snakeHeadLEFT.LoadFile(list[11], format);
//     this->snakeHeadRIGHT.LoadFile(list[12], format);

// }


// // //image handler
// // class wxImagePanel : public wxPanel
// // {
// // public:
// //     wxBitmap apple;

// //     wxBitmap snakeBodyLDDL;
// //     wxBitmap snakeBodyLUUL;
// //     wxBitmap snakeBodyRDDR;
// //     wxBitmap snakeBodyRUUR;

// //     wxBitmap snakeBodyVERTU;
// //     wxBitmap snakeBodyVERTD;
// //     wxBitmap snakeBodyHORIR;
// //     wxBitmap snakeBodyHORIL;

// //     wxBitmap snakeHeadUP;
// //     wxBitmap snakeHeadDOWN;
// //     wxBitmap snakeHeadLEFT;
// //     wxBitmap snakeHeadRIGHT;

// //     wxBitmapType format;    

// //     wxImagePanel(wxFrame* parent,
// //     wxString,
// //     wxString,
// //     wxString,    
// //     wxString,
// //     wxString,
// //     wxString,
// //     wxString,
// //     wxString,
// //     wxString,
// //     wxString,
// //     wxString,
// //     wxString,
// //     wxString,
// //     wxBitmapType format);

// // };
// // wxImagePanel::wxImagePanel(wxFrame* parent,
// // wxString apple,

// // wxString snakeBodyLDDL,
// // wxString snakeBodyLUUL,
// // wxString snakeBodyRDDR,
// // wxString snakeBodyRUUR,

// // wxString snakeBodyVERTU,
// // wxString snakeBodyVERTD,
// // wxString snakeBodyHORIR,
// // wxString snakeBodyHORIL,

// // wxString snakeHeadUP,
// // wxString snakeHeadDOWN,
// // wxString snakeHeadLEFT,
// // wxString snakeHeadRIGHT,
// // wxBitmapType format) :
// // wxPanel(parent)
// // {
// //     this->apple.LoadFile(apple, format);

// //     this->snakeBodyLDDL.LoadFile(snakeBodyLDDL, format);
// //     this->snakeBodyLUUL.LoadFile(snakeBodyLUUL, format);
// //     this->snakeBody0RDDR.LoadFile(snakeBodyRDDR, format);
// //     this->snakeBodyRUUR.LoadFile(snakeBodyRUUR, format);

// //     this->snakeBodyVERTU.LoadFile(snakeBodyVERTU, format);
// //     this->snakeBodyVERTD.LoadFile(snakeBodyVERTD, format);
// //     this->snakeBodyHORIR.LoadFile(snakeBodyHORIR, format);
// //     this->snakeBodyHORIL.LoadFile(snakeBodyHORIL, format);

// //     this->snakeHeadUP.LoadFile(snakeHeadUP, format);
// //     this->snakeHeadDOWN.LoadFile(snakeHeadDOWN, format);
// //     this->snakeHeadLEFT.LoadFile(snakeHeadLEFT, format);
// //     this->snakeHeadRIGHT.LoadFile(snakeHeadRIGHT, format);

// // }