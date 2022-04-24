#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "init.h"
#include "get_input.h"
#include "parse_input.h"
#include "execute_input.h"

#include <stdio.h>
#include <string.h>


void	terminate(int exit_code, t_list* list) {
	free(list->input);
	free(list);
	exit(exit_code);
}

int	is_break(char* str) {
	return (strcmp(str, ";"));
}

int	is_pipe(char* str) {
	return (strcmp(str, "|"));
}
//	t_tree*	current_node;

//	list->tree = create_node(NULL, list);
//	current_node = list->tree;

t_list*	create_node(t_list* previous, t_list* list) {
	t_list*	new_node;

	new_node = NULL;
	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		terminate(MALLOC, list);
	new_node->args = NULL;
	new_node->nb_args = 0;
	new_node->previous = NULL;
	new_node->next = NULL;
	return (new_node);
}


void	add_arg(t_list* list, char* arg) {

}

void	parse_arg(t_list** list, char* arg) {
	if (is_break(arg) && !list)
		return ;
	else if (is_break(arg))
		(*list)->flag = BREAK;
	else if (is_pipe(arg))
		(*list)->flag = PIPE;
	else if (!list)
		create_node(&list, arg);
	else
		add_arg(*list, arg);
}

int main(int argc, char** argv, char** env) {
	t_list*	list;
	int		ret;

	if (argc == 1)
		return (EXIT_SUCCESS);
	list = NULL;
	ret = 0;
	for (int i = 1; i < argc; i++)
		parse_arg(&list, argv[i]);
	if (list)
		ret = execute_input(list, env); //do the rewind before exec
//	printf("%s\n", list->input);
	return (ret);
}
