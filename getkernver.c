#include <sys/utsname.h>

#include "extern.h"

void
getkernver(void)
{
	struct utsname sys;
	uname(&sys);
	iprint("Kernel:     ", sys.release);
}
