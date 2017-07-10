#include "ida.h"
#include "ida.c"

/* process information here */
void processIDA(int S[][SIZE]){
    int r = 0, start = clock(), end = 0, counter = 1, record[MAX], i, j;
    long int generated = 0, expanded = 0;
    double time = 0, threshold = (double)ManhattanDistance(S), // initialize B
    threshold1;
    node_t node;
    
    record[0] = ceil(threshold);
    
    printf("Initial State:\n");
    for(i = 0; i < SIZE; i++){
        for(j = 0;j < SIZE; j++){
            node.state[i][j] = S[i][j];    // copy matrix
            printf("%d ", node.state[i][j]);
        }
        printf("\n");
    }
    printf("Initial Estimate = %d\n", record[0]);
    
    /* the control loop */
    while(1){
        threshold1 = INFINIT;   // initial B'
        node.gn = 0;   // set the initial gn = 0
        node.hn = (double)ManhattanDistance(S);
        node.Fn = node.gn + node.hn;
        r = IDAS(&node, threshold, &threshold1, NEW, &generated, &expanded);
        if(r == 0){
            threshold = threshold1;
            record[counter] = ceil(threshold);
            counter += 1;
        }else{
            break;
        }
    }
    /* control loop ends */
    
    end = clock();
    time = (end-start)/CLOCKS_PER_SEC;
    printf("Threshold = ");
    for(i = 0; i < counter; i++){
        printf("%d ", record[i]);
    }
    printf("\nSolution = %d\n", record[counter-1]);
    printf("Generated = %ld\nExpanded = %ld\n", generated, expanded);
    printf("Time = %.02lf\n", time);
    printf("Expanded/Second = ");
    if(time){
        printf("%ld\n", (long int)(expanded /time));
    }else{
        printf("%ld\n", expanded);
    }
}



/* this function recursively find a result and return it */
int IDAS(node_t *node, double threshold, double *threshold1,
         int prevD, long int *gen, long int *exp){
    int r = 0, i, possibleAction = 0, act[SIZE] = {0};
    node_t nextNode;
    
    *exp += 1;
    
    //printf("exp = %d\n", *exp);
    
    /* get possible directions */
    possibleAction = action(node->state, act, prevD);
    for(i = 0; i < possibleAction; i++){
        
        /* get next possible node according to the current diretion
         * that 0 can move and set up all variables
         * also, track the generated number inside f
         */
        
        nextNode = f(act[i], node);
        *gen += 1;
        prevD = act[i];
        // check threshold
        if((double)nextNode.gn + nextNode.hn > threshold){
            
            // replace it with the min betwee B' and F(n) of nextNode
            if(threshold1 >= &nextNode.Fn){
                *threshold1 = nextNode.Fn;
            }
        }else{
            
            // end function when get to last point
            if( nextNode.hn <= 0){
                return 1;
            }
            // recursion and increment expanded
            r = IDAS(&nextNode, threshold, threshold1, prevD, gen, exp);
            
            if(r != 0){
                return r;
            }
        }
    }
    return 0;
}

/* This function swaps data position according to given direction */
node_t f(int act, node_t *node){
    int i, j, row = 0, col = 0, oldDist = 0, newDist = 0;
    node_t nextNode;
    
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            // copy node
            nextNode.state[i][j] = node->state[i][j];
            // get 0 position
            if(nextNode.state[i][j] == 0){
                row = i;
                col = j;
            }
        }
    }
    /* swap positions and
     * assign new F(n) of node to  nextNode
     */
    if(act == L && col - 1 >= 0){
        oldDist = getDist(nextNode.state[row][col-1], row, col-1);
        swapData(&nextNode.state[row][col], &nextNode.state[row][col - 1]);
    }else if(act == R && col + 1 < SIZE){
        oldDist = getDist(nextNode.state[row][col+1], row, col+1);
        swapData(&nextNode.state[row][col], &nextNode.state[row][col + 1]);
    }else if(act == U && row-1 >= 0){
        oldDist = getDist(nextNode.state[row-1][col], row - 1, col);
        swapData(&nextNode.state[row][col], &nextNode.state[row - 1][col]);
    }else if(act == D && row + 1 <SIZE){
        oldDist = getDist(nextNode.state[row+1][col], row + 1, col);
        swapData(&nextNode.state[row][col], &nextNode.state[row + 1][col]);
    }
    
    newDist = getDist(nextNode.state[row][col], row, col);
    
    nextNode.gn = node->gn + COST;
    if(newDist < oldDist){
        nextNode.hn = node->hn - COST;
    }else{
        nextNode.hn = node->hn + COST;
    }
    nextNode.Fn = nextNode.gn + OMEGA * nextNode.hn;
    return nextNode;
}

