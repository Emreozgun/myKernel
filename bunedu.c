#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <linux/limits.h>

int negative_z = 0;

int sizepathfun (char *path);
int depthFirstApply (char *path, int pathfun (char *path1));


int main(int argc, char ** argv_main) {

	char * path_name;
	struct stat statbuf;
    DIR *dirp;
    char command[MAX_CANON];
    char ch;
    int i = 0;

    char * argv[10];
    for (i = 0 ; i < argc ; i++)
        argv[i] = argv_main[i];
    i = 0;

    //fprintf(stdout, "Argument 1 : %s Argument 2 : %s Argument 3 : %s Argument 4 : %s\n");

    if(argc == 1){
        while( ( ch = getc(stdin)) != EOF ){
            if( ch == '\n')
                break;

            command[i] = ch;
            i++;
        }
        command[i] = '\0';
        
        argv[1] = strtok(command, " \t");
        argc++;
        if(strcmp(argv[1],"-z") == 0){
            argv[2] = strtok(NULL, " \t");
            argc++;
        }

        
    }

    else if(argc == 2 &&  (strcmp(argv[1],"-z") == 0)) {

        while( ( ch = getc(stdin)) != EOF ){
            if( ch == '\n')
                break;

            command[i] = ch;
            i++;
        }
        command[i] = '\0';

        argv[2] = command;
        argc++;
    }



    //fprintf(stdout, "Argument 2 : %s ----- %d \n", argv[2],argc );

    if(argc == 3){
	    if ( (strcmp(argv[1],"-z") != 0) && ((stat(argv[2], &statbuf)  < 0) && !(S_ISDIR(statbuf.st_mode)) ) )  {
            fprintf(stderr, "Usage: %s -[z] FILEPATH \n", argv[0]);
	        exit(1);
	    }
	}
	else if (argc == 2){
		if( ((stat(argv[1], &statbuf)  < 0) && !(S_ISDIR(statbuf.st_mode))) ) {
	    	fprintf(stderr, "Usage: %s [-z] FILEPATH \n", argv[0]);
	        exit(1);
	    }	
	}
	else if (argc > 3){
		fprintf(stderr, "More Argument to command Usage: %s [-z] FILEPATH\n", argv[0]);
	    exit(1);
	}

    /* printf("File Size: %d bytes\n",sizepathfun(argv[2])); */
    if(argc == 3){
        path_name = argv[2];
        negative_z = 1;
    }
    else
        path_name = argv[1];


    //fprintf(stdout, "Welcome to my command \n");
    depthFirstApply(path_name,sizepathfun);


    if( (dirp = opendir(path_name)) != NULL)/*Dosya açılabilmiştir.command line da verilen argümanın ismi ve toplam boyutu basılır. */ 
        printf("%s\n",path_name);

    closedir(dirp);


    return 0;

}


int depthFirstApply (char *path, int pathfun (char *path1)){

	struct dirent *direntp;
    struct stat statbuf;
    char file_path[PATH_MAX];
    DIR *dirp;
    int totalSize_Dir = 0;

    if( (dirp = opendir(path)) == NULL) /*opendir function returns a pointer to a dirent It returns NULL on reaching 
											the end of the directory stream or if an error occurred.*/
    {
        perror("Failed to open directory");
        return -1;
    }

    while (1)
    {
        if((direntp = readdir(dirp)) == NULL){
            fprintf(stdout,"%d  ",totalSize_Dir);
            break;
        }   
        
        if(strcmp(direntp->d_name,".") == 0 || strcmp(direntp->d_name,"..") == 0)
            continue;

        sprintf(file_path, "%s/%s",path, direntp->d_name);

        if (lstat(file_path, &statbuf) != 0)
            continue;

        if(S_ISDIR(statbuf.st_mode)) /* isDirectory */
        {
            if(negative_z == 1)
                totalSize_Dir += depthFirstApply(file_path, sizepathfun) + sizepathfun(file_path);
            else
                depthFirstApply(file_path, sizepathfun);
            
            fprintf(stdout,"%s\n",file_path);
        }
        else if(S_ISLNK(statbuf.st_mode) || S_ISFIFO(statbuf.st_mode) || S_ISCHR(statbuf.st_mode) ||
                                                            S_ISBLK(statbuf.st_mode) || S_ISSOCK(statbuf.st_mode)) {

            fprintf(stdout,"Special file %s\n",direntp->d_name);

        }
        else{
                int check = sizepathfun(file_path);
                if(check == -1)
                    fprintf(stdout,"Cannot read folder %s \n", file_path);
                else
                    totalSize_Dir += check;

        }

    }
    while(closedir(dirp)==-1 && (errno==EINTR));

    return totalSize_Dir;

}

int sizepathfun (char *path){

	struct stat statbuf;


	if (lstat(path, &statbuf) < 0 ) /*Hata */
		return -1;
	else if(S_ISDIR(statbuf.st_mode)) /*Directory boyutu hesaba katılmadı*/
        return 0;
    else if(S_ISREG(statbuf.st_mode))/*Regular fileların boyutunu döndürür*/
		return (int)statbuf.st_size;
    else if(S_ISLNK(statbuf.st_mode) || S_ISFIFO(statbuf.st_mode) || S_ISCHR(statbuf.st_mode) ||
                                                            S_ISBLK(statbuf.st_mode) || S_ISSOCK(statbuf.st_mode)) /*Link veya pipeların boyutu o döndürülür */
        return 0;
    return -1;

}

