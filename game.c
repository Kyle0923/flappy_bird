# Take-aways#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <math.h>

typedef struct
{
    int x;
    int y;
    char shape;
}BODY;

char GameMap[12][80]; //[HEIGHT][WIDTHS]
const int HEIGHTS=11, WIDTHS=79;//Heights=y-1,Widths=x-1
const int NUM_obstacle=8;
const int H_obstacle=11;
const int MAX_gap=15;
const int MAX_delay=500;
int gap;
const char ObsShape='|';
BODY obstacle[9][12];
BODY guy;
void PrintMap();
void InitializeObstacle(int);
void MoveObstacle();
int CheckObs();
int score;
int life;
int cycle;
int godmode=0;

int main()
{
    int delay=500;
    float kbctr=1;
    char EOG;
    int temp;
BEGIN:
    cycle=100;
    score=0;
    gap=MAX_gap;
    life=5;
    guy=(BODY){3,6,'%'};
    obstacle[0][0].x=11;
    InitializeObstacle(obstacle[0][0].x);
    PrintMap();
    printf("Press any key to start...");
    getch();
    while(1)
    {
        if (kbhit())
        {
            while(kbhit())
            {
                if (getch()=='g'){godmode=!godmode;};
                guy.y++;
                if (guy.y>HEIGHTS)
                    guy.y=HEIGHTS;
                PrintMap;
            }
            kbctr=0.7;
        }
        else
        {
            kbctr+=0.3;
            guy.y-=floor(kbctr);
            PrintMap;
            if (guy.y<0)
                guy.y=0;
            if (kbctr>=2){kbctr=2;}
        }
        MoveObstacle();
        temp=CheckObs();
        if (MAX_delay-3*cycle>=100)
            {delay=MAX_delay-3*cycle;}
        else
            {delay=100;}
        if (godmode)
        {delay=50;}
        life-=temp;
        PrintMap();
        if (life <=0 && !godmode)break;

        _sleep(delay);
        gap=MAX_gap-cycle/100;
        if (gap<9){gap=9;}
        //if (gap<10){gap=10;}
        cycle++;
    }
    printf("You LOST!\nPress r to restart...\nPress Esc to exit...");
    //EOG=getch();
    while((EOG=getch())!=27)
    {
        if (EOG=='r'){goto BEGIN;};//hit esc to exit
        //EOG=getch();
    }
    return 0;
}

int CheckObs()
{
    int i,j;
    for (i=0;i<=NUM_obstacle;i++)
    {
        for (j=0;j<=H_obstacle;j++)
        {
            if (obstacle[i][j].x==guy.x && obstacle[i][j].y==guy.y)
                if  (obstacle[i][j].shape==ObsShape)
                {
                    return 1;
                }
                else
                {
                    score++;
                    if (score%30==0){life++;}
                }


        }
    }
    return 0;
}

void MoveObstacle()
{
    int i,j,temp;
    static int outsider=-1;
    srand((unsigned)time(0));
    for (i=0;i<=NUM_obstacle;i++)
    {
        for (j=0;j<=H_obstacle;j++)
        {
            obstacle[i][j].x=obstacle[i][j].x-1;
        }
        if (obstacle[i][0].x<0)
            {outsider=i;}
    }
    if (outsider!=-1)
    {
        obstacle[outsider][0].x=obstacle[(outsider+NUM_obstacle)%(NUM_obstacle+1)][0].x+gap+rand()%4;
        temp=rand()%(H_obstacle-1);
        for (j=0;j<=H_obstacle;j++)
        {
            obstacle[outsider][j].x=obstacle[outsider][0].x;
            if (j>=temp&&j<=temp+3)
                obstacle[outsider][j].shape=' ';
            else
                obstacle[outsider][j].shape=ObsShape;
        }
    }
    outsider=-1;
}

void InitializeObstacle(int x0)
{
    int i,j,temp;
    srand((unsigned)time(NULL));
    for (i=0;i<=NUM_obstacle;i++)
    {
        if (i==0)
            obstacle[i][0].x=x0;
        else
            obstacle[i][0].x=obstacle[i-1][0].x+gap;
        temp=rand()%(H_obstacle-1);
        for (j=0;j<=H_obstacle;j++)
        {
            obstacle[i][j].x=obstacle[i][0].x;
            obstacle[i][j].y=j;
            obstacle[i][j].shape=ObsShape;
            if (j>=temp&&j<=temp+3)
                obstacle[i][j].shape=' ';
            else
                obstacle[i][j].shape=ObsShape;
        }
    }
    return;
}

void PrintMap()
{
    system("cls");
    /**print upper border*/
    int i,j,ox,oy;
        for (j=0;j<=WIDTHS;j++ )
    {
         printf("-");
    }
    printf("\n");

    /**Reset the GameMap array*/
    for (i = HEIGHTS;i>=0;i--)
    {
        for (j=0;j<=WIDTHS;j++ )
        {
            GameMap[i][j]=' ';
        }
    }

    /***Insert the obstacles*/
    for(ox=0;ox<=NUM_obstacle;ox++)
    {
        for(oy=0;oy<=H_obstacle;oy++)
        {
            if(obstacle[ox][oy].x<=WIDTHS)
            {GameMap[obstacle[ox][oy].y][obstacle[ox][oy].x]=obstacle[ox][oy].shape;}
        }
    }

     /**Insert the guy*/
    GameMap[guy.y][guy.x]=guy.shape;

    /**Print map*/
    for (i = HEIGHTS;i>=0;i--)
    {
        for (j=0;j<=WIDTHS;j++)
        {
            printf("%c",GameMap[i][j]);
        }
        printf("\n");
    }
    /**print lower border*/
    for (j=0;j<=WIDTHS;j++ )
    {
         printf("-");
    }
    printf("\n");
    printf(">>Life: %d\n",life);
    /*for (i=0;i<life;i++)
        printf("%%");*/
    printf(">>Your Score is %d\n",score);
    if (godmode==1){printf("==GodMode is on==\n");}
    /*
    for (i=0;i<=NUM_obstacle;i++)
    printf("obs(%d).x=%d\n",i,obstacle[i][0].x);
    printf("guy.y=%d",guy.y);
    */
    return;
}
