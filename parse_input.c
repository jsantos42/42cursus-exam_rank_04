#include "parse_input.h"

int	parse_input(t_cmds* cmds) {
	int i;

	i = -1;
	while (cmds->input[++i] != '\0')
	{
		//skip_white_space
		if (cmds->input[i] == '|')
			;//handle_pipe()
		else if (cmds->input[i] == ';')
			;//handle_semicolon()
	}


}
