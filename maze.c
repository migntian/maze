#include "maze.h"

int map[MAX_ROW][MAX_COL] = {
    {0,1,0,0,0,0},
    {0,1,1,1,0,0},
    {0,1,0,1,1,1},
    {0,1,1,0,0,0},
    {0,0,1,0,0,0},
    {0,0,1,0,0,0}
};
void mazeinit(maze *maze)
{
    if(maze == NULL)
    {
        return;
    }
    size_t i = 0;
    for(;i<MAX_ROW;i++)
    {
        size_t j = 0;
        for(;j<MAX_COL;j++)
        {
            maze->map[i][j] = map[i][j];
        }
    }
    return;
}
void mazeprint(maze *maze)
{
    if(maze == NULL)
    {
        return;
    }
    size_t i = 0;
    for(;i<MAX_ROW;i++)
    {
        size_t j = 0;
        for(;j<MAX_COL;j++)
        {
            printf("%2d",maze->map[i][j]);
        }
        printf("\n");
    }
}

int canstay(maze *maze,point cur)
{
   if(cur.row < 0 ||cur.row > MAX_ROW || cur.col < 0 ||cur.col >MAX_COL) 
   {
       return 0;
   }
   if(maze->map[cur.row][cur.col] == 1)
   {
       return 1;
   }
   return 0;
}
void mark(maze *maze,point cur)
{
    maze->map[cur.row][cur.col] = 2;
    return;
}
int isexit(maze *maze,point cur,point entry)
{
    if(cur.row == entry.row &&cur.col == entry.col)
    {
        //说明检测的当前点就是入口点
        return 0;
    }
    if(cur.row == 0 || cur.row == MAX_ROW-1 || cur.col == 0 || cur.col == MAX_COL-1)
    {
        return 1;
    }
    return 0;
}
void _getpash(maze *maze,point cur,point entry)
{
    printf("cur:(%d,%d)\n",cur.row,cur.col);
    if(!canstay(maze,cur))
    {
        return;
    }
    mark(maze,cur);
    if(isexit(maze,cur,entry))
    {
        printf("找到一条出口\n");
        return;
    }
    point up = cur;
    up.row -= 1;
    _getpash(maze,up,entry);

    point right = cur;
    right.col += 1;
    _getpash(maze,right,entry);

    point down = cur;
    down.row += 1;
    _getpash(maze,down,entry);

    point left = cur;
    left.col -= 1;
    _getpash(maze,left,entry);
    
}

void getpath(maze *maze,point entry)
{
    if(maze == NULL)
    {
        return;
    }
    _getpash(maze,entry,entry);
}
///////////
//test
////////
void test_maze()
{
    maze maze;
    mazeinit(&maze);
    point entry = {0,1};
    getpath(&maze,entry);
    mazeprint(&maze);
    
}
int main()
{
    test_maze();
    return 0;
}
