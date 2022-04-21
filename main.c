#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#include <stdio.h>

//void	execute_input(t_cmds* cmds) {
//}
//
//void	terminate(int exit_code, t_cmds* cmds) {
//
//}


int	ft_strlen(char* str) {
	int	i = 0;
	while (str && str[i] != '\0')
		i++;
	return (i);
}

char*	add_strings(char* first, char* second) {
	char*	sum;
	int		i;

	sum = (char*)malloc(sizeof(char) *
			(ft_strlen(first) + ft_strlen(second) + NULL_CHAR));
	i = 0;
	for (int j = 0; first && first[j] != '\0'; j++)
		sum[i++] = first[j];
	for (int j = 0; second && second[j] != '\0'; j++)
		sum[i++] = second[j];
	sum[i] = '\0';
	free(first);
	return (sum);
}

char*	get_full_input(int argc, char** argv) {
	char*	full_input;

	full_input = NULL;
	for (int i = 1; i < argc; i++)
		full_input = add_strings(full_input, argv[i]);
	return (full_input);
}

//int	parse_input(t_cmds* cmds) {
//
//
//}

int main(int argc, char** argv, char** env) {
	t_cmds*	cmds;

	cmds = NULL;
	if (argc == 1)
		return (EXIT_SUCCESS);
	// put this inside init function
	cmds = malloc(sizeof(t_cmds));

	cmds->input = get_full_input(argc, argv);
//	if (!parse_input(cmds))
//		terminate(-1, cmds);
//	execute_input(cmds);
//	terminate(EXIT_SUCCESS, cmds);
	(void)env;
	printf("%s\n", cmds->input);
	free(cmds->input);
	free(cmds);
	return (0);
}
