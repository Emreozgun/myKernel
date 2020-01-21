
# MyShell

> It is my shell that named gtushell.You can run it with Makefile on terminal.Shell supports some basic commands in linux shell.You can find these commands - [Features](#features) . 

> This project is an application that runs through the console.

![Badges](https://img.shields.io/badge/linux-shell-green) 
![Badges](https://img.shields.io/badge/shell-commands-lightgrey)
![Badges](https://img.shields.io/badge/love-coding-black.svg)
![Badges](https://img.shields.io/badge/core-dumped-red)
![Badges](https://img.shields.io/badge/lsf-wc-yellow)
![Badges](https://img.shields.io/badge/build-passing-succes.svg)
![Badges](https://img.shields.io/badge/test-success-success.svg)
![Badges](https://img.shields.io/badge/computer-science-critical.svg)
![Badges](https://img.shields.io/badge/love-linux-yellow.svg)
![Badges](https://img.shields.io/badge/coding-life-red.svg)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
![Badges](https://img.shields.io/badge/open-source-blueviolet.svg)

***SOME PICTURE FROM SHELL***

![Screenshot from 2020-01-21 18-42-31](https://user-images.githubusercontent.com/30092986/72819411-4470a400-3c7e-11ea-9318-5e1f3927d31e.png)

**When I write the code :)**

![ttystudio GIF](https://giphy.com/gifs/wikitude-augmented-reality-penguin-linux-4Zgy9QqzWU8C3ugvCa/fullscreen)

---

## Table of Contents

- [Installation](#installation)
- [Features](#features)
- [Support](#support)

## Installation

- All the `code` required to get started

### Clone

- Clone this repo to your local machine using `https://github.com/Emreozgun/myShell.git`
- Then open the terminal and go to the directory where the file is located.
- Run with **make all && ./gtushell** 


## Features
  ### Commands 
- My shell support the following commands:
  #### lsf
  >which will list file type (R for regular file, S for non-regular(special) file), access rights (int the
  form of rwxr-xr-x, just like actual ls), file size(bytes) and file name of all files (not directories) in
  the present working directory. It doesn’t take any argument. Does not list any directory.
  #### pwd
  > which will print the path of present working directory.
  #### cd
  > which will change the present working directory to the location provided as argument.
  #### help 
  > which will print the list of supported commands.
  #### cat 
  > which will print on standard output the contents of the file provided to it as argument or from
  standard input. The file can be on any directory on the system. (example, cat file.txt )(example2,
  pwd | cat )
  #### wc 
  > which will print on standard output the number of lines in the file provided to it as argument
  or the string coming from standard input until EOF character (example, Input: wc file.txt Output:55)
  (example2, Input: lsf | wc Output: 5 (there are 5 files in current directory so output of lsf has 5
  lines)).
  #### bunedu 
  > the file path argument of bunedu can also come from standard. bunedu command, short for disk usage, is used to estimate   file space usage.The bunedu command can be used to track the files and directories which are consuming excessive amount of   space on hard disk drive.
  #### exit 
  > That command which will exit the shell.

  ### Other features 
  - When the user types !n , the n-th previous command will run (Its like up and down arrow keys).
  - Each command supports have a single pipe "|" or a single redirection operator > <.
  - You can use Ctr-C to exit from gtushell.


  
## Support

Reach out to me at one of the following places!

- Linkedin at <a href="https://www.linkedin.com/in/emre-ozgun" target="_blank">`Emre_Ozgun_linkedin`</a>
- Stackoverflow at <a href="https://stackoverflow.com/users/12690037/emre-ozgun" target="_blank">`Emre_Ozgun_stackoverflow`</a>

---
