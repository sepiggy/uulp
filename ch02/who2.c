/* who2.c - read /etc/utmp and list info therein
 *        - suppresses empty records
 *        - formats time nicely
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>

void showtime(long);
void show_info(struct utmp *);

int main()
{
  struct utmp utbuf;    /* read info into here */
  int         utmpfd;   /* read from this descriptor */

  if ( (utmpfd = open(UTMP_FILE, O_RDONLY)) == -1 ) {
    perror(UTMP_FILE);
    exit(1);
  }

  while ( read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf) )
    show_info( &utbuf );

  close(utmpfd);
  return 0;
}

void show_info(struct utmp *utbufp)
{
  if ( utbufp->ut_type != USER_PROCESS )
    return;
  
  printf("%-8.8s", utbufp->ut_name);
  printf(" ");
  printf("%-8.8s", utbufp->ut_line);
  printf(" ");
  showtime(utbufp->ut_time);
  printf("\n");
}

void showtime(long timeval)
{
  char *cp;
  cp = ctime(&timeval);
  printf("%12.12s", cp+4); /* pick 12 chars from pos 4 */
}
