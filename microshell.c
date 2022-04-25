#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "microshell.h"

//==============================================================================
//	UTILS
//==============================================================================
int	ft_strlen(char* str) {
	int	i = 0;
	while (str && str[i] != '\0')
		i++;
	return (i);
}

int	print_error(char *str) {
	write(STDERR_FILENO, str, ft_strlen(str));
	return (-1);
}

void	list_rewind(t_list** list) {
	while (*list && (*list)->previous)
		*list = (*list)->previous;
}

/*
 * Beware not to free the args[0-i], since they were not allocated in the heap,
 * but passed on as arguments. Otherwise, we will have this error when freeing:
 *		munmap_chunk(): invalid pointer
 */
void	terminate(int exit_code, t_list* list) {
	t_list*	tmp;

	list_rewind(&list);
	while (list) {
		free(list->args);
		tmp = list->next;
		free(list);
		list = tmp;
	}
	exit(exit_code);
}

//==============================================================================
//	PARSER
//==============================================================================

int	is_break(char* str) {
	return (strcmp(str, ";") == 0);
}

int	is_pipe(char* str) {
	return (strcmp(str, "|") == 0);
}

t_list*	create_new_node(t_list* previous) {
	t_list*	new_node;

	new_node = NULL;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		terminate(MALLOC, previous);
	new_node->args = NULL;
	new_node->nb_args = 0;
	new_node->flag = PARSING;
	new_node->previous = previous;
	if (previous)
		previous->next = new_node;
	new_node->next = NULL;
	return (new_node);
}

void	add_arg(t_list** list, char* arg) {
	char**	new_matrix;
	int		new_size;
	int		i;

	if (!*list || (*list)->flag != PARSING)
		*list = create_new_node(*list);
	new_size = (*list)->nb_args + 1 + NULL_CHAR;
	new_matrix = NULL;
	new_matrix = malloc(new_size * sizeof(char*));
	if (!new_matrix)
		terminate(MALLOC, *list);
	i = -1;
	while (++i < (*list)->nb_args)
		new_matrix[i] = (*list)->args[i];
	new_matrix[i++] = arg;
	new_matrix[i] = NULL;
	free((*list)->args);
	(*list)->args = new_matrix;
	(*list)->nb_args++;
}

void	parse_arg(t_list** list, char* arg) {
	if (!*list && is_break(arg))
		return ;
	if (!*list && !is_break(arg))
		*list = create_new_node(NULL);
	if (is_break(arg))
		(*list)->flag = BREAK;
	else if (is_pipe(arg))
		(*list)->flag = PIPE;
	else
		add_arg(list, arg);
}

//==============================================================================
//	EXECUTOR
//==============================================================================

int	exec_cd(t_list* list) {
	int ret;

	ret = 0;
	if (list->nb_args != 2)
		ret = print_error("error: cd: bad arguments\n");
	else if (chdir(list->args[1])) {
		ret = print_error("error: cd: cannot change directory to ");
		print_error(list->args[1]);
		print_error("\n");
	}
	//no need to change the env?
	return (ret);
}


/*
 * 1) If this command is of type PIPE, then this child process's STD_OUT fd
 * should be replaced with the write_end of the pipe set between the
 * next command and this one. Note that here there's no need to save a
 * copy of the original STD_IN, because this replacement is done inside
 * the child process, where we won't be needing it (remember file
 * descriptors are unique to each process).
 *
 * 2) If the previous command was of type PIPE, then this child process's
 * STD_IN fd should be replaced with the read_end of the pipe set
 * between the previous command and this one (hence, the read end of the pipe of
 * the PREVIOUS command). Note that here the PREVIOUS is paramount!
 * */

int	exec_cmd(t_list* list, char** env) {
	bool	pipe_open = false;
	int		ret = 1;
	pid_t	pid;
	int		status;

	if (list->flag == PIPE || (list->previous && list->previous->flag == PIPE)) {
		pipe_open = true;
		if (pipe(list->pipe_ends))
			return (-1);
	}
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0) {
		if (list->flag == PIPE)								// 1
			if (dup2(list->pipe_ends[1], STDOUT_FILENO) < 0)
				return (-1);
		if (list->previous && list->previous->flag == PIPE)	// 2
			if (dup2(list->previous->pipe_ends[0], STDIN_FILENO) < 0)
				return (-1);
		if (execve(list->args[0], list->args, env))
			print_error("error: cannot execute that command\n");
		exit (-1);
	}
	else {
		waitpid(pid, &status, 0);
		/* If there's an open pipe, then we can close the write_end of it (we
		 * won't write anything else to it. Also, if this is the last command,
		 * no one will read from the read_end either, so we can close it too.
		 * The same reasoning allows us to close the read_end of the previous
		 * command (note that pipe_open might be false in this case!) */
		if (pipe_open) {
			close(list->pipe_ends[1]);
			if (!list->next || list->flag == PARSING)
				close(list->pipe_ends[0]);
		}
		if (list->previous && list->previous->flag == PIPE)
			close(list->previous->pipe_ends[0]);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
	}
	return (ret);
}

int	execute_input(t_list* list, char** env) {
	int ret;

	ret = 0;
	while (list) {
		if (strcmp(list->args[0], "cd") == 0)
			ret = exec_cd(list);
		else
			ret = exec_cmd(list, env);
		if (!list->next)
			break ;
		list = list->next;
	}
	return (ret);
}

//==============================================================================
//	MAIN
//==============================================================================

int main(int argc, char** argv, char** env) {
	t_list*	list;
	int		ret;

	if (argc == 1)
		return (EXIT_SUCCESS);
	list = NULL;
	ret = 0;
	for (int i = 1; i < argc; i++)
		parse_arg(&list, argv[i]);
	list_rewind(&list);
	if (list)
		ret = execute_input(list, env);
	terminate(ret, list);
	return (ret);
}
