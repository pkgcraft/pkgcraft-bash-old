#include <stdio.h>

#include <bash/builtins.h>
#include <bash/shell.h>
#include <bash/builtins/common.h>

#include <pkgcraft.h>

static int ver_test_builtin(WORD_LIST *list)
{
    char **args;
    char *PVR = get_string_value("PVR");
    int args_len, ret;

    args = strvec_from_word_list(list, 0, 0, &args_len);
    ret = pkgcraft_ver_test(&args, args_len, &PVR);
    free(args);

    if (ret == -1) {
	char *err = pkgcraft_last_error();
	if (err != NULL) {
	    fprintf(stderr, "ver_test: error: %s\n", err);
	    pkgcraft_free_str(err);
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
    .short_doc	= "ver_test 1 -lt 2-r1",
    .handle	= NULL,
};
