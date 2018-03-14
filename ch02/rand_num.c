/*
 * generate random numbers and write them to the file
 *      in order to compare cp1.c with variety of buffer size.
 */
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define MY_RAND_SIZE 2000000
#define MY_RAND_LEN 10
#define MY_RAND_START 1
#define MY_RAND_END MY_RAND_SIZE
#define MY_MODE 0777

int rand_btw(int, int);
void write_rand(int);
void oops(char *, char *);

int main() 
{
  int out_fd;

  if ( (out_fd = creat("rand_num.out", MY_MODE)) == -1 )
    oops("Cannot creat", "rand_num.out");
  
  for (int i=0; i<MY_RAND_SIZE; i++)
    write_rand(out_fd);
    
  return 0;
}

void write_rand(int out_fd)
{
  char rand_str[MY_RAND_LEN];

  sprintf( rand_str, "%d\n", rand_btw(MY_RAND_START, MY_RAND_END) );

  if ( write(out_fd, rand_str, MY_RAND_LEN) != MY_RAND_LEN )
    oops("Write error to", "rand_num.out");
}

int rand_btw(int start, int end) 
{
  srand((unsigned)time(NULL));
  return (rand() % (end - start)) + start;
}

void oops(char *s1, char *s2)
{
  fprintf(stderr, "Error: %s ", s1);
  perror(s2);
  exit(1);
}
