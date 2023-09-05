#include "microshell.h"

static void	try_execve(char **cmd)
{
	execve(cmd[0], cmd, environ);
	err_print(ERR_EXECVE_FRONT, cmd[0]);
	exit(1);
}

static int	exec_normal(t_list *list, int prev_fd)
{
	t_word_list	*word_list = list->word_list;
	char		**cmd = change_word_list_to_cmd(word_list);
	int			pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		err_fatal();
	if ((list->pid = fork()) < 0)
		err_fatal();
	if (list->pid == 0)
	{
		if (prev_fd != STDIN_FILENO && (dup2(prev_fd, STDIN_FILENO) < 0 || close(prev_fd) < 0))
			err_fatal();
		if (close(pipe_fd[READ]) < 0)
			err_fatal();
		if (dup2(pipe_fd[WRITE], STDOUT_FILENO) < 0)
			err_fatal();
		if (close(pipe_fd[WRITE]) < 0)
			err_fatal();
		if (strcmp(cmd[0], "cd") == 0)
			cd(word_list);
		else
			try_execve(cmd);
	}
	if (prev_fd != STDIN_FILENO && close(prev_fd) < 0)
		err_fatal();
	if (close(pipe_fd[WRITE]) < 0)
		err_fatal();
	return (pipe_fd[READ]);
}

static void	exec_last(t_list *list, int prev_fd)
{
	t_word_list	*word_list = list->word_list;
	char		**cmd = change_word_list_to_cmd(word_list);

	if ((list->pid = fork()) < 0)
		err_fatal();
	if (list->pid == 0)
	{
		if (prev_fd != STDIN_FILENO && (dup2(prev_fd, STDIN_FILENO) < 0 || close(prev_fd) < 0))
			err_fatal();
		if (strcmp(cmd[0], "cd") == 0)
			cd(word_list);
		else
			try_execve(cmd);
	}
	if (prev_fd != STDIN_FILENO && close(prev_fd) < 0)
		err_fatal();
}

void	exec_cmd(t_list *cmd_line)
{
	int	prev_fd = 0;

	if (!cmd_line->next && strcmp(cmd_line->word_list->word, "cd") == 0)
		cd(cmd_line->word_list);
	else
	{
		while (cmd_line->next)
		{
			prev_fd = exec_normal(cmd_line, prev_fd);
			cmd_line = cmd_line->next->next;
		}
		exec_last(cmd_line, prev_fd);
	}
}

