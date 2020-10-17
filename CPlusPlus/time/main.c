#include <stdio.h>      /* printf */
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */

int frequency_of_primes(int n) {
	int i, j;
	int freq = n - 1;
	for (i = 2; i <= n; ++i) for (j = sqrt(i); j > 1; --j) if (i%j == 0) { --freq; break; }
	return freq;
}

#define MST (-7)
#define UTC (0)
#define CCT (+8)

int main()
{
	{
		puts("********** clock_t **********\n");
		clock_t t;
		int f;
		t = clock();
		printf("Calculating...\n");
		f = frequency_of_primes(99999);
		printf("The number of primes lower than 100,000 is: %d\n", f);
		t = clock() - t;// 毫秒
		printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);

	}
	{
		puts("\n********** time_t **********\n");
	
		time_t timer;
		struct tm y2k = { 0 };
		double seconds;

		y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
		y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

		time(&timer);  /* get current time; same as: timer = time(NULL)  */

		seconds = difftime(timer, mktime(&y2k)); // mktime: time_t => tm

		printf("%.f seconds since January 1, 2000 in the current timezone\n", seconds);
	}

	{
		puts("\n********** time_t => string, UTC, local **********\n");

		time_t rawtime;

		struct tm * timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);			//获取local时间 time_t => tm(local)
		printf("asctime => The current date/time is: %s\n", asctime(timeinfo));   // tm => string

		printf("The current local time is: %s", ctime(&rawtime)); // 等价于 asctime(localtime(&rawtime))   // time_t => string

		struct tm *ptm = gmtime(&rawtime);		//获取UTC时间 time_t => tm(UTC)
		puts("Current time around the World:");
		printf("Phoenix, AZ (U.S.) :  %2d:%02d\n", (ptm->tm_hour + MST) % 24, ptm->tm_min);
		printf("Reykjavik (Iceland) : %2d:%02d\n", (ptm->tm_hour + UTC) % 24, ptm->tm_min);
		printf("Beijing (China) :     %2d:%02d\n", (ptm->tm_hour + CCT) % 24, ptm->tm_min);


		puts("\n********** strftime **********\n");//指定格式存储时间
		char buffer[80];

		strftime(buffer, 80, "Now it's %I:%M%p.", timeinfo); puts(buffer);   	
		strftime(buffer, 80, "Now it's %r.", timeinfo);   puts(buffer);

	}


	return 0;
}