#include "microshell.h"

static t_list	*get_next_cmd_line_and_dis_connect(t_list *list)
{
	t_list	*next_cmd_line;

	if (!list->next)
		return (NULL);
	while (list->next && list->next->type != SEMI)
		list = list->next;
	if (!list->next)
		return (NULL);
	next_cmd_line = list->next->next;
	list->next = NULL;
	return (next_cmd_line);
}

void	exec_cmd(t_list *cmd_line)
{
	int	prev_fd = STDIN_FILENO;

	if (!cmd_line->next && strcmp(cmd_line->word_list->word, "cd") == 0)
		cd(cmd_line->word_list);
	while (cmd_line->next)
	{
		prev_fd = exec_normal(cmd_line, prev_fd);
		cmd_line = cmd_line->next->next;
	}
	exec_last(cmd_line, prev_fd);
}

void	wait_cmd(t_list *cmd_line)
{
	if (!cmd_line->next && strcmp(cmd_line->word_list->word, "cd") == 0)
		return ;
	while (cmd_line)
	{
		waitpid(cmd_line->pid, NULL, 0);
		if (cmd_line->next)
			cmd_line = cmd_line->next->next;
		else
			cmd_line = NULL;
	}
}

void	exec_cmd_line(t_list *list)
{
	t_list	*cmd_line;

	while (list)
	{
		cmd_line = list;
		list = get_next_cmd_line_and_dis_connect(list);
		exec_cmd(cmd_line);
		wait_cmd(cmd_line);
	}
}
