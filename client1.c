#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_LENGTH 200
// Created by Dave Ogle
// Edited by Kianoush Ranjbar




int main(int argc, char *argv[])
{

  int sd; /* the socket descriptor */
  struct sockaddr_in server_address;  /* structures for addresses */
  struct sockaddr_in inaddr;  /* structures for checking addresses */
  int rc;
  int i; /* loop variable */
  char *lineFromFile = NULL;
  size_t lengthRead = 0;
  char serverIP[20]; // provided by the user on the command line */
  int portNumber = 0; // provided by the user on the command line
  FILE *fp;
  char filename[MAX_LENGTH];
 

    
//------------------------------------------------------------------------
  /* check to see if the right number of parameters was entered */
  if (argc < 3){
    printf ("Error: enter <IP Address> first then <Port Number> as parameters\n");
    exit(1); /* just leave if wrong number entered */
  }

  /* this code checks to see if the ip address is a valid ip address */
  /* meaning it is in dotted notation and has valid numbers          */
  if (!inet_pton(AF_INET, argv[1], &inaddr)){
    printf ("Error: enter a valid IP Address (with dotted notation and valid numbers)\n");
    exit (1); /* just leave if is incorrect */
  }
  
    
//------------------------------------------------------------------------
  /* first create a socket */
  sd = socket(AF_INET, SOCK_DGRAM, 0); /* create a socket */
  /* what should you do if the socket descriptor is not valid */

  /* check that the port number is a number..... */

  for (i=0;i<strlen(argv[2]); i++){
    if (!isdigit(argv[2][i]))
      {
	printf ("Error: the port number must be a numerical integer\n");
	exit(1);
      }
  }
//------------------------------------------------------------------------
// Create ip address

  portNumber = strtol(argv[2], NULL, 10); /* many ways to do this */
  /* exit if a portnumber too big or too small  */
  if ((portNumber > 65535) || (portNumber < 0)){
    printf ("Error: you entered an invalid port number out of the range of 0-65535\n");
    exit (1);
  }
  
  strcpy(serverIP, argv[1]); /* copy the ip address */

  memset(&server_address, 0, sizeof(server_address));//got this line from chatGPT
  server_address.sin_family = AF_INET; /* use AF_INET addresses */
  server_address.sin_port = htons(portNumber); /* convert port number */
  server_address.sin_addr.s_addr = inet_addr(serverIP); /* convert IP addr */
  
//------------------------------------------------------------------------
// THIS IS WHERE THE CHANGES ARE MADE    
    //memset (lineFromFile, 0, 100); // ALWAYS null out buffers in C before using them
    
    printf("Enter the name of a text file to open: ");    // first we open the text file
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    
for (;;) {
    rc = getline(&lineFromFile, &lengthRead, fp);     // get the contents of the text file
        
    int len = strlen(lineFromFile);         // remove last trailing endline character from text file
    if (lineFromFile[len-1] == '\n') {
        lineFromFile[len-1] = '\0';
    }
    

    if (rc <= 1){                     
        printf("done with file!\n");
        break;  // exit forever loop
        
    }
    printf("I am sending: '%s'", lineFromFile);
    printf("\nThe length of the string is %lu bytes\n\n", strlen(lineFromFile));
    sendto(sd, lineFromFile, lengthRead, 0, (struct sockaddr *) &server_address, sizeof(server_address));   // send the line to the server
}
    
    

//  /* Check the RC and figure out what to do if it is 'bad' */
//  /* what is a bad RC from sendto?                         */
//	// if the buffer out is overflowed, or if the socket descriptor is invalid
//  if (rc < strlen(lineFromFile)){
//    perror ("Error: there was an error when trying to send the message");
//    // do i exit?
//	exit (1);
//	// yes, so we can fix the error
//  }
  
return 0;

}
