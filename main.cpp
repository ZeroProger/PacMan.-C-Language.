//================================================================
//      Include Libraries

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h>
#include <time.h>

//================================================================
//      Game Settings

    const int width = 1280;
    const int height = 1024;
    const int rowsCount = 18;
    const int columnsCount = 18;
    const unsigned char GameMapStart[rowsCount][columnsCount+1] =   {
                                                                    "##################",
                                                                    "#@@@#@@@##@@@#@@@#",
                                                                    "#@#@@@#@@@@#@@@#@#",
                                                                    "#@##@##@##@##@##@#",
                                                                    "#@@@@@@@##@@@@@@@#",
                                                                    "#@##@##@@@@##@##@#",
                                                                    "#@@#@##@##@##@#@@#",
                                                                    "##@@@@@    @@@@@##",
                                                                    "##@##@# ## #@##@##",
                                                                    "##@##@# ## #@##@##",
                                                                    "##@@@@@ $  @@@@@##",
                                                                    "#@@#@##@##@##@#@@#",
                                                                    "#@##@##@@@@##@##@#",
                                                                    "#@@@@@@@##@@@@@@@#",
                                                                    "#@##@##@##@##@##@#",
                                                                    "#@#@@@#@@@@#@@@#@#",
                                                                    "#@@@#@@@##@@@#@@@#",
                                                                    "##################",
                                                                    };

//================================================================
//      Logics Variables

    //Labirint
    int x1m = 50;
    int y1m = 50;
    int x2m = 100;
    int y2m = 100;
    int xm_step = 50;
    int ym_step = 50;

    //Food
    int food;
    int score = 0;
    char foodScore[5];
    int x1c = 75;
    int y1c = 75;
    int radius = 7;
    int xc_step = 50;
    int yc_step = 50;

    //PacManDirectoin
    int pressButton;
    int lastPressButton;
    int dir = 1;
    int x = 475;
    int y = 575;
    int r = 20;

    //Check Walls
    int k1;
    int k2;
    int k3;
    int k4;
    int k5;
    int f_check;

//================================================================
//      Functions Prototypes

void Initialise();
void FoodCount();
void FoodCheck();
void Render();
void Congratulations();

//================================================================
//      Main Function

int main()
{
    initwindow(width, height);

    settextstyle(10, 0, 3);
    outtextxy(width/4, 10, "Press any button to start!");

    Initialise();
    getch();
    cleardevice();
    Initialise();

    FoodCount();

    do
    {
        Render();
    }
    while ( food != 0 );

    delay(500);
    cleardevice();
    setcolor(WHITE);
    settextstyle(10, 0, 3);
    outtextxy(width/2 - 175, height/2, "YOU WIN! Final score: ");
    outtextxy(width/2 + 145, height/2, foodScore);

    Congratulations();

    delay(5000);
    return 0;
}

//================================================================
//      Functions Descriptions

void Initialise()
{
    for (int i = 0; i < rowsCount; i++)
    {
        for (int j = 0; j < columnsCount; j++)
        {
            unsigned char graph = GameMapStart[i][j];

            switch( graph )
            {
                case '#':
                {
                    setcolor(BLUE);
                    setfillstyle(SOLID_FILL, BLUE);
                    bar(x1m + xm_step*j, y1m + ym_step*i, x2m + xm_step*j, y2m + ym_step*i);

                    break;
                }
                case '@':
                {
                    setcolor(WHITE);
                    setfillstyle(SOLID_FILL, WHITE);
                    fillellipse(x1c + xc_step*j, y1c + yc_step*i, radius, radius);

                    break;
                }
                case '$':
                {
                    setcolor(YELLOW);
                    setfillstyle(SOLID_FILL, YELLOW);
                    sector(x, y, 30, 330, r, r);
                    setcolor(BLACK);
                    setfillstyle(SOLID_FILL, BLACK);
                    fillellipse(x+5, y-15, r/8, r/8);

                    break;
                }
                default:
                {
                    continue;

                    break;
                }
            }
        }
    }
}

