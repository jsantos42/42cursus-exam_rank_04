#ifndef EXAM04_MAIN_H
#define EXAM04_MAIN_H

#define NULL_CHAR 1

typedef struct s_list {
	char**			args;
	struct s_list*	previous;
	struct s_list*	next;
}	t_list;

typedef struct s_cmds {
	char*	input;
	t_list*	list;
}	t_cmds;

#endif