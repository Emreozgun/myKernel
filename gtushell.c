#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define EXIT "exit"


int parse(char *line, char *tokens[]);
void helpPrint();
void checkCommand(char *commandLine);
void execCommands(char *tokens[], int count, char mainPath[]);
int cdir(char *directory);
int chTokenNum(char *tokens[], int tokenCount,char *ch);
void genericFunc(char *command, char *arg[], char *startPath);
char* getPrevCommand(int prevNum,char *prevCommand[],int SumCommand);
int getPreviousNum(char *input);
void toRealloc(char *arg[], int size);
void toMalloc(char *arg[], int size, char *tokens[]);
void sig_handler(int signo);

int main (void) {
    
    char input[MAX_CANON];
    char *tokens[1024];
    int tokenCount;
    char startPath[1024];
    char prevCommand[100][1024];
    int commandCount = 0;
    int i;

    getcwd(startPath, 1024);


    while(1){
        
        fflush(stdout);

        fprintf(stdout, "%s","gtushell>>");

        if (signal(SIGINT, sig_handler) == SIG_ERR)
            printf("\ndidnt execute\n");


        if (fgets(input,MAX_CANON,stdin) == NULL)
            continue;

        if(strcmp(input,"\0") == 0 || strcmp(input,"\n") == 0)
            continue;


        checkCommand(input);

        //Gecerli gecersiz her komutu kopyaladım 
        strcpy (prevCommand[commandCount], input);

        commandCount++;

        //Gecersiz bir sayı girme durumu ve ! kontrolü
        if(input[0] == '!' && ( commandCount > getPreviousNum(input) ) ){

            tokenCount = parse(prevCommand[commandCount - getPreviousNum(input) - 1 ], tokens);

            if (tokenCount < 0) {
                fprintf(stderr, "Failed to parse command line\n");
                exit(1);
            }
            execCommands(tokens,tokenCount,startPath);
            continue;
        }

        tokenCount = parse(input,tokens);


        execCommands(tokens,tokenCount,startPath);


    }

    for(i = 0; i < commandCount; i++)
        free(prevCommand[i]);
    
    return 0;
}


void sig_handler(int signo)
{

  if (signo == SIGINT){
    printf("\n Goodbye ... \n");
    exit(0);
    //kill(getpid(), SIGKILL);
  }

}


int getPreviousNum(char *input){

    char *ptr = (char *)malloc(strlen(input));
    int i;
    for(i = 1; i < strlen(input); i++)
        ptr[i - 1] = input[i];

    ptr[i] = '\0';

    int num = atoi(ptr);
    free(ptr);

    return num;
}

void checkCommand(char *commandLine){
    
    if(commandLine[strlen(commandLine) - 1] == '\n')
        commandLine[strlen(commandLine) - 1] = '\0';

    if (strcmp(commandLine, EXIT) == 0){
            _exit(0);
    }
}

//Return token count;
int parse(char *line, char *tokens[]){

    int tokenCount = 0;
    char *temp;

    temp = strtok(line, " \t");

    while(temp != NULL){
        tokens[tokenCount] = temp;
        //fprintf(stdout, "%s\n",tokens[tokenCount]);
        tokenCount++;
        temp = strtok(NULL," \t");
    }

    return tokenCount;
}


void genericFunc(char *command, char *arg[], char startPath[]){
    
    char *allCommands[5] = {"pwd","lsf","cat","wc","bunedu"};
    int i; 
    int ret;
    char exeCommand[1024];
    /*
    for(i = 0; i < arg[i] != '\0'; i++)
        fprintf(stdout, "Arg [%d] :  %s\n", i , arg[i]);
                                                        */
    //to check command 
    for(i = 0; i < 5; i++){
        if(strcmp(allCommands[i],command) == 0){
            sprintf(exeCommand, "%s/%s",startPath,command);
        }
    }

    if((ret = execvp(exeCommand,arg)) == -1){
        fprintf(stderr, "didnt execute \"%s\" command \n",command);
        exit(EXIT_FAILURE);
    }
    
}

