So the way my programs are structure are that they are the exact same files from Lab0, just with the added functions to read and send a file on the client side, and to parse and print it on the server side.


Instructions:
The instructions for running this program will be the exact same as Lab0
first you run the makefile which produces your executables
second you run the command "./server1 <portnumber>" (make sure to specify port number) 
third you run the "./client <ipaddress> <portnumber>" command
fourth the client file will ask you to enter the name of the text file you would like to use 
DONE!

------------------------------------------------------------------------------------------------------------
  
A few miscellaneous things I learned and/or used alot in this Lab
  
  
// to compile c into executable
$ gcc main.c -o output_name

//ports free to use
Ports 49152-65535
I recommend 55555 easy to remember 

// to select and then delete in nano
Ctrl + shift + 6, to select
Ctrl + k, to cut

------------------------------------------------------------------------------------------------------------

Problems I encountered, But fixed:
Now I have everything working correctly BESIDES separating the quoted portion of the file from the rest, after hours and hours of rigorous research and study I was not able to come to a conclusion on how to separate the quoted portion and treat it as one.

The strtok function is very particular on just letting you parse using one delimiter at a time.
I tried adjusting the input stream fill in all the spaces in-between the quotes, so the delimiter would pick it up as just one value and use the base " " delimiter to separate by spaces but that didn't work it would only print the first line of output, even after flushing the output buffer it didn't work.
