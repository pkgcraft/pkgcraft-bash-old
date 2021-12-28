#include <stdio.h>
#include <time.h>

#include <bash/builtins.h>
#include <bash/builtins/bashgetopt.h>
#include <bash/shell.h>
#include <bash/builtins/common.h>

// bundled bash headers
#include "execute_cmd.h"
#include "input.h"

#include "utils.h"

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
    char *cmd_str;
    char *loops_end = NULL;
    char *units = NULL;
    clock_t start, end;
    double elapsed, d_time;
    int i, opt;
    int ret = 0;
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
    cmd_str = str_join(" ", args);
    free(args);

    // parse string into command
    with_input_from_string(cmd_str, "profile_builtin");
    ret = parse_command();
    with_input_from_stdin();
    if (ret != 0) {
	fprintf(stderr, "failed to parse command: %s\n", cmd_str);
	goto exit;
    }

    start = clock();
    for (i = 0; i < loops; i++) {
	execute_command(global_command);
    }
    end = clock();

    // clean up command
    dispose_command(global_command);
    global_command = (COMMAND *)NULL;

    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    determine_units(elapsed, &d_time, &units);
    fprintf(stderr, "Processor time: %.2f %s\n", d_time, units);
    determine_units(elapsed / loops, &d_time, &units);
    fprintf(stderr, "Average per loop: %.2f %s\n", d_time, units);

exit:
    free(cmd_str);
    return ret;
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