void FoodCount()
{
    for (int i = 0; i < rowsCount; i++)
    {
        for (int j = 0; j < columnsCount; j++)
        {
            unsigned char graph = GameMapStart[i][j];

            if ( graph == '@' ) food++;
        }
    }
}

void FoodCheck()
{
    if ( dir == 1 || pressButton == 1 )
    {
        f_check = getpixel(x+r+5, y);
        if ( f_check == 15 ) {
            score++;
            food--;
            setcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            fillellipse(x+r+10, y, radius, radius);
        }
        itoa(score, foodScore, 10);
        setcolor(WHITE);
        settextstyle(10, 0, 3);
        outtextxy(1000, 100, "You score: ");
        outtextxy(1160, 100, foodScore);
    }

    else if ( dir == 2 || pressButton == 2 )
    {
        f_check = getpixel(x-r-5, y);
        if ( f_check == 15 ) {
            score++;
            food--;
            setcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            fillellipse(x-r-10, y, radius, radius);
        }
        itoa(score, foodScore, 10);
        setcolor(WHITE);
        settextstyle(10, 0, 3);
        outtextxy(1000, 100, "You score: ");
        outtextxy(1160, 100, foodScore);
    }

    else if ( dir == 3 || pressButton == 3 )
    {
        f_check = getpixel(x, y-r-5);
        if ( f_check == 15 ) {
            score++;
            food--;
            setcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            fillellipse(x, y-r-10, radius, radius);
        }
        itoa(score, foodScore, 10);
        setcolor(WHITE);
        settextstyle(10, 0, 3);
        outtextxy(1000, 100, "You score: ");
        outtextxy(1160, 100, foodScore);
    }

    else if ( dir == 4 || pressButton == 4 )
    {
        f_check = getpixel(x, y+r+5);
        if ( f_check == 15 ) {
            score++;
            food--;
            setcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            fillellipse(x, y+r+10, radius, radius);
        }
        itoa(score, foodScore, 10);
        setcolor(WHITE);
        settextstyle(10, 0, 3);
        outtextxy(1000, 100, "You score: ");
        outtextxy(1160, 100, foodScore);
    }
}

