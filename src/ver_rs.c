#include <stdio.h>

#include <bash/builtins.h>
#include <bash/shell.h>
#include <bash/builtins/common.h>

#include <pkgcraft.h>

static int ver_rs_builtin(WORD_LIST *list)
{
    char **argv;
    int	argc, ret;

    argv = make_builtin_argv(list, &argc);
    ret = ver_rs(argc, &argv);
    free(argv);

    if (ret == -1) {
	char *err = last_error_message();
	if (err != NULL) {
	    printf("ver_rs: error: %s\n", err);
	    free(err);
	}
	exit(ret);
    }

    return ret;
}

static char *ver_rs_doc[] = {
    "Perform string substitution on package version strings.",
    ""
    "ver_rs performs string substitution on package version strings.",
    (char *)NULL
};

struct builtin ver_rs_struct = {
    .name	= "ver_rs",
    .function	= ver_rs_builtin,
    .flags	= BUILTIN_ENABLED,
    .long_doc	= ver_rs_doc,
    .short_doc	= "ver_rs 2 - 1.2.3",
    .handle	= NULL,
};
