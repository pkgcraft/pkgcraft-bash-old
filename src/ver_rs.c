#include <stdio.h>

#include <bash/builtins.h>
#include <bash/shell.h>
#include <bash/builtins/common.h>

#include <pkgcraft.h>

static int ver_rs_builtin(WORD_LIST *list)
{
	char **args;
	char *PV = get_string_value("PV");
	int args_len, ret;

	args = strvec_from_word_list(list, 0, 0, &args_len);
	ret = pkgcraft_ver_rs(&args, args_len, &PV);
	free(args);

	if (ret == -1) {
		char *err = pkgcraft_last_error();
		if (err != NULL) {
			fprintf(stderr, "ver_rs: error: %s\n", err);
			pkgcraft_free_str(err);
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
