#include <stdio.h>
#include <string.h>

typedef struct
{
    int x;
    int y;
    int z;
} pos;

// Precomputed: min: 0, max: 19;
#define MAXN 25

struct queue
{
    pos items[MAXN * MAXN * MAXN];
    int front;
    int rear;
};

#define init(s) ((s).front = 0; (s).rear = 0)
#define isempty(s) ((s).front == (s).rear)
#define any(s) ((s).front != (s).rear)
#define push(s, x) ((s).items[((s).rear++)] = (x))
#define pop(s) ((s).items[(s).front++])
#define siz(s) ((s).rear - (s).front)

int loadInputFile();
int nextLine(char *dst);

char line[200];

int space[MAXN][MAXN][MAXN];

enum
{
    EMPTY,
    DROP,
    STEAM
};



struct queue q;
int main()
{
    if (loadInputFile() < 0)
    {
        fprintf(stderr, "Can't open: input.txt\n");
        return 1;
    }

    int x, y, z;
    while (nextLine(line))
    {
        if (sscanf(line, "%d,%d,%d", &x, &y, &z) != 3)
            break;
        space[x+1][y+1][z+1] = DROP; //Displacement (1, 1, 1) to avoid zero coordinates
    }

    pos p = {0, 0, 0}; // EMPTY but needs checking
    int sidesCovered = 0;

    push(q, p);
    while (any(q)) // BFS
    {
        p = pop(q);
        p.x--;
        if (p.x >= 0)
        {
            if (space[p.x][p.y][p.z] == DROP)
            {
                sidesCovered++;
            }
            else if (space[p.x][p.y][p.z] == EMPTY)
            {
                space[p.x][p.y][p.z] = STEAM;
                push(q, p);
            }
        }
        p.x += 2;
        if (p.x < MAXN)
        {
            if (space[p.x][p.y][p.z] == DROP)
            {
                sidesCovered++;
            }
            else if (space[p.x][p.y][p.z] == EMPTY)
            {
                space[p.x][p.y][p.z] = STEAM;
                push(q, p);
            }
        }
        p.x--;

        p.y--;
        if (p.y >= 0)
        {
            if (space[p.x][p.y][p.z] == DROP)
            {
                sidesCovered++;
            }
            else if (space[p.x][p.y][p.z] == EMPTY)
            {
                space[p.x][p.y][p.z] = STEAM;
                push(q, p);
            }
        }
        p.y += 2;
        if (p.y < MAXN)
        {
            if (space[p.x][p.y][p.z] == DROP)
            {
                sidesCovered++;
            }
            else if (space[p.x][p.y][p.z] == EMPTY)
            {
                space[p.x][p.y][p.z] = STEAM;
                push(q, p);
            }
        }
        p.y--;


        p.z--;
        if (p.z >= 0)
        {
            if (space[p.x][p.y][p.z] == DROP)
            {
                sidesCovered++;
            }
            else if (space[p.x][p.y][p.z] == EMPTY)
            {
                space[p.x][p.y][p.z] = STEAM;
                push(q, p);
            }
        }
        p.z += 2;
        if (p.z < MAXN)
        {
            if (space[p.x][p.y][p.z] == DROP)
            {
                sidesCovered++;
            }
            else if (space[p.x][p.y][p.z] == EMPTY)
            {
                space[p.x][p.y][p.z] = STEAM;
                push(q, p);
            }
        }
        p.z--;
    }

    printf("%d\n", sidesCovered);
}

#define BUFSIZE 35000

char fileBuf[BUFSIZE];
char *pbuf = fileBuf;
char *pbufend = fileBuf;

int loadInputFile()
{
    FILE *pf = fopen("input.txt", "r");
    if (!pf)
        return -1;
    pbuf = fileBuf;
    pbufend = fileBuf + fread(fileBuf, 1, BUFSIZE, pf);
    fclose(pf);

    return 0;
}

int nextLine(char *dst)
{
    char c;
    char *orig = dst;

    // read line:
    while (pbuf < pbufend && (c = *(pbuf++)) != '\n')
    {
        *(dst++) = c;
    }
    *dst = '\0';
    // return line length
    return dst - orig;
}