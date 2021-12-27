#include <stdio.h>

#include <bash/builtins.h>
#include <bash/shell.h>
#include <bash/builtins/common.h>

#include <pkgcraft.h>

static int hasv_builtin(WORD_LIST *list)
{
    char **args;
    int args_len, ret;

    args = strvec_from_word_list(list, 0, 0, &args_len);
    ret = hasv(&args, args_len);
    free(args);

    if (ret == -1) {
	char *err = last_error_message();
	if (err != NULL) {
	    fprintf(stderr, "hasv: error: %s\n", err);
	    error_message_free(err);
	}
	exit(ret);
    }

    return ret;
}

static char *hasv_doc[] = {
    "The same as has, but also prints the first argument if found.",
    (char *)NULL
};

struct builtin hasv_struct = {
    .name	= "hasv",
    .function	= hasv_builtin,
    .flags	= BUILTIN_ENABLED,
    .long_doc	= hasv_doc,
    .short_doc	= "hasv needle ${haystack}",
    .handle	= NULL,
};
