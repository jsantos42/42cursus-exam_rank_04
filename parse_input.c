#include <stdlib.h>
#include "parse_input.h"
#include "init.h"
//#include "main.h"

void	store_arg(t_list* cmds, t_tree* current_node, char* str) {
	char**	new_matrix;
	int		new_size;
	int		i;

	new_size = current_node->nb_args + 1 + NULL_CHAR;
	new_matrix = NULL;
	new_matrix = malloc(new_size * sizeof(char*));
	if (!new_matrix)
		terminate(MALLOC, cmds);
	i = -1;
	while (++i < current_node->nb_args)
		new_matrix[i] = current_node->args[i];
	new_matrix[i++] = str;
	new_matrix[i] = NULL;
	free(current_node->args);
	current_node->args = new_matrix;
	current_node->nb_args++;
}

void	get_arg(t_list* cmds, t_tree* current_node, char* str, int *i) {
	int		j;
	int		k;
	char*	new_arg;

	j = *i;
	while (str[j] != ' '
		&& str[j] != '|'
		&& str[j] != ';')
		j++;
	if (j != *i) {
		new_arg = malloc(j - *i + NULL_CHAR);
		k = 0;
		while (*i <= j)
			new_arg[k++] = str[(*i)++];
		new_arg[k] = '\0';
		store_arg(cmds, current_node, new_arg);
	}
}

void	skip_white_space(char* str, int* i) {
	while (str[*i] == ' ')
		(*i)++;
}


int	parse_input(t_list* cmds) {
	int		i;
	t_tree*	current_node;

	cmds->tree = create_node(NULL, cmds);
	current_node = cmds->tree;
	i = -1;
	while (cmds->input[++i] != '\0')
	{
		skip_white_space(cmds->input, &i);
		if (cmds->input[i] == '|')
			handle_pipe(cmds, &current_node, cmds->input, &i);
		else if (cmds->input[i] == ';')
			handle_semicolon(cmds, &current_node, cmds->input, &i);
		else
			get_arg(cmds, current_node, cmds->input, &i);
	}
	if (cmds->input[i] == '\0')
		return (1);
	else
		return (0);
}
