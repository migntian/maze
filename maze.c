#include "maze.h"
#include "seqstack.h"
#include "seqstack.c"

int map[MAX_ROW][MAX_COL] = {
    {0,1,0,0,0,0},
    {0,1,1,1,0,0},
    {0,1,0,1,1,1},
    {1,1,1,0,0,0},
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
void seqstackprint(seqstack *s,const char *msg)
{
    printf("%s\n",msg);
    if(s == NULL)
    {
        return;
    }
    size_t i = 0;
    for(;i < s->size;i++)
    {
        printf("(%d,%d)\n",s->data[i].row,s->data[i].col);
    }
    printf("\n");
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
    if(maze == 0)
    {
        return 0;
    }
   if(cur.row < 0 ||cur.row >= MAX_ROW || cur.col < 0 ||cur.col >= MAX_COL) 
   {
       return 0;
   }
   int value = maze->map[cur.row][cur.col];
   if(value == 1)
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
void seqstackclone(seqstack *from,seqstack *to)
{
    seqstack_destroy(to);
    to->size = from->size;
    to->capacity = from->capacity;
    to->data = (seqstacktype *)malloc(to->capacity *sizeof(seqstacktype));
    size_t i = 0;
    for(;i<from->size;i++)
    {
        to->data[i] = from->data[i];
    }
}
void _getpash(maze *maze,point cur,point entry,seqstack *cur_pash,seqstack *short_pash)
{
    printf("cur:(%d,%d)\n",cur.row,cur.col);
    if(!canstay(maze,cur))
    {
        return;
    }
    mark(maze,cur);
    seqstack_pushback(cur_pash,cur);
    if(isexit(maze,cur,entry))
    {
        printf("找到一条出口\n");
        if(cur_pash->size < short_pash->size || short_pash->size == 0)
        {
            seqstackclone(cur_pash,short_pash);
            printf("找到一条更短的路\n");
        }
        seqstack_popback(cur_pash);
        return;
    }
    point up = cur;
    up.row -= 1;
    _getpash(maze,up,entry,cur_pash,short_pash);

    point right = cur;
    right.col += 1;
    _getpash(maze,right,entry,cur_pash,short_pash);

    point down = cur;
    down.row += 1;
    _getpash(maze,down,entry,cur_pash,short_pash);

    point left = cur;
    left.col -= 1;
    _getpash(maze,left,entry,cur_pash,short_pash);
    
}

void getpath(maze *maze,point entry)
{
    if(maze == NULL)
    {
        return;
    }
    seqstack cur_pash;
    seqstack short_pash;
    seqstack_init(&cur_pash);
    seqstack_init(&short_pash);
    _getpash(maze,entry,entry,&cur_pash,&short_pash);
    seqstackprint(&short_pash,"最短路径是");
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
