#ifndef EXAM04_MAIN_H
#define EXAM04_MAIN_H

#define NULL_CHAR 1

typedef enum e_errors {
	MALLOC = -1
}	t_errors;

typedef enum e_flags {
	PIPE,
	BREAK
}	t_flags;

typedef struct s_list {
	char**			args;
	int				nb_args;
	int				flag;
//	int				pipes[2];
	struct s_list*	previous;
	struct s_list*	next;
}	t_list
;

void	terminate(int exit_code, t_list* list);

#endif