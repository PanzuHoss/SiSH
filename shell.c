#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>

#define bufsize 1024
#define RESET "\e[0m"

char *read_line();
int execute(char **args);
char **split_line(char *line);
void loop();

int s_exit(){
    return 0;
}

int main(){
    loop();
    return 0;
}

void loop(){
    char *line;
    char **args;
    int run;
    do{
        printf("> ");
        line = read_line();
        args = split_line(line);
        run = execute(args);
        free(line);
        free(args);
    }while(run);
}

char *read_line(){
    size_t bufs=0;
    char *buf=NULL;
    size_t c=getline(&buf,&bufs,stdin);
    
    //check EOF
    if(c==-1){
        if(feof(stdin)){
            free(buf);
            exit(EXIT_SUCCESS);
        }
        else{
            perror("error in read_line!\n");
            free(buf);
            exit(EXIT_FAILURE);
        }
    }
    return buf;
}

char **split_line(char *line){
    size_t bufs=bufsize;
    int position = 0;
    char **tokens = malloc(sizeof(char*) * bufs);
    char *token;
    if(!tokens){
        perror("Error in token memory allocation. @'line 64'!\n");
        exit(EXIT_FAILURE);
    }
    
    token=strtok(line," \t\r\n");
    while(token!=NULL){
        tokens[position]=token;
        position++;
        if(position>=bufs){
            bufs+=bufsize;
            tokens=realloc(tokens,bufs*sizeof(char*));
            if(!tokens){
                perror("Error in memory reallocation. @ 'line 75'!");
                exit(EXIT_FAILURE);
            }
        }
        token=strtok(NULL," \t\r\n");
    }
    tokens[position]=NULL;
    return tokens;
}

int execute(char **args){
    pid_t cpid;
    int run;

    if(args[0]==NULL) return 1;
    
    if(strcmp(args[0],"cd")==0){
        char *path = args[1];
        
        if (path == NULL) {
            path = getenv("HOME");
        }
        
        if(path == NULL){
            fprintf(stderr, "cd: No directory specified and HOME not set\n");
        } 
        
        else{
            if(chdir(path) != 0){
                perror("cd");
            }
        }
        return 1;
    }
    
    if(strcmp(args[0],"exit")==0) return s_exit();    
    cpid=fork();  
    
    if(cpid==0){
        if(execvp(args[0],args)<0){
            printf("Command : %s not found\n",args[0]);
            exit(EXIT_FAILURE);
        }
    }

    else if(cpid<0){
        fprintf(stderr,"error forking!\n");
        exit(EXIT_FAILURE);
    }
    
    else{
        waitpid(cpid,&run,WUNTRACED);
    }
    return 1;
}
