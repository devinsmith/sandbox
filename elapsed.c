
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	struct timeval start, end;
	long mtime, seconds, useconds;

	gettimeofday(&start, NULL);
	sleep(2);
	gettimeofday(&end, NULL);

	seconds  = end.tv_sec  - start.tv_sec;
	useconds = (end.tv_usec / 1000) - (start.tv_usec / 1000);
	mtime = ((seconds) * 1000 + useconds) + 0.5;

	printf("Elapsed time: %ld milliseconds\n", mtime);

	return 0;
}


