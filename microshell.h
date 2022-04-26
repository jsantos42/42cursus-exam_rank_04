#ifndef EXAM04_MICROSHELL_H
#define EXAM04_MICROSHELL_H

#define NULL_CHAR 1

typedef enum e_flags {
	PARSING,
	PIPE,
	BREAK
}	t_flags;

typedef struct s_list {
	char**			args;
	int				nb_args;
	int				flag;
	int				pipe_ends[2];
	struct s_list*	previous;
	struct s_list*	next;
}	t_list
;

void	terminate(int exit_code, t_list* list);

#endif