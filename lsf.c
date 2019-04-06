#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <linux/limits.h>

int main(int argc, char **argv){
    
   char currentDir[1024];
   struct dirent *direntp;
   struct stat statbuf;
   DIR *dirp;
   char file_path[PATH_MAX];
   int ret = 0;

   //fprintf(stdout, "Welcome to my command \n");

   if(argc > 1){
        fprintf(stderr, "lsf command doesnt take any argument.\n");
        return -1;
   }

   if (getcwd(currentDir, sizeof(currentDir)) == NULL){
   		fprintf(stdout, "Dont have list to that %s directory.\n",currentDir);
    }


    if( (dirp = opendir(currentDir)) == NULL) 
    {
        perror("Failed to open directory");
        return -1;
    }

   // fprintf(stdout, "\n");

    while (1)
    {
        if((direntp = readdir(dirp)) == NULL){
            break;
        }   
        
        if(strcmp(direntp->d_name,".") == 0 || strcmp(direntp->d_name,"..") == 0)
            continue;


        sprintf(file_path, "%s/%s",currentDir, direntp->d_name);

        if((ret = lstat(file_path, &statbuf)) == -1)
        	fprintf(stderr, "Return value lstat: %d to %s\n",ret,file_path);


            fprintf(stdout,(statbuf.st_mode & S_IRUSR) ? "r" : "-");
            fprintf(stdout,(statbuf.st_mode & S_IWUSR) ? "w" : "-");
    		fprintf(stdout,(statbuf.st_mode & S_IXUSR) ? "x" : "-");

    		fprintf(stdout,(statbuf.st_mode & S_IRGRP) ? "r" : "-");
    		fprintf(stdout,(statbuf.st_mode & S_IWGRP) ? "w" : "-");
    		fprintf(stdout,(statbuf.st_mode & S_IXGRP) ? "x" : "-");
    		
    		fprintf(stdout,(statbuf.st_mode & S_IROTH) ? "r" : "-");
    		fprintf(stdout,(statbuf.st_mode & S_IWOTH) ? "w" : "-");
    		fprintf(stdout,(statbuf.st_mode & S_IXOTH) ? "x" : "-");
    		fprintf(stdout,"\t");


        if(S_ISLNK(statbuf.st_mode) || S_ISFIFO(statbuf.st_mode) || S_ISCHR(statbuf.st_mode) ||
                                                            S_ISBLK(statbuf.st_mode) || S_ISSOCK(statbuf.st_mode)) {

            fprintf(stdout,"%s\t%10d\t%s\n","S",(int)statbuf.st_size,direntp->d_name);
        }
        else{
        	fprintf(stdout,"%s\t%10d\t%s\n","R",(int)statbuf.st_size,direntp->d_name);
        }

    }
    
    while(closedir(dirp)==-1 && (errno==EINTR));

    return 0;
}