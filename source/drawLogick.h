  //Segments display logick
    for (int i = 1; i < vecSnake.size(); ++i) {
        // xSTEP
        //TurnVertical
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
        //TurnHorizontal
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





if // 1
 ( (vecSnake[i].y == vecSnake[i-1].y)
&& (vecSnake[i-1].y > vecSnake[i-2].y)
&& (vecSnake[i].x < vecSnake[i-1].x)
&& (vecSnake[i-1] == vecSnake[i-2])
){
    dc.DrawBitmap(imageLoader->snakeBodyLUUL, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep, false);
    continue;
}
else if //2
 ( (vecSnake[i].y == vecSnake[i-1].y)
&& (vecSnake[i-1].y > vecSnake[i-2].y)
&& (vecSnake[i].x < vecSnake[i-1].x)
&& (vecSnake[i-1].x == vecSnake[i-2].x) )
{ 
    dc.DrawBitmap(imageLoader->snakeBodyRUUR, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep, false);
    continue;
}
else if //3
 ( (vecSnake[i].y < vecSnake[i-1].y)
&& (vecSnake[i-1].y == vecSnake[i-2].y)
&& (vecSnake[i].x == vecSnake[i-1].x)
&& (vecSnake[i-1].x < vecSnake[i-2].x) )
{
    dc.DrawBitmap(imageLoader->snakeBodyLUUL, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep, false);
    continue;
}
else if //4
 ( (vecSnake[i].y < vecSnake[i-1].y)
&& (vecSnake[i-1].y == vecSnake[i-2].y)
&& (vecSnake[i].x == vecSnake[i-1].x)
&& (vecSnake[i-1].x > vecSnake[i-2].x) )
{
    dc.DrawBitmap(imageLoader->snakeBodyRUUR, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep, false);
    continue;
}
else if //5
 ( (vecSnake[i].y == vecSnake[i-1].y)
&& (vecSnake[i-1].y < vecSnake[i-2].y)
&& (vecSnake[i].x > vecSnake[i-1].x)
&& (vecSnake[i-1].x == vecSnake[i-2].x) )
{
    dc.DrawBitmap(imageLoader->snakeBodyLDDL, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep, false);
    continue;
}
else if //6
 ( (vecSnake[i].y == vecSnake[i-1].y)
&& (vecSnake[i-1].y < vecSnake[i-2].y)
&& (vecSnake[i].x < vecSnake[i-1].x)
&& (vecSnake[i-1].x == vecSnake[i-2].x) )
{
    dc.DrawBitmap(imageLoader->snakeBodyRDDR, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep, false);
    continue;
}
else if //7
 ( (vecSnake[i].y > vecSnake[i-1].y)
&& (vecSnake[i-1].y == vecSnake[i-2].y)
&& (vecSnake[i].x == vecSnake[i-1].x)
&& (vecSnake[i-1].x < vecSnake[i-2].x) )
{
    dc.DrawBitmap(imageLoader->snakeBodyLDDL, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep, false);
    continue;
}
else if //8
 ( (vecSnake[i].y > vecSnake[i-1].y)
&& (vecSnake[i-1].y == vecSnake[i-2].y)
&& (vecSnake[i].x == vecSnake[i-1].x)
&& (vecSnake[i-1].x > vecSnake[i-2].x) )
{
    dc.DrawBitmap(imageLoader->snakeBodyRDDR, vecSnake[i-1].x-(xStep/4)*3, vecSnake[i-1].y-yStep, false);
    continue;
}