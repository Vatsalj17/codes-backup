#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main (void) {
    time_t now = time(NULL);
    printf("\n%ld\n\n", now);
    // sleep(2);
    // time_t twosec = time(NULL);
    // printf("%ld\n", twosec);
    // double diff = difftime(twosec, now);
    // printf("diff = %f\n\n", diff);

    char *str_now = ctime(&now);
    puts(str_now);

    struct tm *gm = gmtime(&now);
    printf("tm_sec = %d\n", gm->tm_sec);
    printf("tm_hour = %d\n", gm->tm_hour);
    printf("tm_min = %d\n", gm->tm_min);
    printf("tm_gmtoff = %ld\n", gm->tm_gmtoff);
    printf("tm_isdst = %d\n", gm->tm_isdst);
    printf("tm_mday = %d\n", gm->tm_mday);
    printf("tm_mon = %d\n", gm->tm_mon);
    printf("tm_wday = %d\n", gm->tm_wday);
    printf("tm_yday = %d\n", gm->tm_yday);
    printf("tm_year = %d\n", gm->tm_year);
    printf("tm_zone = %s\n", gm->tm_zone);

    printf("\n\n");

    struct tm *local = localtime(&now);
    printf("tm_sec = %d\n", local->tm_sec);
    printf("tm_hour = %d\n", local->tm_hour);
    printf("tm_min = %d\n", local->tm_min);
    printf("tm_gmtoff = %ld\n", local->tm_gmtoff);
    printf("tm_isdst = %d\n", local->tm_isdst);
    printf("tm_mday = %d\n", local->tm_mday);
    printf("tm_mon = %d\n", local->tm_mon);
    printf("tm_wday = %d\n", local->tm_wday);
    printf("tm_yday = %d\n", local->tm_yday);
    printf("tm_year = %d\n", local->tm_year);
    printf("tm_zone = %s\n", local->tm_zone);

    printf("\n%s\n", asctime(local));

    // Changing time
    local->tm_sec += 1;
    time_t new = mktime(local);
    printf("%ld\n", new);
    printf("%s\n", ctime(&new));

    clock_t start, end;
    start = clock();
    printf("start: %ld\n", start);
    for (int i = 0; i < 100000000; i++) { }
    end = clock();
    printf("end: %ld\n", end);
    double total = (double) (end - start) / CLOCKS_PER_SEC;
    printf("Time: %fs\n", total);
}
