#include <stdlib.h>
#include "main.h"
#include "get_input.h"

int	ft_strlen(char* str) {
	int	i = 0;
	while (str && str[i] != '\0')
		i++;
	return (i);
}

static char*	add_strings(char* existent, char* new_arg) {
	char*	sum;
	int		i;

	sum = (char*)malloc(sizeof(char) *
						(ft_strlen(existent) + ft_strlen(new_arg) + NULL_CHAR));
	i = 0;
	for (int j = 0; existent && existent[j] != '\0'; j++)
		sum[i++] = existent[j];
	for (int j = 0; new_arg && new_arg[j] != '\0'; j++)
		sum[i++] = new_arg[j];
	sum[i] = '\0';
	free(existent);
	return (sum);
}

char*	get_full_input(int argc, char** argv) {
	char*	full_input;

	full_input = NULL;
	for (int i = 1; i < argc; i++)
		full_input = add_strings(full_input, argv[i]);
	return (full_input);
}
