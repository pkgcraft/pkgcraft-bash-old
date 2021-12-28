#include <stdlib.h>
#include <string.h>

char *str_join(const char *separator, char **str_array)
{
    char *string, *ptr;

    if (str_array == NULL) return NULL;
    if (separator == NULL) separator = "";

    if (*str_array) {
	unsigned int i;
	unsigned int len = 0;

	// get output string length
	for (i = 0; str_array[i] != NULL; i++) {
	    len += strlen(str_array[i]);
	}
	// add separator lengths
	len += strlen(separator) * (i - 1);
	// and NULL terminator
	len++;

	// build the string
	string = (char *)malloc(sizeof(char)*len);
	ptr = stpcpy(string, *str_array);
	for (i = 1; str_array[i] != NULL; i++) {
	    ptr = stpcpy(ptr, separator);
	    ptr = stpcpy(ptr, str_array[i]);
	}
    } else {
	string = strdup("");
    }

    return string;
}


