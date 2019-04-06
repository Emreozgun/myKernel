#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <linux/limits.h>

int main(int argc, char **argv){

   char currentDir[1024];
   
   //fprintf(stdout, "Welcome to my command \n");

   if (getcwd(currentDir, sizeof(currentDir)) == NULL){
   		fprintf(stdout, "Dont have list to that %s directory.\n",currentDir);
   }else{
   		fprintf(stdout, "%s\n",currentDir);
   }
	
	return 0;
}
