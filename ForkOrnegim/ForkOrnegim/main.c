#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void process_leaf(){
    srand(getpid());
    int r = rand()%100;
    char filename[20];
    sprintf(filename,"%d.txt",getpid());
    
    fflush(stdout);
    //printf("%s",filename);
    FILE *fp = fopen(filename,"w");
    fprintf(fp,"%d",r);
    fclose(fp);
}

int read_file(int pid){ // read file content as integer with given pid
    wait(NULL);
    char filename[20];
    int r;
    sprintf(filename,"%d.txt",pid);
    FILE *fp = fopen(filename,"r");
    fscanf(fp,"%d",&r);
    fclose(fp);
    return r;
}

int parent_process(int pidleft,int pidright){
    int lvalue = read_file(pidleft);
    int rvalue = read_file(pidright);
    char filename[20];
    sprintf(filename,"%d.txt",getpid());
    //printf("%s",filename);
    FILE *fp = fopen(filename,"w");
    fprintf(fp,"%d",(lvalue+rvalue));
    
    fclose(fp);
    return rvalue+lvalue;
}

void tree(int height){
    if(height<=0) {process_leaf(); return;}
    int pid= fork(); // new process
    if(pid>0){ // parent
        int pid2=fork();
        if(pid2>0){//parent
            printf(" parent: %d , lchild:%d,rchild:%d, height:%d\n",getpid(),pid,pid2,height);
            wait(NULL); // after this point all childeren is finished
            //read file sum them up
            int result = parent_process(pid,pid2);
            if(height==3)
                printf(" RESULT : %d\n",result);
        }
        if(pid2==0){ //right child
            //right
            // create a file write random number in it
            tree(--height);
        }
    }
    if(pid==0){
        //left
        // create a file write random number in it
        tree(--height);
    }
    
    
    
    
}
int main(){
    tree(3);
}
