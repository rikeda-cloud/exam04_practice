#ifndef MICROSHELL
# define MICROSHELL

#define ERR_CD "error: cd: cannot change directory to "
#define ERR_CD_BAD "error: cd: bad arguments"
#define ERR_EXECVE_FRONT "error: cannot execute "
#define ERR_FATAL "error: fatal"

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef enum e_type
{
	WORD,
	SEMI,
	PIPE,
}	t_type;

enum
{
	READ = 0,
	WRITE = 1,
};

typedef struct s_word_list
{
	char				*word;
	struct s_word_list	*next;
}	t_word_list;

typedef struct s_list
{
	t_word_list		*word_list;
	struct s_list	*next;
	pid_t			pid;
	t_type			type;
}	t_list;

t_list		*create_list(int argc, char **argv);

void		exec_cmd_line(t_list *list);
void		exec_cmd(t_list *cmd_line);
char		**change_word_list_to_cmd(t_word_list *word_list);

void		cd(t_word_list *word_list);

void		wait_cmd(t_list *cmd_line);

/* new */
t_word_list	*new_word_list(char *str);
t_list		*new_list(char *str, t_type type);

/* utils */
size_t		ft_strlen(const char *str);
void		ft_putstr(const char *str);
void		ft_putendl(const char *str);
void		err_print(const char *str1, const char *str2);
void		err_fatal();
void		*free_list(t_list *list);

extern char **environ;

/* debug */
void	print_list(t_list *list);
#include <stdio.h>

#endif
