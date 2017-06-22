#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

typedef struct
{
    int x;
    int y;
    char shape;
}BODY;

char GameMap[12][70]; //[HEIGHT][WIDTHS]
const int HEIGHTS=11, WIDTHS=69;//Heights=y-1£»Widths=x-1
const int NUM_obstacle=5;
const int H_obstacle=2;
BODY guy[5];
BODY obstacle[6][3];
void PrintMap();
void CreatObstacle(int);

int main()
{
    guy[0]=(BODY){3,2,'P'};
    guy[1]=(BODY){3,1,'T'};
    guy[2]=(BODY){2,0,'/'};
    guy[3]=(BODY){4,0,'>'};
    guy[4]=(BODY){4,1,'~'};
    obstacle[0][0].x=11;
    CreatObstacle(obstacle[0][0].x);
    PrintMap();
    return 0;
}

void CreatObstacle(int x0)
{
    int i,j;
    for (i=0;i<=NUM_obstacle;i++)
    {
        if (i!=0)
        {
            if(i==1)
            {
                obstacle[i][0].x=x0+10;
            }
            else
            {
                obstacle[i][0].x=obstacle[i-1][0].x+10;
            }
        }
        for (j=0;j<=H_obstacle;j++)
        {
            obstacle[i][j].x=obstacle[i][0].x;
            obstacle[i][j].y=j;
            obstacle[i][j].shape='#';
        }
    }
}

void PrintMap()
{
    system("cls");
    int i,j,ox,oy;
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
            GameMap[obstacle[ox][oy].y][obstacle[ox][oy].x]='#';
        }
    }

     /**Insert the guy*/
    for (i=0;i<=4;i++)
    {
        GameMap[guy[i].y][guy[i].x]=guy[i].shape;
    }

    /**Print map*/
    for (i = HEIGHTS;i>=0;i--)
    {
        for (j=0;j<=WIDTHS;j++ )
        {
            printf("%c",GameMap[i][j]);
        }
        printf("\n");
    }
    for (j=0;j<=WIDTHS;j++ )
    {
         printf("-");
    }
    printf("\n");
    return;
}
