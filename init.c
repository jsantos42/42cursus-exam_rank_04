#include <stdlib.h>
#include "init.h"

void	init_cmds(t_list* cmds) {
	cmds->input = NULL;
	cmds->tree = NULL;
}

t_tree*	create_node(t_list *previous, t_list *list) {
	t_tree*	new_node;

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