void execCommands(char *tokens[], int count, char mainPath[]){


    //fprintf(stdout, "First token : %s Token count: %d Main path : %s \n",tokens[0],count,mainPath );

    char *firstCommand = tokens[0];
    char *arg[4];
    int ret;
    pid_t child_pid;
    pid_t pipeID;
    int fd[2];
    int status;

    //fprintf(stdout, "Token count : %d \n",count );
    
    if(strcmp(firstCommand,"help") == 0){
        helpPrint();
        return;
    }

    if(strcmp(firstCommand,"cd") == 0){
        if((ret = cdir(tokens[1])) == -1)
            fprintf(stderr,"Failed to change current working directory to %s\n",tokens[1]);
        return;    
    }

    pipe(fd);

    child_pid = fork();

    if(child_pid == -1){
        
        fprintf(stderr, "didnt exist child with fork %d\n",errno);
        return;
    }
    else if(child_pid == 0){
        int pipeStart;
        int rdReadStart;
        int rdWriteStart;
        int countComman = count;
       
        pipeStart = chTokenNum(tokens, count,"|");
        rdReadStart = chTokenNum(tokens, count,"<");
        rdWriteStart = chTokenNum(tokens, count,">");

        if(pipeStart != 0 ){

            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
            countComman = pipeStart;
        
        }else if(rdReadStart != 0){

            fd[0] = open(tokens[rdReadStart + 1], O_RDONLY);
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);
            countComman = rdReadStart;

        }else if(rdWriteStart != 0){

            fd[1] = open(tokens[rdWriteStart + 1], O_CREAT | O_WRONLY ,0666 );
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            countComman = rdWriteStart;

        }

        toMalloc(arg,countComman,tokens);
        //fprintf(stdout, "pipe start : %d \n", countComman);
        genericFunc(firstCommand,arg,mainPath);

        toRealloc(arg,countComman);

        exit(1);
    }else {

        int pipeStart;
        if((pipeStart = chTokenNum(tokens, count,"|")) > 0){
            
            pipeID = fork();

            if(pipeID == -1){

                fprintf(stderr, "didnt exist child with fork %d\n",errno);
                return;

            }else if(pipeID == 0){

                char *arg2[4];

                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);
                close(fd[1]);

                toMalloc(arg2,(count - pipeStart - 1),&(tokens[pipeStart + 1]));
               // fprintf(stdout, "Right side of pipe : %s\n",tokens[pipeStart + 1]);
                
                firstCommand = tokens[pipeStart + 1];
                genericFunc(firstCommand,arg2,mainPath);

                toRealloc(arg2,(count - pipeStart - 1));
                exit(1);
            
            }else{

                close(fd[0]);
                close(fd[1]);
                waitpid(pipeID, &status, 0);
            
            }
        }
        waitpid(child_pid,&status,0);
    }

}


void toMalloc(char *arg[], int size, char *tokens[]){

    int i;

    for(i = 0; i < size; i++){
        //arg[i] = (char *) malloc(strlen(tokens[i]));
        //strcpy(arg[i], tokens[i]);
        arg[i] = tokens[i];
    }

    arg[i] = NULL;


}

void toRealloc(char *arg[], int size){
    int i;
   // fprintf(stdout, "start size : %d \n",size );
    for(i = 0; i < size; i++)
        free(arg[i]);
    //fprintf(stdout, "end \n" );
}

int chTokenNum(char *tokens[], int tokenCount,char *ch){
    
    int i = 0;

    while(i < tokenCount){
        if(strcmp(tokens[i],ch) == 0)
            return i;
        i++;
    }

    return 0;
}

int cdir(char *directory){

    if (chdir(directory) == -1)
        return -1;   // as error  

   return 0; // as success
}

void helpPrint()
{
    fprintf(stdout,"- lsf command : which will list file type (R for regular file, S for non-regular(special) file), access rights (int the form of rwxr-xr-x, just like actual ls), file size(bytes) and file name of all files (not directories) in the present working directory.\n");
    fprintf(stdout,"- pwd command : which will print the present working directory.\n") ;
    fprintf(stdout,"- cd command : which will change the present working directory to the location provided as argument.\n");
    fprintf(stdout,"- help command : which will print the list of supported commands.\n");
    fprintf(stdout,"- cat command : which will print on standard output the contents of the file provided to it as argument or from standard input.\n");
    fprintf(stdout,"- wc command : which will print on standard output the number of lines in the file provided to it as argument.\n");
    fprintf(stdout,"- bunedu command : Summarize disk usage of the set of FILEs, recursively for directories.\n");
    fprintf(stdout,"- exit; which will exit the shell\n");

    fflush(STDIN_FILENO); //to clear stdin
}