void Render()
{
    if (GetAsyncKeyState(VK_RIGHT)) {pressButton = 1;}
    else if (GetAsyncKeyState(VK_LEFT)) {pressButton = 2;}
    else if (GetAsyncKeyState(VK_UP)) {pressButton = 3;}
    else if (GetAsyncKeyState(VK_DOWN)) {pressButton = 4;}
    else {pressButton = 0;}

    lastPressButton = pressButton;

    switch ( pressButton )
    {
        case 0:
        {
            if (dir == 1)
            {
                FoodCheck();

                k1 = getpixel(x+r+10, y+r);
                k2 = getpixel(x+r+10, y+r/2);
                k3 = getpixel(x+r+10, y);
                k4 = getpixel(x+r+10, y+r/2);
                k5 = getpixel(x+r+10, y+r);

                if ( k1 == 1 || k2 == 1 || k3 == 1 || k4 == 1 || k5 == 1 ) {dir = -1337;}
                else
                {
                    setcolor(BLACK);
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(x-24, y-24, x+24, y+24);

                    x += 10;
                    //PacMan draw
                    setcolor(YELLOW);
                    setfillstyle(SOLID_FILL, YELLOW);
                    sector(x, y, 30, 330, r, r);
                    //Eye draw
                    setcolor(BLACK);
                    setfillstyle(SOLID_FILL, BLACK);
                    fillellipse(x+5, y-15, r/8, r/8);
                }


                break;
            }
            else if (dir == 2)
            {
                FoodCheck();

                k1 = getpixel(x-r-10, y+r);
                k2 = getpixel(x-r-10, y+r/2);
                k3 = getpixel(x-r-10, y);
                k4 = getpixel(x-r-10, y+r/2);
                k5 = getpixel(x-r-10, y+r);
                if ( k1 == 1 || k2 == 1 || k3 == 1 || k4 == 1 || k5 == 1 ) {dir = -1337;}
                else
                {
                    setcolor(BLACK);
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(x-24, y-24, x+24, y+24);

                    x -= 10;
                    //PacMan draw
                    setcolor(YELLOW);
                    setfillstyle(SOLID_FILL, YELLOW);
                    sector(x, y, 210, 150, r, r);
                    //Eye draw
                    setcolor(BLACK);
                    setfillstyle(SOLID_FILL, BLACK);
                    fillellipse(x+5, y-15, r/8, r/8);
                }

                break;
            }
            else if (dir == 3)
            {
                FoodCheck();

                k1 = getpixel(x+r, y-r-10);
                k2 = getpixel(x+r/2, y-r-10);
                k3 = getpixel(x, y-r-10);
                k4 = getpixel(x-r/2, y-r-10);
                k5 = getpixel(x-r, y-r-10);
                if ( k1 == 1 || k2 == 1 || k3 == 1 || k4 == 1 || k5 == 1 ) {dir = -1337;}
                else
                {
                    setcolor(BLACK);
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(x-24, y-24, x+24, y+24);

                    y -= 10;
                    //PacMan draw
                    setcolor(YELLOW);
                    setfillstyle(SOLID_FILL, YELLOW);
                    sector(x, y, 120, 60, r, r);
                    //Eye draw
                    setcolor(BLACK);
                    setfillstyle(SOLID_FILL, BLACK);
                    fillellipse(x-15, y-5, r/8, r/8);
                }

                break;
            }
            else if (dir == 4)
            {
                FoodCheck();

                k1 = getpixel(x+r, y+r+10);
                k2 = getpixel(x+r/2, y+r+10);
                k3 = getpixel(x, y+r+10);
                k4 = getpixel(x-r/2, y+r+10);
                k5 = getpixel(x-r, y+r+10);
                if ( k1 == 1 || k2 == 1 || k3 == 1 || k4 == 1 || k5 == 1 ) {dir = -1337;}
                else
                {
                    setcolor(BLACK);
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(x-24, y-24, x+24, y+24);

                    y += 10;
                    //PacMan draw
                    setcolor(YELLOW);
                    setfillstyle(SOLID_FILL, YELLOW);
                    sector(x, y, 300, 240, r, r);
                    //Eye draw
                    setcolor(BLACK);
                    setfillstyle(SOLID_FILL, BLACK);
                    fillellipse(x+15, y-5, r/8, r/8);
                }

                break;
            }
            else if (dir == -1337)
            {
                break;
            }

            break;
        }

        case 1:
        {
            k1  = getpixel(x+r+10, y+r);
            k2  = getpixel(x+r+10, y+r/2);
            k3  = getpixel(x+r+10, y);
            k4  = getpixel(x+r+10, y-r/2);
            k5  = getpixel(x+r+10, y-r);
            if ( k1 == 1 || k2 == 1 || k3 == 1 || k4 == 1 || k5 == 1 ) {dir = -1337;}
            else
            {
                FoodCheck();

                setcolor(BLACK);
                setfillstyle(SOLID_FILL, BLACK);
                bar(x-24, y-24, x+24, y+24);

                dir = 1;
                x += 10;

                //PacMan draw
                setcolor(YELLOW);
                setfillstyle(SOLID_FILL, YELLOW);
                sector(x, y, 30, 330, r, r);
                //Eye draw
                setcolor(BLACK);
                setfillstyle(SOLID_FILL, BLACK);
                fillellipse(x+5, y-15, r/8, r/8);
            //}

            break;
        }

        case 2:
        {
            k1 = getpixel(x-r-10, y+r);
            k2 = getpixel(x-r-10, y+r/2);
            k3 = getpixel(x-r-10, y);
            k4 = getpixel(x-r-10, y-r/2);
            k5 = getpixel(x-r-10, y-r);
            if ( k1 == 1 || k2 == 1 || k3 == 1 || k4 == 1 || k5 == 1 ) {dir = -1337;}
            else
            {
                FoodCheck();

                setcolor(BLACK);
                setfillstyle(SOLID_FILL, BLACK);
                bar(x-24, y-24, x+24, y+24);

                dir = 2;
                x -= 10;

                //PacMan draw
                setcolor(YELLOW);
                setfillstyle(SOLID_FILL, YELLOW);
                sector(x, y, 210, 150, r, r);
                //Eye draw
                setcolor(BLACK);
                setfillstyle(SOLID_FILL, BLACK);
                fillellipse(x+5, y-15, r/8, r/8);
            }

            break;
        }

        case 3:
        {
            k1 = getpixel(x+r, y-r-10);
            k2 = getpixel(x+r/2, y-r-10);
            k3 = getpixel(x, y-r-10);
            k4 = getpixel(x-r/2, y-r-10);
            k5 = getpixel(x-r, y-r-10);
            if ( k1 == 1 || k2 == 1 || k3 == 1 || k4 == 1 || k5 == 1 ) {dir = -1337;}
            else
            {
                FoodCheck();

                setcolor(BLACK);
                setfillstyle(SOLID_FILL, BLACK);
                bar(x-24, y-24, x+24, y+24);

                dir = 3;
                y -= 10;

                //PacMan draw
                setcolor(YELLOW);
                setfillstyle(SOLID_FILL, YELLOW);
                sector(x, y, 120, 60, r, r);
                //Eye draw
                setcolor(BLACK);
                setfillstyle(SOLID_FILL, BLACK);
                fillellipse(x-15, y-5, r/8, r/8);
            }

            break;
        }

        case 4:
        {
            k1 = getpixel(x+r, y+r+10);
            k2 = getpixel(x+r/2, y+r+10);
            k3 = getpixel(x, y+r+10);
            k4 = getpixel(x-r/2, y+r+10);
            k5 = getpixel(x-r, y+r+10);
            if ( k1 == 1 || k2 == 1 || k3 == 1 || k4 == 1 || k5 == 1 ) {dir = -1337;}
            else
            {
                FoodCheck();

                setcolor(BLACK);
                setfillstyle(SOLID_FILL, BLACK);
                bar(x-24, y-24, x+24, y+24);

                dir = 4;
                y += 10;

                //PacMan draw
                setcolor(YELLOW);
                setfillstyle(SOLID_FILL, YELLOW);
                sector(x, y, 300, 240, r, r);
                //Eye draw
                setcolor(BLACK);
                setfillstyle(SOLID_FILL, BLACK);
                fillellipse(x+15, y-5, r/8, r/8);
            }

            break;
        }
    }

    delay(40);
}

void Congratulations()
{
    srand(time(NULL));

    int x1x = 1;
    int y1y = 1;
    int x2x = 1;
    int y2y = 1;
    int d = 1;
    int colorrr = 1;

    for ( int i = 0; i <= 10000; i++ ) {
        x1x = rand()%1280;
        y1y = rand()%1024;
        colorrr = 1 + rand()%15;
        d = rand()%2;

        if ( d == 1 ) {
            x2x = x1x - 10 + rand()%5;
            y2y = y1y + 10 - rand()%5;
        }
        else if ( d == 0 ) {
            x2x = x1x + 10 - rand()%5;
            y2y = y1y - 10 + rand()%5;
        }

        if ( x1x > 440 && x1x < 840 && x2x > 440 && x2x < 840 && y1y > 475 && y1y < 575 && y2y > 475 && y2y < 575 ) continue;

        setcolor(colorrr);
        if (y1y > y2y) {
            line( x1x , y1y , x2x , y2y );
        }
        else {
            line( x1x , y2y , x2x , y1y );
        }
        delay(1);
    }
}
