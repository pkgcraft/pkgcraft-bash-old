#include <stdio.h>

#include <bash/builtins.h>
#include <bash/shell.h>
#include <bash/builtins/common.h>

#include <pkgcraft.h>

static int ver_cut_builtin(WORD_LIST *list)
{
    char **argv;
    int	argc, ret;

    argv = make_builtin_argv(list, &argc);
    // pkgcraft handles freeing argv
    ret = ver_cut(argc, argv);

    if (ret == -1) {
	char *err = last_error_message();
	if (err != NULL) {
	    printf("ver_cut: error: %s\n", err);
	    free(err);
	}
	exit(ret);
    }

    return ret;
}

static char *ver_cut_doc[] = {
    "Output substring from package version string and range arguments.",
    ""
    "ver_cut outputs a substring related to package version string and range arguments.",
    (char *)NULL
};

struct builtin ver_cut_struct = {
    .name	= "ver_cut",
    .function	= ver_cut_builtin,
    .flags	= BUILTIN_ENABLED,
    .long_doc	= ver_cut_doc,
    .short_doc	= "ver_cut 1-2",
    .handle	= NULL,
};
