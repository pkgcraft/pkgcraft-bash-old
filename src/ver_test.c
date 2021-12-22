#include <stdio.h>

#include <bash/builtins.h>
#include <bash/shell.h>
#include <bash/builtins/common.h>

#include <pkgcraft.h>

extern char **make_builtin_argv ();

static int ver_test_builtin(WORD_LIST *list)
{
    char **argv;
    int	argc, ret;

    argv = make_builtin_argv(list, &argc);
    // rust handles freeing argv
    ret = ver_test(argc, argv);

    if (ret == -1) {
	char *err = last_error_message();
	if (err != NULL) {
	    printf("ver_test: error: %s\n", err);
	}
	exit(ret);
    }

    return ret;
}


static char *ver_test_doc[] = {
    "Perform package version checks.",
    ""
    "ver_test performs package version checks for Gentoo ebuilds.",
    (char *)NULL
};

struct builtin ver_test_struct = {
    .name	= "ver_test",
    .function	= ver_test_builtin,
    .flags	= BUILTIN_ENABLED,
    .long_doc	= ver_test_doc,
    .short_doc	= "ver_test ${ver} -lt 2-r1",
    .handle	= NULL,
};
