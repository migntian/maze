#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define MAX_ROW 6
#define MAX_COL 6

typedef struct maze{
    int map[MAX_ROW][MAX_COL];
}maze;
typedef struct point{
    int row;
    int col;
}point;
typedef point seqstacktype;
typedef struct seqstack{
    seqstacktype *data;
    size_t size;
    size_t capacity;
}seqstack;
