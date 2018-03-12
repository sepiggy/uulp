#include <stdio.h>
#include <stdlib.h>
#include <utmpx.h>

int main()
{
  struct utmpx *current_record;
  while ((current_record = getutxent())) {
    time_t t = current_record -> ut_tv.tv_sec;
    struct tm *p = localtime(&t);
    char buf[55];
    strftime(buf, sizeof(buf), "%b %d %H:%M", p);

    if (current_record -> ut_type == USER_PROCESS)
      printf("%s %s %s %s\n", current_record->ut_user, current_record->ut_line, buf, current_record->ut_host);
  }
  endutxent();
  return 0;
}
