#include <stdio.h>

#include <bash/builtins.h>
#include <bash/shell.h>
#include <bash/builtins/common.h>

#include <pkgcraft.h>

static int ver_cut_builtin(WORD_LIST *list)
{
	char **args;
	char *PV = get_string_value("PV");
	int args_len, ret;

	args = strvec_from_word_list(list, 0, 0, &args_len);
	ret = pkgcraft_ver_cut(&args, args_len, &PV);
	free(args);

	if (ret == -1) {
		char *err = pkgcraft_last_error();
		if (err != NULL) {
			fprintf(stderr, "ver_cut: error: %s\n", err);
			pkgcraft_free_str(err);
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
