#include <stdio.h>

#include <bash/builtins.h>
#include <bash/shell.h>
#include <bash/builtins/common.h>

#include <pkgcraft.h>

static int has_builtin(WORD_LIST *list)
{
    char **argv;
    int argc, ret;

    argv = make_builtin_argv(list, &argc);
    ret = has(argc, &argv);
    free(argv);

    if (ret == -1) {
	char *err = last_error_message();
	if (err != NULL) {
	    fprintf(stderr, "has: error: %s\n", err);
	    error_message_free(err);
	}
	exit(ret);
    }

    return ret;
}

static char *has_doc[] = {
    "Returns 0 if the first argument is found in the list of subsequent arguments, 1 otherwise.",
    (char *)NULL
};

struct builtin has_struct = {
    .name	= "has",
    .function	= has_builtin,
    .flags	= BUILTIN_ENABLED,
    .long_doc	= has_doc,
    .short_doc	= "has needle ${haystack}",
    .handle	= NULL,
};
