#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "get_input.h"
#include "parse_input.h"
#include "execute_input.h"

#include <stdio.h>


void	terminate(int exit_code, t_cmds* cmds) {
	free(cmds->input);
	free(cmds);
	exit(exit_code);
}


void	init_cmds(t_cmds* cmds) {
	cmds = malloc(sizeof(t_cmds));
	cmds->input = NULL;
	cmds->list = NULL;
}

int main(int argc, char** argv, char** env) {
	t_cmds*	cmds;

	if (argc == 1)
		return (EXIT_SUCCESS);
	cmds = NULL;
	init_cmds(cmds);
	cmds->input = get_full_input(argc, argv);
	if (!parse_input(cmds))
		terminate(-1, cmds);
	execute_input(cmds);
	terminate(EXIT_SUCCESS, cmds);
	(void)env;
	printf("%s\n", cmds->input);
	return (0);
}
