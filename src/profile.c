#include <stdio.h>
#include <string.h>
#include <time.h>

#include <bash/builtins.h>
#include <bash/builtins/bashgetopt.h>
#include <bash/shell.h>
#include <bash/builtins/common.h>
#include "input.h"

char *str_join(const char *separator, char **str_array)
{
    char *string, *ptr;

    if (str_array == NULL) return NULL;
    if (separator == NULL) separator = "";

    if (*str_array) {
	unsigned int i;
	unsigned int len = 0;

	// get output string length
	for (i = 0; str_array[i] != NULL; i++) {
	    len += strlen(str_array[i]);
	}
	// add separator lengths
	len += strlen(separator) * (i - 1);
	// and NULL terminator
	len++;

	// build the string
	string = (char *)malloc(sizeof(char)*len);
	ptr = stpcpy(string, *str_array);
	for (i = 1; str_array[i] != NULL; i++) {
	    ptr = stpcpy(ptr, separator);
	    ptr = stpcpy(ptr, str_array[i]);
	}
    } else {
	string = strdup("");
    }

    return string;
}

void determine_units(double time, double *new_time, char **units)
{
    const char *UNITS[4] = {"s", "ms", "μs", "ns"};
    int idx = 0;

    while (time < 1 && idx < 4) {
	time *= 1000;
	idx++;
    }

    *new_time = time;
    *units = (char *)UNITS[idx];
}

static int profile_builtin(WORD_LIST *list)
{
    char **args;
    char *cmd;
    char *loops_end = NULL;
    char *units = NULL;
    clock_t start, end;
    double elapsed, d_time;
    int i, opt;
    unsigned int loops = 10000;

    reset_internal_getopt();
    while ((opt = internal_getopt(list, "n:")) != -1) {
	switch (opt) {
	    case 'n':
		loops = strtol(list_optarg, &loops_end, 10);
		if (*loops_end != '\0') {
		    builtin_error("-n: option requires an integer argument");
		    return EX_USAGE;
		}
		break;
	    default:
		builtin_usage();
		return EX_USAGE;
	}
    }

    // skip past options
    if ((list = loptend) == NULL) {
	builtin_usage();
	return EX_USAGE;
    }

    args = strvec_from_word_list(list, 0, 0, NULL);
    cmd = str_join(" ", args);
    free(args);

    start = clock();
    for (i = 0; i < loops; i++) {
	execute_variable_command(cmd, "-c");
    }
    end = clock();

    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    determine_units(elapsed, &d_time, &units);
    fprintf(stderr, "Processor time: %.2f %s\n", d_time, units);
    determine_units(elapsed / loops, &d_time, &units);
    fprintf(stderr, "Average per loop: %.2f %s\n", d_time, units);
    free(cmd);

    return 0;
}

static char *profile_doc[] = {
    "Profile a given function's processor time usage.",
    (char *)NULL
};

struct builtin profile_struct = {
    .name	= "profile",
    .function	= profile_builtin,
    .flags	= BUILTIN_ENABLED,
    .long_doc	= profile_doc,
    .short_doc	= "profile [-n 1000] func arg1 arg2",
    .handle	= NULL,
};
