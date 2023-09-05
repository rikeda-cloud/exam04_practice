#ifndef MICROSHELL
# define MICROSHELL

#define ERR_CD "error: cd: cannot "
#define ERR_CD_BAD "error: cd: bad arguments"
#define ERR_EXECVE_FRONT "error: cannot "
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
	int				fd;
	pid_t			pid;
	t_type			type;
}	t_list;

t_list	*create_list(int argc, char **argv);
void	exec_cmd_line(t_list *list);
void	cd(t_word_list *word_list);
int		exec_normal(t_list *list, int prev_fd);
void	exec_last(t_list *list, int prev_fd);
char	**change_word_list_to_char(t_word_list *word_list);

/* utils */
size_t	ft_strlen(const char *str);
void	ft_putstr(const char *str);
void	ft_putendl(const char *str);
void	err_print(const char *str1, const char *str2);
void	err_fatal();

extern char **environ;

/* debug */
void	print_list(t_list *list);
#include <stdio.h>

#endif
