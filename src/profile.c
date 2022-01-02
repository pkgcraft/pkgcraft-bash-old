#include <signal.h>
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

volatile sig_atomic_t profile_builtin_timeout;

void profile_sighandler(int signum) {
	profile_builtin_timeout = signum;
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
	char *cmd_str;
	char *endptr = NULL;
	char *units = NULL;
	clock_t start, end;
	double elapsed, d_time;
	int i, opt;
	int ret = 0;
	unsigned int loops = 0;
	unsigned int loop_time = 0;

	reset_internal_getopt();
	while ((opt = internal_getopt(list, "n:s:")) != -1) {
		switch (opt) {
			case 'n':
				loops = strtol(list_optarg, &endptr, 10);
				if (*endptr != '\0') {
					builtin_error("-n: option requires an integer argument");
					return EX_USAGE;
				}
				break;
			case 's':
				loop_time = strtol(list_optarg, &endptr, 10);
				if (*endptr != '\0') {
					builtin_error("-s: option requires an integer argument");
					return EX_USAGE;
				}
				break;
			default:
				builtin_usage();
				return EX_USAGE;
		}
	}

	if (loops != 0 && loop_time != 0) {
		builtin_error("-n and -s options are mutually exclusive");
		return EX_USAGE;
	} else if (loops == 0 && loop_time == 0) {
		// default to using 5 seconds of command looping
		loop_time = 5;
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
	if (loops != 0) {
		for (i = 0; i < loops; i++) {
			execute_command(global_command);
		}
	} else {
		struct sigaction act, orig_sigalrm, orig_sigint;
		act.sa_handler = profile_sighandler;
		act.sa_flags = 0;
		sigaction(SIGALRM, &act, &orig_sigalrm);
		sigaction(SIGINT, &act, &orig_sigint);

		// set a SIGALRM to go off
		alarm(loop_time);
		profile_builtin_timeout = 0;

		// execute the command while waiting for SIGALRM/SIGINT to trigger
		while (profile_builtin_timeout == 0) {
			execute_command(global_command);
			loops++;
		}

		sigaction(SIGALRM, &orig_sigint, NULL);
		sigaction(SIGINT, &orig_sigint, NULL);
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
	"",
	"Options:",
	"	-n loops	execute command for a given number of loops",
	"	-s seconds	execute command for a given number of seconds",
	(char *)NULL
};

struct builtin profile_struct = {
	.name	= "profile",
	.function	= profile_builtin,
	.flags	= BUILTIN_ENABLED,
	.long_doc	= profile_doc,
	.short_doc	= "profile [-n loops] [-s seconds] func arg1 arg2",
	.handle	= NULL,
};
