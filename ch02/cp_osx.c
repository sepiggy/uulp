#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 8

int main(int argc, char *argv[])
{
  if (argc < 3) {
    fprintf(stderr, "The command of cp is error, please check.\n");
    fprintf(stderr, "It needs three arguments, please check again.\n");
    exit(1);
  } 

  char buf[BUFSIZE];
  int fd_in = open(argv[1], O_RDONLY);
  int fd_out = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);

  int read_rst;

  while ( (read_rst = read(fd_in, buf, BUFSIZE) ) {
    write(fd_out, buf, BUFSIZE);
  }
  close(fd_in);
  close(fd_out);

  printf("COPY FINISHED...");

  return 0;
}
