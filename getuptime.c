#include <stdio.h>
#include <time.h>

#include "extern.h"

void
getuptime(void)
{
	struct timespec time;
	time_t uptime;
	int d, h, m;

	char buf[256];

	if (clock_gettime(CLOCK_BOOTTIME, &time) != -1) {
		uptime = time.tv_sec;
		if (uptime > 59) {
			d = uptime / 86400;
			uptime %= 86400;
			h = uptime / 3600;
			uptime %= 3600;
			m = uptime / 60;

			if (d > 0)
				(void)sprintf(buf, "%dd %dh %dm", d, h, m);
			if (h > 0 && m > 0)
				(void)sprintf(buf, "%dh %dm", h, m);
			else {
				if (h > 0)
					(void)sprintf(buf, "%dh", h);
				if (m > 0)
					(void)sprintf(buf, "%dm", m);
			}
		} else
			(void)sprintf(buf, "%ld secs", uptime);

	} else
		(void)sprintf(buf, "unknown");

	iprint("Uptime:     ", buf);
}
