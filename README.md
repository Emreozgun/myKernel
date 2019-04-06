# MyKernel
It is my shell that named gtushell.You can run it with Makefile on terminal.
Commands to run : make all && ./gtushell
My shell support the following commands:
- lsf; which will list file type (R for regular file, S for non-regular(special) file), access rights (int the
form of rwxr-xr-x, just like actual ls), file size(bytes) and file name of all files (not directories) in
the present working directory. It doesn’t take any argument. Does not list any directory.
- pwd; which will print the path of present working directory.
- cd; which will change the present working directory to the location provided as argument.
- help; which will print the list of supported commands.
- cat; which will print on standard output the contents of the file provided to it as argument or from
standard input. The file can be on any directory on the system. (example, cat file.txt )(example2,
pwd | cat )
- wc; which will print on standard output the number of lines in the file provided to it as argument
or the string coming from standard input until EOF character (example, Input: wc file.txt Output:55)
(example2, Input: lsf | wc Output: 5 (there are 5 files in current directory so output of lsf has 5
lines)).
- bunedu; your HW#1. This time, the file path argument of bunedu can also come from standard
input.
- exit; which will exit the shell
- When the user types !n , the n-th previous command will run.
- Each command supports have a single pipe "|" or a single redirection operator > <.
- You can use Ctr-C to exit from gtushell
