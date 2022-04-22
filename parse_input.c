#include <stdlib.h>
#include "parse_input.h"

void	store_arg(t_cmds* cmds, char* str) {
	int	i;

	if (!cmds->list)
		cmds->list = malloc(sizeof(*cmds->list));
	if (!cmds->list->args)
		cmds->list->args = malloc(sizeof(*cmds->list->args)); //wrong size
	else
		;//increment size
	i = 0;
	while (cmds->list->args[i] != NULL)
		i++;
	cmds->list->args[i] = str;



//if no node, create new node
	//save str in the node

}

void	get_arg(t_cmds* cmds, int *i) {
	int		j;
	int		k;
	char*	new_arg;

	j = *i;
	while (cmds->input[j] != ' '
		&& cmds->input[j] != '|'
		&& cmds->input[j] != ';')
		j++;
	if (j != *i) {
		new_arg = malloc(j - *i + NULL_CHAR);
		k = 0;
		while (*i <= j)
			new_arg[k++] = cmds->input[(*i)++];
		new_arg[k] = '\0';
		store_arg(cmds, new_arg);
	}
}

void	skip_white_space(char* str, int* i) {
	while (str[*i] == ' ')
		(*i)++;
}

int	parse_input(t_cmds* cmds) {
	int i;

	i = -1;
	while (cmds->input[++i] != '\0')
	{
		skip_white_space(cmds->input, &i);
		if (cmds->input[i] == '|')
			;//handle_pipe()
		else if (cmds->input[i] == ';')
			;//handle_semicolon()
		else
			get_arg(cmds, &i);
	}
	if (cmds->input[i] == '\0')
		return (1);
	else
		return (0);


}
