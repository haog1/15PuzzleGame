

/* get possible directions that 0 can move */
int action(int S[][SIZE], int A[], int prevD){
    int i, j, result = 0, row = 0, col = 0;
    
    for(i = 0; i< SIZE; i++){
        for(j = 0; j < SIZE; j++){
            if(S[i][j] == 0){
                row = i;
                col = j;
                break;
            }
        }
    }
    // if 0 is not at top
    if(row != 0 && -1 * prevD != U){
        A[result++] = U;
    }
    // 0 is not at bottom
    if(row != 3 && -1 * prevD != D){
        A[result++] = D;
    }
    // 0 is not at left
    if(col != 0 && -1 * prevD != L){
        A[result++] = L;
    }
    // 0 is not at right
    if(col != 3 && -1 * prevD != R){
        A[result++] = R;
    }
    return result;
}


/* get Signle Distance */
int getDist(int dot, int i, int j){
    int x = dot/SIZE;
    int y = dot % SIZE;
    return abs(x-i) + abs(y-j);
}


/* This function gets every number from 2d array and find the position it
 * should go. Finally, it returns the Manhattan Value
 */
int ManhattanDistance(int S[][SIZE]){
    int i, j, heuristic = 0;
    int x, y;
    
    for(i = 0; i<SIZE; i++)
        for(j = 0; j< SIZE;j++)
            if(S[i][j] != 0){
                x = S[i][j] / SIZE;    // row index
                y = S[i][j] % SIZE;    // col index
                heuristic += abs(x - i) + abs(y - j);
            }
    
    
    return heuristic;
    
}


/* swap data */
void swapData(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}
