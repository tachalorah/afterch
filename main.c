#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "extern.h"

#define C_RESET	  "\033[0m"
#define C_RED	  "\033[1;31m"
#define C_GREEN	  "\033[1;32m"
#define C_YELLOW  "\033[1;33m"
#define C_BLUE	  "\033[1;34m"
#define C_MAGENTA "\033[1;35m"
#define C_CYAN	  "\033[1;36m"
#define C_WHITE	  "\033[1;39m"

static void
getshell(void)
{
	iprint("Shell:      ", getenv("SHELL"));
}

static void
getterm(void)
{
	iprint("Terminal:   ", getenv("TERM"));
}

static char *
strloop(const char *restrict x, const int y)
{
	if (x && y > 0) {
		size_t len = strlen(x) * y;
		char *buf = malloc(len + 1);
		if (buf == NULL)
			return (NULL);
		for (int i = 0; i < y; i++)
			(void)memcpy(buf + (i * strlen(x)), x, strlen(x));
		buf[len] = '\0';
		return (buf);
	}
	return (NULL);
}

int
main(void)
{
	int i, j;
	char *fgcodes[] = { "4", "10" };
	char hostname[257];
	gethostname(hostname, sizeof(hostname));

	printf("\n  %s--->%s     %s%s%s@%s%s%s\n", C_MAGENTA, C_RESET, C_GREEN,
	    getlogin(), C_YELLOW, C_RED, strtok(hostname, "."), C_RESET);
	printf("  %s%s>%s\n\n", C_MAGENTA, strloop("-", 32), C_RESET);

	getsysname(), getkernver(), getshell(), getterm(), getuptime();

	puts("");

	for (i = 0; i < 2; i++) {
		printf("  %s--->%s  ", C_CYAN, C_RESET);
		for (j = 0; j < 8; j++)
			printf("\033[1;%s%dm   ", fgcodes[i], j);
		printf("%s\n", C_RESET);
	}

	puts("");
}

void
iprint(char *text, char *info)
{
	printf("     %s->%s %s%s%s%s\n", C_CYAN, C_RESET, C_BLUE, text, C_RESET,
	    info);
}
