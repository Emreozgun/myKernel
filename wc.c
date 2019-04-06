#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> 
#include <string.h>
#include <unistd.h> 

int main(int argc, char **argv)
{
	
	int line_Count = 0;
	char ch;
	char *fileName;
	FILE *fd;
	//fprintf(stdout, "Welcome to my command \n");

	//fprintf(stdout, "Argumant 1 : %s Argumant 2 : %s Argumant count : %d \n",argv[0], argv[1], argc);

	if(argc == 2)
		fileName = argv[1];

	if(argc == 1){

			while((ch = getc(stdin) ) != EOF){

				if(ch == '\n')
					line_Count++;
			
			}				
	}else if(argc == 2){

		struct stat st;

		lstat(fileName, &st);

		if(!S_ISREG(st.st_mode)){
			fprintf(stdout, "It is not regular file %s\n",fileName);
			return -1;
		}

		if( (fd = fopen(fileName,"r")) == NULL)
			fprintf(stderr, "Error to opening file : %s\n",fileName);
		
		while((ch = getc(fd))!=EOF){
			if(ch =='\n')
				line_Count++;
		}

		fclose(fd);
	}else{
		
		fprintf(stderr,"wc: Not available to this\n");
	
	}


	fprintf(stdout, "%d\n",line_Count );


	//fflush(STDIN_FILENO);//to clear stdin	
	

	return 0;
}