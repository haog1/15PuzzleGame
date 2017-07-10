#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SIZE        4
#define COST        1

#define U           1
#define D           -1
#define L           2
#define R           -2

#define INFINIT     100000 // just assume it's infinit
#define MAX         50
#define NEW         3
#define OMEGA       1.5



typedef struct node node_t;

struct node{
    int state[SIZE][SIZE];
    int gn;
    double Fn;
    double hn;
};

int readInput(char *input, int S[][SIZE]);
void processIDA(int S[][SIZE]);
int IDAS(node_t *node, double threshold, double *threshold1, int prevD,
         long int *gen, long int *exp);
int action(int S[][SIZE], int A[], int prevD);
node_t f(int act, node_t *node);
int getDist(int dot, int i, int j);
int ManhattanDistance(int S[][SIZE]);
void swapData(int *x, int *y);