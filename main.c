#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 81
#define MAX_ROW 10
#define MAX_COL 10
#define MAX_BUF_SIZE 50 //max buffer size for reading file

typedef enum {
    FALSE,
    TRUE
}BOOLEAN;

typedef struct {
    int row;
    int col;
    BOOLEAN rtnPT;
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

int main()
{
    init(maze);
    printMaze();
    return 0;
}
