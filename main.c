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

ELEMENT stack[MAX_STACK_SIZE]; int top=-1; //when empty -1
int maze[MAX_COL][MAX_ROW]; //start=[1][0] , exit=[MAX_COL][MAX_ROW-1]


/**
READ TXT FILE FOR MAZE
0 = wall 1 = path
*/
void init(int (*maze)[MAX_ROW]){
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

void push(ELEMENT e){
    if(top>=MAX_STACK_SIZE-1){
        puts("stack full");
        return -1;
    }
    stack[++top]=e; // top++ , stack[top]=e;
    puts("pushed");
}
ELEMENT* pop(){
    if(top<0){
        puts("stack empty");
        return;
    }
    return &stack[top--]; //tmp=stack[top] , top-- , return tmp
}
ELEMENT* peek(){
    if(top<0){
        puts("stack empty");
        return;
    }
    return &stack[top];
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
    int i; int sum=0;
    for(i=0;i<5;i++){sum+=dir[i];}   dir[4]=sum;
    return dir;   //////////////////////////////////////////FREEEEEEEEEEEEEEEEEEEEEEEEEEEE
}

void find_path(ELEMENT e,int count){ //count=0 when start
    //while(only one way) proceed(top++), if stuck return -1(reset stack(reset top) to 갈림길)
    //if(갈림길) recur
    //for(arr[N0,E0,W1,S1])else RECUR
    int i;
    char* dir=allocAdjacent(e);

    fputs("directions available: ",stdout);
    for(int i=0;i<5;i++)
        printf("%d  ",dir[i]);
    puts("");

    if(dir[4]>1) //at junction always reset count
        count=0;

    if(dir[4]>=1){ //while one way proceed
        push(e); ELEMENT e1;
        for(i=0;i<4;i++){
            if(dir[i]==1){ //which root available
                switch(i){
                    case N: //0
                        e1.col=e.col-1; e1.row=e.row; e1.from=S;
                        break;
                    case E: //1
                        e1.col=e.col; e1.row=e.row+1; e1.from=W;
                        break;
                    case W: //2
                        e1.col=e.col; e1.row=e.row-1; e1.from=E;
                        break;
                    case S: //3
                        e1.col=e.col+1; e1.row=e.row; e1.from=N;
                        break;
                }
                puts("----------------------------------------");
                printf("WAS AT: e[%d][%d],from=%d \n",e.col,e.row,e.from);
                printf("NOW AT: e1[%d][%d],from=%d \n",e1.col,e1.row,e1.from);
                find_path(e1,++count);
            }
        }
        free(dir);
    }else{//when dir[4]==0
        for(i=0;i<count;i++)
            pop();
        return;
    }
}

void print_Answer(){
    int ans[MAX_COL][MAX_ROW];
    int i,j;
    for(i=0;i<MAX_COL;i++){
        for(j=0;j<MAX_ROW;j++){
            ans[i][j]=' ';
        }
    }
    for(i=0;i<=top;i++){
        ans[stack[i].col][stack[i].row]='O';
    }
    for(i=0;i<MAX_COL;i++){
        for(j=0;j<MAX_ROW;j++){
            printf("%3d",ans[i][j]);
        }printf("\n");
    }
}

int main()
{
    init(maze);
    printMaze();
    ELEMENT e={.row=1,.col=1,.from=W}; //start position
    //printf("west = %d\n",e.from);
    find_path(e,0);
    //print_Answer();
    return 0;
}
