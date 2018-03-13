#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 8

int main(int argc, char *argv[])
{
  int  infd, outfd;
  char buf[BUFSIZE];
  int  readlen;

  if (argc < 3) {
    fprintf(stderr, "cp command needs two arguments.\n");
    exit(1);
  } 

  if ( (infd = open(argv[1], O_RDONLY)) == -1 ) {
    perror(argv[1]);
    exit(1);
  }

  if ( (outfd = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU)) == -1 ) {
    perror(argv[2]);
    exit(1);
  }

  while ( (readlen = read(infd, buf, BUFSIZE)) == BUFSIZE ) {
    write(outfd, buf, BUFSIZE);
  }
  write(outfd, buf, readlen);

  close(infd);
  close(outfd);

  puts("FINISHED...");

  return 0; 
}
