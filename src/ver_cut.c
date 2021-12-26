#include <stdio.h>

#include <bash/builtins.h>
#include <bash/shell.h>
#include <bash/builtins/common.h>

#include <pkgcraft.h>

static int ver_cut_builtin(WORD_LIST *list)
{
    char **argv;
    int argc, ret;

    argv = make_builtin_argv(list, &argc);
    ret = ver_cut(argc, &argv);
    free(argv);

    if (ret == -1) {
	char *err = last_error_message();
	if (err != NULL) {
	    fprintf(stderr, "ver_cut: error: %s\n", err);
	    error_message_free(err);
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
    .short_doc	= "ver_cut 1-2 1.2.3",
    .handle	= NULL,
};
