#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 81
#define MAX_ROW 10
#define MAX_COL 10
#define MAX_BUF_SIZE 50 //max buffer size for reading file

typedef enum {
    N,
    E,
    W,
    S
}NEWS;

typedef struct {
    int row; //coordinate
    int col;
    NEWS from; //adjacent directions can be N,E,W,S
}ELEMENT;

ELEMENT stack[MAX_STACK_SIZE];
char maze[MAX_COL][MAX_ROW]; //start=[1][0] , exit=[MAX_COL][MAX_ROW-1]


/**
READ TXT FILE FOR MAZE
0 = wall 1 = path
*/
void init(char (*maze)[MAX_ROW]){
    FILE* fp=fopen("maze.txt","rt");
    if(fp==NULL){
        puts("an error occurred while trying to create a stream");
        return -1;
    }

    int col=0; char buff[MAX_BUF_SIZE];
    while(fgets(buff,MAX_BUF_SIZE,fp)!=NULL){
             //printf("%s",buff);
        int i;   *(*(maze+col))=atoi(strtok(buff," "));
        for(i=1;i<MAX_ROW;i++){
            *(*(maze+col)+i)=atoi(strtok(NULL," "));
        }
        col++;
    }
    fclose(fp);
}

void printMaze(){
    int i,j;
    for(i=0;i<MAX_COL;i++){
        for(j=0;j<MAX_ROW;j++){
            printf("%3d",maze[i][j]);
        }printf("\n");
    }
}

void adjacent(NEWS news,ELEMENT e,char* arr){
    int i,j,index=0;
    for(i=-1;i<=1;i++){
        for(j=-1;j<=1;j++){
            if(abs(i)^abs(j)){ //xor, exclude diagonal adjacents
                *(arr+index)=(maze[e.col+i][e.row+j]==1) ? 1 : 0;
                index++;
            }
        }
    }  // arr=[N,W,E,S]
    char tmp=arr[2]; //swap
    *(arr+2)=arr[1];
    *(arr+1)=tmp; // now arr=[N,E,W,S]
    for(i=0;i<4;i++){ //for each direction NEWS
        if(news==i) //exclude direction element came from
            *(arr+i)=0;
    }
}
char* allocAdjacent(ELEMENT e){ //return an array showing adjacents (1/0)
    char* dir=(char*)malloc(5); //4+1(sum)
    switch(e.from){
        case N: //0
            adjacent(N,e,dir);
            break;
        case E: //1
            adjacent(E,e,dir);
            break;
        case W: //2
            adjacent(W,e,dir);
            break;
        case S: //3
            adjacent(S,e,dir);
            break;
    }
    int i; char sum;
    for(i=0;i<5;i++){sum+=dir[i];}   dir[4]=sum;
    return dir;   //////////////////////////////////////////FREEEEEEEEEEEEEEEEEEEEEEEEEEEE
}

void find_path(ELEMENT e){ //recursive?
    //while(only one way) proceed(top++), if stuck return -1(reset stack(reset top) to 갈림길)
    //if(갈림길) recur
    //for(arr[N0,E0,W1,S1])else RECUR


}

int main()
{
    init(maze);
    printMaze();
    ELEMENT e={.row=1,.col=3,.from=N};
    char* dir=allocAdjacent(e);
    for(int i;i<5;i++)
        printf("%d  ",dir[i]);
    return 0;
}
