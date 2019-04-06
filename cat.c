
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	int stdout_fd = fileno(stdout);
	int in_fd;
	char temp[1024];
	int ret;

	if(argc > 1)
	{
		if( (in_fd = open(argv[1], O_RDONLY)) == -1){
			fprintf(stderr, "Error to opening file : %s\n",argv[1]);
			exit(-1);
		}
	}
	else
	{
		in_fd = fileno(stdin);
	}


	while( (ret = read(in_fd, temp, 1024)) != 0)
    {  
    	write(stdout_fd, temp, ret);
    }

    if (argc == 2)
    	close(in_fd);

    return 0;

}