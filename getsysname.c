#include <sys/utsname.h>

#include <stdio.h>
#include <stdlib.h>

#include "extern.h"

void
getsysname(void)
{
	struct utsname sys;
	uname(&sys);

#ifdef __linux__
	FILE *f = fopen("/etc/os-release", "r");

	if (f != NULL) {
		char buf[32];
		char *l = NULL;
		size_t strlen;

		while (getline(&l, &strlen, f) != -1)
			if (sscanf(l, "ID=%[^\\0\n]+", buf))
				break;

		free(l);
		iprint("OS/System:  ", buf);
	} else
		iprint("OS/System:  ", sys.sysname);

	fclose(f);
#else
	iprint("OS/System:  ", sys.sysname);
#endif
}
