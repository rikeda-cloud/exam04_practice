#include "microshell.h"

static t_list	*get_next_cmd_line_and_dis_connect(t_list *list)
{
	t_list	*next_cmd_line;
	t_list	*tmp;

	if (!list->next)
		return (NULL);
	while (list->next && list->next->type != SEMI)
		list = list->next;
	if (!list->next)
		return (NULL);
	next_cmd_line = list->next->next;
	tmp = list->next;
	tmp->next = NULL;
	list->next = free_list(tmp);
	return (next_cmd_line);
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
		free_list(cmd_line);
	}
}
